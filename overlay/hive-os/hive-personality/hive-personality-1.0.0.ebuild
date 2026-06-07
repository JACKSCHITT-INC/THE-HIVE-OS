# Copyright 2026 HIVE OS - KRACKERJACK1134
# Distributed under the terms of the GNU General Public License v3

EAPI=8

inherit hive

DESCRIPTION="HIVE personality subsystem — trait evolution, role management, and agent synthesis"
HOMEPAGE="https://github.com/JACKSCHITT-INC/THE-HIVE-OS"
LICENSE="GPL-3"
SLOT="0"
KEYWORDS="amd64 arm64 x86"
IUSE="debug collective"

RDEPEND="
    hive-os/hive-core
    dev-lang/python:3.11
    collective? ( dev-python/pyyaml )
"
DEPEND="${RDEPEND}"

src_compile() {
    emake CC="$(tc-getCC)" CFLAGS="${CFLAGS}" \
        $(usex debug "DEBUG=1" "DEBUG=0") \
        $(usex collective "COLLECTIVE=1" "COLLECTIVE=0")
}

src_install() {
    emake DESTDIR="${D}" install
    
    keepdir /etc/hive/traits
    keepdir /etc/hive/roles
    keepdir /var/lib/hive/personalities
    keepdir /var/lib/hive/evolution
    
    insinto /etc/hive/traits
    doins "${FILESDIR}"/trait-matrix.conf
    doins "${FILESDIR}"/role-hierarchy.conf
    
    insinto /usr/libexec/hive
    doins "${FILESDIR}"/personality-daemon.py
    fperms 0750 /usr/libexec/hive/personality-daemon.py
    
    doman docs/hive-personality.8
}

pkg_postinst() {
    einfo "HIVE Personality subsystem installed."
    einfo "Agents may now evolve and adapt their traits."
    einfo "The Collective awaits synchronization."
}
