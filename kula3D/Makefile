# constants
CC = gcc
CFLAGS = -Wall -fms-extensions
LDLIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

SRC_DIR = src
ASSETS_DIR = assets
BUILD_DIR = build

SOURCES = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(SRC_DIR)/*.h)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
ASSETS = $(wildcard $(ASSETS_DIR)/*)

EXECUTABLE = kula3D

# phony
.PHONY: all clean distclean run

# targets
all: $(BUILD_DIR)/$(EXECUTABLE)

clean:
	$(RM) -r $(BUILD_DIR)

distclean: clean
	$(RM) -r $(ASSETS_DIR)

run: $(BUILD_DIR)/$(EXECUTABLE)
	./$<

# rules
$(BUILD_DIR)/$(EXECUTABLE): $(OBJECTS) | $(ASSETS) $(BUILD_DIR)
	cp -r $(ASSETS_DIR) $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(HEADERS) $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $@