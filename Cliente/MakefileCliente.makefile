Cliente: Cliente.c mongoose.o
	cc Cliente.c  mongoose.o -o Cliente -g  -W -Wall  -I -Wno-unused-function -DMG_ENABLE_HTTP_STREAMING_MULTIPART -pthread
Solicitud.o: Solicitud.cpp Solicitud.h
	g++ Solicitud.cpp -c
SocketDatagrama.o: SocketDatagrama.cpp SocketDatagrama.h
	g++ SocketDatagrama.cpp -c
PaqueteDatagrama.o: PaqueteDatagrama.cpp  PaqueteDatagrama.h
	g++ PaqueteDatagrama.cpp -c
mongoose.o: mongoose.c mongoose.h
	cc mongoose.c -c 
clean:
	rm -f *.o
