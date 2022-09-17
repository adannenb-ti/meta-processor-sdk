FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI_append_am62xx-evm = " \
    file://0001-HACK-lib-lmb-Allow-re-reserving-post-relocation-U-Bo.patch \
"

SRC_URI_append_am62xx-evm-k3r5 = " \
    file://0001-HACK-lib-lmb-Allow-re-reserving-post-relocation-U-Bo.patch \
"
PR = "r28"
