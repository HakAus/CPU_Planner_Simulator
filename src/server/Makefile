# Variables:

# Comando para compilar el main
# main: 
# gcc algorithm/fifo.c algorithm/fifo.h algorithm/sjf.c algorithm/sjf.h algorithm/np_sjf.c algorithm/np_sjf.h algorithm/rr.c algorithm/rr.h record.c record.h process.c process.h evaluate.c evaluate.h clock.c clock.h cpu.c cpu.h cpu_scheduler.c cpu_scheduler.h option.c option.h -g -w

CC = gcc
CFLAGS = -g -w
TARGET = main

SRC = server
ALGOSRC = algorithm
BUILD = _build

MAIN = main.c 
CLEAN = *.o $(TARGET) $(BUILD)

ALGOS = fifo.o sjf.o rr.o hpf.o
OBJS = list.o record.o process.o evaluate.o clock.o cpu.o cpu_scheduler.o job_scheduler.o option.o server.o

all: echocompiling $(TARGET)
	@mkdir -p $(BUILD)
	@mv *.o $(BUILD)
	@echo 'done'
	@echo './main --help' for help

echocompiling:
	@echo 'compiling...'

debug: $(TARGET)

$(TARGET): $(OBJS) $(ALGOS)
	@$(CC) $(MAIN) -o $@ $^ $(CFLAGS) -lpthread

$(OBJS): %.o: %.c 
	@$(CC) -c $< -o $@ $(CFLAGS)

$(ALGOS): %.o: $(ALGOSRC)/%.c
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@rm -f -r $(CLEAN)
	@echo 'removed'