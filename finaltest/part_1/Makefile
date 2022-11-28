CXX = g++

TARGET = VanDongVien

TARGET_LIB_A = lib_utils.a

__DIRNAME := $(abspath $(lastword $(dir $(MAKEFILE_LIST))))

__DIR_BUILD = $(__DIRNAME)/build
__DIR_LIBS = $(__DIR_BUILD)/libs
__DIR_UTILS = $(__DIRNAME)/utils

__DIR_LIBA = $(__DIR_LIBS)/$(TARGET_LIB_A)

LIBS_CPP = sort.cpp
LIBS_OBJ = $(LIBS_CPP:.cpp=.o)

MODELS_CPP = van_dong_vien.cpp
MODELS_OBJS = $(MODELS_CPP:.cpp=.o)

MAIN_CPP = main.cpp
MAIN_OBJ = $(MAIN_CPP:.cpp=.o)

vpath %.h $(__DIR_UTILS)
vpath %.cpp $(__DIR_UTILS)

vpath %.h $(__DIRNAME)/models
vpath %.cpp $(__DIRNAME)/models

CPPFLAGS += $(addprefix -I , $(__DIR_UTILS))

all: build_lib $(TARGET) run

build_lib: $(LIBS_OBJ) $(MODELS_OBJS) 
	@ar rcs $(__DIR_LIBS)/$(TARGET_LIB_A) $(LIBS_OBJ) $(MODELS_OBJS)

$(TARGET): $(MAIN_OBJ)
	@g++ $(MAIN_OBJ) $(__DIR_LIBS)/$(TARGET_LIB_A) -o $(__DIR_BUILD)/$(TARGET) 

run:
	@$(__DIR_BUILD)/$(TARGET)