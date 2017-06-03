################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.local

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS_QUOTED += \
"../Sources/MCUinit.c" \
"../Sources/MEF.c" \
"../Sources/SCI.c" \
"../Sources/interaccion.c" \
"../Sources/main.c" \
"../Sources/sonido.c" \

C_SRCS += \
../Sources/MCUinit.c \
../Sources/MEF.c \
../Sources/SCI.c \
../Sources/interaccion.c \
../Sources/main.c \
../Sources/sonido.c \

OBJS += \
./Sources/MCUinit_c.obj \
./Sources/MEF_c.obj \
./Sources/SCI_c.obj \
./Sources/interaccion_c.obj \
./Sources/main_c.obj \
./Sources/sonido_c.obj \

OBJS_QUOTED += \
"./Sources/MCUinit_c.obj" \
"./Sources/MEF_c.obj" \
"./Sources/SCI_c.obj" \
"./Sources/interaccion_c.obj" \
"./Sources/main_c.obj" \
"./Sources/sonido_c.obj" \

C_DEPS += \
./Sources/MCUinit_c.d \
./Sources/MEF_c.d \
./Sources/SCI_c.d \
./Sources/interaccion_c.d \
./Sources/main_c.d \
./Sources/sonido_c.d \

OBJS_OS_FORMAT += \
./Sources/MCUinit_c.obj \
./Sources/MEF_c.obj \
./Sources/SCI_c.obj \
./Sources/interaccion_c.obj \
./Sources/main_c.obj \
./Sources/sonido_c.obj \


# Each subdirectory must supply rules for building sources it contributes
Sources/MCUinit_c.obj: ../Sources/MCUinit.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/MCUinit.args" -ObjN="Sources/MCUinit_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/%.d: ../Sources/%.c
	@echo 'Regenerating dependency file: $@'
	
	@echo ' '

Sources/MEF_c.obj: ../Sources/MEF.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/MEF.args" -ObjN="Sources/MEF_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/SCI_c.obj: ../Sources/SCI.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/SCI.args" -ObjN="Sources/SCI_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/interaccion_c.obj: ../Sources/interaccion.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/interaccion.args" -ObjN="Sources/interaccion_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/main_c.obj: ../Sources/main.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/main.args" -ObjN="Sources/main_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '

Sources/sonido_c.obj: ../Sources/sonido.c
	@echo 'Building file: $<'
	@echo 'Invoking: HCS08 Compiler'
	"$(HC08ToolsEnv)/chc08" -ArgFile"Sources/sonido.args" -ObjN="Sources/sonido_c.obj" "$<" -Lm="$(@:%.obj=%.d)" -LmCfg=xilmou
	@echo 'Finished building: $<'
	@echo ' '


