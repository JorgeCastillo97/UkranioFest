#include "SocketDatagrama.h"
#include "PaqueteDatagrama.h"
#include "mensaje.h"
class Solicitud{
	public:
		Solicitud();
		char * doOperation(char *IP, int puerto, int operationId, char *arguments, int size);
	private:
		SocketDatagrama *socketlocal;
};