BDIR        =   bin
SDIR        =   src
ODIR        =   obj
IDIR        =   include

CC          =   gcc -std=c17
OPTIMIZE    =   -O3 -Wall -Wextra -pedantic
CFLAGS      =   $(OPTIMIZE) -I$(IDIR)
LDFLAGS     =   -lm

_DEPS       =   odeint.h
DEPS        =   $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ        =   main.o
OBJ         =   $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/odeint: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~