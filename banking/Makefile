CPPFLAGS = --std=c++11
LIBFLAGS = --shared

all: lib

banking.o: banking.cc banking.hh banking.h
	g++ ${CPPFLAGS} -fPIC -c banking.cc

lib: banking.o
	g++ ${CPPFLAGS} ${LIBFLAGS} -o libbanking.so banking.o

clean:
	rm -f libbanking.so banking.o
