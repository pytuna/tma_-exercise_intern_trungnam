CXX = g++
TARGET = singleton

SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)

CUR_PATH = $(abspath $(dir $(MAKEFILE_LIST)))

VPATH = $(CUR_PATH)

.PHONY = all

all: build run

path:
	@echo $(CUR_PATH)

build: $(OBJS)
	@$(CXX) $(OBJS) -o $(TARGET)

run: 
	@./$(TARGET)

clean:
	@rm $(OBJS) $(TARGET)