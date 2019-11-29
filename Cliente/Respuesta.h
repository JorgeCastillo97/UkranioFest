#ifndef H_RESPUESTA
#define H_RESPUESTA
#include "SocketDatagrama.h"
#include "Mensaje.h"

class Respuesta{
public:
	Respuesta(int pl);
	struct mensaje *getRequest( void );
	void sendReply( char *respuesta );
	void setTotal( int );
	
private:
	SocketDatagrama *socketlocal;
	msg msgR;
};


#endif