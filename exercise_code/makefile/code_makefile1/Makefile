CPP = g++

TARGET = sort_array

OBJS=main.cpp sort.cpp

DEPS=sort.h

MKFILE_PATH := $(abspath $(lastword $(MAKEFILE_LIST))) # lay duong dan cua makefile

CURRENT_DIR := $(patsubst %/,%,$(dir $(MKFILE_PATH))) #xoa ten makefile

CRD_2 = $(abspath $(dir $(MAKEFILE_LIST)/../)) #lay duong dan thu muc cua makefile

CURRENT_DIR2 :=$(abspath $(dir $(MAKEFILE_LIST))) # nhu cai tren

$(TARGET): $(OBJS)
	$(CPP) -o $@ $(OBJS)

run:
	./$(TARGET)

clean:
	@rm $(TARGET)
	@echo Clean $(TARGET)

test:
	@echo $(MKFILE_PATH)
	@echo $(CURRENT_DIR)
	@echo $(CURRENT_DIR2)
	@echo $(CRD_2)
