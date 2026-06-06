#ifndef HIVE_PERSONALITY_H
#define HIVE_PERSONALITY_H

#include <stdint.h>
#include <stdbool.h>

#define HIVE_MAX_TYPE_NAME 16
#define HIVE_MAX_ROLE_NAME 16
#define HIVE_MAX_SOVEREIGN 32
#define HIVE_MAX_NODE_ID 64
#define HIVE_MAX_HISTORY 1024
#define HIVE_MAX_WISDOM 4096
#define HIVE_MAX_SHARES 512
#define HIVE_MAX_KEEPS 512
#define HIVE_MAX_CERT 256
#define HIVE_MAX_SIGNATURE 256

enum hive_node_type {
    HIVE_TYPE_WORKER = 0,
    HIVE_TYPE_SENTINEL,
    HIVE_TYPE_QUEEN,
    HIVE_TYPE_DRONE,
    HIVE_TYPE_SCOUT,
    HIVE_TYPE_BUILDER,
    HIVE_TYPE_GUARDIAN,
    HIVE_TYPE_CUSTOM,
    HIVE_TYPE_MAX
};

enum hive_role_tier {
    HIVE_TIER_NOVICE = 0,
    HIVE_TIER_ADEPT,
    HIVE_TIER_EXPERT,
    HIVE_TIER_MASTER,
    HIVE_TIER_LEGEND
};

struct hive_trait_vector {
    float diligence;
    float vigilance;
    float curiosity;
    float caution;
    float sociability;
    float authority;
    float resilience;
    float precision;
};

struct hive_experience {
    uint64_t tasks_completed;
    uint64_t tasks_failed;
    uint64_t threats_detected;
    uint64_t updates_shared;
    uint64_t updates_received;
    uint64_t peers_known;
    uint64_t collective_contributions;
    uint64_t wisdom_shared;
    uint64_t wisdom_received;
};

struct hive_personality {
    char node_id[HIVE_MAX_NODE_ID];
    char sovereign[HIVE_MAX_SOVEREIGN];
    char birth_cert[HIVE_MAX_CERT];
    char birth_signature[HIVE_MAX_SIGNATURE];
    enum hive_node_type type;
    char type_name[HIVE_MAX_TYPE_NAME];
    enum hive_role_tier role_tier;
    char role_name[HIVE_MAX_ROLE_NAME];
    char role_history[HIVE_MAX_HISTORY];
    struct hive_trait_vector traits;
    struct hive_experience exp;
    char shares[HIVE_MAX_SHARES];
    char keeps_private[HIVE_MAX_KEEPS];
    char local_wisdom[HIVE_MAX_WISDOM];
    float collective_trust;
    uint64_t last_collective_sync;
};

int hive_personality_init(struct hive_personality *p,
                          const char *node_id,
                          const char *sovereign,
                          enum hive_node_type type,
                          const char *role_name);
void hive_personality_evolve(struct hive_personality *p,
                              const char *action,
                              const char *outcome,
                              float intensity);
bool hive_personality_should_share(const struct hive_personality *p,
                                    const char *data_category,
                                    const char *data_content);
bool hive_personality_should_receive(const struct hive_personality *p,
                                      const char *sender_type,
                                      const char *data_category);
char *hive_personality_prepare_share(const struct hive_personality *p,
                                      const char *raw_data,
                                      const char *category,
                                      bool *anonymize);
int hive_personality_save(const struct hive_personality *p, const char *path);
int hive_personality_load(struct hive_personality *p, const char *path);
const char *hive_type_name(enum hive_node_type t);
enum hive_node_type hive_type_from_name(const char *name);

#endif