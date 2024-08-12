CC = gcc
IDIR = includes

CFLAGS = -Wall -g `pkg-config --cflags --libs glib-2.0` -I$(IDIR)
OPTIFLAGS = -O2

OBJ = $(patsubst %.c,%.o,$(wildcard src/*.c))
DEPS = $(IDIR)/$(wildcard *.h)
EXE = programa-principal

.PHONY: all run time clean
all: $(EXE)
	mkdir Resultados

$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(OPTIFLAGS)

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(OPTIFLAGS)

program: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(OPTIFLAGS)

clean:
	rm -r programa-principal Resultados src/*.o
