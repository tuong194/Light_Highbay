################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/common/app_beacon.c \
../vendor/common/app_health.c \
../vendor/common/app_heartbeat.c \
../vendor/common/app_privacy_beacon.c \
../vendor/common/app_provison.c \
../vendor/common/app_proxy.c \
../vendor/common/battery_check.c \
../vendor/common/battery_check_827x.c \
../vendor/common/beacon.c \
../vendor/common/ble_ll_ota.c \
../vendor/common/blt_led.c \
../vendor/common/blt_soft_timer.c \
../vendor/common/cmd_interface.c \
../vendor/common/config_model.c \
../vendor/common/directed_forwarding.c \
../vendor/common/dual_mode_adapt.c \
../vendor/common/ev.c \
../vendor/common/factory_reset.c \
../vendor/common/fast_provision_model.c \
../vendor/common/flash_fw_check.c \
../vendor/common/flash_prot.c \
../vendor/common/gateway_common.c \
../vendor/common/generic_model.c \
../vendor/common/gw_node_info.c \
../vendor/common/light.c \
../vendor/common/lighting_model.c \
../vendor/common/lighting_model_HSL.c \
../vendor/common/lighting_model_LC.c \
../vendor/common/lighting_model_xyl.c \
../vendor/common/mesh_access_layer.c \
../vendor/common/mesh_common.c \
../vendor/common/mesh_fn.c \
../vendor/common/mesh_log.c \
../vendor/common/mesh_lpn.c \
../vendor/common/mesh_network_layer.c \
../vendor/common/mesh_node.c \
../vendor/common/mesh_ota.c \
../vendor/common/mesh_ota_initiator.c \
../vendor/common/mesh_property.c \
../vendor/common/mesh_test_cmd.c \
../vendor/common/myprintf.c \
../vendor/common/op_agg_model.c \
../vendor/common/ota_fw_ow.c \
../vendor/common/pair_provision.c \
../vendor/common/remote_prov.c \
../vendor/common/remote_prov_cli.c \
../vendor/common/remote_prov_gatt.c \
../vendor/common/scene.c \
../vendor/common/scheduler.c \
../vendor/common/security_network_beacon.c \
../vendor/common/sensors_model.c \
../vendor/common/smart_provision.c \
../vendor/common/solicitation_rpl_cfg_model.c \
../vendor/common/subnet_bridge.c \
../vendor/common/system_time.c \
../vendor/common/tc32_std_lib_api.c \
../vendor/common/time_model.c \
../vendor/common/tlv_flash.c \
../vendor/common/user_ali.c \
../vendor/common/user_ali_time.c \
../vendor/common/user_du.c \
../vendor/common/user_nmw.c \
../vendor/common/user_proc.c \
../vendor/common/vendor_model.c 

OBJS += \
./vendor/common/app_beacon.o \
./vendor/common/app_health.o \
./vendor/common/app_heartbeat.o \
./vendor/common/app_privacy_beacon.o \
./vendor/common/app_provison.o \
./vendor/common/app_proxy.o \
./vendor/common/battery_check.o \
./vendor/common/battery_check_827x.o \
./vendor/common/beacon.o \
./vendor/common/ble_ll_ota.o \
./vendor/common/blt_led.o \
./vendor/common/blt_soft_timer.o \
./vendor/common/cmd_interface.o \
./vendor/common/config_model.o \
./vendor/common/directed_forwarding.o \
./vendor/common/dual_mode_adapt.o \
./vendor/common/ev.o \
./vendor/common/factory_reset.o \
./vendor/common/fast_provision_model.o \
./vendor/common/flash_fw_check.o \
./vendor/common/flash_prot.o \
./vendor/common/gateway_common.o \
./vendor/common/generic_model.o \
./vendor/common/gw_node_info.o \
./vendor/common/light.o \
./vendor/common/lighting_model.o \
./vendor/common/lighting_model_HSL.o \
./vendor/common/lighting_model_LC.o \
./vendor/common/lighting_model_xyl.o \
./vendor/common/mesh_access_layer.o \
./vendor/common/mesh_common.o \
./vendor/common/mesh_fn.o \
./vendor/common/mesh_log.o \
./vendor/common/mesh_lpn.o \
./vendor/common/mesh_network_layer.o \
./vendor/common/mesh_node.o \
./vendor/common/mesh_ota.o \
./vendor/common/mesh_ota_initiator.o \
./vendor/common/mesh_property.o \
./vendor/common/mesh_test_cmd.o \
./vendor/common/myprintf.o \
./vendor/common/op_agg_model.o \
./vendor/common/ota_fw_ow.o \
./vendor/common/pair_provision.o \
./vendor/common/remote_prov.o \
./vendor/common/remote_prov_cli.o \
./vendor/common/remote_prov_gatt.o \
./vendor/common/scene.o \
./vendor/common/scheduler.o \
./vendor/common/security_network_beacon.o \
./vendor/common/sensors_model.o \
./vendor/common/smart_provision.o \
./vendor/common/solicitation_rpl_cfg_model.o \
./vendor/common/subnet_bridge.o \
./vendor/common/system_time.o \
./vendor/common/tc32_std_lib_api.o \
./vendor/common/time_model.o \
./vendor/common/tlv_flash.o \
./vendor/common/user_ali.o \
./vendor/common/user_ali_time.o \
./vendor/common/user_du.o \
./vendor/common/user_nmw.o \
./vendor/common/user_proc.o \
./vendor/common/vendor_model.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/common/%.o: ../vendor/common/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"E:\Telink_code\SDK_test\firmware" -I"E:\Telink_code\SDK_test\firmware\proj\include" -I"E:\Telink_code\SDK_test\firmware\vendor\common\mi_api\mijia_ble_api" -I"E:\Telink_code\SDK_test\firmware\vendor\common\mi_api\libs" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\sdk_src\include" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\include" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\cfg" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\data_template" -D__PROJECT_MESH__=1 -D__telink__ -DCHIP_TYPE=CHIP_TYPE_8258 -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


