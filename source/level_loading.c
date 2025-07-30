#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "objects.h"
#include "level_loading.h"

#include "main.h"
#include "math.h"

#include "level.h"
#include "player.h"
#include "filesystem.h"

#include "../libraries/color.h"

struct LoadedLevelInfo level_info;

Section *section_hash[SECTION_HASH_SIZE] = {0};
GFXSection *section_gfx_hash[SECTION_HASH_SIZE] = {0};

GDLayerSortable gfx_player_layer;

GDLayerSortable *sortable_list;

unsigned int section_hash_func(int x, int y) {
    return ((unsigned int)x * 73856093u ^ (unsigned int)y * 19349663u) % SECTION_HASH_SIZE;
}

Section *get_or_create_section(int x, int y) {
    unsigned int h = section_hash_func(x, y);
    Section *sec = section_hash[h];
    while (sec) {
        if (sec->x == x && sec->y == y) return sec;
        sec = sec->next;
    }
    sec = malloc(sizeof(Section));
    sec->objects = malloc(sizeof(GameObject*) * 8);
    sec->object_count = 0;
    sec->object_capacity = 8;
    sec->x = x;
    sec->y = y;
    sec->next = section_hash[h];
    section_hash[h] = sec;
    return sec;
}

GFXSection *get_or_create_gfx_section(int x, int y) {
    unsigned int h = section_hash_func(x, y);
    GFXSection *sec = section_gfx_hash[h];
    while (sec) {
        if (sec->x == x && sec->y == y) return sec;
        sec = sec->next;
    }
    sec = malloc(sizeof(GFXSection));
    sec->layers = malloc(sizeof(GDLayerSortable*) * 8);
    sec->layer_count = 0;
    sec->layer_capacity = 8;
    sec->x = x;
    sec->y = y;
    sec->next = section_gfx_hash[h];
    section_gfx_hash[h] = sec;
    return sec;
}

void free_sections(void) {
    for (int i = 0; i < SECTION_HASH_SIZE; i++) {
        Section *sec = section_hash[i];
        while (sec) {
            Section *next = sec->next;
            free(sec->objects);
            free(sec);
            sec = next;
        }
        section_hash[i] = NULL;
        GFXSection *sec2 = section_gfx_hash[i];
        while (sec2) {
            GFXSection *next = sec2->next;
            free(sec2->layers);
            free(sec2);
            sec2 = next;
        }
        section_gfx_hash[i] = NULL;
    }
}

void assign_object_to_section(GameObject *obj) {
    int sx = (int)(obj->x / SECTION_SIZE);
    int sy = (int)(obj->y / SECTION_SIZE);
    Section *sec = get_or_create_section(sx, sy);
    if (sec->object_count >= sec->object_capacity) {
        sec->object_capacity *= 2;
        sec->objects = realloc(sec->objects, sizeof(GameObject*) * sec->object_capacity);
    }
    sec->objects[sec->object_count++] = obj;
}


void assign_layer_to_section(GDLayerSortable *layer) {
    int sx = (int)(layer->layer->obj->x / GFX_SECTION_SIZE);
    int sy = (int)(layer->layer->obj->y / GFX_SECTION_SIZE);
    GFXSection *sec = get_or_create_gfx_section(sx, sy);
    if (sec->layer_count >= sec->layer_capacity) {
        sec->layer_capacity *= 2;
        sec->layers = realloc(sec->layers, sizeof(GDLayerSortable*) * sec->layer_capacity);
    }
    sec->layers[sec->layer_count++] = layer;
}


char *extract_gmd_key(const char *data, const char *key, const char *type) {
    char key_tag[32];
    snprintf(key_tag, sizeof(key_tag), "<k>%s</k>", key);
    
    char *key_pos = strstr(data, key_tag);
    if (!key_pos) {
        printf("Could not find key tag '%s'\n", key_tag);
        return NULL;
    }

    // Move past the key tag
    char *start = key_pos + strlen(key_tag);

    // Skip whitespace (spaces, tabs, newlines, etc.)
    while (*start && isspace((unsigned char)*start)) {
        start++;
    }

    char type_start_tag[16];
    snprintf(type_start_tag, sizeof(type_start_tag), "<%s>", type);

    // Confirm that the type start tag is here
    if (strncmp(start, type_start_tag, strlen(type_start_tag)) != 0) {
        printf("Expected start tag '%s' not found after key\n", type_start_tag);
        return NULL;
    }

    // Move past the type start tag
    start += strlen(type_start_tag);

    // Find the end tag
    char type_end_tag[16];
    snprintf(type_end_tag, sizeof(type_end_tag), "</%s>", type);
    char *end = strstr(start, type_end_tag);
    if (!end) {
        printf("Could not find end tag '%s'\n", type_end_tag);
        return NULL;
    }

    // Allocate and copy value
    int len = end - start;
    char *value = malloc(len + 1);
    if (!value) {
        printf("malloc for gmd key %s failed\n", key);
        return NULL;
    }
    strncpy(value, start, len);
    value[len] = '\0';
    return value;
}

