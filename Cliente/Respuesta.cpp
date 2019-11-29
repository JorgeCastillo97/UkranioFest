#include "Respuesta.h"
#include <iostream>
using namespace std;

Respuesta::Respuesta( int pl ) {
	socketlocal = new SocketDatagrama(pl);
} // end Respuesta


void Respuesta::sendReply( char *respuesta ) {
	PaqueteDatagrama p2( sizeof(msg) );
	p2.inicializaDatos( respuesta );
	socketlocal->envia(p2, 0);
} // end sendReply

struct mensaje * Respuesta::getRequest( void ) {
	while(1) {
		PaqueteDatagrama p( sizeof(msg) );
		socketlocal->recibe(p);
		msg * msgR1 = ( msg * )p.obtieneDatos();
		return msgR1;
	} // end while
} // end getRequest

void Respuesta::setTotal( int n ) {
	if( n > 0 )
		msgR.total = n;
	else
		cout << "El valor debe ser mayor a cero >:("  << endl;
} // end setTotal
