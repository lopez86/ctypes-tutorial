GCC = gcc
CFLAGS = -L banking -I. -lbanking

all: lib exe

lib:
	$(MAKE) -C banking

exe: bank_example.c
	$(GCC) -o bank_example.exe bank_example.c $(CFLAGS)

clean:
	$(MAKE) -C banking clean
	rm -f bank_example.exe
