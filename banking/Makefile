CPPFLAGS = --std=c++11
LIBFLAGS = --shared

all: lib

banking.o: banking.cc banking.hh banking.h
	g++ ${CPPFLAGS} -fPIC -c banking.cc

security.o: security.cc security.hh
	g++ ${CPPFLAGS} -fPIC -c security.cc

lib: banking.o security.o
	g++ ${CPPFLAGS} ${LIBFLAGS} -o libbanking.so banking.o security.o

clean:
	rm -f libbanking.so banking.o security.o