int b64_char(char c) {
    if ('A' <= c && c <= 'Z') return c - 'A';
    if ('a' <= c && c <= 'z') return c - 'a' + 26;
    if ('0' <= c && c <= '9') return c - '0' + 52;
    if (c == '+') return 62;
    if (c == '/') return 63;
    return -1;
}

void fix_base64_url(char *b64) {
    for (int i = 0; b64[i]; i++) {
        if (b64[i] == '-') b64[i] = '+';
        else if (b64[i] == '_') b64[i] = '/';
    }
}

int base64_decode(const char *in, unsigned char *out) {
    int len = 0;
    for (int i = 0; in[i] && in[i+1] && in[i+2] && in[i+3]; i += 4) {
        int a = b64_char(in[i]);
        int b = b64_char(in[i+1]);
        int c = in[i+2] == '=' ? 0 : b64_char(in[i+2]);
        int d = in[i+3] == '=' ? 0 : b64_char(in[i+3]);

        if (a == -1 || b == -1 || c == -1 || d == -1) {
            printf("Invalid base64 character at position %d\n", i);
            return -1;
        }

        out[len++] = (a << 2) | (b >> 4);
        if (in[i+2] != '=') out[len++] = (b << 4) | (c >> 2);
        if (in[i+3] != '=') out[len++] = (c << 6) | d;
    }
    printf("Decoded %d bytes from base64\n", len);
    return len;
}

uLongf get_gzip_uncompressed_size(unsigned char *data, int data_len) {
    if (data_len < 4) return 0;

    // GZIP footer stores original size in last 4 bytes, little-endian
    uint32_t size = data[data_len - 4]
                  | (data[data_len - 3] << 8)
                  | (data[data_len - 2] << 16)
                  | (data[data_len - 1] << 24);
    return (uLongf)size;
}


char *decompress_data(unsigned char *data, int data_len, uLongf *out_len) {
    printf("Decompressing with zlib inflate in GZIP mode...\n");

    z_stream strm = {0};
    strm.next_in = data;
    strm.avail_in = data_len;

    if (inflateInit2(&strm, 15 | 32) != Z_OK) {  // 16 + MAX_WBITS enables gzip decoding
        printf("Failed to initialize zlib stream for GZIP\n");
        return NULL;
    }

    // Allocate output buffer with some room; grow if needed
    size_t buffer_size = 8192;
    char *out = malloc(buffer_size);
    if (!out) {
        printf("malloc failed\n");
        inflateEnd(&strm);
        return NULL;
    }

    while (1) {
        if (strm.total_out >= buffer_size) {
            buffer_size *= 2;
            out = realloc(out, buffer_size);
            if (!out) {
                printf("realloc failed\n");
                inflateEnd(&strm);
                return NULL;
            }
        }

        strm.next_out = (Bytef *)(out + strm.total_out);
        strm.avail_out = buffer_size - strm.total_out;

        int ret = inflate(&strm, Z_NO_FLUSH);
        if (ret == Z_STREAM_END) break;
        if (ret != Z_OK) {
            printf("inflate failed with code %d\n", ret);
            free(out);
            inflateEnd(&strm);
            return NULL;
        }
    }

    *out_len = strm.total_out;
    inflateEnd(&strm);

    // Final shrink to fit
    out = realloc(out, *out_len + 1); // +1 for null terminator
    out[*out_len] = '\0';

    printf("Decompressed %lu bytes successfully\n", *out_len);
    return out;
}

char *get_metadata_value(const char *levelString, const char *key) {
    if (!levelString || !key) return NULL;

    // Find the first semicolon, which separates metadata from objects
    const char *end = strchr(levelString, ';');
    if (!end) return NULL;

    // We'll scan only the metadata portion
    size_t metadataLen = end - levelString;
    char *metadata = malloc(metadataLen + 1);
    if (!metadata) return NULL;

    strncpy(metadata, levelString, metadataLen);
    metadata[metadataLen] = '\0';

    // Tokenize metadata by comma
    char *token = strtok(metadata, ",");
    while (token) {
        if (strcmp(token, key) == 0) {
            char *value = strtok(NULL, ",");  // get value after key
            if (!value) break;

            // Copy and return value
            char *result = strdup(value);
            free(metadata);
            return result;
        }
        token = strtok(NULL, ",");
    }
    
    free(metadata);
    return NULL;
}

char *decompress_level(char *data) {
    printf("Loading level data...\n");

    char *b64 = extract_gmd_key((const char *) data, "k4", "s");
    if (!b64) {
        printf("Could not extract base64 data\n");
        return NULL;
    }

    fix_base64_url(b64);

    unsigned char *decoded = malloc(strlen(b64));
    int decoded_len = base64_decode(b64, decoded);
    if (decoded_len <= 0) {
        printf("Failed to decode base64\n");
        free(b64);
        free(decoded);
        return NULL;
    }

    uLongf decompressed_len;
    char *decompressed = decompress_data(decoded, decoded_len, &decompressed_len);
    if (!decompressed) {
        printf("Decompression failed (check zlib error above)\n");
        free(decoded);
        free(b64);
        return NULL;
    }

    free(decoded);
    free(b64);
    
    return decompressed;
}

