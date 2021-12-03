CXX := clang++
CXXFLAGS := -O0

PROJ_PATH := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# INCLUDES := 

SRC_PATH := $(PROJ_PATH)/src
OUT_PATH := $(PROJ_PATH)/out

.PHONY: all clean

all: $(OUT_PATH)/day01 $(OUT_PATH)/day02

$(OUT_PATH)/%: $(SRC_PATH)/%.cpp
	@mkdir -p $(OUT_PATH)
	$(CXX) $(CXXFLAGS) $^ -o $@


clean:
	@rm -rf $(OUT_PATH)