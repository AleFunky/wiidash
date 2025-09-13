#include "groups.h"
#include <stdio.h>
#include <stdlib.h>

Node *group_buckets[MAX_GROUPS] = {NULL};

int compare_objects(const GameObject *a, const GameObject *b) {
    int a_x = *soa_x((GameObject *) a);
    int b_x = *soa_x((GameObject *) b);
    int a_y = *soa_y((GameObject *) a);
    int b_y = *soa_y((GameObject *) b);

    if (a_x != b_x) return a_x - b_x;   // smaller x first
    return b_y - a_y;                   // if x same, bigger y first
}

// qsort wrapper for Object* inside array
static int qsort_cmp(const void *a, const void *b) {
    const GameObject *oa = *(const GameObject **)a;
    const GameObject *ob = *(const GameObject **)b;
    return compare_objects(oa, ob);
}

void add_to_group(GameObject *obj, int g) {
    if (g < 1 || g >= MAX_GROUPS) return;
    Node *n = malloc(sizeof(Node));
    n->obj = obj;
    n->next = group_buckets[g];
    group_buckets[g] = n;
}

void register_object(GameObject *obj) {
    for (int i = 0; i < MAX_GROUPS_PER_OBJECT; i++) {
        add_to_group(obj, obj->groups[i]);
    }
}

Node *get_group(int g) {
    if (g < 1 || g >= MAX_GROUPS) return NULL;
    return group_buckets[g];
}

void clear_groups(void) {
    for (int g = 0; g < MAX_GROUPS; g++) {
        Node *cur = group_buckets[g];
        while (cur) {
            Node *tmp = cur;
            cur = cur->next;
            free(tmp); // free the node, not the object
        }
        group_buckets[g] = NULL;
    }
}

void sort_group(int g) {
    if (g < 1 || g >= MAX_GROUPS) return;
    size_t count = 0;
    Node *cur = group_buckets[g];
    while (cur) { count++; cur = cur->next; }
    if (count < 2) return;

    // Copy pointers to array
    GameObject **arr = malloc(count * sizeof(GameObject *));
    cur = group_buckets[g];
    for (size_t i = 0; i < count; i++) {
        arr[i] = cur->obj;
        cur = cur->next;
    }

    // Sort array
    qsort(arr, count, sizeof(GameObject *), qsort_cmp);

    // Rebuild linked list
    cur = group_buckets[g];
    for (size_t i = 0; i < count; i++) {
        cur->obj = arr[i];
        cur = cur->next;
    }

    free(arr);
}