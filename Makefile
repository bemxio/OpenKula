# constants
GAME_TARGETS = kula kula3D kulatwo

CMAKE = cmake
PYTHON = python3

BUILD_DIR = build

# phony
.PHONY: all clean distclean $(GAME_TARGETS)

# targets
all: $(GAME_TARGETS)

clean:
	$(RM) -r $(BUILD_DIR)

distclean: clean
	$(RM) -r $(GAME_TARGETS:%=%/assets)

# rules
$(GAME_TARGETS): %: %/assets
	$(CMAKE) -S $@ -B $(BUILD_DIR)/$@ -DCMAKE_BUILD_TYPE=Release \
		-DSDL2MIXER_DEPS_SHARED=OFF -DSDL2MIXER_MIDI_FLUIDSYNTH=OFF -DSDL2MIXER_WAVPACK=OFF
	$(CMAKE) --build $(BUILD_DIR)/$@

%/assets:
	$(PYTHON) tools/copy_assets_to_game.py $*