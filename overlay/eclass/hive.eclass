# Copyright 2026 HIVE OS - KRACKERJACK1134
# Distributed under the terms of the GNU General Public License v2

inherit user

HIVE_USER="hive"
HIVE_GROUP="hive"

hive_pkg_setup() {
    enewgroup ${HIVE_GROUP}
    enewuser ${HIVE_USER} -1 -1 /var/lib/hive ${HIVE_GROUP}
}

EXPORT_FUNCTIONS pkg_setup