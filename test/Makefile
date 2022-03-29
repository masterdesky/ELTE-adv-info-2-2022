BDIR        =   bin
SDIR        =   src
ODIR        =   obj
IDIR        =   include

CC          =   gcc -std=c17
OPTIMIZE    =   -O3 -Wall -Wextra -pedantic
CFLAGS      =   $(OPTIMIZE) -I$(IDIR)
LDFLAGS     =   -lm

_OBJ        =   main.o
OBJ         =   $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/diff: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~