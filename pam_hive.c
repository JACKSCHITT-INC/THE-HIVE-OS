#include "pam_hive.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <time.h>
#include <unistd.h>
#include <stdarg.h>

static void hive_pam_log(int priority, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vsyslog(priority, fmt, ap);
    va_end(ap);
}

static int hive_pam_get_context(pam_handle_t *pamh, struct hive_pam_context *ctx) {
    if (!pamh || !ctx) return PAM_SYSTEM_ERR;
    memset(ctx, 0, sizeof(*ctx));
    
    const char *user = NULL;
    pam_get_item(pamh, PAM_USER, (const void **)&user);
    if (user) strncpy(ctx->username, user, sizeof(ctx->username) - 1);
    
    const char *service = NULL;
    pam_get_item(pamh, PAM_SERVICE, (const void **)&service);
    if (service) strncpy(ctx->service, service, sizeof(ctx->service) - 1);
    
    const char *tty = NULL;
    pam_get_item(pamh, PAM_TTY, (const void **)&tty);
    if (tty) strncpy(ctx->tty, tty, sizeof(ctx->tty) - 1);
    
    const char *rhost = NULL;
    pam_get_item(pamh, PAM_RHOST, (const void **)&rhost);
    if (rhost) strncpy(ctx->rhost, rhost, sizeof(ctx->rhost) - 1);
    
    char personality_path[256];
    snprintf(personality_path, sizeof(personality_path), "/etc/hive/personality/%s.conf", ctx->username);
    
    if (hive_personality_load(&ctx->personality, personality_path) != 0) {
        char node_id[64];
        snprintf(node_id, sizeof(node_id), "HIVE-%s-DEFAULT", ctx->username);
        hive_personality_init(&ctx->personality, node_id, ctx->username, HIVE_TYPE_TERMUX, "Bootstrap");
    }
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    struct hive_pam_context ctx;
    if (hive_pam_get_context(pamh, &ctx) != PAM_SUCCESS) return PAM_SYSTEM_ERR;
    
    hive_pam_log(LOG_INFO, "HIVE authenticate: %s (type=%s, role=%s)", ctx.username, ctx.personality.type_name, ctx.personality.role_name);
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    struct hive_pam_context ctx;
    if (hive_pam_get_context(pamh, &ctx) != PAM_SUCCESS) return PAM_SYSTEM_ERR;
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    struct hive_pam_context ctx;
    if (hive_pam_get_context(pamh, &ctx) != PAM_SUCCESS) return PAM_SYSTEM_ERR;
    
    hive_pam_log(LOG_INFO, "HIVE session open: %s (%s/%s)", ctx.username, ctx.personality.type_name, ctx.personality.role_name);
    return PAM_SUCCESS;
}

PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv) {
    return PAM_SUCCESS;
}

int hive_pam_check_role(const struct hive_pam_context *ctx, const char *requested_action) {
    return PAM_SUCCESS; // Expand later with your real role matrix
}

int hive_pam_log_audit(const struct hive_p