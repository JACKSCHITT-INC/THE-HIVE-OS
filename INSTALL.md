# HIVE OS Installation Guide

**Proprietary - All Rights Reserved - KRACKERJACK1134 2026**

## Quick Install (Gentoo)

### 1. Create Overlay
```bash
mkdir -p /var/db/repos/hive-os
cp -r /path/to/THE-HIVE-OS/overlay/* /var/db/repos/hive-os/

cat > /etc/portage/repos.conf/hive-os.conf << 'EOF'
[hive-os]
location = /var/db/repos/hive-os
auto-sync = no
EOF
emerge --sync hive-os
emerge hive-os/hive-meta
# For Gentoo installs (from USB/live)
hive-init --type GENTOO --sovereign "YOURNAME" --role "System Architect"

# For Termux installs
hive-init --type TERMUX --sovereign "YOURNAME" --role "Mobile Swarm Coordinator"
cp /etc/pam.d/system-auth /etc/pam.d/system-auth.bak
cp /var/db/repos/hive-os/hive-os/hive-pam/files/hive-system-auth /etc/pam.d/system-auth
su - YOURNAME
# Should show [HIVE:GENTOO:System Architect]$ or [HIVE:TERMUX:Mobile Swarm Coordinator]$
