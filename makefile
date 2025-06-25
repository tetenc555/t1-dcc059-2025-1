CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -I src

SRC_DIR := src
BUILD_DIR := build
BIN := $(BUILD_DIR)/main

SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))

.PHONY: all run clean

all: $(BIN)

run: $(BIN)
	$(BIN)

# Link final
$(BIN): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar objetos
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Cria a pasta build se necessário
$(BUILD_DIR):
	mkdir $(BUILD_DIR)

# Limpar arquivos
clean:
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
