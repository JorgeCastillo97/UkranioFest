servidor: PaqueteDatagrama.o SocketDatagrama.o Respuesta.o servidor.cpp
	g++ servidor.cpp PaqueteDatagrama.o SocketDatagrama.o Respuesta.o -o servidor 

Respuesta.o: Respuesta.cpp Respuesta.h
	g++ Respuesta.cpp -c

Solicitud.o: Solicitud.cpp Solicitud.h
	g++ Solicitud.cpp -c

SocketDatagrama.o: PaqueteDatagrama.o SocketDatagrama.cpp
	g++ SocketDatagrama.cpp -c

PaqueteDatagrama.o: PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c 

clean:
	rm -f *.o