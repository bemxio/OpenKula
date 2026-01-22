# constants
CC = gcc
CFLAGS = -Wall -fms-extensions -O2
LDLIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

SRC_DIR = src
ASSETS_DIR = assets
BUILD_DIR = ../build/kula

SOURCES = $(wildcard $(SRC_DIR)/*.c)
HEADERS = $(wildcard $(SRC_DIR)/*.h)
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))
ASSETS = $(wildcard $(ASSETS_DIR)/*)

EXECUTABLE = kula
ARCHIVE = kula-$(shell git rev-parse --short=7 HEAD)-linux-x64.tar.gz

# phony
.PHONY: all dist clean distclean run

# targets
all: $(BUILD_DIR)/$(EXECUTABLE)

dist: $(BUILD_DIR)/$(EXECUTABLE)
	tar -czf $(ARCHIVE) -C $(BUILD_DIR) --exclude='*.o' .

clean:
	$(RM) -r $(BUILD_DIR) *.tar.gz

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