################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include externals/zlib/src/subdir.mk
-include externals/zlib/obj/subdir.mk
-include externals/tsne/src/subdir.mk
-include externals/tsne/obj/subdir.mk
-include externals/tsne/GPU/src/subdir.mk
-include externals/tsne/CPU/src/subdir.mk
-include externals/libtiff/src/subdir.mk
-include externals/libsvm/src/subdir.mk
-include externals/libsvm/obj/subdir.mk
-include externals/libpng/src/subdir.mk
-include externals/libpng/obj/subdir.mk
-include externals/libnifti/src/subdir.mk
-include externals/libnifti/obj/subdir.mk
-include externals/libnifti/demo/subdir.mk
-include externals/libjpeg/src/subdir.mk
-include externals/libjpeg/obj/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: iris-detection-task

# Tool invocations
iris-detection-task: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++  -o "iris-detection-task" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) iris-detection-task
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
