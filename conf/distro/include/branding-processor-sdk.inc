ARAGO_TISDK_IMAGE = "processor-sdk-linux${ARAGO_KERNEL_SUFFIX}-bundle"

INHERIT += "recipe-data"

# For TI devices with only baremetal/TI RTOS support
PREFERRED_PROVIDER_virtual/kernel_c66x = "linux-dummy"
PREFERRED_PROVIDER_virtual/kernel_omapl137 = "linux-dummy"

#PREFERRED_PROVIDER_virtual/kernel = "linux-processor-sdk${ARAGO_KERNEL_SUFFIX}"
#PREFERRED_PROVIDER_virtual/kernel_am335x-evm = "linux-processor-sdk${ARAGO_KERNEL_SUFFIX}"
#PREFERRED_PROVIDER_virtual/kernel_am437x-evm = "linux-processor-sdk${ARAGO_KERNEL_SUFFIX}"
#PREFERRED_PROVIDER_virtual/kernel_am57xx-evm = "linux-processor-sdk${ARAGO_KERNEL_SUFFIX}"
#PREFERRED_PROVIDER_virtual/kernel_keystone = "linux-processor-sdk${ARAGO_KERNEL_SUFFIX}"
PREFERRED_VERSION_linux-processor-sdk = "4.4%"
PREFERRED_VERSION_tensorflow-lite_am65xx = "1.15"


# Remove wayland from keystone DISTRO_FEATURES.
DISTRO_FEATURES_remove_keystone = "wayland opengl"

# CMEM reserved memory
RESERVE_CMEM_dra7xx = "1"
RESERVE_CMEM_keystone = "1"

# Enable TI UIO devices
ENABLE_TI_UIO_DEVICES = "0"

# Increase priority of ti-ipc-rtos firmwares
ALTERNATIVE_PRIORITY_pn-ti-ipc-rtos = "15"

# Add DTBs specific to the Processor SDK kernel
PSDK_KERNEL_DEVICETREE ?= ""
KERNEL_DEVICETREE_append = " ${PSDK_KERNEL_DEVICETREE}"


AM57XX_KERNEL_DEVICETREE = " \
    am571x-idk-pps.dtb \
    am572x-idk-pps.dtb \
    am574x-idk-pps.dtb \
"

PSDK_KERNEL_DEVICETREE_ti33x = " "
PSDK_KERNEL_DEVICETREE_ti43x = " "
PSDK_KERNEL_DEVICETREE_k2g   = " "

PSDK_KERNEL_DEVICETREE_am57xx-evm = " ${AM57XX_KERNEL_DEVICETREE}"
PSDK_KERNEL_DEVICETREE_am57xx-hs-evm = " ${AM57XX_KERNEL_DEVICETREE}"

# Configure ROS to use python3
ROS_USE_PYTHON3 = "yes"

# ROS packages which rdepend on python3-dev
INSANE_SKIP_tf2-py += "dev-deps"
INSANE_SKIP_camera-calibration-parsers += "dev-deps"
INSANE_SKIP_cv-bridge += "dev-deps"

# Additional moules to autoload
KERNEL_MODULE_AUTOLOAD_EXTRAS = ""
KERNEL_MODULE_AUTOLOAD_EXTRAS_keystone += "rpmsg_proto"
KERNEL_MODULE_AUTOLOAD += "${KERNEL_MODULE_AUTOLOAD_EXTRAS}"

# Override MKUBIFS_ARGS when our image size exceeds upstream limits
MKUBIFS_ARGS_am335x-evm     = "-F -m 2048 -e 126976 -c 13000"
MKUBIFS_ARGS_am335x-hs-evm  = "-F -m 2048 -e 126976 -c 13000"
MKUBIFS_ARGS_am437x-evm     = "-F -m 4096 -e 253952 -c 6500"
MKUBIFS_ARGS_am437x-hs-evm  = "-F -m 4096 -e 253952 -c 6500"
MKUBIFS_ARGS_am57xx-evm     = "-F -m 2048 -e 126976 -c 15000"
MKUBIFS_ARGS_am57xx-hs-evm  = "-F -m 2048 -e 126976 -c 15000"
MKUBIFS_ARGS_dra7xx-evm     = "-F -m 2048 -e 126976 -c 15000"
MKUBIFS_ARGS_dra7xx-hs-evm  = "-F -m 2048 -e 126976 -c 15000"
MKUBIFS_ARGS_k2hk           = "-F -m 2048 -e 126976 -c 5600"
MKUBIFS_ARGS_k2e            = "-F -m 2048 -e 126976 -c 4800"
MKUBIFS_ARGS_k2g            = "-F -m 4096 -e 253952 -c 2400"
MKUBIFS_ARGS_k2l            = "-F -m 4096 -e 253952 -c 2800"

