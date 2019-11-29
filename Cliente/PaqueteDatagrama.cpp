#include <iostream>
#include "PaqueteDatagrama.h"
using namespace std;

PaqueteDatagrama::PaqueteDatagrama(char * paquete, unsigned int len, char * dir, int port) {
	
	if( port >= 5000 )
		puerto = port;
	else {
		cout << "ERROR de asignación de puerto" << endl;
		exit( 1 );
	}

	if( len < 1 ) {
		cout << "ERROR de asignación de longitud" << endl;
		exit(0);
	} // end if

	// if( dir == NULL ) {
	// 	cout << "ERROR de asignación de ip" << endl;
	// 	exit(0);
	// } // end if
	
	// cout << "longitud: " << len << " dir:" << dir << endl; //" paquete:" << *(int *)paquete << "\n";
	longitud = len;
	datos = (char*)malloc(len);
	// datos = paquete;
	memcpy( ip, dir, sizeof(char) * 16 );
	memcpy( datos, paquete, longitud );
	// ip = dir;

}

PaqueteDatagrama::PaqueteDatagrama(unsigned int len) : longitud(len) {
	datos = (char *)malloc( len );
}

PaqueteDatagrama::~PaqueteDatagrama() {
	// free(datos);
}


char * PaqueteDatagrama::obtieneDireccion(void) {
	return ip;
} // end obtieneDireccion

unsigned int PaqueteDatagrama::obtieneLongitud(void) {
	return longitud;
} // end obtieneLongitud

int PaqueteDatagrama::obtienePuerto(void) {
	return puerto;
} // end obtienePuerto

char * PaqueteDatagrama::obtieneDatos() {
	return datos;
} // end obtieneDatos

void PaqueteDatagrama::inicializaPuerto(int l) {
	puerto = l;
} //end inicializaPuerto


void PaqueteDatagrama::inicializaIp(char * d) {
	memcpy( ip, d, sizeof(char) * 16 );
} //end inicializaIp


void PaqueteDatagrama::inicializaDatos(char * d) {
	datos = d;
} //end inicializaDatos
