#!/bin/bash
# HIVE periodic synchronization (intended for cron)
# Ensures collective state remains synchronized on non-systemd systems

set -euo pipefail

LOGFILE="/var/log/hive/cron-sync.log"
STATE_DIR="/var/lib/hive/collective"

echo "[$(date)] HIVE collective sync initiated" >> "$LOGFILE"

# Ensure state directory exists
mkdir -p "$STATE_DIR"
chown hive:hive "$STATE_DIR"
chmod 750 "$STATE_DIR"

# Run collective sync
if command -v python3 &> /dev/null; then
    /usr/libexec/hive/collective-sync.py >> "$LOGFILE" 2>&1 || echo "[$(date)] Sync failed" >> "$LOGFILE"
else
    echo "[$(date)] ERROR: python3 not found" >> "$LOGFILE"
    exit 1
fi

echo "[$(date)] HIVE collective sync completed" >> "$LOGFILE"
