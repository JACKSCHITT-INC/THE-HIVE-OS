# Copyright 2026 HIVE OS - KRACKERJACK1134
# Distributed under the terms of the GNU General Public License v3

EAPI=8

DESCRIPTION="HIVE OpenRC integration — boot, service management, and collective startup for non-systemd systems"
HOMEPAGE="https://github.com/JACKSCHITT-INC/THE-HIVE-OS"
LICENSE="GPL-3"
SLOT="0"
KEYWORDS="amd64 arm64 arm x86 x86-64"

RDEPEND="
    hive-os/hive-core
    sys-apps/openrc
"
DEPEND="${RDEPEND}"

src_install() {
    insinto /etc/init.d
    doins "${FILESDIR}"/hive-personality
    doins "${FILESDIR}"/hive-audit
    doins "${FILESDIR}"/hive-collective-sync
    fperms 0755 /etc/init.d/hive-personality /etc/init.d/hive-audit /etc/init.d/hive-collective-sync
    
    insinto /etc/conf.d
    doins "${FILESDIR}"/hive
    
    insinto /usr/local/sbin
    doins "${FILESDIR}"/hive-cron-sync.sh
    fperms 0750 /usr/local/sbin/hive-cron-sync.sh
}

pkg_postinst() {
    einfo "HIVE OpenRC integration installed."
    einfo "Services: hive-personality (daemon), hive-audit (logging), hive-collective-sync (cron)"
    einfo "Run: rc-update add hive-personality boot && rc-update add hive-audit boot"
}
