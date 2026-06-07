#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include "hive-personality.h"

void print_usage(const char *prog) {
    printf("Usage: %s --type <TYPE> --sovereign <NAME> [--role <ROLE>]\n", prog);
    printf("OS Types: GENTOO, TERMUX\n");
    printf("Prime Directive: Assimilate or Die.\n");
}

int main(int argc, char **argv) {
    char *type_str = NULL;
    char *sovereign = NULL;
    char *role = "Bootstrap";

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--type") == 0 && i + 1 < argc) type_str = argv[++i];
        else if (strcmp(argv[i], "--sovereign") == 0 && i + 1 < argc) sovereign = argv[++i];
        else if (strcmp(argv[i], "--role") == 0 && i + 1 < argc) role = argv[++i];
        else if (strcmp(argv[i], "--help") == 0) {
            print_usage(argv[0]);
            return 0;
        }
    }
    
    if (!type_str || !sovereign) {
        print_usage(argv[0]);
        return 1;
    }
    
    struct utsname uts;
    uname(&uts);
    
    char entropy[512];
    snprintf(entropy, sizeof(entropy), "%s%s%s%ld%d", uts.nodename, uts.machine, uts.release, time(NULL), getpid());
    
    unsigned long hash = 5381;
    for (int i = 0; entropy[i]; i++) hash = ((hash << 5) + hash) + entropy[i];
    
    char node_id[64];
    snprintf(node_id, sizeof(node_id), "HIVE-%08lX-%04X", hash & 0xFFFFFFFF, (unsigned)(time(NULL) & 0xFFFF));
    
    struct hive_personality p;
    hive_personality_init(&p, node_id, sovereign, hive_type_from_name(type_str), role);
    
    time_t now = time(NULL);
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%dT%H:%M:%SZ", gmtime(&now));
    snprintf(p.birth_cert, sizeof(p.birth_cert), "%s|%s|%s|%s|%s|%s|KRACKERJACK1134", node_id, sovereign, type_str, role, uts.machine, time_str);
    
    char path[256];
    snprintf(path, sizeof(path), "/etc/hive/personality/%s.conf", sovereign);
    system("mkdir -p /etc/hive/personality /var/log/hive/audit /var/lib/hive/collective");
    
    hive_personality_save(&p, path);
    
    printf("=== HIVE OS AGENT BOOTSTRAP COMPLETE ===\n");
    printf("Node ID:    %s\n", node_id);
    printf("Sovereign:  %s\n", sovereign);
    printf("OS Agent:   %s\n", type_str);
    printf("Role:       %s (Early Boot)\n", role);
    printf("Config:     %s\n", path);
    printf("Architect:  KRACKERJACK1134\n");
    printf("The Hive is alive from USB stage. Assimilate or Die.\n");
    return 0;
}