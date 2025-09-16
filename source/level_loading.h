#pragma once

#include "math.h"

#define MAX_GROUPS_PER_OBJECT 20

#define MAX_OBJECT_LAYERS 4

typedef struct Section Section;
typedef struct GFXSection GFXSection;
typedef struct GDLayerSortable GDLayerSortable;

typedef enum {
    GD_VAL_INT,
    GD_VAL_FLOAT,
    GD_VAL_BOOL,
    GD_VAL_HSV,
    GD_VAL_INT_ARRAY,
    GD_VAL_UNKNOWN
} GDValueType;

typedef union {
    int i;
    float f;
    bool b;
    short int_array[MAX_GROUPS_PER_OBJECT]; // For groups
    HSV hsv;
} GDValue;

typedef struct {
    u8 trig_colorR;      // key 7
    u8 trig_colorG;      // key 8
    u8 trig_colorB;      // key 9
    float opacity;       // key 35

    u8 tintGround:1;     // key 14
    u8 p1_color:1;       // key 15
    u8 p2_color:1;       // key 16
    u8 blending:1;       // key 17
    
    int target_color_id; // key 23
    HSV copied_hsv;      // key 49
    int copied_color_id; // key 50
} ColTrigger;

typedef struct {
    Color color;           // keys 7, 8 and 9

    int target_color_id;   // key 23

    float fade_in;         // key 45
    float hold;            // key 46
    float fade_out;        // key 47
    int pulse_mode;        // key 48
    
    HSV copied_hsv;        // key 49
    int copied_color_id;   // key 50
    int target_group;      // key 51
    int pulse_target_type; // key 52

    bool main_only;        // key 65
    bool detail_only;      // key 66
} PulseTrigger;

typedef struct {
    float opacity;       // key 35
    int target_group;    // key 51
} AlphaTrigger;

typedef struct {
    int target_group;       // key 51
    bool activate_group;    // key 56
} ToggleTrigger;

typedef struct {
    int target_group;     // key 51
    float spawn_delay;    // key 63
} SpawnTrigger;

typedef struct {
    int offsetX;           // key 28
    int offsetY;           // key 29
    int easing;            // key 30
    int target_group;      // key 51
    u8 lock_to_player_x:1; // key 58
    u8 lock_to_player_y:1; // key 59
} MoveTrigger;

typedef struct {
    float trig_duration; // key 10
    u8 touch_triggered;  // key 11
    u8 spawn_triggered;  // key 62
    
    union {
        ColTrigger col_trigger;
        MoveTrigger move_trigger;
        PulseTrigger pulse_trigger;
        AlphaTrigger alpha_trigger;
        ToggleTrigger toggle_trigger;
        SpawnTrigger spawn_trigger;
    };
} Trigger;

typedef struct GameObject GameObject;

typedef struct {
    int u1p9_col_channel; // key 19
    int main_col_channel;   // key 21
    int detail_col_channel; // key 22

    int zsheetlayer;     // no key has this, but used internally
    int zlayer;          // key 24
    int zorder;          // key 25

    float scale_x;         // key 32 and 128
    float scale_y;         // key 32 and 129

    bool main_col_HSV_enabled;
    bool detail_col_HSV_enabled;
    HSV main_col_HSV;
    HSV detail_col_HSV;

    Color main_color;
    Color detail_color;

    bool main_being_pulsed;
    Color main_col_pulse;
    bool detail_being_pulsed;
    Color detail_col_pulse;

    float delta_x;
    float delta_y;

    float orange_tp_portal_y_offset; // key 54
    GameObject *child_object;

    float animation_timer;

    unsigned char touching_player;
    unsigned char prev_touching_player;
    unsigned char touching_side;
    // Slope
    unsigned char orientation;

    unsigned char num_pulses;
    
} NormalObject;

typedef enum {
    TYPE_NORMAL_OBJECT,
    TYPE_COL_TRIGGER,
    TYPE_MOVE_TRIGGER,
    TYPE_PULSE_TRIGGER,
    TYPE_ALPHA_TRIGGER,
    TYPE_TOGGLE_TRIGGER,
    TYPE_SPAWN_TRIGGER,
} ObjectType;

typedef struct GameObjectSoA {
    float *x;
    float *y;
    float *delta_x;
    float *delta_y;
    unsigned char *touching_player;
    unsigned char *prev_touching_player;
} GameObjectSoA;

typedef struct GameObject {
    int id;              // key 1

    int soa_index;

    ObjectType type;     // Defines the type

    float x;             // key 2
    float y;             // key 3
    bool flippedH;       // key 4
    bool flippedV;       // key 5
    float rotation;      // key 6
    short groups[MAX_GROUPS_PER_OBJECT]; // key 57
    
    float opacity;

    bool has_two_channels;
    bool both_channels_blending;
    
    union {
        NormalObject object;
        Trigger trigger;
    };

    int random;                     // random number assigned to this object
    bool activated[2];              // if it has been activated
    unsigned int hitbox_counter[2]; // number of times the player has entered the hitbox
    bool collided[2];               // if the object just started being touched
    float ampl_scaling;             // the amplitude scaling for pulsing objects
    u8 transition_applied;          // the transition applied to the object
    bool toggled;                   // toggle trigger status
    bool hide_sprite;
    float width;
    float height;

    Section *cur_section;
    int section_index;   // index in section->objects[]

    bool dirty;

    int layer_count;
    GDLayerSortable *layers[MAX_OBJECT_LAYERS];
} GameObject;

#pragma pack(push, 1)
typedef struct {
    GDValue values[15];
    unsigned char keys[15];
    unsigned char types[15];
    unsigned char propCount;
} GDObject;
#pragma pack(pop)

typedef struct {
    GDObject *objects;
    int objectCount;
} GDObjectList;

typedef struct {
    int count;
    GameObject **objects;
} GDGameObjectList;

typedef struct {
    GameObject *obj;
    int originalIndex;
} GDObjectSortable;

typedef struct {
    GameObject *obj;
    struct ObjectLayer *layer;
    int col_channel;
    bool blending;
    int layerNum;
} GDObjectLayer;

typedef struct GDLayerSortable {
    GDObjectLayer *layer;
    int zlayer;
    int originalIndex;
    int layerNum;

    GFXSection *cur_section;
    int section_index;
} GDLayerSortable;

typedef struct {
    int count;
    GDObjectLayer **layers;
} GDObjectLayerList;

typedef struct {
    int fromRed;
    int fromGreen;
    int fromBlue;
    int playerColor;
    bool blending;
    int channelID;
    float fromOpacity;
    bool toggleOpacity;
    int inheritedChannelID;
    HSV hsv;
    int toRed;
    int toGreen;
    int toBlue;
    float deltaTime;
    float toOpacity;
    float duration;
    bool copyOpacity;
} GDColorChannel;

struct LoadedLevelInfo {
    float last_obj_x;
    float wall_x;
    float wall_y;

    int object_count;
    int layer_count;

    int pulsing_type;
    int song_id;
    int custom_song_id;
    float song_offset;
    bool completing;
    int background_id;
    int ground_id;
    int initial_gamemode;
    bool initial_mini;
    unsigned char initial_speed;
    bool initial_dual;
    bool initial_upsidedown;
    bool level_is_empty;
    bool level_is_custom;
};

#define BG_COUNT 7
#define G_COUNT 7

#define SECTION_HASH_SIZE 600

#define SECTION_SIZE 128
#define GFX_SECTION_SIZE 128

typedef struct Section {
    GameObject **objects;
    int object_count;
    int object_capacity;

    int x, y; // Section coordinates
    struct Section *next; // For chaining in hash map
} Section;

typedef struct GFXSection {
    GDLayerSortable **layers;
    int layer_count;
    int layer_capacity;

    int x, y; // Section coordinates
    struct GFXSection *next; // For chaining in hash map
} GFXSection;

bool init_object_soa(int count, GameObjectSoA *soa);

extern Section *section_hash[SECTION_HASH_SIZE];
extern GFXSection *section_gfx_hash[SECTION_HASH_SIZE];
unsigned int section_hash_func(int x, int y);
Section *get_or_create_section(int x, int y);
GFXSection *get_or_create_gfx_section(int x, int y);
void free_sections(void);
void free_gfx_sections(void);
void update_object_section(GameObject *obj, float new_x, float new_y);

char *get_level_name(char *data_ptr);
char *get_author_name(char *data_ptr);
int compare_sortable_layers(const void *a, const void *b);

extern struct LoadedLevelInfo level_info;

struct ObjectPos {
    float x;
    float y;
};

extern GDGameObjectList *objectsArrayList;
extern struct ObjectPos *origPositionsList;
extern GDObjectLayerList *layersArrayList;

extern GDLayerSortable gfx_player_layer;
extern GameObject *player_game_object;

GameObject* add_object(int object_id, float x, float y, float rotation);

void free_game_object_list(GDGameObjectList *list);
void free_game_object_array(GameObject **array, int count);
int load_level(char *data, bool is_custom);
void unload_level();
void reload_level();
void reset_color_channels();
void set_color_channels();
void calculate_lbg();

int get_main_channel_id(int id);
int get_detail_channel_id(int id);

char *extract_gmd_key(const char *data, const char *key, const char *type);

char *load_song(const char *file_name, size_t *out_size);
char *load_user_song(int id, size_t *out_size);

bool check_song(int id);
void update_percentage();

extern GameObjectSoA *gameObjectSoA;

inline float* soa_x(GameObject *obj) { return &gameObjectSoA->x[obj->soa_index]; }
inline float* soa_y(GameObject *obj) { return &gameObjectSoA->y[obj->soa_index]; }
inline float* soa_delta_x(GameObject *obj) { return &gameObjectSoA->delta_x[obj->soa_index]; }
inline float* soa_delta_y(GameObject *obj) { return &gameObjectSoA->delta_y[obj->soa_index]; }