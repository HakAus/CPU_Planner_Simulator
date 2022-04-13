# Variables:
CC = gcc
CFLAGS = -g -w
TARGET = main

SRC = client
BUILD = _build

MAIN = main.c 
CLEAN = *.o $(TARGET) $(BUILD)

OBJS =  option.o reader.o process_generator.o client.o process.o util.o

all: echocompiling $(TARGET)
	@mkdir -p $(BUILD)
	@mv *.o $(BUILD)
	@echo 'done'
	@echo './main --help' for help

echocompiling:
	@echo 'compiling...'

debug: $(TARGET)

$(TARGET): $(OBJS) 
	@$(CC) $(MAIN) -o $@ $^ $(CFLAGS) -lpthread

$(OBJS): %.o: %.c 
	@$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@rm -f -r $(CLEAN)
	@echo 'removed'