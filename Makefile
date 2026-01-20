# constants
GAME_TARGETS = kula kula3D kulatwo

CMAKE = cmake
PYTHON = python3

BUILD_DIR = build
WIISDSYNC_DIR = ~/.local/share/dolphin-emu/Load/WiiSDSync

# phony
.PHONY: all clean distclean wiisdsync $(GAME_TARGETS)

# targets
all: $(GAME_TARGETS)

clean:
	$(RM) -r $(BUILD_DIR)

distclean: clean
	$(RM) -r $(GAME_TARGETS:%=%/assets)

wiisdsync: $(GAME_TARGETS)
	$(RM) -r $(WIISDSYNC_DIR)/apps/*

	for game in $(GAME_TARGETS); do \
		cp -r $(BUILD_DIR)/$$game/apps/$$game $(WIISDSYNC_DIR)/apps; \
	done

# rules
$(GAME_TARGETS): %: %/assets
	$(CMAKE) -S $@ -B $(BUILD_DIR)/$@ -DCMAKE_BUILD_TYPE=Release && $(CMAKE) --build $(BUILD_DIR)/$@

%/assets:
	$(PYTHON) tools/copy_assets_to_game.py $*