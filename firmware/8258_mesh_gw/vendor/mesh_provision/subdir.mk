################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../vendor/mesh_provision/app.c \
../vendor/mesh_provision/app_att.c \
../vendor/mesh_provision/app_l2cap_coc.c \
../vendor/mesh_provision/app_ui.c \
../vendor/mesh_provision/main.c 

OBJS += \
./vendor/mesh_provision/app.o \
./vendor/mesh_provision/app_att.o \
./vendor/mesh_provision/app_l2cap_coc.o \
./vendor/mesh_provision/app_ui.o \
./vendor/mesh_provision/main.o 


# Each subdirectory must supply rules for building sources it contributes
vendor/mesh_provision/%.o: ../vendor/mesh_provision/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"E:\Telink_code\SDK_test\firmware" -I"E:\Telink_code\SDK_test\firmware\proj\include" -I"E:\Telink_code\SDK_test\firmware\vendor\common\mi_api\mijia_ble_api" -I"E:\Telink_code\SDK_test\firmware\vendor\common\mi_api\libs" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\sdk_src\include" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\include" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\cfg" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\data_template" -D__PROJECT_MESH_PRO__=1 -D__telink__ -DCHIP_TYPE=CHIP_TYPE_8258 -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


