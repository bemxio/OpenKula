# constants
EE_CFLAGS = -I$(PS2SDK)/ports/include -I$(PS2DEV)/gsKit/include -Wall -fms-extensions
EE_LDFLAGS = -L$(PS2SDK)/ports/lib -L$(PS2DEV)/gsKit/lib

#EE_LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
EE_LIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm -lpatches -lgskit -ldmakit -lps2_drivers -lmodplug -lxmp -lfreetype -lstdc++ -lz -lpng

SRC_DIR = src
ASSETS_DIR = assets

EE_OBJS = $(patsubst %.c,%.o,$(wildcard $(SRC_DIR)/*.c))
EE_BIN = kula.elf

# phony
.PHONY: all clean distclean run

# targets
all: $(EE_BIN)

clean:
	$(RM) -r $(EE_OBJS) $(EE_BIN)

distclean: clean
	$(RM) -r $(ASSETS_DIR)

run: $(EE_BIN)
	ps2client execee host:$<

# includes
include $(PS2SDK)/samples/Makefile.pref
include $(PS2SDK)/samples/Makefile.eeglobal