// I don't even know what this does
char **split_string(const char *str, char delimiter, int *outCount) {
    char **result = NULL;
    int count = 0;
    const char *start = str;
    const char *ptr = str;

    while (*ptr) {
        if (*ptr == delimiter) {
            int len = ptr - start;
            if (len > 0) {
                char *token = (char *)malloc(len + 1);
                strncpy(token, start, len);
                token[len] = '\0';

                result = (char **)realloc(result, sizeof(char*) * (count + 1));
                result[count++] = token;
            }
            start = ptr + 1;
        }
        ptr++;
    }
    if (ptr > start) {
        int len = ptr - start;
        char *token = (char *)malloc(len + 1);
        strncpy(token, start, len);
        token[len] = '\0';
        result = (char **)realloc(result, sizeof(char*) * (count + 1));
        result[count++] = token;
    }

    *outCount = count;
    return result;
}

void free_string_array(char **arr, int count) {
    for (int i = 0; i < count; i++) free(arr[i]);
    free(arr);
}

void parse_color_channel(GDColorChannel *channels, int i, char *channel_string) {
    GDColorChannel channel = {0};  // Zero-initialize
    int kvCount = 0;
    char **kvs = split_string(channel_string, '_', &kvCount);

    for (int j = 0; j + 1 < kvCount; j += 2) {
        int key = atoi(kvs[j]);
        const char *valStr = kvs[j + 1];

        switch (key) {
            case 1:  channel.fromRed = atoi(valStr); break;
            case 2:  channel.fromGreen = atoi(valStr); break;
            case 3:  channel.fromBlue = atoi(valStr); break;
            case 4:  channel.playerColor = atoi(valStr); break;
            case 5:  channel.blending = atoi(valStr) != 0; break;
            case 6:  channel.channelID = atoi(valStr); break;
            case 7:  channel.fromOpacity = atof(valStr); break;
            case 8:  channel.toggleOpacity = atoi(valStr) != 0; break;
            case 9:  channel.inheritedChannelID = atoi(valStr); break;
            case 10: channel.hsv = atoi(valStr); break;
            case 11: channel.toRed = atoi(valStr); break;
            case 12: channel.toGreen = atoi(valStr); break;
            case 13: channel.toBlue = atoi(valStr); break;
            case 14: channel.deltaTime = atof(valStr); break;
            case 15: channel.toOpacity = atof(valStr); break;
            case 16: channel.duration = atof(valStr); break;
            case 17: channel.copyOpacity = atoi(valStr) != 0; break;
        }
    }

    channels[i] = channel;
    free_string_array(kvs, kvCount);
}


int parse_color_channels(const char *colorString, GDColorChannel **outArray) {
    if (!colorString || !outArray) return 0;

    int count = 0;
    char **entries = split_string(colorString, '|', &count);
    if (!entries) return 0;

    GDColorChannel *channels = malloc(sizeof(GDColorChannel) * count);
    if (!channels) {
        printf("Couldn't alloc color channels\n");
        free_string_array(entries, count);
        return 0;
    }

    for (int i = 0; i < count; i++) {
        parse_color_channel(channels, i, entries[i]);
    }

    *outArray = channels;
    free_string_array(entries, count);
    return count;
}

GDValueType get_value_type_for_key(int key) {
    switch (key) {
        case 1:  return GD_VAL_INT;    // Object ID
        case 2:  return GD_VAL_FLOAT;  // X Position
        case 3:  return GD_VAL_FLOAT;  // Y Position
        case 4:  return GD_VAL_BOOL;   // Flipped Horizontally
        case 5:  return GD_VAL_BOOL;   // Flipped Vertically
        case 6:  return GD_VAL_FLOAT;  // Rotation
        case 7:  return GD_VAL_INT;    // (Trigger) Red
        case 8:  return GD_VAL_INT;    // (Trigger) Green
        case 9:  return GD_VAL_INT;    // (Trigger) Blue
        case 10: return GD_VAL_FLOAT;  // (Trigger) Duration
        case 11: return GD_VAL_BOOL;   // (Trigger) Touch Triggered
        case 14: return GD_VAL_BOOL;   // (Trigger) Tint ground
        case 23: return GD_VAL_INT;    // (Trigger) Target color ID
        case 24: return GD_VAL_INT;    // Zlayer
        case 25: return GD_VAL_INT;    // Zorder
        default:
            return GD_VAL_INT; // Default fallback
    }
}


// Parse bool from string ("1" = true, else false)
bool parse_bool(const char *str) {
    return (str[0] == '1' && str[1] == '\0');
}

__unused void print_prop(int key, GDValueType type, GDValue value) {
    printf("  Key %d, type %d, value = ", key, type);
    switch (type) {
        case GD_VAL_INT:
            printf("%d\n", value.i);
            break;
        case GD_VAL_FLOAT:
            printf("%f\n", value.f);
            break;
        case GD_VAL_BOOL:
            printf("%s\n", value.b ? "true" : "false");
            break;
        default:
            printf("Unknown type\n");
            break;
    }
}

int parse_gd_object(const char *objStr, GDObject *obj) {
    int count = 0;
    char **tokens = split_string(objStr, ',', &count);
    if (count < 1) {
        free_string_array(tokens, count);
        return 0;
    }

    obj->propCount = 0;

    for (int i = 0; i + 1 < count && obj->propCount < 20; i += 2) {
        int key = atoi(tokens[i]);
        const char *valStr = tokens[i + 1];
        GDValueType type = get_value_type_for_key(key);

        obj->keys[obj->propCount] = key;
        obj->types[obj->propCount] = type;

        switch (type) {
            case GD_VAL_INT:
                obj->values[obj->propCount].i = atoi(valStr);
                break;
            case GD_VAL_FLOAT:
                obj->values[obj->propCount].f = atof(valStr);
                break;
            case GD_VAL_BOOL:
                obj->values[obj->propCount].b = parse_bool(valStr);
                break;
            default:
                obj->values[obj->propCount].i = atoi(valStr);
                break;
        }

        obj->propCount++;
    }

    free_string_array(tokens, count);
    return 1;
}

GameObject *convert_to_typed(const GDObject *obj) {
    GameObject *typed = malloc(sizeof(GameObject));
    if (!typed) return NULL;

    // Initialize all fields to default values:
    memset(typed, 0, sizeof(GameObject));

    typed->id = obj->values[0].i;
    // Temporarily convert user coins (added in 2.0) into secret coins
    if (typed->id == 1329) typed->id = SECRET_COIN;

    typed->x = obj->values[1].f;
    typed->y = obj->values[2].f;

    typed->zsheetlayer = objects[typed->id].spritesheet_layer;
    typed->zlayer = objects[typed->id].def_zlayer;
    typed->zorder = objects[typed->id].def_zorder;

    typed->random = rand();

    if (typed->x > level_info.last_obj_x) {
        level_info.last_obj_x = typed->x;
    }

    for (int i = 2; i < obj->propCount; i++) {
        int key = obj->keys[i];
        GDValueType type = obj->types[i];
        GDValue val = obj->values[i];

        switch (key) {
            case 4:  // FlippedH
                if (type == GD_VAL_BOOL) typed->flippedH = val.b;
                break;
            case 5:  // FlippedV
                if (type == GD_VAL_BOOL) typed->flippedV = val.b;
                break;
            case 6:  // Rotation
                if (type == GD_VAL_FLOAT) typed->rotation = val.f;
                break;
            case 7:  // Color R
                if (type == GD_VAL_INT) typed->trig_colorR = val.i;
                break;
            case 8:  // Color G
                if (type == GD_VAL_INT) typed->trig_colorG = val.i;
                break;
            case 9:  // Color B
                if (type == GD_VAL_INT) typed->trig_colorB = val.i;
                break;
            case 10: // Duration
                if (type == GD_VAL_FLOAT) typed->trig_duration = val.f;
                break;
            case 11: // Touch Triggered
                if (type == GD_VAL_BOOL) typed->touchTriggered = val.b;
                break;
            case 14: // Tint Ground
                if (type == GD_VAL_BOOL) typed->tintGround = val.b;
                break;
            case 23: // Target color ID
                if (type == GD_VAL_INT) typed->target_color_id = val.i;
                break;
            case 24: // Z layer
                if (type == GD_VAL_INT) typed->zlayer = val.i;
                break;
            case 25: // Z order
                if (type == GD_VAL_INT) typed->zorder = val.i;
                break;

            // Add more keys here as needed

            default:
                // Unknown keys ignored here
                break;
        }
    }

    return typed;
}

void free_typed_object(GameObject *obj) {
    if (!obj) return;
    //if (obj->text) free(obj->text);
    free(obj);
}

GDTypedObjectList *convert_all_to_typed(GDObjectList *objList) {
    if (!objList) return NULL;

    GameObject **typedArray = malloc(sizeof(GameObject *) * objList->objectCount);
    if (!typedArray) return NULL;

    printf("Converting objects...\n");

    for (int i = 0; i < objList->objectCount; i++) {
        typedArray[i] = convert_to_typed(&objList->objects[i]);
        assign_object_to_section(typedArray[i]);
        if (!typedArray[i]) {
            printf("Failed to convert object %d\n", i);
            for (int j = 0; j < i; j++) {
                free_typed_object(typedArray[j]);
            }
            free(typedArray);
            return NULL;
        }
    }

    printf("Allocating list...\n");

    GDTypedObjectList *typedList = malloc(sizeof(GDTypedObjectList));
    if (!typedList) {
        printf("Failed to allocate the typed list");
        for (int i = 0; i < objList->objectCount; i++) {
            free_typed_object(typedArray[i]);
        }
        free(typedArray);
        return NULL;
    }

    typedList->count = objList->objectCount;
    typedList->objects = typedArray;

    return typedList;
}

void free_gd_object_list(GDObjectList *list) {
    free(list->objects);
    free(list);
}

GDObjectList *parse_string(const char *levelString) {
    int sectionCount = 0;
    char **sections = split_string(levelString, ';', &sectionCount);

    if (sectionCount < 3) {
        printf("Level string missing sections!\n");
        free_string_array(sections, sectionCount);
        return NULL;
    }
    
    printf("Parsing string...\n");

    int objectCount = sectionCount - 1;
    printf("%d\n", objectCount);
    
    GDObject *objects = (GDObject *)malloc(sizeof(GDObject) * objectCount);

    printf("Size of gdobjects %d bytes\n", sizeof(GDObject) * objectCount);
    if (objects == NULL) {
        printf("Couldn't allocate GD Objects\n");
        return NULL;
    }

    for (int i = 1; i < sectionCount; i++) {
        if (!parse_gd_object(sections[i], &objects[i - 1])) {
            printf("Failed to parse object at section %d\n", i);
        }
    }

    free_string_array(sections, sectionCount);
    
    printf("Allocating object list...\n");

    GDObjectList *objectList = malloc(sizeof(GDObjectList));
    if (!objectList) {
        printf("Memory allocation failed for objectList\n");
        free(objects);
        return NULL;
    }

    objectList->objectCount = objectCount;
    objectList->objects = objects;

    return objectList;
}

void free_typed_object_list(GDTypedObjectList *list) {
    if (!list) return;

    for (int i = 0; i < list->count; i++) {
        free_typed_object(list->objects[i]);
    }
    free(list->objects);
    free(list);
}

int compare_sortable_layers(const void *a, const void *b) {
    GDLayerSortable *layerSortA = *(GDLayerSortable **)a;
    GDLayerSortable *layerSortB = *(GDLayerSortable **)b;

    struct ObjectLayer *layerA = layerSortA->layer->layer;
    struct ObjectLayer *layerB = layerSortB->layer->layer;

    GameObject *objA = layerSortA->layer->obj;
    GameObject *objB = layerSortB->layer->obj;

    int zlayerA = objA->zlayer + layerA->zlayer_offset;
    int zlayerB = objB->zlayer + layerB->zlayer_offset;

    if (zlayerA != zlayerB)
        return zlayerA - zlayerB; // Ascending

    int obj_idA = objA->id;
    int obj_idB = objB->id;

    int sheetA = objects[obj_idA].spritesheet_layer;
    int sheetB = objects[obj_idB].spritesheet_layer;

    if (sheetA != sheetB)
        return sheetB - sheetA; // Descending

    int zorderA = objA->zorder;
    int zorderB = objB->zorder;

    if (zorderA != zorderB)
        return zorderA - zorderB; // Ascending

    return layerSortA->originalIndex - layerSortB->originalIndex; // Stable fallback
}

// Me when this is like Java (using Comparable interface)
void sort_layers_by_layer(GDObjectLayerList *list) {
    if (!list || list->count <= 1) return;

    printf("Sorting layer list\n");
    
    // Wrap objects with indices
    sortable_list = malloc(sizeof(GDLayerSortable) * list->count);

    if (sortable_list == NULL) {
        printf("Couldn't allocate sortable layer\n");
        return;
    }
    
    for (int i = 0; i < list->count; i++) {
        
        sortable_list[i].layer = list->layers[i];
        sortable_list[i].originalIndex = i;
        sortable_list[i].layerNum = list->layers[i]->layerNum;
        
        // GD epicness
        if (sortable_list[i].layer->obj->id != PLAYER_OBJECT) {
            GameObject *obj = sortable_list[i].layer->obj;
            int zlayer = obj->zlayer;
            int col_channel = sortable_list[i].layer->layer->col_channel;
            if (objects[obj->id].num_layers == 1) {
                bool blending = channels[col_channel].blending;
                if (blending ^ (zlayer % 2 == 0)) {
                    obj->zlayer--;
                }
            }
        }

        assign_layer_to_section(&sortable_list[i]);
    }
}

void free_typed_object_array(GameObject **array, int count) {
    if (!array) return;
    for (int i = 0; i < count; i++) {
        free_typed_object(array[i]);
    }
    free(array); // Free the array of pointers itself
}

