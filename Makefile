GCC = gcc


all: lib exe

lib:
	$(MAKE) -C banking

exe: bank_example.c
	$(GCC) -L banking -I. -o bank_example.exe bank_example.c -lbanking

clean:
	$(MAKE) -C banking clean
	rm -f bank_example.exe