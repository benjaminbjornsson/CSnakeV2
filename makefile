SRC_DIR := src
OBJ_DIR := obj
BUILD_DIR := build

EXE := $(BUILD_DIR)/CSnake
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -Wall
LDFLAGS  := -Llib
LDLIBS   := -lm

.PHONY: all clean

all: $(EXE)

$(EXE): $(OBJ) | $(BUILD_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -lncurses -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR) $(OBJ_DIR):
	mkdir -p $@

clean:
	@$(RM) -rv $(BUILD_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)
