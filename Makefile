CC	= gcc
CFLAGS	= -std=c99 -pedantic -Wall
LIBS	= -lm

$(ID)	: $(ID).c
	@echo "=== COMPILING: ==="
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)
