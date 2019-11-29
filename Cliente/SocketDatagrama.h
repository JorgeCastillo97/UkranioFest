#ifndef H_SOCKETDAT
#define H_SOCKETDAT
#include "PaqueteDatagrama.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <strings.h>
#include <unistd.h>
#include <errno.h>

class SocketDatagrama{
public:
	SocketDatagrama(int);
	~SocketDatagrama();
 //Recibe un paquete tipo datagrama proveniente de este socket
	int recibe(PaqueteDatagrama & p);
 //Envía un paquete tipo datagrama desde este socket
	int envia(PaqueteDatagrama & p, int type);

	int recibeTimeout(PaqueteDatagrama & p, time_t segundos, suseconds_t microsegundos);
private:
	struct sockaddr_in direccionLocal;
	struct timeval timeout;
	struct sockaddr_in direccionForanea;
	int s; //ID socket
};
#endif