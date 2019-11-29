#include "SocketDatagrama.h"
#include "Solicitud.h"
#include "mensaje.h"

Solicitud::Solicitud(struct timeval timeout) {
	timeoutSocket = timeout;
	socketlocal = new SocketDatagrama(0,timeout);
}

char * Solicitud::doOperation(char* IP, int puerto, int operationId, char* arguments) {
	struct mensaje msj;
	int id;// registros = atoi(arguments); // id de 0 a 65535

	msj.messageType = 1;
	msj.requestId = 10;
	memcpy(msj.IP, IP, 16);
	msj.puerto = puerto;
	msj.operationId = operationId;
	memset( msj.arguments, 0, sizeof(msj) );
	memcpy( msj.arguments, arguments, 512 );
	PaqueteDatagrama paq((char*) &msj, sizeof(msj), IP, puerto);
	socketlocal->envia(paq);
	PaqueteDatagrama paq1(sizeof(msj));
	int res = socketlocal->recibeTimeout(paq1,timeoutSocket.tv_sec,timeoutSocket.tv_usec);



	return "WAA";
}
