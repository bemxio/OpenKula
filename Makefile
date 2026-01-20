# constants
GAME_TARGETS = kula kula3D kulatwo

# phony
.PHONY: all clean distclean $(GAME_TARGETS)

# targets
all: $(GAME_TARGETS)

clean:
	rm -rf $(GAME_TARGETS:%=%/build)

distclean: clean
	rm -rf $(GAME_TARGETS:%=%/assets)

# rules
$(GAME_TARGETS): %: %/assets
	cmake -S $@ -B $@/build -DCMAKE_BUILD_TYPE=Release && cmake --build $@/build

%/assets:
	python tools/copy_assets_to_game.py $*