# Variables:

CC = gcc
CFLAGS = -g -w
TARGET = main

SRC = server
ALGOSRC = algorithm
BUILD = _build

MAIN = main.c 
CLEAN = *.o $(TARGET) $(BUILD)

ALGOS = fifo.o sjf.o rr.o hpf.o
OBJS = list.o process.o evaluate.o clock.o cpu.o cpu_scheduler.o job_scheduler.o option.o server.o

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