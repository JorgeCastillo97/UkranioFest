#include "Solicitud.h"
#include <iostream>
#include <cstring>
using namespace std;
unsigned int contRequest = 0;

Solicitud::Solicitud() {
	socketlocal = new SocketDatagrama(0);
}

char *Solicitud::doOperation(char *IP, int puerto, int operationId, char *arguments, int size) {
	struct mensaje sms;
	sms.messageType = 0;
	sms.size=size;
	sms.requestId = contRequest;
	printf("\nContRequest: %u\n", contRequest);
	sms.operationId = operationId;
	string auxca= string(arguments);
	memcpy(sms.arguments, arguments, sizeof(auxca));
	PaqueteDatagrama p = PaqueteDatagrama((char *)&sms, sizeof(sms), IP, puerto);
	//cout << "Direccion: " << p.obtieneDireccion() << endl;
	//cout << "Puerto: " << p.obtienePuerto() << endl;
	socketlocal->envia(p);
	PaqueteDatagrama p1 = PaqueteDatagrama(65000);
	int tam = socketlocal->recibeTimeout(p1, 2, 500);
	int n = 1;
	while (tam == -1 && n < 7) {
		socketlocal->envia(p);
		tam = socketlocal->recibeTimeout(p1, 2, 500);
		n++;
	}
	if (n == 7) {
		cout << "Servidor no esta disponible, intente mas tarde." << endl;
		int error[2];
		error[0]=-1;
		error[1]=-1;
		//return  ((char *) error);
	}
	else
	{
		cout << "Mensaje recibido" << endl;
		//cout << "Direccion: " << p1.obtieneDireccion() << endl;
		//cout << "Puerto: " << p1.obtienePuerto() << endl;
		struct mensaje *msj = (struct mensaje *)p1.obtieneDatos();
		contRequest++;
		return (char *)msj->arguments;
	}
}