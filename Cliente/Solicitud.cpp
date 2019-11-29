#include "SocketDatagrama.h"
#include "Solicitud.h"

Solicitud::Solicitud(struct timeval timeout) {
	timeoutSocket = timeout;
	socketlocal = new SocketDatagrama(0,timeout);
}

char * Solicitud::doOperation(char* IP, int puerto, int operationId, char* arguments) {


	msg msg1;
	msg1.operationId = 1;
	memcpy( msg1.arguments, arguments, sizeof(msg) );

	PaqueteDatagrama p( (char*)&msg1, sizeof(msg), IP, puerto );
	PaqueteDatagrama p2( (char*)&msg1, sizeof(msg), IP, puerto ); 
	
	int intentos = 0;
	int bytes = -1;
	while( bytes == -1 && intentos < 7 ) {
		socketlocal->envia(p);
		bytes = socketlocal->recibeTimeout( p2, 2, 50000 );
		intentos ++;
	} // end while

	if( intentos == 7 ) {
		cout << "El servidor no está disponible " << endl;
		exit(1);
	}	//end if
   	return p2.obtieneDatos();
}
