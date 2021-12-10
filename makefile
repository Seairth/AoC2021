CXX := clang++
CXXFLAGS := -O0 -std=c++17

PROJ_PATH := $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

# INCLUDES := 

SRC_PATH := $(PROJ_PATH)/src
OUT_PATH := $(PROJ_PATH)/out

.PHONY: all clean week1 week2

all: week1 week2

week1: $(OUT_PATH)/day01 $(OUT_PATH)/day02 $(OUT_PATH)/day03 $(OUT_PATH)/day04 $(OUT_PATH)/day05 $(OUT_PATH)/day06 $(OUT_PATH)/day07

week2: $(OUT_PATH)/day08 $(OUT_PATH)/day09 $(OUT_PATH)/day10

$(OUT_PATH)/%: $(SRC_PATH)/%.cpp
	@mkdir -p $(OUT_PATH)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	@rm -rf $(OUT_PATH)