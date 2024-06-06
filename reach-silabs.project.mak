####################################################################
# Automatically-generated file. Do not edit!                       #
# Makefile Version 15                                              #
####################################################################

BASE_SDK_PATH = C:/Users/chuck.peplinski/SimplicityStudio/SDKs/gecko_sdk_4.4
UNAME:=$(shell $(POSIX_TOOL_PATH)uname -s | $(POSIX_TOOL_PATH)sed -e 's/^\(CYGWIN\).*/\1/' | $(POSIX_TOOL_PATH)sed -e 's/^\(MINGW\).*/\1/')
ifeq ($(UNAME),MINGW)
# Translate "C:/super" into "/C/super" for MinGW make.
SDK_PATH := /$(shell $(POSIX_TOOL_PATH)echo $(BASE_SDK_PATH) | sed s/://)
endif
SDK_PATH ?= $(BASE_SDK_PATH)
COPIED_SDK_PATH ?= gecko_sdk_4.4.3

# This uses the explicit build rules below
PROJECT_SOURCE_FILES =

C_SOURCE_FILES   += $(filter %.c, $(PROJECT_SOURCE_FILES))
CXX_SOURCE_FILES += $(filter %.cpp, $(PROJECT_SOURCE_FILES))
CXX_SOURCE_FILES += $(filter %.cc, $(PROJECT_SOURCE_FILES))
ASM_SOURCE_FILES += $(filter %.s, $(PROJECT_SOURCE_FILES))
ASM_SOURCE_FILES += $(filter %.S, $(PROJECT_SOURCE_FILES))
LIB_FILES        += $(filter %.a, $(PROJECT_SOURCE_FILES))

C_DEFS += \
 '-DEFR32BG22C224F512IM40=1' \
 '-DSL_APP_PROPERTIES=1' \
 '-DBOOTLOADER_APPLOADER=1' \
 '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' \
 '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' \
 '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' \
 '-DHFXO_FREQ=38400000' \
 '-DSL_BOARD_NAME="BRD4184A"' \
 '-DSL_BOARD_REV="A01"' \
 '-DSL_COMPONENT_CATALOG_PRESENT=1' \
 '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' \
 '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' \
 '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' \
 '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' \
 '-DSLI_RADIOAES_REQUIRES_MASKING=1' \
 '-DSL_KIT_NAME="SLTB010A"' \
 '-DSL_KIT_REV="A04"'

ASM_DEFS += \
 '-DEFR32BG22C224F512IM40=1' \
 '-DSL_APP_PROPERTIES=1' \
 '-DBOOTLOADER_APPLOADER=1' \
 '-DHARDWARE_BOARD_DEFAULT_RF_BAND_2400=1' \
 '-DHARDWARE_BOARD_SUPPORTS_1_RF_BAND=1' \
 '-DHARDWARE_BOARD_SUPPORTS_RF_BAND_2400=1' \
 '-DHFXO_FREQ=38400000' \
 '-DSL_BOARD_NAME="BRD4184A"' \
 '-DSL_BOARD_REV="A01"' \
 '-DSL_COMPONENT_CATALOG_PRESENT=1' \
 '-DMBEDTLS_CONFIG_FILE=<sl_mbedtls_config.h>' \
 '-DMBEDTLS_PSA_CRYPTO_CONFIG_FILE=<psa_crypto_config.h>' \
 '-DSL_RAIL_LIB_MULTIPROTOCOL_SUPPORT=0' \
 '-DSL_RAIL_UTIL_PA_CONFIG_HEADER=<sl_rail_util_pa_config.h>' \
 '-DSLI_RADIOAES_REQUIRES_MASKING=1' \
 '-DSL_KIT_NAME="SLTB010A"' \
 '-DSL_KIT_REV="A04"'

INCLUDES += \
 -Iconfig \
 -Iconfig/btconf \
 -Iautogen \
 -I. \
 -I$(SDK_PATH)/platform/Device/SiliconLabs/EFR32BG22/Include \
 -I$(SDK_PATH)/app/common/util/app_assert \
 -I$(SDK_PATH)/app/common/util/app_timer \
 -I$(SDK_PATH)/protocol/bluetooth/inc \
 -I$(SDK_PATH)/platform/common/inc \
 -I$(SDK_PATH)/protocol/bluetooth/bgcommon/inc \
 -I$(SDK_PATH)/protocol/bluetooth/bgstack/ll/inc \
 -I$(SDK_PATH)/hardware/board/inc \
 -I$(SDK_PATH)/platform/bootloader \
 -I$(SDK_PATH)/platform/bootloader/api \
 -I$(SDK_PATH)/platform/driver/button/inc \
 -I$(SDK_PATH)/platform/CMSIS/Core/Include \
 -I$(SDK_PATH)/hardware/driver/configuration_over_swo/inc \
 -I$(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/include \
 -I$(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src \
 -I$(SDK_PATH)/platform/driver/debug/inc \
 -I$(SDK_PATH)/platform/service/device_init/inc \
 -I$(SDK_PATH)/platform/emdrv/dmadrv/inc \
 -I$(SDK_PATH)/platform/emdrv/common/inc \
 -I$(SDK_PATH)/platform/emlib/inc \
 -I$(SDK_PATH)/app/bluetooth/common/gatt_service_device_information \
 -I$(SDK_PATH)/platform/emdrv/gpiointerrupt/inc \
 -I$(SDK_PATH)/platform/driver/i2cspm/inc \
 -I$(SDK_PATH)/hardware/driver/icm20648/inc \
 -I$(SDK_PATH)/hardware/driver/imu/inc \
 -I$(SDK_PATH)/app/bluetooth/common/in_place_ota_dfu \
 -I$(SDK_PATH)/platform/service/iostream/inc \
 -I$(SDK_PATH)/platform/driver/leddrv/inc \
 -I$(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/config \
 -I$(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/config/preset \
 -I$(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/inc \
 -I$(SDK_PATH)/util/third_party/mbedtls/include \
 -I$(SDK_PATH)/util/third_party/mbedtls/library \
 -I$(SDK_PATH)/hardware/driver/mic/inc \
 -I$(SDK_PATH)/platform/service/mpu/inc \
 -I$(SDK_PATH)/hardware/driver/mx25_flash_shutdown/inc/sl_mx25_flash_shutdown_usart \
 -I$(SDK_PATH)/platform/emdrv/nvm3/inc \
 -I$(SDK_PATH)/platform/service/power_manager/inc \
 -I$(SDK_PATH)/util/third_party/printf \
 -I$(SDK_PATH)/util/third_party/printf/inc \
 -I$(SDK_PATH)/platform/security/sl_component/sl_psa_driver/inc \
 -I$(SDK_PATH)/platform/radio/rail_lib/common \
 -I$(SDK_PATH)/platform/radio/rail_lib/protocol/ble \
 -I$(SDK_PATH)/platform/radio/rail_lib/protocol/ieee802154 \
 -I$(SDK_PATH)/platform/radio/rail_lib/protocol/wmbus \
 -I$(SDK_PATH)/platform/radio/rail_lib/protocol/zwave \
 -I$(SDK_PATH)/platform/radio/rail_lib/chip/efr32/efr32xg2x \
 -I$(SDK_PATH)/platform/radio/rail_lib/protocol/sidewalk \
 -I$(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions \
 -I$(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/efr32xg22 \
 -I$(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_power_manager_init \
 -I$(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_pti \
 -I$(SDK_PATH)/platform/security/sl_component/se_manager/inc \
 -I$(SDK_PATH)/platform/security/sl_component/se_manager/src \
 -I$(SDK_PATH)/app/bluetooth/common/sensor_hall \
 -I$(SDK_PATH)/app/bluetooth/common/sensor_imu \
 -I$(SDK_PATH)/app/bluetooth/common/sensor_light \
 -I$(SDK_PATH)/app/bluetooth/common/sensor_rht \
 -I$(SDK_PATH)/app/bluetooth/common/sensor_select \
 -I$(SDK_PATH)/app/bluetooth/common/sensor_sound \
 -I$(SDK_PATH)/hardware/driver/si1133/inc \
 -I$(SDK_PATH)/hardware/driver/si70xx/inc \
 -I$(SDK_PATH)/hardware/driver/si7210/inc \
 -I$(SDK_PATH)/util/silicon_labs/silabs_core/memory_manager \
 -I$(SDK_PATH)/platform/common/toolchain/inc \
 -I$(SDK_PATH)/platform/service/system/inc \
 -I$(SDK_PATH)/platform/service/sleeptimer/inc \
 -I$(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src \
 -I$(SDK_PATH)/platform/service/udelay/inc

GROUP_START =-Wl,--start-group
GROUP_END =-Wl,--end-group

PROJECT_LIBS = \
 -lgcc \
 -lc \
 -lm \
 -lnosys \
 $(SDK_PATH)/protocol/bluetooth/bgcommon/lib/libbgcommon_efr32xg22_gcc_release.a \
 $(SDK_PATH)/protocol/bluetooth/bgstack/ll/lib/libbluetooth_controller_efr32xg22_gcc_release.a \
 $(SDK_PATH)/protocol/bluetooth/lib/libbluetooth_host_efr32xg22_gcc_release.a \
 $(SDK_PATH)/platform/emdrv/nvm3/lib/libnvm3_CM33_gcc.a \
 $(SDK_PATH)/platform/radio/rail_lib/autogen/librail_release/librail_efr32xg22_gcc_release.a

LIBS += $(GROUP_START) $(PROJECT_LIBS) $(GROUP_END)

LIB_FILES += $(filter %.a, $(PROJECT_LIBS))

C_FLAGS += \
 -mcpu=cortex-m33 \
 -mthumb \
 -mfpu=fpv5-sp-d16 \
 -mfloat-abi=hard \
 -std=c99 \
 -Wall \
 -Wextra \
 -Os \
 -fdata-sections \
 -ffunction-sections \
 -fomit-frame-pointer \
 -imacros sl_gcc_preinclude.h \
 -mcmse \
 -fno-builtin-printf \
 -fno-builtin-sprintf \
 --specs=nano.specs \
 -g

CXX_FLAGS += \
 -mcpu=cortex-m33 \
 -mthumb \
 -mfpu=fpv5-sp-d16 \
 -mfloat-abi=hard \
 -std=c++11 \
 -fno-rtti \
 -fno-exceptions \
 -Wall \
 -Wextra \
 -Os \
 -fdata-sections \
 -ffunction-sections \
 -fomit-frame-pointer \
 -imacros sl_gcc_preinclude.h \
 -mcmse \
 -fno-builtin-printf \
 -fno-builtin-sprintf \
 --specs=nano.specs \
 -g

ASM_FLAGS += \
 -mcpu=cortex-m33 \
 -mthumb \
 -mfpu=fpv5-sp-d16 \
 -mfloat-abi=hard \
 -imacros sl_gcc_preinclude.h \
 -x assembler-with-cpp

LD_FLAGS += \
 -mcpu=cortex-m33 \
 -mthumb \
 -mfpu=fpv5-sp-d16 \
 -mfloat-abi=hard \
 -T"autogen/linkerfile.ld" \
 --specs=nano.specs \
 -Xlinker -Map=$(OUTPUT_DIR)/$(PROJECTNAME).map \
 -Wl,--gc-sections \
 -Wl,--no-warn-rwx-segments


####################################################################
# Pre/Post Build Rules                                             #
####################################################################
pre-build:
	# No pre-build defined

post-build: $(OUTPUT_DIR)/$(PROJECTNAME).out
	# No post-build defined

####################################################################
# SDK Build Rules                                                  #
####################################################################
$(OUTPUT_DIR)/sdk/app/bluetooth/common/in_place_ota_dfu/sl_bt_in_place_ota_dfu.o: $(SDK_PATH)/app/bluetooth/common/in_place_ota_dfu/sl_bt_in_place_ota_dfu.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/app/bluetooth/common/in_place_ota_dfu/sl_bt_in_place_ota_dfu.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/app/bluetooth/common/in_place_ota_dfu/sl_bt_in_place_ota_dfu.c
CDEPS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/in_place_ota_dfu/sl_bt_in_place_ota_dfu.d
OBJS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/in_place_ota_dfu/sl_bt_in_place_ota_dfu.o

$(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_hall/sl_sensor_hall.o: $(SDK_PATH)/app/bluetooth/common/sensor_hall/sl_sensor_hall.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/app/bluetooth/common/sensor_hall/sl_sensor_hall.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/app/bluetooth/common/sensor_hall/sl_sensor_hall.c
CDEPS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_hall/sl_sensor_hall.d
OBJS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_hall/sl_sensor_hall.o

$(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_imu/sl_sensor_imu.o: $(SDK_PATH)/app/bluetooth/common/sensor_imu/sl_sensor_imu.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/app/bluetooth/common/sensor_imu/sl_sensor_imu.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/app/bluetooth/common/sensor_imu/sl_sensor_imu.c
CDEPS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_imu/sl_sensor_imu.d
OBJS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_imu/sl_sensor_imu.o

$(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_light/sl_sensor_light.o: $(SDK_PATH)/app/bluetooth/common/sensor_light/sl_sensor_light.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/app/bluetooth/common/sensor_light/sl_sensor_light.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/app/bluetooth/common/sensor_light/sl_sensor_light.c
CDEPS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_light/sl_sensor_light.d
OBJS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_light/sl_sensor_light.o

$(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_rht/sl_sensor_rht.o: $(SDK_PATH)/app/bluetooth/common/sensor_rht/sl_sensor_rht.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/app/bluetooth/common/sensor_rht/sl_sensor_rht.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/app/bluetooth/common/sensor_rht/sl_sensor_rht.c
CDEPS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_rht/sl_sensor_rht.d
OBJS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_rht/sl_sensor_rht.o

$(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_select/sl_sensor_select.o: $(SDK_PATH)/app/bluetooth/common/sensor_select/sl_sensor_select.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/app/bluetooth/common/sensor_select/sl_sensor_select.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/app/bluetooth/common/sensor_select/sl_sensor_select.c
CDEPS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_select/sl_sensor_select.d
OBJS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_select/sl_sensor_select.o

$(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_sound/sl_sensor_sound.o: $(SDK_PATH)/app/bluetooth/common/sensor_sound/sl_sensor_sound.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/app/bluetooth/common/sensor_sound/sl_sensor_sound.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/app/bluetooth/common/sensor_sound/sl_sensor_sound.c
CDEPS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_sound/sl_sensor_sound.d
OBJS += $(OUTPUT_DIR)/sdk/app/bluetooth/common/sensor_sound/sl_sensor_sound.o

$(OUTPUT_DIR)/sdk/app/common/util/app_timer/app_timer.o: $(SDK_PATH)/app/common/util/app_timer/app_timer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/app/common/util/app_timer/app_timer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/app/common/util/app_timer/app_timer.c
CDEPS += $(OUTPUT_DIR)/sdk/app/common/util/app_timer/app_timer.d
OBJS += $(OUTPUT_DIR)/sdk/app/common/util/app_timer/app_timer.o

$(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_control_gpio.o: $(SDK_PATH)/hardware/board/src/sl_board_control_gpio.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/board/src/sl_board_control_gpio.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/board/src/sl_board_control_gpio.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_control_gpio.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_control_gpio.o

$(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_init.o: $(SDK_PATH)/hardware/board/src/sl_board_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/board/src/sl_board_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/board/src/sl_board_init.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_init.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/board/src/sl_board_init.o

$(OUTPUT_DIR)/sdk/hardware/driver/configuration_over_swo/src/sl_cos.o: $(SDK_PATH)/hardware/driver/configuration_over_swo/src/sl_cos.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/driver/configuration_over_swo/src/sl_cos.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/driver/configuration_over_swo/src/sl_cos.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/driver/configuration_over_swo/src/sl_cos.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/driver/configuration_over_swo/src/sl_cos.o

$(OUTPUT_DIR)/sdk/hardware/driver/icm20648/src/sl_icm20648.o: $(SDK_PATH)/hardware/driver/icm20648/src/sl_icm20648.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/driver/icm20648/src/sl_icm20648.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/driver/icm20648/src/sl_icm20648.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/driver/icm20648/src/sl_icm20648.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/driver/icm20648/src/sl_icm20648.o

$(OUTPUT_DIR)/sdk/hardware/driver/imu/src/sl_imu_dcm.o: $(SDK_PATH)/hardware/driver/imu/src/sl_imu_dcm.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/driver/imu/src/sl_imu_dcm.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/driver/imu/src/sl_imu_dcm.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/driver/imu/src/sl_imu_dcm.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/driver/imu/src/sl_imu_dcm.o

$(OUTPUT_DIR)/sdk/hardware/driver/imu/src/sl_imu_fuse.o: $(SDK_PATH)/hardware/driver/imu/src/sl_imu_fuse.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/driver/imu/src/sl_imu_fuse.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/driver/imu/src/sl_imu_fuse.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/driver/imu/src/sl_imu_fuse.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/driver/imu/src/sl_imu_fuse.o

$(OUTPUT_DIR)/sdk/hardware/driver/imu/src/sl_imu_icm20648.o: $(SDK_PATH)/hardware/driver/imu/src/sl_imu_icm20648.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/driver/imu/src/sl_imu_icm20648.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/driver/imu/src/sl_imu_icm20648.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/driver/imu/src/sl_imu_icm20648.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/driver/imu/src/sl_imu_icm20648.o

$(OUTPUT_DIR)/sdk/hardware/driver/imu/src/sl_imu_math.o: $(SDK_PATH)/hardware/driver/imu/src/sl_imu_math.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/driver/imu/src/sl_imu_math.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/driver/imu/src/sl_imu_math.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/driver/imu/src/sl_imu_math.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/driver/imu/src/sl_imu_math.o

$(OUTPUT_DIR)/sdk/hardware/driver/mic/src/sl_mic_pdm.o: $(SDK_PATH)/hardware/driver/mic/src/sl_mic_pdm.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/driver/mic/src/sl_mic_pdm.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/driver/mic/src/sl_mic_pdm.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/driver/mic/src/sl_mic_pdm.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/driver/mic/src/sl_mic_pdm.o

$(OUTPUT_DIR)/sdk/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.o: $(SDK_PATH)/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/driver/mx25_flash_shutdown/src/sl_mx25_flash_shutdown_usart/sl_mx25_flash_shutdown.o

$(OUTPUT_DIR)/sdk/hardware/driver/si1133/src/sl_si1133.o: $(SDK_PATH)/hardware/driver/si1133/src/sl_si1133.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/driver/si1133/src/sl_si1133.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/driver/si1133/src/sl_si1133.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/driver/si1133/src/sl_si1133.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/driver/si1133/src/sl_si1133.o

$(OUTPUT_DIR)/sdk/hardware/driver/si70xx/src/sl_si70xx.o: $(SDK_PATH)/hardware/driver/si70xx/src/sl_si70xx.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/driver/si70xx/src/sl_si70xx.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/driver/si70xx/src/sl_si70xx.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/driver/si70xx/src/sl_si70xx.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/driver/si70xx/src/sl_si70xx.o

$(OUTPUT_DIR)/sdk/hardware/driver/si7210/src/sl_si7210.o: $(SDK_PATH)/hardware/driver/si7210/src/sl_si7210.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/hardware/driver/si7210/src/sl_si7210.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/hardware/driver/si7210/src/sl_si7210.c
CDEPS += $(OUTPUT_DIR)/sdk/hardware/driver/si7210/src/sl_si7210.d
OBJS += $(OUTPUT_DIR)/sdk/hardware/driver/si7210/src/sl_si7210.o

$(OUTPUT_DIR)/sdk/platform/bootloader/api/btl_interface.o: $(SDK_PATH)/platform/bootloader/api/btl_interface.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/bootloader/api/btl_interface.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/bootloader/api/btl_interface.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/bootloader/api/btl_interface.d
OBJS += $(OUTPUT_DIR)/sdk/platform/bootloader/api/btl_interface.o

$(OUTPUT_DIR)/sdk/platform/bootloader/api/btl_interface_storage.o: $(SDK_PATH)/platform/bootloader/api/btl_interface_storage.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/bootloader/api/btl_interface_storage.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/bootloader/api/btl_interface_storage.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/bootloader/api/btl_interface_storage.d
OBJS += $(OUTPUT_DIR)/sdk/platform/bootloader/api/btl_interface_storage.o

$(OUTPUT_DIR)/sdk/platform/bootloader/app_properties/app_properties.o: $(SDK_PATH)/platform/bootloader/app_properties/app_properties.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/bootloader/app_properties/app_properties.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/bootloader/app_properties/app_properties.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/bootloader/app_properties/app_properties.d
OBJS += $(OUTPUT_DIR)/sdk/platform/bootloader/app_properties/app_properties.o

$(OUTPUT_DIR)/sdk/platform/common/src/sl_assert.o: $(SDK_PATH)/platform/common/src/sl_assert.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/common/src/sl_assert.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/common/src/sl_assert.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_assert.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_assert.o

$(OUTPUT_DIR)/sdk/platform/common/src/sl_slist.o: $(SDK_PATH)/platform/common/src/sl_slist.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/common/src/sl_slist.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/common/src/sl_slist.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_slist.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_slist.o

$(OUTPUT_DIR)/sdk/platform/common/src/sl_string.o: $(SDK_PATH)/platform/common/src/sl_string.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/common/src/sl_string.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/common/src/sl_string.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_string.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_string.o

$(OUTPUT_DIR)/sdk/platform/common/src/sl_syscalls.o: $(SDK_PATH)/platform/common/src/sl_syscalls.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/common/src/sl_syscalls.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/common/src/sl_syscalls.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_syscalls.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/src/sl_syscalls.o

$(OUTPUT_DIR)/sdk/platform/common/toolchain/src/sl_memory.o: $(SDK_PATH)/platform/common/toolchain/src/sl_memory.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/common/toolchain/src/sl_memory.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/common/toolchain/src/sl_memory.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/common/toolchain/src/sl_memory.d
OBJS += $(OUTPUT_DIR)/sdk/platform/common/toolchain/src/sl_memory.o

$(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFR32BG22/Source/startup_efr32bg22.o: $(SDK_PATH)/platform/Device/SiliconLabs/EFR32BG22/Source/startup_efr32bg22.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/Device/SiliconLabs/EFR32BG22/Source/startup_efr32bg22.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/Device/SiliconLabs/EFR32BG22/Source/startup_efr32bg22.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFR32BG22/Source/startup_efr32bg22.d
OBJS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFR32BG22/Source/startup_efr32bg22.o

$(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFR32BG22/Source/system_efr32bg22.o: $(SDK_PATH)/platform/Device/SiliconLabs/EFR32BG22/Source/system_efr32bg22.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/Device/SiliconLabs/EFR32BG22/Source/system_efr32bg22.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/Device/SiliconLabs/EFR32BG22/Source/system_efr32bg22.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFR32BG22/Source/system_efr32bg22.d
OBJS += $(OUTPUT_DIR)/sdk/platform/Device/SiliconLabs/EFR32BG22/Source/system_efr32bg22.o

$(OUTPUT_DIR)/sdk/platform/driver/button/src/sl_button.o: $(SDK_PATH)/platform/driver/button/src/sl_button.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/driver/button/src/sl_button.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/driver/button/src/sl_button.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/driver/button/src/sl_button.d
OBJS += $(OUTPUT_DIR)/sdk/platform/driver/button/src/sl_button.o

$(OUTPUT_DIR)/sdk/platform/driver/button/src/sl_simple_button.o: $(SDK_PATH)/platform/driver/button/src/sl_simple_button.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/driver/button/src/sl_simple_button.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/driver/button/src/sl_simple_button.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/driver/button/src/sl_simple_button.d
OBJS += $(OUTPUT_DIR)/sdk/platform/driver/button/src/sl_simple_button.o

$(OUTPUT_DIR)/sdk/platform/driver/debug/src/sl_debug_swo.o: $(SDK_PATH)/platform/driver/debug/src/sl_debug_swo.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/driver/debug/src/sl_debug_swo.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/driver/debug/src/sl_debug_swo.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/driver/debug/src/sl_debug_swo.d
OBJS += $(OUTPUT_DIR)/sdk/platform/driver/debug/src/sl_debug_swo.o

$(OUTPUT_DIR)/sdk/platform/driver/i2cspm/src/sl_i2cspm.o: $(SDK_PATH)/platform/driver/i2cspm/src/sl_i2cspm.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/driver/i2cspm/src/sl_i2cspm.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/driver/i2cspm/src/sl_i2cspm.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/driver/i2cspm/src/sl_i2cspm.d
OBJS += $(OUTPUT_DIR)/sdk/platform/driver/i2cspm/src/sl_i2cspm.o

$(OUTPUT_DIR)/sdk/platform/driver/leddrv/src/sl_led.o: $(SDK_PATH)/platform/driver/leddrv/src/sl_led.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/driver/leddrv/src/sl_led.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/driver/leddrv/src/sl_led.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/driver/leddrv/src/sl_led.d
OBJS += $(OUTPUT_DIR)/sdk/platform/driver/leddrv/src/sl_led.o

$(OUTPUT_DIR)/sdk/platform/driver/leddrv/src/sl_simple_led.o: $(SDK_PATH)/platform/driver/leddrv/src/sl_simple_led.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/driver/leddrv/src/sl_simple_led.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/driver/leddrv/src/sl_simple_led.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/driver/leddrv/src/sl_simple_led.d
OBJS += $(OUTPUT_DIR)/sdk/platform/driver/leddrv/src/sl_simple_led.o

$(OUTPUT_DIR)/sdk/platform/emdrv/dmadrv/src/dmadrv.o: $(SDK_PATH)/platform/emdrv/dmadrv/src/dmadrv.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emdrv/dmadrv/src/dmadrv.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emdrv/dmadrv/src/dmadrv.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emdrv/dmadrv/src/dmadrv.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emdrv/dmadrv/src/dmadrv.o

$(OUTPUT_DIR)/sdk/platform/emdrv/gpiointerrupt/src/gpiointerrupt.o: $(SDK_PATH)/platform/emdrv/gpiointerrupt/src/gpiointerrupt.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emdrv/gpiointerrupt/src/gpiointerrupt.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emdrv/gpiointerrupt/src/gpiointerrupt.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emdrv/gpiointerrupt/src/gpiointerrupt.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emdrv/gpiointerrupt/src/gpiointerrupt.o

$(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_default_common_linker.o: $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_default_common_linker.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_default_common_linker.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_default_common_linker.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_default_common_linker.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_default_common_linker.o

$(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_hal_flash.o: $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_hal_flash.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_hal_flash.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_hal_flash.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_hal_flash.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_hal_flash.o

$(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_lock.o: $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_lock.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_lock.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emdrv/nvm3/src/nvm3_lock.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_lock.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emdrv/nvm3/src/nvm3_lock.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_burtc.o: $(SDK_PATH)/platform/emlib/src/em_burtc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_burtc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_burtc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_burtc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_burtc.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_cmu.o: $(SDK_PATH)/platform/emlib/src/em_cmu.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_cmu.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_cmu.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_cmu.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_cmu.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_core.o: $(SDK_PATH)/platform/emlib/src/em_core.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_core.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_core.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_core.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_core.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_dbg.o: $(SDK_PATH)/platform/emlib/src/em_dbg.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_dbg.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_dbg.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_dbg.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_dbg.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_emu.o: $(SDK_PATH)/platform/emlib/src/em_emu.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_emu.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_emu.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_emu.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_emu.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_eusart.o: $(SDK_PATH)/platform/emlib/src/em_eusart.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_eusart.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_eusart.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_eusart.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_eusart.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpcrc.o: $(SDK_PATH)/platform/emlib/src/em_gpcrc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_gpcrc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_gpcrc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpcrc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpcrc.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpio.o: $(SDK_PATH)/platform/emlib/src/em_gpio.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_gpio.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_gpio.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpio.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_gpio.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_i2c.o: $(SDK_PATH)/platform/emlib/src/em_i2c.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_i2c.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_i2c.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_i2c.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_i2c.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_iadc.o: $(SDK_PATH)/platform/emlib/src/em_iadc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_iadc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_iadc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_iadc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_iadc.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_ldma.o: $(SDK_PATH)/platform/emlib/src/em_ldma.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_ldma.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_ldma.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_ldma.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_ldma.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_letimer.o: $(SDK_PATH)/platform/emlib/src/em_letimer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_letimer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_letimer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_letimer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_letimer.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_msc.o: $(SDK_PATH)/platform/emlib/src/em_msc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_msc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_msc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_msc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_msc.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_pdm.o: $(SDK_PATH)/platform/emlib/src/em_pdm.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_pdm.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_pdm.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_pdm.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_pdm.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_prs.o: $(SDK_PATH)/platform/emlib/src/em_prs.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_prs.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_prs.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_prs.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_prs.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_rmu.o: $(SDK_PATH)/platform/emlib/src/em_rmu.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_rmu.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_rmu.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_rmu.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_rmu.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_rtcc.o: $(SDK_PATH)/platform/emlib/src/em_rtcc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_rtcc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_rtcc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_rtcc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_rtcc.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_se.o: $(SDK_PATH)/platform/emlib/src/em_se.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_se.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_se.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_se.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_se.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_system.o: $(SDK_PATH)/platform/emlib/src/em_system.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_system.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_system.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_system.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_system.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_timer.o: $(SDK_PATH)/platform/emlib/src/em_timer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_timer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_timer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_timer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_timer.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_usart.o: $(SDK_PATH)/platform/emlib/src/em_usart.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_usart.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_usart.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_usart.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_usart.o

$(OUTPUT_DIR)/sdk/platform/emlib/src/em_wdog.o: $(SDK_PATH)/platform/emlib/src/em_wdog.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/emlib/src/em_wdog.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/emlib/src/em_wdog.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_wdog.d
OBJS += $(OUTPUT_DIR)/sdk/platform/emlib/src/em_wdog.o

$(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.o: $(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.d
OBJS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/pa-conversions/pa_conversions_efr32.o

$(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/pa-conversions/pa_curves_efr32.o: $(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/pa_curves_efr32.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/pa_curves_efr32.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/radio/rail_lib/plugin/pa-conversions/pa_curves_efr32.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/pa-conversions/pa_curves_efr32.d
OBJS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/pa-conversions/pa_curves_efr32.o

$(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.o: $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.d
OBJS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_power_manager_init/sl_rail_util_power_manager_init.o

$(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.o: $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.d
OBJS += $(OUTPUT_DIR)/sdk/platform/radio/rail_lib/plugin/rail_util_pti/sl_rail_util_pti.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_attestation.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_attestation.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_attestation.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_attestation.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_attestation.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_attestation.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_cipher.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_cipher.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_cipher.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_cipher.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_cipher.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_cipher.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_entropy.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_entropy.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_entropy.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_entropy.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_entropy.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_entropy.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_hash.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_hash.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_hash.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_hash.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_hash.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_hash.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_key_derivation.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_key_derivation.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_key_derivation.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_key_derivation.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_key_derivation.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_key_derivation.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_key_handling.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_key_handling.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_key_handling.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_key_handling.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_key_handling.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_key_handling.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_signature.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_signature.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_signature.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_signature.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_signature.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_signature.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_util.o: $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_util.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_util.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/se_manager/src/sl_se_manager_util.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_util.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/se_manager/src/sl_se_manager_util.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/ba414ep_config.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/ba414ep_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/ba414ep_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/ba414ep_config.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/ba414ep_config.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/ba414ep_config.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/ba431_config.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/ba431_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/ba431_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/ba431_config.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/ba431_config.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/ba431_config.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/cryptodma_internal.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/cryptodma_internal.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/cryptodma_internal.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/cryptodma_internal.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/cryptodma_internal.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/cryptodma_internal.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/cryptolib_types.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/cryptolib_types.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/cryptolib_types.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/cryptolib_types.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/cryptolib_types.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/cryptolib_types.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_aes.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_aes.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_aes.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_aes.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_aes.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_aes.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_blk_cipher.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_blk_cipher.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_blk_cipher.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_blk_cipher.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_blk_cipher.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_blk_cipher.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_dh_alg.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_dh_alg.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_dh_alg.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_dh_alg.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_dh_alg.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_dh_alg.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecc_curves.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecc_curves.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecc_curves.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecc_curves.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecc_curves.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecc_curves.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecc_keygen_alg.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecc_keygen_alg.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecc_keygen_alg.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecc_keygen_alg.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecc_keygen_alg.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecc_keygen_alg.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecdsa_alg.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecdsa_alg.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecdsa_alg.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecdsa_alg.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecdsa_alg.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_ecdsa_alg.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_hash.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_hash.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_hash.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_hash.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_hash.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_hash.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_math.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_math.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_math.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_math.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_math.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_math.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_memcmp.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_memcmp.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_memcmp.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_memcmp.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_memcmp.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_memcmp.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_memcpy.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_memcpy.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_memcpy.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_memcpy.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_memcpy.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_memcpy.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_primitives.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_primitives.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_primitives.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_primitives.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_primitives.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_primitives.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_rng.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_rng.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_rng.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_rng.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_rng.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_rng.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_trng.o: $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_trng.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_trng.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_cryptoacc_library/src/sx_trng.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_trng.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_cryptoacc_library/src/sx_trng.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/cryptoacc_aes.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/cryptoacc_aes.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/cryptoacc_aes.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/cryptoacc_aes.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/cryptoacc_aes.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/cryptoacc_aes.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/cryptoacc_gcm.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/cryptoacc_gcm.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/cryptoacc_gcm.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/cryptoacc_gcm.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/cryptoacc_gcm.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/cryptoacc_gcm.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ccm.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ccm.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ccm.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ccm.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ccm.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ccm.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_cmac.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ecdsa_ecdh.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ecdsa_ecdh.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ecdsa_ecdh.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ecdsa_ecdh.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ecdsa_ecdh.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/mbedtls_ecdsa_ecdh.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_mbedtls.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sl_psa_crypto.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.o: $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_mbedtls_support/src/sli_psa_crypto.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_radioaes.o: $(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_radioaes.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_radioaes.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_radioaes.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_radioaes.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_protocol_crypto/src/sli_protocol_crypto_radioaes.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_protocol_crypto/src/sli_radioaes_management.o: $(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src/sli_radioaes_management.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src/sli_radioaes_management.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_protocol_crypto/src/sli_radioaes_management.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_protocol_crypto/src/sli_radioaes_management.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_protocol_crypto/src/sli_radioaes_management.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/cryptoacc_management.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/cryptoacc_management.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/cryptoacc_management.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/cryptoacc_management.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/cryptoacc_management.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/cryptoacc_management.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sl_psa_its_nvm3.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sl_psa_its_nvm3.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sl_psa_its_nvm3.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sl_psa_its_nvm3.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sl_psa_its_nvm3.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sl_psa_its_nvm3.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_driver_trng.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_driver_trng.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_driver_trng.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_driver_trng.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_driver_trng.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_driver_trng.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_aead.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_aead.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_aead.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_aead.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_aead.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_aead.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_cipher.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_cipher.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_cipher.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_cipher.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_cipher.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_cipher.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_hash.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_hash.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_hash.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_hash.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_hash.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_hash.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_key_derivation.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_key_derivation.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_key_derivation.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_key_derivation.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_key_derivation.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_key_derivation.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_key_management.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_key_management.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_key_management.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_key_management.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_key_management.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_key_management.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_mac.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_mac.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_mac.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_mac.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_mac.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_mac.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_signature.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_signature.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_signature.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_signature.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_signature.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_cryptoacc_transparent_driver_signature.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_common.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_driver_init.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_psa_trng.o

$(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.o: $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.d
OBJS += $(OUTPUT_DIR)/sdk/platform/security/sl_component/sl_psa_driver/src/sli_se_version_dependencies.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_dcdc_s2.o: $(SDK_PATH)/platform/service/device_init/src/sl_device_init_dcdc_s2.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_init/src/sl_device_init_dcdc_s2.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_init/src/sl_device_init_dcdc_s2.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_dcdc_s2.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_dcdc_s2.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_emu_s2.o: $(SDK_PATH)/platform/service/device_init/src/sl_device_init_emu_s2.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_init/src/sl_device_init_emu_s2.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_init/src/sl_device_init_emu_s2.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_emu_s2.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_emu_s2.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_hfxo_s2.o: $(SDK_PATH)/platform/service/device_init/src/sl_device_init_hfxo_s2.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_init/src/sl_device_init_hfxo_s2.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_init/src/sl_device_init_hfxo_s2.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_hfxo_s2.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_hfxo_s2.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_lfrco.o: $(SDK_PATH)/platform/service/device_init/src/sl_device_init_lfrco.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_init/src/sl_device_init_lfrco.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_init/src/sl_device_init_lfrco.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_lfrco.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_lfrco.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_lfxo_s2.o: $(SDK_PATH)/platform/service/device_init/src/sl_device_init_lfxo_s2.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_init/src/sl_device_init_lfxo_s2.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_init/src/sl_device_init_lfxo_s2.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_lfxo_s2.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_lfxo_s2.o

$(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_nvic.o: $(SDK_PATH)/platform/service/device_init/src/sl_device_init_nvic.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/device_init/src/sl_device_init_nvic.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/device_init/src/sl_device_init_nvic.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_nvic.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/device_init/src/sl_device_init_nvic.o

$(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream.o: $(SDK_PATH)/platform/service/iostream/src/sl_iostream.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/iostream/src/sl_iostream.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/iostream/src/sl_iostream.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream.o

$(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_retarget_stdio.o: $(SDK_PATH)/platform/service/iostream/src/sl_iostream_retarget_stdio.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/iostream/src/sl_iostream_retarget_stdio.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/iostream/src/sl_iostream_retarget_stdio.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_retarget_stdio.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_retarget_stdio.o

$(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_stdlib_config.o: $(SDK_PATH)/platform/service/iostream/src/sl_iostream_stdlib_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/iostream/src/sl_iostream_stdlib_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/iostream/src/sl_iostream_stdlib_config.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_stdlib_config.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_stdlib_config.o

$(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_uart.o: $(SDK_PATH)/platform/service/iostream/src/sl_iostream_uart.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/iostream/src/sl_iostream_uart.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/iostream/src/sl_iostream_uart.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_uart.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_uart.o

$(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_usart.o: $(SDK_PATH)/platform/service/iostream/src/sl_iostream_usart.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/iostream/src/sl_iostream_usart.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/iostream/src/sl_iostream_usart.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_usart.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/iostream/src/sl_iostream_usart.o

$(OUTPUT_DIR)/sdk/platform/service/mpu/src/sl_mpu.o: $(SDK_PATH)/platform/service/mpu/src/sl_mpu.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/mpu/src/sl_mpu.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/mpu/src/sl_mpu.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/mpu/src/sl_mpu.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/mpu/src/sl_mpu.o

$(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager.o: $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager.o

$(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_debug.o: $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_debug.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_debug.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_debug.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_debug.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_debug.o

$(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_hal_s2.o: $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_hal_s2.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_hal_s2.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/power_manager/src/sl_power_manager_hal_s2.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_hal_s2.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/power_manager/src/sl_power_manager_hal_s2.o

$(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer.o: $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer.o

$(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.o: $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_burtc.o

$(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_prortc.o: $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_prortc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_prortc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_prortc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_prortc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_prortc.o

$(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_rtcc.o: $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_rtcc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_rtcc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_rtcc.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_rtcc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_rtcc.o

$(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.o: $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/sleeptimer/src/sl_sleeptimer_hal_timer.o

$(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_init.o: $(SDK_PATH)/platform/service/system/src/sl_system_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/system/src/sl_system_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/system/src/sl_system_init.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_init.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_init.o

$(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_process_action.o: $(SDK_PATH)/platform/service/system/src/sl_system_process_action.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/system/src/sl_system_process_action.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/system/src/sl_system_process_action.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_process_action.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/system/src/sl_system_process_action.o

$(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay.o: $(SDK_PATH)/platform/service/udelay/src/sl_udelay.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/udelay/src/sl_udelay.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/platform/service/udelay/src/sl_udelay.c
CDEPS += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay.o

$(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay_armv6m_gcc.o: $(SDK_PATH)/platform/service/udelay/src/sl_udelay_armv6m_gcc.S
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/platform/service/udelay/src/sl_udelay_armv6m_gcc.S'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(ASMFLAGS) -c -o $@ $(SDK_PATH)/platform/service/udelay/src/sl_udelay_armv6m_gcc.S
ASMDEPS_S += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay_armv6m_gcc.d
OBJS += $(OUTPUT_DIR)/sdk/platform/service/udelay/src/sl_udelay_armv6m_gcc.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_apploader_util_s2.o: $(SDK_PATH)/protocol/bluetooth/src/sl_apploader_util_s2.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sl_apploader_util_s2.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sl_apploader_util_s2.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_apploader_util_s2.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_apploader_util_s2.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_bt_stack_init.o: $(SDK_PATH)/protocol/bluetooth/src/sl_bt_stack_init.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sl_bt_stack_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sl_bt_stack_init.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_bt_stack_init.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sl_bt_stack_init.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_accept_list_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_accept_list_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_accept_list_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_accept_list_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_accept_list_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_accept_list_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_advertiser_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_advertiser_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_advertiser_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_advertiser_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_advertiser_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_advertiser_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_connection_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_connection_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_connection_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_connection_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_connection_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_connection_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_dynamic_gattdb_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_l2cap_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_l2cap_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_l2cap_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_l2cap_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_l2cap_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_l2cap_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_pawr_advertiser_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_periodic_adv_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_periodic_adv_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_periodic_adv_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_periodic_adv_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_periodic_adv_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_periodic_adv_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_periodic_advertiser_config.o

$(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_sync_config.o: $(SDK_PATH)/protocol/bluetooth/src/sli_bt_sync_config.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/protocol/bluetooth/src/sli_bt_sync_config.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/protocol/bluetooth/src/sli_bt_sync_config.c
CDEPS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_sync_config.d
OBJS += $(OUTPUT_DIR)/sdk/protocol/bluetooth/src/sli_bt_sync_config.o

$(OUTPUT_DIR)/sdk/util/silicon_labs/silabs_core/memory_manager/sl_malloc.o: $(SDK_PATH)/util/silicon_labs/silabs_core/memory_manager/sl_malloc.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/silicon_labs/silabs_core/memory_manager/sl_malloc.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/silicon_labs/silabs_core/memory_manager/sl_malloc.c
CDEPS += $(OUTPUT_DIR)/sdk/util/silicon_labs/silabs_core/memory_manager/sl_malloc.d
OBJS += $(OUTPUT_DIR)/sdk/util/silicon_labs/silabs_core/memory_manager/sl_malloc.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher.o: $(SDK_PATH)/util/third_party/mbedtls/library/cipher.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/cipher.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/cipher.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher_wrap.o: $(SDK_PATH)/util/third_party/mbedtls/library/cipher_wrap.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/cipher_wrap.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/cipher_wrap.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher_wrap.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/cipher_wrap.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/constant_time.o: $(SDK_PATH)/util/third_party/mbedtls/library/constant_time.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/constant_time.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/constant_time.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/constant_time.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/constant_time.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform.o: $(SDK_PATH)/util/third_party/mbedtls/library/platform.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/platform.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/platform.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform_util.o: $(SDK_PATH)/util/third_party/mbedtls/library/platform_util.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/platform_util.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/platform_util.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform_util.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/platform_util.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_aead.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_aead.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_aead.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_aead.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_aead.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_aead.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_cipher.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_cipher.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_cipher.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_cipher.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_cipher.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_cipher.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_client.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_client.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_client.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_client.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_client.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_client.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_driver_wrappers_no_static.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_driver_wrappers_no_static.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_driver_wrappers_no_static.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_driver_wrappers_no_static.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_driver_wrappers_no_static.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_driver_wrappers_no_static.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_ecp.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_ecp.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_ecp.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_ecp.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_ecp.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_ecp.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_ffdh.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_ffdh.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_ffdh.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_ffdh.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_ffdh.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_ffdh.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_hash.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_hash.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_hash.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_hash.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_hash.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_hash.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_mac.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_mac.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_mac.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_mac.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_mac.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_mac.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_pake.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_pake.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_pake.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_pake.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_pake.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_pake.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_rsa.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_rsa.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_rsa.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_rsa.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_rsa.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_rsa.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_se.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_se.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_se.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_se.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_se.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_se.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_slot_management.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_slot_management.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_slot_management.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_slot_management.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_slot_management.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_slot_management.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_storage.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_storage.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_storage.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_crypto_storage.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_storage.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_crypto_storage.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_util.o: $(SDK_PATH)/util/third_party/mbedtls/library/psa_util.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/psa_util.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/psa_util.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_util.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/psa_util.o

$(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/threading.o: $(SDK_PATH)/util/third_party/mbedtls/library/threading.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/mbedtls/library/threading.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/mbedtls/library/threading.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/threading.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/mbedtls/library/threading.o

$(OUTPUT_DIR)/sdk/util/third_party/printf/printf.o: $(SDK_PATH)/util/third_party/printf/printf.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/printf/printf.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/printf/printf.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/printf/printf.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/printf/printf.o

$(OUTPUT_DIR)/sdk/util/third_party/printf/src/iostream_printf.o: $(SDK_PATH)/util/third_party/printf/src/iostream_printf.c
	@$(POSIX_TOOL_PATH)echo 'Building $(SDK_PATH)/util/third_party/printf/src/iostream_printf.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ $(SDK_PATH)/util/third_party/printf/src/iostream_printf.c
CDEPS += $(OUTPUT_DIR)/sdk/util/third_party/printf/src/iostream_printf.d
OBJS += $(OUTPUT_DIR)/sdk/util/third_party/printf/src/iostream_printf.o

$(OUTPUT_DIR)/project/app.o: app.c
	@$(POSIX_TOOL_PATH)echo 'Building app.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ app.c
CDEPS += $(OUTPUT_DIR)/project/app.d
OBJS += $(OUTPUT_DIR)/project/app.o

$(OUTPUT_DIR)/project/autogen/gatt_db.o: autogen/gatt_db.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/gatt_db.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/gatt_db.c
CDEPS += $(OUTPUT_DIR)/project/autogen/gatt_db.d
OBJS += $(OUTPUT_DIR)/project/autogen/gatt_db.o

$(OUTPUT_DIR)/project/autogen/sl_bluetooth.o: autogen/sl_bluetooth.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_bluetooth.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_bluetooth.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_bluetooth.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_bluetooth.o

$(OUTPUT_DIR)/project/autogen/sl_board_default_init.o: autogen/sl_board_default_init.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_board_default_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_board_default_init.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_board_default_init.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_board_default_init.o

$(OUTPUT_DIR)/project/autogen/sl_device_init_clocks.o: autogen/sl_device_init_clocks.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_device_init_clocks.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_device_init_clocks.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_device_init_clocks.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_device_init_clocks.o

$(OUTPUT_DIR)/project/autogen/sl_event_handler.o: autogen/sl_event_handler.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_event_handler.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_event_handler.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_event_handler.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_event_handler.o

$(OUTPUT_DIR)/project/autogen/sl_i2cspm_init.o: autogen/sl_i2cspm_init.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_i2cspm_init.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_i2cspm_init.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_i2cspm_init.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_i2cspm_init.o

$(OUTPUT_DIR)/project/autogen/sl_iostream_handles.o: autogen/sl_iostream_handles.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_iostream_handles.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_iostream_handles.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_iostream_handles.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_iostream_handles.o

$(OUTPUT_DIR)/project/autogen/sl_iostream_init_usart_instances.o: autogen/sl_iostream_init_usart_instances.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_iostream_init_usart_instances.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_iostream_init_usart_instances.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_iostream_init_usart_instances.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_iostream_init_usart_instances.o

$(OUTPUT_DIR)/project/autogen/sl_power_manager_handler.o: autogen/sl_power_manager_handler.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_power_manager_handler.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_power_manager_handler.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_power_manager_handler.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_power_manager_handler.o

$(OUTPUT_DIR)/project/autogen/sl_simple_button_instances.o: autogen/sl_simple_button_instances.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_simple_button_instances.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_simple_button_instances.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_simple_button_instances.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_simple_button_instances.o

$(OUTPUT_DIR)/project/autogen/sl_simple_led_instances.o: autogen/sl_simple_led_instances.c
	@$(POSIX_TOOL_PATH)echo 'Building autogen/sl_simple_led_instances.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ autogen/sl_simple_led_instances.c
CDEPS += $(OUTPUT_DIR)/project/autogen/sl_simple_led_instances.d
OBJS += $(OUTPUT_DIR)/project/autogen/sl_simple_led_instances.o

$(OUTPUT_DIR)/project/main.o: main.c
	@$(POSIX_TOOL_PATH)echo 'Building main.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ main.c
CDEPS += $(OUTPUT_DIR)/project/main.d
OBJS += $(OUTPUT_DIR)/project/main.o

$(OUTPUT_DIR)/project/sl_gatt_service_device_information.o: sl_gatt_service_device_information.c
	@$(POSIX_TOOL_PATH)echo 'Building sl_gatt_service_device_information.c'
	@$(POSIX_TOOL_PATH)mkdir -p $(@D)
	$(ECHO)$(CC) $(CFLAGS) -c -o $@ sl_gatt_service_device_information.c
CDEPS += $(OUTPUT_DIR)/project/sl_gatt_service_device_information.d
OBJS += $(OUTPUT_DIR)/project/sl_gatt_service_device_information.o

# Automatically-generated Simplicity Studio Metadata
# Please do not edit or delete these lines!
# SIMPLICITY_STUDIO_METADATA=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END_SIMPLICITY_STUDIO_METADATA
# END OF METADATA