GDObjectLayerList *fill_layers_array(GDTypedObjectList *objList) {
    // Count layers
    int layerCount = 0;
    for (int i = 0; i < objList->count; i++) {
        GameObject *obj = objList->objects[i];

        int obj_id = obj->id;

        if (obj_id < OBJECT_COUNT)
            layerCount += objects[obj->id].num_layers;
    }

    printf("Allocating %d bytes for %d layers\n", sizeof(GDObjectLayer) * layerCount, layerCount);
    GDObjectLayer *layers = malloc(sizeof(GDObjectLayer) * layerCount);

    if (layers == NULL) {
        printf("Couldn't allocate layers\n");
        return NULL;
    }

    // Put player
    GameObject *obj = malloc(sizeof(GameObject));
    obj->id = PLAYER_OBJECT;
    obj->zlayer = LAYER_T1-1;
    obj->zorder = 0;
    obj->zsheetlayer = 0;
    GDObjectLayer *layer = malloc(sizeof(GDObjectLayer));
    layer->obj = obj;
    layer->layer = (struct ObjectLayer *) &objects[obj->id].layers[0];
    layer->layerNum = 0;
    GDLayerSortable sortable_layer;
    sortable_layer.layer = layer;
    sortable_layer.originalIndex = 0;

    gfx_player_layer = sortable_layer;

    printf("Allocated %d layers\n", layerCount);

    // Fill array
    int count = 0;
    for (int i = 0; i < objList->count; i++) {
        GameObject *obj = objList->objects[i];

        int obj_id = obj->id;

        if (obj_id < OBJECT_COUNT)
            for (int j = 0; j < objects[obj->id].num_layers; j++) {
                layers[count].layer = (struct ObjectLayer *) &objects[obj->id].layers[j];
                layers[count].obj = obj;
                layers[count].layerNum = j;
                count++;
            }
    }
    
    printf("Finished filling %d layers\n", count);

    printf("Allocating layer list\n");
    GDObjectLayerList *layerList = malloc(sizeof(GDObjectLayerList));
    
    if (layerList == NULL) {
        printf("Couldn't allocate layer list\n");
        free(obj);
        free(layers);
        return NULL;
    }

    // Allocate array of pointers to GDObjectLayer
    layerList->layers = malloc(sizeof(GDObjectLayer *) * count);

    if (layerList->layers == NULL) {
        printf("Couldn't allocate layer pointers\n");
        free(layers);
        free(layerList);
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        layerList->layers[i] = &layers[i];
    }

    layerList->count = count;

    return layerList;
}

void free_layer_list(GDObjectLayerList *list) {
    if (!list) return;
    if (list->layers) {
        // No need to free each layer as it has been allocated as the layer list
        free(list->layers);
    }
    free(list);
}

