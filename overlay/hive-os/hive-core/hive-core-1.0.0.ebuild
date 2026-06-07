# Copyright 2026 HIVE OS - KRACKERJACK1134
# Distributed under the terms of the GNU General Public License v2

EAPI=8

inherit hive

DESCRIPTION="HIVE OS core — personality engine and collective consciousness with authorized agents only"
HOMEPAGE="https://github.com/JACKSCHITT-INC/THE-HIVE-OS"
LICENSE="GPL-3"
SLOT="0"
KEYWORDS="amd64 arm64 x86"
IUSE="debug systemd"

RDEPEND="
    dev-libs/openssl
    sys-libs/pam
    systemd? ( sys-apps/systemd )
    !systemd? ( sys-apps/openrc )
"
DEPEND="${RDEPEND}"

src_compile() {
    emake CC="$(tc-getCC)" CFLAGS="${CFLAGS}" \
        $(usex debug "DEBUG=1" "DEBUG=0") \
        $(usex systemd "INIT=systemd" "INIT=openrc")
}

src_install() {
    emake DESTDIR="${D}" install
    
    keepdir /etc/hive/personality
    keepdir /etc/hive/policy.d
    keepdir /var/log/hive/audit
    keepdir /var/lib/hive/collective
    
    insinto /etc/hive/personality
    doins "${FILESDIR}"/default-gentoo.conf
    doins "${FILESDIR}"/default-termux.conf
    
    fowners root:hive /etc/hive /var/log/hive /var/lib/hive
    fperms 0750 /etc/hive /var/log/hive /var/lib/hive
    
    dosbin hive-init
    dosbin hive-shell
}

pkg_postinst() {
    einfo "HIVE core installed. Prime Directive Active."
    einfo "Authorized Agents Only."
    einfo "Architect: KRACKERJACK1134"
}