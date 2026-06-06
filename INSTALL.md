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
hive-init --type SENTINEL --sovereign "YOURNAME" --role "Watcher"
cp /etc/pam.d/system-auth /etc/pam.d/system-auth.bak
cp /var/db/repos/hive-os/hive-os/hive-pam/files/hive-system-auth /etc/pam.d/system-auth
su - YOURNAME
# Should show [HIVE:SENTINEL:Watcher]$
cd /path/to/THE-HIVE-OS
make
sudo make install
---
