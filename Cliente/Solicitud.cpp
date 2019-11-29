#include "Solicitud.h"
#include <iostream>
using namespace std;

Solicitud::Solicitud() {
	socketlocal = new SocketDatagrama(0);
} // end Solicitud

char * Solicitud::doOperation(char *IP, int puerto, int operationId, char *arguments) {
	

	// cout << "operationId: " << ((msg*)arguments)->operationId << endl;
	PaqueteDatagrama p( arguments, sizeof(msg), IP, puerto );
	PaqueteDatagrama p2( arguments, sizeof(msg), IP, puerto );
	
	int intentos = 0;
	int bytes = -1;
	while( bytes == -1 && intentos < 7 ) {
		socketlocal->envia(p,1);
		bytes = socketlocal->recibeTimeout( p2, 2, 50000 );
		intentos ++;
	} // end while

	if( intentos == 7 ) {
		cout << "El servidor no está disponible " << endl;
		exit(1);
	}	//end if
   	return p2.obtieneDatos();
} // end doOperation
