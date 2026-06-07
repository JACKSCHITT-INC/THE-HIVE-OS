# Copyright 2026 HIVE OS - KRACKERJACK1134
# Distributed under the terms of the GNU General Public License v3

EAPI=8

DESCRIPTION="HIVE systemd integration — boot, service management, and collective startup"
HOMEPAGE="https://github.com/JACKSCHITT-INC/THE-HIVE-OS"
LICENSE="GPL-3"
SLOT="0"
KEYWORDS="amd64 arm64 x86"

RDEPEND="
    hive-os/hive-core
    sys-apps/systemd
"
DEPEND="${RDEPEND}"

src_install() {
    insinto /etc/systemd/system
    doins "${FILESDIR}"/hive-personality.service
    doins "${FILESDIR}"/hive-personality.timer
    doins "${FILESDIR}"/hive-audit.service
    doins "${FILESDIR}"/hive-collective-sync.service
    doins "${FILESDIR}"/hive-collective-sync.timer
    
    insinto /etc/systemd/system-sleep
    doins "${FILESDIR}"/hive-sleep-handler.sh
    fperms 0755 /etc/systemd/system-sleep/hive-sleep-handler.sh
    
    insinto /usr/lib/systemd/system-preset
    doins "${FILESDIR}"/60-hive.preset
    
    insinto /etc/systemd
    doins "${FILESDIR}"/hive-system.conf
}

pkg_postinst() {
    einfo "HIVE systemd integration installed."
    einfo "Services: hive-personality (daemon), hive-audit (logging), hive-collective-sync (5min)"
    einfo "Run: systemctl daemon-reload && systemctl preset 60-hive"
}
