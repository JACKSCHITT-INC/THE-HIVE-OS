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
