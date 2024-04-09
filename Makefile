# include and lib directories
IDIR=/usr/local/include
LDIR=/usr/local/lib
# compiler
CC=gcc
# clags
CFLAGS=-Wall -Wextra -O2

# build and object directories
TDIR=target
ODIR=$(TDIR)/obj
BDIR=$(TDIR)/bin
SLIB=libcolr.a

# libraries
LIBS=-lm

# dependencies
DEPS=color.h
# object files
OBJ=$(ODIR)/main.o $(ODIR)/color.o
# executable name
TARGET=$(BDIR)/color

all: prebuild build install

prebuild:
	mkdir -p $(ODIR); mkdir -p $(BDIR)

build: prebuild $(OBJ)
	$(CC) -o $(TARGET) $(OBJ) $(CFLAGS) $(LIBS)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

install: build
	install -m 755 $(TARGET) /usr/local/bin/

uninstall: $(TARGET)
	rm -f /usr/local/bin/$(notdir $(TARGET))

build-lib: prebuild $(ODIR)/color.o
	ar rcs $(TDIR)/$(SLIB) $(ODIR)/color.o

install-lib: build-lib
	cp $(TDIR)/$(SLIB) /usr/local/lib/ ; cp $(DEPS) $(IDIR)/

.PHONY: clean

clean:
	rm -rf $(TDIR)
