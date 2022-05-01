BDIR        =   bin
SDIR        =   src
ODIR        =   obj
<<<<<<< HEAD
IDIR        =   compp

CC          =   clang++-14 -std=c++17
OPTIMIZE    =   -O3 -Wall -Wextra -pedantic
CFLAGS      =   $(OPTIMIZE) -I$(IDIR)
LDFLAGS     =   

_DEPS       =   vector.hpp
DEPS        =   $(patsubst %,$(IDIR)/%,$(_DEPS))
LIBS        =   $(patsubst %.hpp,%.cpp,$(DEPS))
=======
IDIR        =   include

CC          =   gcc -std=c17
OPTIMIZE    =   -O3 -Wall -Wextra -pedantic
CFLAGS      =   $(OPTIMIZE) -I$(IDIR)
LDFLAGS     =   -lm

_DEPS       =   odeint.h
DEPS        =   $(patsubst %,$(IDIR)/%,$(_DEPS))
>>>>>>> 8f1e9b45576a54801252c6d0361fedfa8f9971a5

_OBJ        =   main.o
OBJ         =   $(patsubst %,$(ODIR)/%,$(_OBJ))

<<<<<<< HEAD
$(ODIR)/%.o: $(IDIR)/%.cpp $(LIBS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


=======
$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

>>>>>>> 8f1e9b45576a54801252c6d0361fedfa8f9971a5
$(BDIR)/odeint: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(IDIR)/*~