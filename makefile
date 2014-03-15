###############################################################################
###     
###      makefile template
###---------------------------------------------------------------------------     
###        date     version         author	       modification
###     2013-09-10    0.1       guowei0043001791      created
###############################################################################

C_SRCS := $(wildcard source/*.c) 

OBJS := $(patsubst source/%.c,./source/%.o,$(C_SRCS))

C_DEPS := $(patsubst source/%.c,./source/%.d,$(C_SRCS))

CFLAGS := -fprofile-arcs -ftest-coverage -D_LINUX -D_GTEST -O0 -g3 -c -fmessage-length=0 -MMD -MP
INCLUDE_DIR := -I./include \
               -I./pub

AUTO_CREATE_STUB_MEM := $(shell python stub_mem.py stub_mem.c test ./ ./source)

$(OBJS): source/%.o: source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	python stub_mem.py $< test ./ ./source
	gcc $(CFLAGS) $(INCLUDE_DIR) -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

test: $(OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -fprofile-arcs -ftest-coverage -lpthread -o "test" $(OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

all: test

clean: 
	@rm -rf source/*.o source/*.gcno source/*.gcda source/*.d
	@rm -rf test
