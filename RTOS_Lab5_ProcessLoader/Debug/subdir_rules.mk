################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
ADC.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/inc/ADC.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"ADC.d_raw" -MT"ADC.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Clock.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/inc/Clock.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"Clock.d_raw" -MT"Clock.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

DFT16.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/DFT16.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"DFT16.d_raw" -MT"DFT16.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

IRDistance.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/IRDistance.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"IRDistance.d_raw" -MT"IRDistance.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Interpreter.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/Interpreter.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"Interpreter.d_raw" -MT"Interpreter.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

LPF.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/LPF.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"LPF.d_raw" -MT"LPF.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

LaunchPad.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/LaunchPad.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"LaunchPad.d_raw" -MT"LaunchPad.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

OS.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/OS.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"OS.d_raw" -MT"OS.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Program.o: ../Program.s $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -gdwarf-3 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Program2.o: ../Program2.s $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -gdwarf-3 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RTOS_FIFO.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/RTOS_FIFO.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"RTOS_FIFO.d_raw" -MT"RTOS_FIFO.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

%.o: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"$(basename $(<F)).d_raw" -MT"$(@)" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RTOS_UART.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/RTOS_UART.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"RTOS_UART.d_raw" -MT"RTOS_UART.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

RTOS_UARTints.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/RTOS_UARTints.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"RTOS_UARTints.d_raw" -MT"RTOS_UARTints.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

SPI.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/SPI.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"SPI.d_raw" -MT"SPI.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

ST7735_SDC.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/ST7735_SDC.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"ST7735_SDC.d_raw" -MT"ST7735_SDC.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TFLuna2.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/TFLuna2.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"TFLuna2.d_raw" -MT"TFLuna2.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

TFLunaCommon.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/TFLunaCommon.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"TFLunaCommon.d_raw" -MT"TFLunaCommon.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

Timer.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/inc/Timer.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"Timer.d_raw" -MT"Timer.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

eDisk.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/eDisk.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"eDisk.d_raw" -MT"eDisk.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

eFile.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/eFile.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"eFile.d_raw" -MT"eFile.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

heap.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/heap.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -D__MSPM0G3507__ -gdwarf-3 -MMD -MP -MF"heap.d_raw" -MT"heap.o" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" -std=c99 $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

osasm.o: C:/UT\ Courses/Spring\ 2026/ECE-445M/MSPM0LabProjects/RTOS_Labs_common/osasm.s $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: Arm Compiler'
	"C:/ti/ccs2040/ccs/tools/compiler/ti-cgt-armllvm_4.0.4.LTS/bin/tiarmclang.exe" -c -march=thumbv6m -mcpu=cortex-m0plus -mfloat-abi=soft -mlittle-endian -mthumb -O0 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader" -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug" -I"C:/ti/mspm0_sdk_2_03_00_07/source/third_party/CMSIS/Core/Include" -I"C:/ti/mspm0_sdk_2_03_00_07/source" -gdwarf-3 -I"C:/UT Courses/Spring 2026/ECE-445M/MSPM0LabProjects/RTOS_Lab5_ProcessLoader/Debug/syscfg" $(GEN_OPTS__FLAG) -o"$@" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


