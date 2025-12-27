# constants
GAME_TARGETS = kula kula3D kulatwo
PYTHON = python3

# phony
.PHONY: all $(GAME_TARGETS)

# targets
all: $(GAME_TARGETS)

$(GAME_TARGETS): %: %/assets
	$(MAKE) -C $@ $(filter-out $@,$(MAKECMDGOALS))

%/assets:
	$(PYTHON) tools/copy_assets_to_game.py $*

# empty rule to avoid "No rule to make target" errors
%:
	@: