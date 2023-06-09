PR_append = ".tisdk72"

FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append = "\
    file://Makefile_video-graphics-test \
    file://Makefile_evse-hmi \
    file://Makefile_protection-relays-hmi \
    file://Makefile_tiovx-app-host \
    file://Makefile_tidl-examples \
    file://Makefile_pru-adc \
    file://Makefile_linux-fitimage \
"
SRC_URI_append_am65xx = "\
    file://Makefile_sysfw-image-am65xx \
"

MAKEFILES_remove_am65xx-evm = " sysfw-image"
MAKEFILES_remove_am65xx-hs-evm = " sysfw-image"
MAKEFILES_append_am65xx-evm = " sysfw-image-am65xx"
MAKEFILES_append_am65xx-hs-evm = " sysfw-image-am65xx"

SRC_URI_append_am65xx-evm = "\
    file://Makefile_ti-sgx-ddk-km-am65xx \
"

SRC_URI_remove_am65xx-evm = "\
    file://Makefile_matrix-gui \
    file://Makefile_matrix-gui-browser \
    file://Makefile_refresh-screen \
    file://Makefile_qt-tstat \
    file://Makefile_pru \
    file://Makefile_pru-icss \
    file://Makefile_barcode-roi \
    file://Makefile_mmwavegesture-hmi \
    file://Makefile_pdm-anomaly-detection \
    file://Makefile_ti-ipc \
    file://Makefile_ti-sgx-ddk-km \
"
MAKEFILES_append_am65xx-evm = " ti-sgx-ddk-km-am65xx \
"

MAKEFILES_COMMON_remove_am65xx-evm = "\
    matrix-gui \
    matrix-gui-browser \
    refresh-screen \
    qt-tstat \
"
MAKEFILES_remove_am65xx-evm = " \
    pru \
    pru-icss \
    barcode-roi \
    mmwavegesture-hmi \
    pdm-anomaly-detection \
    ti-ipc \
    ti-sgx-ddk-km \
"

SRC_URI_append_omap-a15 = " file://Makefile_big-data-ipc-demo"
SRC_URI_append_am62xx = " file://Makefile_ti-img-rogue-driver_am62"

# FIXME: ti-crypto-examples require openssl 1.0, but devkit packages openssl 1.1
MAKEFILES_remove = "ti-crypto-examples"

MAKEFILES_remove_ti33x = " barcode-roi"

MAKEFILES_remove_ti43x = " barcode-roi"

MAKEFILES_append_k2g = " opencl-examples \
                         openmpacc-examples \
"

MAKEFILES_append_omap-a15 = " dual-camera-demo \
                              image-gallery \
                              big-data-ipc-demo \
			      evse-hmi \
                              video-graphics-test \
"

MAKEFILES_append_ti43x = " evse-hmi \
"

MAKEFILES_append_ti33x = " evse-hmi \
			   protection-relays-hmi \
"

MAKEFILES_append_am335x-evm = " pru-adc"

MAKEFILES_append_am57xx-evm = " \
                                tidl-examples \
"
MAKEFILES_append_am57xx-hs-evm = " tidl-examples"

MAKEFILES_append_dra7xx = " tiovx-app-host"
MAKEFILES_append_am62xx = " ti-img-rogue-driver_am62 \
                            linux-fitimage \
"

MAKEFILES_append_am64xx = " linux-fitimage"
MAKEFILES_append_am62axx = " linux-fitimage"

KERNEL_BUILD_CMDS_append_am64xx-hs-evm = " Image.gz"
MAKEFILES_append_am64xx-hs-evm = " linux-fitimage"
PRU_ICSS_INSTALL_TARGET_am64xx = "pru-icss_install_am64x"

MAKEFILES_remove_ti33x = "${@bb.utils.contains('MACHINE_FEATURES', 'gpu', '', 'ti-sgx-ddk-km', d)}"
MAKEFILES_remove_ti43x = "${@bb.utils.contains('MACHINE_FEATURES', 'gpu', '', 'ti-sgx-ddk-km', d)}"

MAKEFILES_remove_keystone = "hplib-mod ipsecmgr-mod"

# Populate UBOOT_MACHINE when UBOOT_CONFIG is used
# (see uboot-config.bbclass)
python() {
    ubootmachine = d.getVar("UBOOT_MACHINE", True)
    ubootconfigflags = d.getVarFlags('UBOOT_CONFIG')
    # The "doc" varflag is special, we don't want to see it here
    ubootconfigflags.pop('doc', None)

    if ubootmachine and ubootconfigflags:
        bb.warn('UBOOT_MACHINE = "%s", UBOOT_CONFIG(flags) = "%s"' % (ubootmachine, ubootconfigflags))
        raise bb.parse.SkipPackage("You cannot use UBOOT_MACHINE and UBOOT_CONFIG at the same time.")

    if not ubootconfigflags:
        return

    ubootconfig = (d.getVar('UBOOT_CONFIG', True) or "").split()
    if len(ubootconfig) > 0:
        for config in ubootconfig:
            for f, v in ubootconfigflags.items():
                if config == f:
                    items = v.split(',')
                    if items[0] and len(items) > 3:
                        raise bb.parse.SkipPackage('Only config,images,binary can be specified!')
                    # From u-boot-ti.inc, the last config is the default
                    # So keep overwriting UBOOT_MACHINE to get to the default
                    d.setVar('UBOOT_MACHINE', items[0])
                    break
    elif len(ubootconfig) == 0:
       raise bb.parse.SkipPackage('You must set a default in UBOOT_CONFIG.')
}
