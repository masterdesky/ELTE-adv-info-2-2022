BDIR        =   bin
SDIR        =   src
ODIR        =   obj
IDIR        =   include

CC          =   clang -std=c17
OPTIMIZE    =   -O3 -Wall -Wextra -pedantic
CFLAGS      =   $(OPTIMIZE) -I$(IDIR)
LDFLAGS     =   -lm

_DEPS       =   vector.h
DEPS        =   $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ        =   main.o
OBJ         =   $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/vector: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~