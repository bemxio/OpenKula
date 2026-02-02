# constants
PYTHON = python3
FFMPEG = ffmpeg

GAME_TARGETS = kula kula3D kulatwo

# phony
.PHONY: all $(GAME_TARGETS)

# targets
all: $(GAME_TARGETS)

$(GAME_TARGETS): %: %/assets
	$(MAKE) $(if $(WINDOWS),-C $@ -f Makefile.win,-C $@) $(filter-out $@,$(MAKECMDGOALS))

%/assets:
	$(PYTHON) tools/copy_assets_to_game.py $*
	$(FFMPEG) -i $*/assets/mortietunes.mp3 $*/assets/mortietunes.wav
	$(RM) $*/assets/mortietunes.mp3

# empty rule to avoid "No rule to make target" errors
%:
	@: