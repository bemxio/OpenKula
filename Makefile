# constants
PYTHON = python3

GAME_TARGETS = kula kula3D kulatwo
WINDOWS = 0

# phony
.PHONY: all $(GAME_TARGETS)

# targets
all: $(GAME_TARGETS)

$(GAME_TARGETS): %: %/assets
	@if [ $(WINDOWS) -eq 1 ]; then \
		$(MAKE) -C $@ -f Makefile.win $(filter-out $@,$(MAKECMDGOALS)); \
	else \
		$(MAKE) -C $@ $(filter-out $@,$(MAKECMDGOALS)); \
	fi

%/assets:
	$(PYTHON) tools/copy_assets_to_game.py $*

# empty rule to avoid "No rule to make target" errors
%:
	@: