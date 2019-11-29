SOURCES = $(PROG).cpp mongoose.c  SocketDatagrama.cpp PaqueteDatagrama.cpp PaqueteDatagrama.h Solicitud.cpp Solicitud.h
CFLAGS = -g  -W -Wall -Wno-unused-function $(CFLAGS_EXTRA) $(MODULE_CFLAGS)
CC = g++
all: $(PROG)

ifeq ($(OS), Windows_NT)
# TODO(alashkin): enable SSL in Windows
CFLAGS += -lws2_32
CC = gcc
else
CFLAGS += -pthread
endif

ifeq ($(SSL_LIB),openssl)
CFLAGS += -DMG_ENABLE_SSL -lssl -lcrypto
endif
ifeq ($(SSL_LIB), krypton)
CFLAGS += -DMG_ENABLE_SSL ../../../krypton/krypton.c -I../../../krypton
endif
ifeq ($(SSL_LIB),mbedtls)
CFLAGS += -DMG_ENABLE_SSL -DMG_SSL_IF=MG_SSL_IF_MBEDTLS -DMG_SSL_MBED_DUMMY_RANDOM -lmbedcrypto -lmbedtls -lmbedx509
endif

ifdef ASAN
CC = clang
CFLAGS += -fsanitize=address
endif


$(PROG): $(SOURCES) 
	$(CC)  -std=c++11 $(SOURCES)  -o $@ $(CFLAGS)

$(PROG).exe: $(SOURCES) 
	cl $(SOURCES)  /I../.. /MD /Fe$@

Solicitud.o: Solicitud.cpp Solicitud.h
	g++ Solicitud.cpp -c
SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h
	g++ SocketDatagrama.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp  PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c


clean:
	rm -rf *.gc* *.dSYM *.exe *.obj *.o a.out $(PROG)
