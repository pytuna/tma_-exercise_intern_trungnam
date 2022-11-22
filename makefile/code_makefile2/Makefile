# hehehe
CPP = g++

TARGET_LIB_A = lib_utils.a

TARGET = my_sort_algorithm

__DIRNAME := $(abspath $(lastword $(dir $(MAKEFILE_LIST))))

__DIR_BUILD = $(__DIRNAME)/build
__DIR_LIBS = $(__DIR_BUILD)/libs
__DIR_UTILS = $(__DIRNAME)/utils

__DIR_LIBA = $(__DIR_LIBS)/$(TARGET_LIB_A)

LIBS_CPP = string_ultis.cpp sort_ultis.cpp
LIBS_OBJ = $(patsubst %.cpp, %.o, $(LIBS_CPP))
TEST := $(addprefix $(__DIR_UTILS)/, $(LIBS_CPP:.cpp=.o))

MAIN_CPP = main.cpp
MAIN_OBJ = $(MAIN_CPP:.cpp=.o)

vpath %.h $(__DIR_UTILS)
vpath %.cpp $(__DIR_UTILS)
#vpath = %.cpp $(__DIRNAME)
vpath %.o $(__DIR_UTILS)
#vpath = %.o $(__DIRNAME)

#VPATH = $(__DIR_UTILS) $(__DIRNAME)

CPPFLAGS += $(addprefix -I, $(__DIR_UTILS))

all: test run

build_o: 
	echo $(CPPFLAGS)


test: $(LIBS_OBJ) $(MAIN_OBJ)
	ar rcs $(__DIR_LIBS)/$(TARGET_LIB_A) $(LIBS_OBJ)
	g++ $(MAIN_OBJ) $(__DIR_LIBS)/$(TARGET_LIB_A) -o $(__DIR_BUILD)/$(TARGET) 
run:
	$(__DIR_BUILD)/$(TARGET)

mkdir:
	@mkdir $(__DIRNAME)/build
	@mkdir $(__DIRNAME)/build/libs

