# constants
GAME_TARGETS = kula kula3D kulatwo

# phony
.PHONY: all $(GAME_TARGETS)

# targets
all: $(GAME_TARGETS)

$(GAME_TARGETS): %: %/assets
	cmake -S $@ -B $@/build && cmake --build $@/build

%/assets:
	python tools/copy_assets_to_game.py $*

# empty rule to avoid "No rule to make target" errors
%:
	@: