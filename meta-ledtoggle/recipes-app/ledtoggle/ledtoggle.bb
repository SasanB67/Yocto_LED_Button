SUMMARY = "Toggle an LED with a push button"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRC_URI = "file://ledtoggle.c file://ledtoggle.service"
S = "${WORKDIR}"

inherit systemd
SYSTEMD_SERVICE:${PN} = "ledtoggle.service"

do_compile() {
    ${CC} ${CFLAGS} ${LDFLAGS} -o ledtoggle ledtoggle.c
}

do_install() {
    install -Dm 0755 ledtoggle ${D}${bindir}/ledtoggle
    install -Dm 0644 ledtoggle.service ${D}${systemd_system_unitdir}/ledtoggle.service
}
