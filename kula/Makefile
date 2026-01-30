# constants
SRC_DIR = src
ASSETS_DIR = assets
OUTPUT_DIR = ../build/kula

SRCS = $(wildcard $(SRC_DIR)/*.c)
ASSETS = $(patsubst $(ASSETS_DIR)/%,$(OUTPUT_DIR)/assets/%,$(wildcard $(ASSETS_DIR)/*))

NXDK_DIR = ../nxdk
NXDK_SDL = y

XBE_TITLE = Kula
GEN_XISO = kula-$(shell git rev-parse --short=7 HEAD)-xbox.iso

# targets
$(GEN_XISO): $(ASSETS)

$(OUTPUT_DIR)/assets/%: $(ASSETS_DIR)/%
	$(VE)cp $< $@

TARGET += $(ASSETS)

# includes
include $(NXDK_DIR)/Makefile