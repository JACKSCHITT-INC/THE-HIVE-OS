# Copyright 2026 HIVE OS - KRACKERJACK1134
# Distributed under the terms of the GNU General Public License v3

EAPI=8

inherit linux-mod toolchain-funcs

DESCRIPTION="HIVE kernel module — personality enforcement and collective awareness at kernel level"
HOMEPAGE="https://github.com/JACKSCHITT-INC/THE-HIVE-OS"
LICENSE="GPL-3"
SLOT="0"
KEYWORDS="amd64 arm64"
IUSE="debug audit"

RDEPEND="
    hive-os/hive-core
    sys-kernel/linux-headers
"
DEPEND="${RDEPEND}"
BDEPEND="
    virtual/linux-sources
"

MODULE_NAMES="hive_personality(hive:${S}/hive_personality)"
BUILD_TARGETS="modules"

src_compile() {
    local myemakeargs=(
        CC="$(tc-getCC)"
        CFLAGS="${CFLAGS}"
        $(usex debug "DEBUG=1" "DEBUG=0")
        $(usex audit "AUDIT_ENABLE=1" "AUDIT_ENABLE=0")
    )
    linux-mod_src_compile
}

src_install() {
    linux-mod_src_install
    
    insinto /etc/hive/kernel
    doins "${FILESDIR}"/hive-kernel.conf
    doins "${FILESDIR}"/hive-lsm.conf
    
    insinto /usr/src/hive-kernel-module-${PV}
    doins *.c *.h Makefile
}

pkg_postinst() {
    einfo "HIVE kernel module installed."
    einfo "Personality enforcement now active at kernel level."
    einfo "The Prime Directive is enforced by the kernel."
    linux-mod_pkg_postinst
}
