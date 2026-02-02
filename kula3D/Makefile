# constants
SRC_DIR = src
ASSETS_DIR = assets
OUTPUT_DIR = ../build/kula3D

SRCS = $(wildcard $(SRC_DIR)/*.c) ../mixer/mixer.c
ASSETS = $(patsubst $(ASSETS_DIR)/%,$(OUTPUT_DIR)/assets/%,$(wildcard $(ASSETS_DIR)/*))

NXDK_CFLAGS += -Wall -fms-extensions -O2
NXDK_DIR = ../nxdk
NXDK_SDL = y

XBE_TITLE = Kula\ 3D
GEN_XISO = kula3D-$(shell git rev-parse --short=7 HEAD)-xbox.iso

TARGET += $(ASSETS)

# rules
$(GEN_XISO): $(ASSETS)

$(OUTPUT_DIR)/assets/%: $(ASSETS_DIR)/% | $(OUTPUT_DIR)/assets
	$(VE)cp $< $@

$(OUTPUT_DIR)/assets:
	$(VE)mkdir -p $@

# includes
include $(NXDK_DIR)/Makefile

# targets
distclean: clean
	$(VE)$(RM) -r $(NXDK_DIR)/tools/extract-xiso/build
	$(VE)$(MAKE) -C $(NXDK_DIR)/tools/fp20compiler distclean $(QUIET)
	$(VE)$(MAKE) -C $(NXDK_DIR)/tools/vp20compiler distclean $(QUIET)
	$(VE)$(MAKE) -C $(NXDK_DIR)/tools/cxbe clean $(QUIET)
	$(VE)$(RM) -r $(ASSETS_DIR) $(OUTPUT_DIR)