# By default, do not include OPTEE for any HS platform
# Comment the following lines to build Processor SDK with OPTEE
FITIMAGE_PACK_TEE_am437x-hs-evm = "0"
FITIMAGE_PACK_TEE_am57xx-hs-evm = "0"
FITIMAGE_PACK_TEE_dra7xx-hs-evm = "0"

# To create newlines in the message \n is used and the slash must be escaped
# to function properly

SRCIPK_GIT_COMMIT_MESSAGE = "\
Create local branch\\n\
\\n\
The below commit is used for this local branch and is the one used by\\n\
this sdk:\\n\
${SRCREV}."

SRCIPK_SHALLOW_GIT_COMMIT_MESSAGE ="${SRCIPK_GIT_COMMIT_MESSAGE}\\n\\n\
To reduce the size of the SDK installer only a portion of the git commit\\n\
history has been preserved. Also links to remote branches and tags do\\n\
not exist in this copy of the repository.\\n\
To fix this please run the unshallow-repositories.sh\\n\
script located in the sdk\'s bin directory\\n\
\\n\
The script may take several minutes but you will then have a full copy of\\n\
the git repository including its entire git history.\\n"

CREATE_SRCIPK_pn-linux-processor-sdk = "1"
SRCIPK_INSTALL_DIR_pn-linux-processor-sdk = "board-support/linux-${PV}${KERNEL_LOCALVERSION}"
SRCIPK_PRESERVE_GIT_pn-linux-processor-sdk = "true"
SRCIPK_CUSTOM_GIT_BRANCH_pn-linux-processor-sdk = "processor-sdk-local"
SRCIPK_CUSTOM_GIT_MESSAGE_pn-linux-processor-sdk = "${SRCIPK_SHALLOW_GIT_COMMIT_MESSAGE}"
SRCIPK_SHALLOW_CLONE_pn-linux-processor-sdk = "true"
SRCIPK_SHALLOW_DEPTH_pn-linux-processor-sdk = "100"

CREATE_SRCIPK_pn-linux-processor-sdk-rt = "1"
SRCIPK_INSTALL_DIR_pn-linux-processor-sdk-rt = "board-support/linux-rt-${PV}${KERNEL_LOCALVERSION}"
SRCIPK_PRESERVE_GIT_pn-linux-processor-sdk-rt = "true"
SRCIPK_CUSTOM_GIT_BRANCH_pn-linux-processor-sdk-rt = "processor-sdk-local"
SRCIPK_CUSTOM_GIT_MESSAGE_pn-linux-processor-sdk-rt = "${SRCIPK_SHALLOW_GIT_COMMIT_MESSAGE}"
SRCIPK_SHALLOW_CLONE_pn-linux-processor-sdk-rt = "true"
SRCIPK_SHALLOW_DEPTH_pn-linux-processor-sdk-rt = "100"

SRCIPK_CUSTOM_GIT_BRANCH_pn-linux-ti-staging = "processor-sdk-local"
SRCIPK_CUSTOM_GIT_MESSAGE_pn-linux-ti-staging = "${SRCIPK_SHALLOW_GIT_COMMIT_MESSAGE}"
SRCIPK_SHALLOW_CLONE_pn-linux-ti-staging = "true"
SRCIPK_SHALLOW_DEPTH_pn-linux-ti-staging = "100"

CREATE_SRCIPK_pn-linux-ti-staging-rt = "1"
SRCIPK_INSTALL_DIR_pn-linux-ti-staging-rt = "board-support/linux-rt-${PV}${KERNEL_LOCALVERSION}"
SRCIPK_PRESERVE_GIT_pn-linux-ti-staging-rt = "true"
SRCIPK_CUSTOM_GIT_BRANCH_pn-linux-ti-staging-rt = "processor-sdk-local"
SRCIPK_CUSTOM_GIT_MESSAGE_pn-linux-ti-staging-rt = "${SRCIPK_SHALLOW_GIT_COMMIT_MESSAGE}"
SRCIPK_SHALLOW_CLONE_pn-linux-ti-staging-rt = "true"
SRCIPK_SHALLOW_DEPTH_pn-linux-ti-staging-rt = "100"

SRCIPK_CUSTOM_GIT_BRANCH_pn-u-boot-ti-staging = "processor-sdk-local"
SRCIPK_CUSTOM_GIT_MESSAGE_pn-u-boot-ti-staging = "${SRCIPK_GIT_COMMIT_MESSAGE}"

IMAGE_BOOT_FILES_am64xx-hs-evm = " tiboot3.bin ${SPL_BINARYNAME} ${UBOOT_IMAGE} uEnv.txt"
UBOOT_IMAGE_am64xx-hs-evm = "u-boot.img"
