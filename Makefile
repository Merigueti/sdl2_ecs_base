TARGET = app
CXX = g++
PKG_CONFIG = pkg-config

SDL3_CFLAGS = $(shell $(PKG_CONFIG) --cflags sdl3)
SDL3_LIBS = $(shell $(PKG_CONFIG) --libs sdl3)

CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude $(SDL3_CFLAGS)

SRC_DIR = src
BUILD_DIR = build

SOURCES = $(wildcard $(SRC_DIR)/*.cpp) \
          $(wildcard $(SRC_DIR)/ECS/*.cpp) \
          $(wildcard $(SRC_DIR)/Components/*.cpp) \
          $(wildcard $(SRC_DIR)/Systems/*.cpp) \
          $(wildcard $(SRC_DIR)/Game/*.cpp)

OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SOURCES))

$(shell mkdir -p $(BUILD_DIR)/ECS $(BUILD_DIR)/Components $(BUILD_DIR)/Systems $(BUILD_DIR)/Game)

all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@ $(SDL3_LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean
