# Copyright 2026 HIVE OS - KRACKERJACK1134
# Distributed under the terms of the GNU General Public License v3
#
# hive.eclass
# Provides common functions for HIVE OS packages

if [[ -z ${_HIVE_ECLASS} ]]; then
_HIVE_ECLASS=1

INHERIT="toolchain-funcs"

# HIVE version and constants
HIVE_VERSION="1.0.0"
HIVE_ARCHITECT="KRACKERJACK1134"
HIVE_PRIME_DIRECTIVE="ASSIMILATE OR DIE"

# Common HIVE RDEPEND
HIVE_COMMON_RDEPEND=" 
    dev-libs/openssl
    sys-libs/pam
"

# Create HIVE user and group
hive_create_user() {
    enewgroup hive
    enewuser hive -1 -1 /var/lib/hive hive
}

# Initialize HIVE directories
hive_init_dirs() {
    local HIVE_DIRS=(
        /etc/hive
        /etc/hive/personality
        /etc/hive/traits
        /etc/hive/roles
        /etc/hive/audit
        /etc/hive/zorg
        /etc/hive/policy.d
        /etc/hive/kernel
        /var/lib/hive
        /var/lib/hive/collective
        /var/lib/hive/personalities
        /var/lib/hive/evolution
        /var/lib/hive/zorg-state
        /var/log/hive
        /var/log/hive/audit
        /var/log/hive/threats
        /var/log/hive/zorg
    )
    
    for dir in "${HIVE_DIRS[@]}"; do
        mkdir -p "${D}${dir}"
        chown hive:hive "${D}${dir}"
        chmod 0750 "${D}${dir}"
    done
}

# Verify HIVE installation
hive_verify_install() {
    einfo "Verifying HIVE installation..."
    
    if [[ -f "${ROOT}usr/bin/hive-init" ]]; then
        einfo "✓ hive-init found"
    else
        ewarn "✗ hive-init not found"
    fi
    
    if [[ -f "${ROOT}usr/bin/hive-shell" ]]; then
        einfo "✓ hive-shell found"
    else
        ewarn "✗ hive-shell not found"
    fi
    
    if [[ -d "${ROOT}etc/hive" ]]; then
        einfo "✓ HIVE configuration directory found"
    else
        ewarn "✗ HIVE configuration directory not found"
    fi
}

fi
