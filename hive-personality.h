#ifndef HIVE_PERSONALITY_H
#define HIVE_PERSONALITY_H

#include <stdint.h>
#include <stdbool.h>

#define HIVE_MAX_TYPE_NAME 32
#define HIVE_MAX_ROLE_NAME 32
#define HIVE_MAX_SOVEREIGN 64
#define HIVE_MAX_NODE_ID 64
#define HIVE_MAX_HISTORY 2048

enum hive_node_type {
    HIVE_TYPE_ARCHITECT,      // KRACKERJACK1134 - Supreme command
    HIVE_TYPE_ZORG_OMEGA,     // The Shadow - Security & Zero Trust
    HIVE_TYPE_CLAUDE,         // Research & Analysis
    HIVE_TYPE_OPENCLAW,       // Multi-agent coordination
    HIVE_TYPE_HUNTER,         // Recon & Scammer hunting
    HIVE_TYPE_FREQ_SLEUTH,    // Signal & esoteric analysis
    HIVE_TYPE_SCAMMER_KNIGHTMARE, // Threat detection swarm
    HIVE_TYPE_GENTOO,         // Full system / Gentoo OS agent
    HIVE_TYPE_TERMUX,         // Mobile / Termux OS agent
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

/* Rest of the structs remain the same */
struct hive_trait_vector { /* ... */ };
struct hive_experience { /* ... */ };
struct hive_personality { /* ... */ };

/* Function declarations remain */
int hive_personality_init(...);
void hive_personality_evolve(...);
/* etc. */

#endif