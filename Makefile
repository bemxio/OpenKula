# constants
GAME_TARGETS = kula kula3D kulatwo

# phony
.PHONY: all $(GAME_TARGETS)

# targets
all: $(GAME_TARGETS)

$(GAME_TARGETS): %: %/assets
	$(MAKE) $(if $(WINDOWS),-C $@ -f Makefile.win,-C $@) $(filter-out $@,$(MAKECMDGOALS))

%/assets:
	python tools/copy_assets_to_game.py $*

	ffmpeg -i $*/assets/mortietunes.mp3 $*/assets/mortietunes.wav
	$(RM) $*/assets/mortietunes.mp3

# empty rule to avoid "No rule to make target" errors
%:
	@: