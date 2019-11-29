#include "SocketDatagrama.h"
#include <iostream>
using namespace std;

SocketDatagrama::SocketDatagrama(int port = 0) {

	s = socket(AF_INET, SOCK_DGRAM, 0);
	
	bzero((char *)&direccionLocal, sizeof(direccionLocal));
	direccionLocal.sin_family = AF_INET;	
	direccionLocal.sin_addr.s_addr = INADDR_ANY;	
	direccionLocal.sin_port = htons(port);
	// cout << "Puerto" << htons(port) << endl;
	bind(s, (struct sockaddr *)&direccionLocal, sizeof(direccionLocal));

} // end construct

SocketDatagrama::~SocketDatagrama() {
	close(s);
}

int SocketDatagrama::recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos) {
	

	// Inicializa el timeout
	timeout.tv_sec = segundos;
	timeout.tv_usec = microsegundos;

	setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));

	char * aux = (char*)malloc( p.obtieneLongitud() );
    socklen_t clilen = sizeof(direccionForanea);
    int len = recvfrom(s, aux, p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, &clilen);

    // Si el tiempo se agota
	if (len < 0) {
		if (errno == EWOULDBLOCK) {
			fprintf(stderr, "Tiempo para recepción transcurrido\n");
			// cout << ((msg*)p.obtieneDatos())->requestId << endl;
			return -1;
		}
		else
			fprintf(stderr, "Error en recvfrom\n");
	} // end if


    // Copiar dirección ip
    unsigned char * ip;

    ip = (unsigned char*)inet_ntoa(direccionForanea.sin_addr);
    p.inicializaPuerto(ntohs(direccionForanea.sin_port));
    p.inicializaIp( (char*)ip );
    p.inicializaDatos(aux);
    return len;
}

int SocketDatagrama::recibe(PaqueteDatagrama & p) {

	char * aux = (char*)malloc( p.obtieneLongitud() );
    socklen_t clilen = sizeof(direccionForanea);
    int len = recvfrom(s, aux, p.obtieneLongitud(), 0, (struct sockaddr *) &direccionForanea, &clilen);

    // Copiar dirección ip
    unsigned char * ip;

    ip = (unsigned char*)inet_ntoa(direccionForanea.sin_addr);
    p.inicializaPuerto(ntohs(direccionForanea.sin_port));
    p.inicializaIp( (char*)ip );
    p.inicializaDatos(aux);
    // p.~PaqueteDatagrama();

	return len;	
} // end recibe

int SocketDatagrama::envia(PaqueteDatagrama & p, int type) {

	if( type ) {
		bzero((char *)&direccionForanea, sizeof(direccionForanea));
		direccionForanea.sin_addr.s_addr = inet_addr(p.obtieneDireccion());
		direccionForanea.sin_family = AF_INET;
		direccionForanea.sin_port = htons(p.obtienePuerto());
	}

	int clilen = sizeof(direccionForanea);

	return sendto(s, p.obtieneDatos(), p.obtieneLongitud(), 0, (struct sockaddr *)&direccionForanea, clilen);
}// end envia