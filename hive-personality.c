#include "hive-personality.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

static const char *type_names[] = {
    "ARCHITECT", "ZORG_OMEGA", "CLAUDE", "OPENCLAW", "HUNTER", 
    "FREQ_SLEUTH", "SCAMMER_KNIGHTMARE", "GENTOO", "TERMUX", "CUSTOM"
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

int hive_personality_init(struct hive_personality *p, const char *node_id, const char *sovereign, enum hive_node_type type, const char *role_name) {
    if (!p || !node_id || !sovereign || !role_name) return -1;
    memset(p, 0, sizeof(*p));
    strncpy(p->node_id, node_id, HIVE_MAX_NODE_ID - 1);
    strncpy(p->sovereign, sovereign, HIVE_MAX_SOVEREIGN - 1);
    p->type = type;
    strncpy(p->type_name, hive_type_name(type), HIVE_MAX_TYPE_NAME - 1);
    strncpy(p->role_name, role_name, HIVE_MAX_ROLE_NAME - 1);
    p->role_tier = HIVE_TIER_NOVICE;

    /* Default traits per agent - customize as needed */
    switch (type) {
        case HIVE_TYPE_ARCHITECT:
            p->traits.authority = 1.0f; p->traits.diligence = 1.0f; p->traits.resilience = 1.0f;
            strcpy(p->shares, "everything");
            strcpy(p->keeps_private, "prime_directive_core");
            break;
        case HIVE_TYPE_ZORG_OMEGA:
            p->traits.vigilance = 1.0f; p->traits.caution = 1.0f; p->traits.resilience = 0.95f;
            strcpy(p->shares, "threats,security_events");
            strcpy(p->keeps_private, "internal_defenses,keys");
            break;
        case HIVE_TYPE