# constants
SRC_DIR = src
ASSETS_DIR = assets
OUTPUT_DIR = ../build/kula

SRCS = $(wildcard $(SRC_DIR)/*.c) ../mixer/mixer.c
ASSETS = $(patsubst $(ASSETS_DIR)/%,$(OUTPUT_DIR)/assets/%,$(wildcard $(ASSETS_DIR)/*))

NXDK_CFLAGS += -Wall -O2
NXDK_DIR = ../nxdk
NXDK_SDL = y

XBE_TITLE = Kula
GEN_XISO = kula-$(shell git rev-parse --short=7 HEAD)-xbox.iso

TARGET += $(ASSETS)

# targets
$(GEN_XISO): $(ASSETS)

$(OUTPUT_DIR)/assets/%: $(ASSETS_DIR)/% | $(OUTPUT_DIR)/assets
	$(VE)cp $< $@

$(OUTPUT_DIR)/assets:
	$(VE)mkdir -p $@

# includes
include $(NXDK_DIR)/Makefile