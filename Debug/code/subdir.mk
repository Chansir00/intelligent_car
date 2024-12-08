################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../code/KEY.c \
../code/adc.c \
../code/car.c \
../code/encoder.c \
../code/image.c \
../code/motor.c \
../code/uart.c 

COMPILED_SRCS += \
./code/KEY.src \
./code/adc.src \
./code/car.src \
./code/encoder.src \
./code/image.src \
./code/motor.src \
./code/uart.src 

C_DEPS += \
./code/KEY.d \
./code/adc.d \
./code/car.d \
./code/encoder.d \
./code/image.d \
./code/motor.d \
./code/uart.d 

OBJS += \
./code/KEY.o \
./code/adc.o \
./code/car.o \
./code/encoder.o \
./code/image.o \
./code/motor.o \
./code/uart.o 


# Each subdirectory must supply rules for building sources it contributes
code/%.src: ../code/%.c code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
<<<<<<< HEAD
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc26xb "-fD:/Users/64271/AURIX-v1.9.4-workspace2/intel_car/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<" && \
=======
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc26xb "-fX:/TC264_source/camera_car/Debug/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc26xb -Y0 -N0 -Z0 -o "$@" "$<" && \
>>>>>>> ccc3f4231577228addca1a3d483ab8c7f985445d
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/code\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

code/%.o: ./code/%.src code/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-code

clean-code:
	-$(RM) ./code/KEY.d ./code/KEY.o ./code/KEY.src ./code/adc.d ./code/adc.o ./code/adc.src ./code/car.d ./code/car.o ./code/car.src ./code/encoder.d ./code/encoder.o ./code/encoder.src ./code/image.d ./code/image.o ./code/image.src ./code/motor.d ./code/motor.o ./code/motor.src ./code/uart.d ./code/uart.o ./code/uart.src

.PHONY: clean-code

