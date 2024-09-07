################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drivers/8258/flash/flash_mid011460c8.c \
../drivers/8258/flash/flash_mid1060c8.c \
../drivers/8258/flash/flash_mid11325e.c \
../drivers/8258/flash/flash_mid1160c8.c \
../drivers/8258/flash/flash_mid13325e.c \
../drivers/8258/flash/flash_mid134051.c \
../drivers/8258/flash/flash_mid136085.c \
../drivers/8258/flash/flash_mid1360c8.c \
../drivers/8258/flash/flash_mid1360eb.c \
../drivers/8258/flash/flash_mid14325e.c \
../drivers/8258/flash/flash_mid146085.c \
../drivers/8258/flash/flash_mid1460c8.c 

OBJS += \
./drivers/8258/flash/flash_mid011460c8.o \
./drivers/8258/flash/flash_mid1060c8.o \
./drivers/8258/flash/flash_mid11325e.o \
./drivers/8258/flash/flash_mid1160c8.o \
./drivers/8258/flash/flash_mid13325e.o \
./drivers/8258/flash/flash_mid134051.o \
./drivers/8258/flash/flash_mid136085.o \
./drivers/8258/flash/flash_mid1360c8.o \
./drivers/8258/flash/flash_mid1360eb.o \
./drivers/8258/flash/flash_mid14325e.o \
./drivers/8258/flash/flash_mid146085.o \
./drivers/8258/flash/flash_mid1460c8.o 


# Each subdirectory must supply rules for building sources it contributes
drivers/8258/flash/%.o: ../drivers/8258/flash/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: TC32 Compiler'
	tc32-elf-gcc -ffunction-sections -fdata-sections -I"E:\Telink_code\SDK_test\firmware" -I"E:\Telink_code\SDK_test\firmware\proj\include" -I"E:\Telink_code\SDK_test\firmware\vendor\common\mi_api\mijia_ble_api" -I"E:\Telink_code\SDK_test\firmware\vendor\common\mi_api\libs" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\sdk_src\include" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\include" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\cfg" -I"E:\Telink_code\SDK_test\firmware\vendor\common\llsync\data_template" -D__PROJECT_MESH__=1 -D__telink__ -DCHIP_TYPE=CHIP_TYPE_8258 -Wall -O2 -fpack-struct -fshort-enums -finline-small-functions -std=gnu99 -fshort-wchar -fms-extensions -c -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


