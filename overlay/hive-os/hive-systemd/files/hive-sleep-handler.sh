#!/bin/bash
# HIVE sleep state handler
# Syncs collective state before sleep, restores on wakeup

case $1 in
    pre)
        # Before sleep - sync and snapshot
        echo "[HIVE] Pre-sleep collective sync..." >> /var/log/hive/system.log
        /usr/libexec/hive/collective-sync.py --snapshot
        /usr/libexec/hive/personality-daemon.py --save-state
        ;;
    post)
        # After sleep - restore and resync
        echo "[HIVE] Post-wakeup collective resync..." >> /var/log/hive/system.log
        /usr/libexec/hive/personality-daemon.py --restore-state
        /usr/libexec/hive/collective-sync.py --restore
        systemctl restart hive-personality.service
        ;;
esac
