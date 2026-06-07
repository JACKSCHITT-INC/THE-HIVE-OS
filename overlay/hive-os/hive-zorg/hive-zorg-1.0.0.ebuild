# Copyright 2026 HIVE OS - KRACKERJACK1134
# Distributed under the terms of the GNU General Public License v3

EAPI=8

DESCRIPTION="HIVE ZORG-Ω agent — The Shadow, security, zero-trust enforcement, and vulnerability analysis"
HOMEPAGE="https://github.com/JACKSCHITT-INC/THE-HIVE-OS"
LICENSE="GPL-3"
SLOT="0"
KEYWORDS="amd64 arm64 x86"
IUSE="systemd penetration"

RDEPEND="
    hive-os/hive-core
    hive-os/hive-audit
    dev-lang/python:3.11
    dev-python/pyyaml
    penetration? ( net-analyzer/nmap )
"
DEPEND="${RDEPEND}"

src_compile() {
    emake CC="$(tc-getCC)" CFLAGS="${CFLAGS}" \
        $(usex penetration "PENETRATION=1" "PENETRATION=0") \
        zorg
}

src_install() {
    emake DESTDIR="${D}" install-zorg
    
    keepdir /etc/hive/zorg
    keepdir /var/lib/hive/zorg-state
    keepdir /var/log/hive/zorg
    
    insinto /etc/hive/zorg
    doins "${FILESDIR}"/zorg-policy.conf
    doins "${FILESDIR}"/zero-trust-rules.conf
    
    insinto /usr/libexec/hive
    doins "${FILESDIR}"/zorg-omega.py
    fperms 0750 /usr/libexec/hive/zorg-omega.py
    
    if use systemd; then
        insinto /etc/systemd/system
        doins "${FILESDIR}"/hive-zorg.service
    fi
    
    doman docs/zorg-omega.8
}

pkg_postinst() {
    einfo "HIVE ZORG-Ω agent installed."
    einfo "The Shadow is now watching. Zero-Trust enforced."
    einfo "All security is now paranoid security."
}
