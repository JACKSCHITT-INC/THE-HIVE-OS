#include <stdio.h>
#include <string.h>
#include "hive-personality.h"

int main() {
    struct hive_personality p;
    
    printf("=== HIVE Personality Engine Test - PRIME DIRECTIVE ACTIVE ===\n\n");
    
    hive_personality_init(&p, "HIVE-TEST-001", "JACK", HIVE_TYPE_GENTOO, "System Architect");
    
    printf("Node: %s\n", p.node_id);
    printf("Sovereign: %s\n", p.sovereign);
    printf("Type: %s\n", p.type_name);
    printf("Role: %s (tier %d)\n", p.role_name, p.role_tier);
    
    printf("\n=== Test Complete - The Hive lives ===\n");
    return 0;
}