# Copyright 2026 HIVE OS - KRACKERJACK1134
# Distributed under the terms of the GNU General Public License v2

EAPI=8

inherit hive pam

DESCRIPTION="HIVE PAM module — RBAC and personality-aware authentication"
HOMEPAGE="https://github.com/JACKSCHITT-INC/THE-HIVE-OS"
SRC_URI=""

LICENSE="GPL-3"
SLOT="0"
KEYWORDS="amd64 arm64 x86"

RDEPEND="
    hive-os/hive-core
    sys-libs/pam
"
DEPEND="${RDEPEND}"

src_compile() {
    emake CC="$(tc-getCC)" CFLAGS="${CFLAGS}" PAMDIR="/$(get_libdir)/security"
}

src_install() {
    emake DESTDIR="${D}" PAMDIR="/$(get_libdir)/security" install
    
    insinto /etc/pam.d
    doins "${FILESDIR}"/hive-system-auth
    doins "${FILESDIR}"/hive-sshd
    doins "${FILESDIR}"/hive-su
}

pkg_postinst() {
    einfo "HIVE PAM module installed. Prime Directive Enforced."
}