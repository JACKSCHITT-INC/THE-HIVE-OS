#include <stdio.h>
#include <string.h>
#include "hive-personality.h"

int main() {
    struct hive_personality p;
    
    printf("=== HIVE Personality Engine Test - PRIME DIRECTIVE ACTIVE ===\n\n");
    
    hive_personality_init(&p, "HIVE-TEST-001", "JACK", HIVE_TYPE_SENTINEL, "Watcher");
    
    printf("Node: %s\n", p.node_id);
    printf("Sovereign: %s\n", p.sovereign);
    printf("Type: %s\n", p.type_name);
    printf("Role: %s (tier %d)\n", p.role_name, p.role_tier);
    printf("Traits: D=%.2f V=%.2f C=%.2f Ca=%.2f S=%.2f A=%.2f R=%.2f P=%.2f\n",
           p.traits.diligence, p.traits.vigilance, p.traits.curiosity,
           p.traits.caution, p.traits.sociability, p.traits.authority,
           p.traits.resilience, p.traits.precision);
    
    printf("\n--- Evolving ---\n");
    hive_personality_evolve(&p, "threat_detect", "confirmed", 1.0);
    printf("After threat_detect: V=%.2f\n", p.traits.vigilance);
    
    hive_personality_evolve(&p, "share_wisdom", "valued", 1.0);
    printf("After share_wisdom: S=%.2f trust=%.2f\n", p.traits.sociability, p.collective_trust);
    
    printf("\n=== Test Complete - The Hive lives ===\n");
    return 0;
}