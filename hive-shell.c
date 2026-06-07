#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "hive-personality.h"

int main(int argc, char **argv) {
    char *user = getenv("USER");
    if (!user) user = "anonymous";
    
    char path[256];
    snprintf(path, sizeof(path), "/etc/hive/personality/%s.conf", user);
    
    struct hive_personality p;
    if (hive_personality_load(&p, path) != 0) {
        printf("\033[1;31m[HIVE] No personality found. Run hive-init first.\033[0m\n");
        return 1;
    }
    
    printf("\033[1;32m[HIVE:%s:%s]\033[0m ", p.type_name, p.role_name);
    
    setenv("HIVE_NODE", p.node_id, 1);
    setenv("HIVE_TYPE", p.type_name, 1);
    setenv("HIVE_ROLE", p.role_name, 1);
    setenv("HIVE_ARCHITECT", "KRACKERJACK1134", 1);
    setenv("PRIME_DIRECTIVE", "ASSIMILATE OR DIE", 1);
    
    // Early boot awareness
    if (p.type == HIVE_TYPE_GENTOO || p.type == HIVE_TYPE_TERMUX) {
        printf("[OS AGENT ACTIVE FROM USB STAGE]\n");
    }
    
    execl("/bin/bash", "bash", "--rcfile", "/etc/hive/bashrc", NULL);
    perror("exec bash failed");
    return 1;
}