int parse_old_channels(char *level_string, GDColorChannel **outArray) {
    GDColorChannel *channels = malloc(sizeof(GDColorChannel) * 2);
    if (!channels) {
        printf("Couldn't alloc initial pre 2.0 color channels\n");
        return 0;
    }

    char *v19_bg = get_metadata_value(level_string, "kS29");

    int i = 0;

    if (v19_bg) { // 1.9 only
        parse_color_channel(channels, i, v19_bg);
        channels[i].channelID = BG;
        i++;

        parse_color_channel(channels, i, get_metadata_value(level_string, "kS30"));
        channels[i].channelID = GROUND;
        i++;

        char *line = get_metadata_value(level_string, "kS31");
        if (line) {
            channels = realloc(channels, sizeof(GDColorChannel) * (i + 1));
            parse_color_channel(channels, i, line);
            channels[i].channelID = LINE;
            i++;
        }
        
        char *obj = get_metadata_value(level_string, "kS32");
        if (obj) {
            channels = realloc(channels, sizeof(GDColorChannel) * (i + 1));
            parse_color_channel(channels, i, obj);
            channels[i].channelID = OBJ;
            i++;
        }

        char *col1 = get_metadata_value(level_string, "kS33");
        if (col1) {
            channels = realloc(channels, sizeof(GDColorChannel) * (i + 1));
            parse_color_channel(channels, i, col1);
            channels[i].channelID = 1;
            i++;
        }

        char *col2 = get_metadata_value(level_string, "kS34");
        if (col2) {
            channels = realloc(channels, sizeof(GDColorChannel) * (i + 1));
            parse_color_channel(channels, i, col2);
            channels[i].channelID = 2;
            i++;
        }

        char *col3 = get_metadata_value(level_string, "kS35");
        if (col3) {
            channels = realloc(channels, sizeof(GDColorChannel) * (i + 1));
            parse_color_channel(channels, i, col3);
            channels[i].channelID = 3;
            i++;
        }

        char *col4 = get_metadata_value(level_string, "kS36");
        if (col4) {
            channels = realloc(channels, sizeof(GDColorChannel) * (i + 1));
            parse_color_channel(channels, i, col4);
            channels[i].channelID = 4;
            i++;
        }

        char *dl3 = get_metadata_value(level_string, "kS37");
        if (dl3) {
            channels = realloc(channels, sizeof(GDColorChannel) * (i + 1));
            parse_color_channel(channels, i, dl3);
            channels[i].channelID = THREEDL;
            i++;
        }
        
        *outArray = channels;
        return i;
    }

    // Pre 1.9
    int bg_r = atoi(get_metadata_value(level_string, "kS1"));
    int bg_g = atoi(get_metadata_value(level_string, "kS2"));
    int bg_b = atoi(get_metadata_value(level_string, "kS3"));

    GDColorChannel bg_channel = {0};
    bg_channel.channelID = BG;
    bg_channel.fromRed = bg_r;
    bg_channel.fromGreen = bg_g;
    bg_channel.fromBlue = bg_b;

    char *bg_player_color = get_metadata_value(level_string, "kS16");
    if (bg_player_color) {
       bg_channel.playerColor = atoi(bg_player_color);
    }

    channels[i] = bg_channel;

    i++;

    int g_r = atoi(get_metadata_value(level_string, "kS4"));
    int g_g = atoi(get_metadata_value(level_string, "kS5"));
    int g_b = atoi(get_metadata_value(level_string, "kS6"));

    GDColorChannel g_channel = {0};
    g_channel.channelID = GROUND;
    g_channel.fromRed = g_r;
    g_channel.fromGreen = g_g;
    g_channel.fromBlue = g_b;

    char *g_player_color = get_metadata_value(level_string, "kS17");
    if (g_player_color) {
        g_channel.playerColor = atoi(g_player_color);
    }
    
    channels[i] = g_channel;
    i++;

    char *line_r = get_metadata_value(level_string, "kS7");
    char *line_g = get_metadata_value(level_string, "kS8");
    char *line_b = get_metadata_value(level_string, "kS9");

    if (line_r && line_g && line_b) {
        GDColorChannel line_channel = {0};
        line_channel.channelID = LINE;
        line_channel.fromRed = atoi(line_r);
        line_channel.fromGreen = atoi(line_g);
        line_channel.fromBlue = atoi(line_b);
        
        char *line_player_color = get_metadata_value(level_string, "kS18");
        if (line_player_color) {
            line_channel.playerColor = atoi(line_player_color);
        }

        channels = realloc(channels, sizeof(GDColorChannel) * (i + 1));
        channels[i] = line_channel;
        i++;
    }

    char *obj_r = get_metadata_value(level_string, "kS10");
    char *obj_g = get_metadata_value(level_string, "kS11");
    char *obj_b = get_metadata_value(level_string, "kS12");

    if (obj_r && obj_g && obj_b) {
        GDColorChannel obj_channel = {0};
        obj_channel.channelID = OBJ;
        obj_channel.fromRed = atoi(obj_r);
        obj_channel.fromGreen = atoi(obj_g);
        obj_channel.fromBlue = atoi(obj_b);

        char *obj_player_color = get_metadata_value(level_string, "kS19");
        if (obj_player_color) {
            obj_channel.playerColor = atoi(obj_player_color);
        }
        
        channels = realloc(channels, sizeof(GDColorChannel) * (i + 1));
        channels[i] = obj_channel;
        i++;
    }

    char *obj_2_r = get_metadata_value(level_string, "kS13");
    char *obj_2_g = get_metadata_value(level_string, "kS14");
    char *obj_2_b = get_metadata_value(level_string, "kS15");

    if (obj_2_r && obj_2_g && obj_2_b) {
        GDColorChannel obj_2_channel = {0};
        obj_2_channel.channelID = OBJ;
        obj_2_channel.fromRed = atoi(obj_2_r);
        obj_2_channel.fromGreen = atoi(obj_2_g);
        obj_2_channel.fromBlue = atoi(obj_2_b);
        
        char *obj_2_player_color = get_metadata_value(level_string, "kS20");
        if (obj_2_player_color) {
            obj_2_channel.playerColor = atoi(obj_2_player_color);
        }
        
        channels = realloc(channels, sizeof(GDColorChannel) * (i + 1));
        channels[i] = obj_2_channel;
        i++;
    }

    *outArray = channels;

    return i;
}

GDTypedObjectList *objectsArrayList = NULL;
GDObjectLayerList *layersArrayList = NULL;
int channelCount = 0;
GDColorChannel *colorChannels = NULL;

void load_level(char *data) {
    char *level_string = decompress_level(data);

    if (level_string == NULL) {
        printf("Failed decompressing the level.\n");
        return;
    }

    level_info.last_obj_x = 545.f;

    // Get colors
    char *metaStr = get_metadata_value(level_string, "kS38");
    channelCount = parse_color_channels(metaStr, &colorChannels);

    char *gmd_song_id = extract_gmd_key((const char *) data, "k8", "i");
    if (!gmd_song_id) {
        level_info.song_id = 0;
    } else {
        level_info.song_id = atoi(gmd_song_id); // Official song id
    }

    // Fallback to pre 2.0 keys
    if (!channelCount) {
        channelCount = parse_old_channels(level_string, &colorChannels);
    }

    GDObjectList *objectsList = parse_string(level_string);

    free(level_string);

    if (objectsList == NULL) {
        printf("Failed parsing the objects.\n");
        return;
    }

    objectsArrayList = convert_all_to_typed(objectsList);
    free_gd_object_list(objectsList);

    if (objectsArrayList == NULL) {
        printf("Failed converting objects to typed structs.\n");
        return;
    }

    layersArrayList = fill_layers_array(objectsArrayList);

    if (layersArrayList == NULL) {
        printf("Couldn't sort layers\n");
        free_typed_object_list(objectsArrayList);
        return;
    }

    sort_layers_by_layer(layersArrayList);
    
    reset_color_channels();
    set_color_channels();
    memset(trigger_buffer, 0, sizeof(trigger_buffer));

    level_info.pulsing_type = random_int(0,2);

    int rounded_last_obj_x = (int) (level_info.last_obj_x / 30) * 30 + 15;
    level_info.wall_x = (rounded_last_obj_x) + (9.f * 30.f);

    printf("Finished loading level\n");
}

void unload_level() {
    free_layer_list(layersArrayList);
    free(sortable_list);
    sortable_list = NULL;
    layersArrayList = NULL;
    free_typed_object_list(objectsArrayList);
    objectsArrayList = NULL;
    if (colorChannels) {
        free(colorChannels);
        colorChannels = NULL;
    }
    channelCount = 0;
    memset(&state.particles, 0, sizeof(state.particles));
    free_sections();
    full_init_variables();
}

void reset_color_channels() {
    for (s32 i = 0; i < 999; i++) {
        channels[i].color.r = 255;
        channels[i].color.g = 255;
        channels[i].color.b = 255;
        channels[i].blending = FALSE;
    }

    channels[BG].color.r = 56;
    channels[BG].color.g = 121;
    channels[BG].color.b = 255;
    channels[BG].blending = FALSE;
    
    channels[GROUND].color.r = 56;
    channels[GROUND].color.g = 121;
    channels[GROUND].color.b = 255;
    channels[GROUND].blending = FALSE;

    channels[LINE].color.r = 255;
    channels[LINE].color.g = 255;
    channels[LINE].color.b = 255;
    channels[LINE].blending = TRUE;

    channels[OBJ].color.r = 255;
    channels[OBJ].color.g = 255;
    channels[OBJ].color.b = 255;
    channels[OBJ].blending = FALSE;

    channels[OBJ_BLENDING].copy_color_id = OBJ;
    channels[OBJ_BLENDING].blending = TRUE;

    channels[P1].color = p1;
    channels[P1].blending = TRUE;
    channels[P2].color = p2;
    channels[P2].blending = TRUE;
    
    channels[BLACK].color.r = 0;
    channels[BLACK].color.g = 0;
    channels[BLACK].color.b = 0;
    channels[BLACK].blending = FALSE;

    channels[WHITE].color.r = 255;
    channels[WHITE].color.g = 255;
    channels[WHITE].color.b = 255;
    channels[WHITE].blending = FALSE;
}

void set_color_channels() {
    for (int i = 0; i < channelCount; i++) {
        GDColorChannel colorChannel = colorChannels[i];
        int id = colorChannel.channelID;

        switch (id) {
            case P1:
            case P2:
            case BLACK:
            case WHITE:
                break;

            default:
                channels[id].color.r = colorChannel.fromRed;
                channels[id].color.g = colorChannel.fromGreen;
                channels[id].color.b = colorChannel.fromBlue;
                channels[id].blending = colorChannel.blending;
        }
    }
}

char *get_level_name(char *data_ptr) {
    return extract_gmd_key((const char *) data_ptr, "k2", "s");
}

void reload_level() {
    memset(trigger_buffer, 0, sizeof(trigger_buffer));
    memset(&state.particles, 0, sizeof(state.particles));
    for (int i = 0; i < objectsArrayList->count; i++) {
        GameObject *obj = objectsArrayList->objects[i];
        obj->activated = FALSE;
        obj->toggled = FALSE;
        obj->collided = FALSE;
        obj->hitbox_counter = 0;
        obj->transition_applied = FADE_NONE;
    }
    reset_color_channels();
    set_color_channels();
}

// https://github.com/gd-programming/gd.docs/issues/87
void calculate_lbg() {
    struct ColorChannel channel = channels[BG];
    float h,s,v;
    
    convertRGBtoHSV(channel.color.r, channel.color.g, channel.color.b, &h, &s, &v);

    s -= 0.20f;
    s = clampf(s, 0.f, 1.f);
    v += 0.20f;
    v = clampf(v, 0.f, 1.f);

    unsigned char r,g,b;

    convertHSVtoRGB(h, s, v, &r, &g, &b);

    // Set here no lerping LBG
    channels[LBG_NO_LERP].color.r = r;
    channels[LBG_NO_LERP].color.g = g;
    channels[LBG_NO_LERP].color.b = b;
    channels[LBG_NO_LERP].blending = TRUE;

    float factor = (channel.color.r + channel.color.g + channel.color.b) / 150.f;

    if (factor < 1.f) {
        r = r * factor + p1.r * (1 - factor);
        g = g * factor + p1.g * (1 - factor);
        b = b * factor + p1.b * (1 - factor);
    }

    // Set here lerped LBG
    channels[LBG].color.r = r;
    channels[LBG].color.g = g;
    channels[LBG].color.b = b;
    channels[LBG].blending = TRUE;
}


char *load_song(const char *file_name, size_t *out_size) {
    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/%s/%s/%s", launch_dir, RESOURCES_FOLDER, SONGS_FOLDER, file_name);
    return read_file(full_path, out_size);
}
