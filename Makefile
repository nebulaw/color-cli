# include directory
IDIR=/usr/include
# compiler
CC=gcc
# clags
CFLAGS=-Wall -Wextra -O2 -I$(IDIR)

LDIR=/usr/lib
# build and object directories
TDIR=target
ODIR=$(TDIR)/obj
BDIR=$(TDIR)/bin

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

build: $(OBJ)
	$(CC) -o $(TARGET) $^ $(CFLAGS) $(LIBS)

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

install: build
	install -m 755 $(TARGET) /usr/local/bin/

uninstall: $(TARGET)
	rm -f /usr/local/bin/$(notdir $(TARGET))

.PHONY: clean

clean:
	rm -rf $(TDIR)
