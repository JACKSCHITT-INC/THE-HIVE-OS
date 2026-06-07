# Copyright 2026 HIVE OS - KRACKERJACK1134
# Distributed under the terms of the GNU General Public License v3

EAPI=8

inherit systemd

DESCRIPTION="HIVE Audit subsystem — collective intelligence logging and threat analysis"
HOMEPAGE="https://github.com/JACKSCHITT-INC/THE-HIVE-OS"
LICENSE="GPL-3"
SLOT="0"
KEYWORDS="amd64 arm64 x86"
IUSE="systemd"

RDEPEND="
    hive-os/hive-core
    systemd? ( sys-apps/systemd )
    !systemd? ( sys-apps/openrc )
    dev-lang/python:3.11
    dev-python/pyyaml
"
DEPEND="${RDEPEND}"

src_compile() {
    emake CC="$(tc-getCC)" CFLAGS="${CFLAGS}" audit
}

src_install() {
    emake DESTDIR="${D}" install-audit
    
    keepdir /var/log/hive/audit
    keepdir /var/log/hive/threats
    keepdir /etc/hive/audit
    
    insinto /etc/hive/audit
    doins "${FILESDIR}"/audit-rules.conf
    doins "${FILESDIR}"/threat-detection.conf
    
    insinto /usr/libexec/hive
    doins "${FILESDIR}"/hive-audit-daemon.py
    fperms 0750 /usr/libexec/hive/hive-audit-daemon.py
    
    if use systemd; then
        systemd_dounit "${FILESDIR}"/hive-audit.service
    fi
    
    doman docs/hive-audit.8
}

pkg_postinst() {
    einfo "HIVE Audit subsystem installed."
    einfo "All collective activities will be logged to /var/log/hive/audit/"
    einfo "The Prime Directive is now audited."
}
