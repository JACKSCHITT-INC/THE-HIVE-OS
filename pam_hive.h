#ifndef PAM_HIVE_H
#define PAM_HIVE_H

#include <security/pam_modules.h>
#include "hive-personality.h"

#define HIVE_POLICY_DIR "/etc/hive/policy.d"
#define HIVE_AUDIT_LOG "/var/log/hive/audit.log"

struct hive_pam_context {
    struct hive_personality personality;
    char username[64];
    char service[64];
    char tty[64];
    char rhost[64];
    int role_verified;
};

PAM_EXTERN int pam_sm_authenticate(pam_handle_t *pamh, int flags, int argc, const char **argv);
PAM_EXTERN int pam_sm_setcred(pam_handle_t *pamh, int flags, int argc, const char **argv);
PAM_EXTERN int pam_sm_acct_mgmt(pam_handle_t *pamh, int flags, int argc, const char **argv);
PAM_EXTERN int pam_sm_open_session(pam_handle_t *pamh, int flags, int argc, const char **argv);
PAM_EXTERN int pam_sm_close_session(pam_handle_t *pamh, int flags, int argc, const char **argv);
PAM_EXTERN int pam_sm_chauthtok(pam_handle_t *pamh, int flags, int argc, const char **argv);

int hive_pam_check_role(const struct hive_pam_context *ctx, const char *requested_action);
int hive_pam_log_audit(const struct hive_pam_context *ctx, const char *action, int result);

#endif