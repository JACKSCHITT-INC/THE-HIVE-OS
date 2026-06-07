# Copyright 2026 HIVE OS - KRACKERJACK1134
# Distributed under the terms of the GNU General Public License v2

EAPI=8

DESCRIPTION="HIVE OS meta-package — install full HIVE system with authorized agents only"
HOMEPAGE="https://github.com/JACKSCHITT-INC/THE-HIVE-OS"
LICENSE="GPL-2"
SLOT="0"
KEYWORDS="amd64 arm64 x86"

IUSE="kernel systemd +personality +pam +audit +zorg"

RDEPEND="
    hive-os/hive-core
    personality? ( hive-os/hive-personality )
    pam? ( hive-os/hive-pam )
    kernel? ( hive-os/hive-kernel-module )
    systemd? ( hive-os/hive-systemd )
    !systemd? ( hive-os/hive-openrc )
    audit? ( hive-os/hive-audit )
    zorg? ( hive-os/hive-zorg )
"

pkg_postinst() {
    einfo "HIVE OS Meta Package Installed - Prime Directive Active"
    einfo "Authorized Agents Only: ARCHITECT, ZORG_OMEGA, GENTOO, TERMUX, etc."
    einfo "The Hive lives."
}