Servidor: Servidor.cpp Respuesta.o Solicitud.o SocketDatagrama.o PaqueteDatagrama.o
	g++ -std=c++11 Servidor.cpp Respuesta.o Solicitud.o SocketDatagrama.o PaqueteDatagrama.o -o Servidor -lpthread
Respuesta.o: Respuesta.cpp Respuesta.h
	g++ Respuesta.cpp -c
Solicitud.o: Solicitud.cpp Solicitud.h
	g++ Solicitud.cpp -c
SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h
	g++ SocketDatagrama.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp  PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c
clean:
	rm -f *.o
