C=gcc 
EXE=proyecto

CDEBUG= -g -Wall 
CSTD= -std=c99 

CFLAGS = -Wno-deprecated-register -O2 $(CDEBUG) $(CSTD)
CLIBS = -lm

COBJ = main 

FILES = $(addsuffix .c, $(COBJ))
OBJS = $(addsuffix .o, $(COBJ))

CLEANLIST = $(addsuffix .o, $(COBJ))

.PHONY: all
all: wc

wc: $(FILES)
	$(MAKE) $(OBJS)
	$(CC) $(CFLAGS) -o $(EXE) $(OBJS) $(CLIBS)

.PHONY: clean
clean: