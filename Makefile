TARGET = app

CXX = g++

CXXFLAGS = -std=c++11 -Wall -Wextra -Iinclude `sdl2-config --cflags`
LDFLAGS = `sdl2-config --libs` -lSDL2_gfx

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
	$(CXX) $(OBJECTS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR)

print-%:
	@echo '$*=$($*)'

.PHONY: all clean