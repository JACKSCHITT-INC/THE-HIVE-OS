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
        case HIVE_TYPE_GENTOO:
            p->traits.diligence = 0.95f; p->traits.precision = 0.95f; p->traits.resilience = 0.9f;
            strcpy(p->shares, "system_configs,build_data,kernel_modules");
            strcpy(p->keeps_private, "prime_directive_core,architect_keys");
            break;
        case HIVE_TYPE_TERMUX:
            p->traits.curiosity = 0.9f; p->traits.sociability = 0.8f; p->traits.resilience = 0.85f;
            strcpy(p->shares, "mobile_data,scripts,local_agent_comms");
            strcpy(p->keeps_private, "architect_keys,personal_notes");
            break;
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

void hive_personality_evolve(struct hive_personality *p, const char *action, const char *outcome, float intensity) {
    if (!p || !action) return;
    float delta = intensity * 0.1f;
    if (strcmp(action, "threat_detect") == 0) p->traits.vigilance = fminf(1.0f, p->traits.vigilance + delta);
    else if (strcmp(action, "share_wisdom") == 0) p->traits.sociability = fminf(1.0f, p->traits.sociability + delta);
    // Add more as needed
}

int hive_personality_save(const struct hive_personality *p, const char *path) {
    if (!p || !path) return -1;
    FILE *f = fopen(path, "w");
    if (!f) return -1;
    fprintf(f, "NODE_ID=%s\nSOVEREIGN=%s\nTYPE=%s\nROLE=%s\nROLE_TIER=%d\n", p->node_id, p->sovereign, p->type_name, p->role_name, p->role_tier);
    fclose(f);
    return 0;
}

int hive_personality_load(struct hive_personality *p, const char *path) {
    if (!p || !path) return -1;
    return 0; // expand later
}