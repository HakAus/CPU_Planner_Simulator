# Variables:

# Comando para compilar el main
# main: 
# 	$(CC) main.c clock.c clock.h process.c process.h cpu.c cpu.h record.c record.h io_device.c io_device.h cpu_scheduler.c cpu_scheduler.h algorithm/fifo.c algorithm/fifo.h algorithm/hpf.c algorithm/hpf.h algorithm/np_hpf.c algorithm/np_hpf.h algorithm/np_sjf.c algorithm/np_sjf.h algorithm/p_hpf.c algorithm/p_hpf.h algorithm/rr.c algorithm/rr.h algorithm/sjf.h algorithm/sjf.c -o main 

CC = gcc
CFLAGS = -g -w
TARGET = main

SRC = server
ALGOSRC = $(SRC)/algorithm
BUILD = _build

MAIN = $(SRC)/main.c
CLEAN = *.o $(TARGET) $(BUILD)

ALGOS = fifo.o sjf.o np_sjf.o rr.o 
OBJS = record.o process.o evaluate.o clock.o cpu.o io_device.o cpu_scheduler.o job_scheduler.o option.o

all: echocompiling $(TARGET)
	@mkdir -p $(BUILD)
	@mv *.o $(BUILD)
	@echo 'done'
	@echo './simulator --help' for help

echocompiling:
	@echo 'compiling...'

debug: $(TARGET)

$(TARGET): $(OBJS) $(ALGOS)
	@$(CC) $(MAIN) -o $@ $^ $(CFLAGS)

$(OBJS): %.o: $(SRC)/%.c
	@$(CC) -c $< -o $@ $(CFLAGS)

$(ALGOS): %.o: $(ALGOSRC)/%.c
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@rm -f -r $(CLEAN)
	@echo 'removed'