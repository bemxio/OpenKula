# constants
GAME_TARGETS := kula kula3D kulatwo

# phony
.PHONY: all clean $(GAME_TARGETS)

# targets
all: $(GAME_TARGETS)

clean:
	@for directory in $(GAME_TARGETS); do \
		$(MAKE) -C $$directory clean; \
	done

$(GAME_TARGETS):
	@$(MAKE) -C $@ $(filter-out $@,$(MAKECMDGOALS))

# empty rule to avoid "No rule to make target" errors
%:
	@: