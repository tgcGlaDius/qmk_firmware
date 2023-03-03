ifeq ($(strip $(NEW_BONGO)), yes)
	OPT_DEFS += -DNEW_BONGO
else
	SRC += lib/bongocat.c
endif
