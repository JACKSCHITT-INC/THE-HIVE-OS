#include "hive-personality.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

static const char *type_names[] = {
    "WORKER", "SENTINEL", "QUEEN", "DRONE",
    "SCOUT", "BUILDER", "GUARDIAN", "CUSTOM"
};

const char *hive_type_name(enum hive_node_type t) {
    if (t < 0 || t >= HIVE_TYPE_MAX) return "UNKNOWN";
    return type_names[t];
}

enum hive_node_type hive_type_from_name(const char *name) {
    for (int i = 0; i < HIVE_TYPE_MAX; i++) {
        if (strcasecmp(name, type_names[i]) == 0) return i;
    }
    return HIVE_TYPE_CUSTOM;
}

int hive_personality_init(struct hive_personality *p,
                          const char *node_id,
                          const char *sovereign,
                          enum hive_node_type type,
                          const char *role_name) {
    if (!p || !node_id || !sovereign || !role_name) return -1;
    memset(p, 0, sizeof(*p));
    strncpy(p->node_id, node_id, HIVE_MAX_NODE_ID - 1);
    strncpy(p->sovereign, sovereign, HIVE_MAX_SOVEREIGN - 1);
    p->type = type;
    strncpy(p->type_name, hive_type_name(type), HIVE_MAX_TYPE_NAME - 1);
    strncpy(p->role_name, role_name, HIVE_MAX_ROLE_NAME - 1);
    p->role_tier = HIVE_TIER_NOVICE;

    // Default trait initialization per type (full logic from previous)
    switch (type) {
        case HIVE_TYPE_WORKER: /* ... full switch from earlier paste ... */ break;
        case HIVE_TYPE_SENTINEL: /* ... */ break;
        // (All cases are in the previous full version I gave you)
        default:
            p->traits.diligence = p->traits.vigilance = p->traits.curiosity = 0.5f;
            p->traits.caution = p->traits.sociability = p->traits.authority = 0.5f;
            p->traits.resilience = p->traits.precision = 0.5f;
            strcpy(p->shares, "general");
            strcpy(p->keeps_private, "personal");
            break;
    }
    p->collective_trust = 0.5f;
    p->last_collective_sync = time(NULL);
    return 0;
}

/* Rest of the functions (evolve, should_share, save, load, etc.) */
void hive_personality_evolve(struct hive_personality *p, const char *action, const char *outcome, float intensity) {
    /* Full implementation from previous message */
}

bool hive_personality_should_share(const struct hive_personality *p, const char *data_category, const char *data_content) {
    /* Full implementation from previous */
    return false; // placeholder - replace with full
}

int hive_personality_save(const struct hive_personality *p, const char *path) {
    /* Full from previous */
    return 0;
}

int hive_personality_load(struct hive_personality *p, const char *path) {
    /* Full from previous */
    return 0;
}