/*@brief servidor.cpp
*  Este programa recibe números aleatorios simulando ser depósitos bancarios desde un cliente
*  acumulando dichos depósitos y retornando el total de estos.
*  Puede recuperandose de los paquetes perdidos mediante sockets por el protocolo UDP.
*  @autor José Pach Delgado
*/
#include <iostream>
#include "Respuesta.h"

using namespace std;

/********************************
*            SERVIDOR           *
*********************************/

int main( int argc, char * argv[] ) {

	Respuesta resp(7777);
	int cuenta      = 0;
	int messageType = 1;
	int operationId = 0;
	int requestId   = 0;
	int total       = 0;
	int res         = 0;

	while( 1 ) {
		cout << "esperando solicitud" << endl;
		msg * msgs = resp.getRequest();
		
		// if( msgs->requestId  != requestId ) {
		// 	cout << "Server : " << requestId << endl;
		// 	cout << "Cliente: " << msgs->requestId << endl;
		// 	msgs->requestId = requestId;
		// } else {
		// 	cout 
		// 	// res      = *((int *)msgs->arguments);
		// 	total    =  msgs->total;
   			
		// 	cout << endl;
		// 	cout << endl;
		// 	cout << "--------------------------------" << endl;
		// 	cout << "ID     CLIENTE: " << msgs->requestId << endl;
		// 	cout << "ID     SERVER : " << requestId << endl;
		// 	cout << "CUENTA SERVER : " << cuenta << endl;
		// 	cout << "Total: " << total << endl;

		// 	msgs->requestId = requestId;
	 //   		msgs->cuenta = cuenta;

   			
		// } // end else
		// requestId++;

		cout << msgs->arguments << endl;


		// Reiniciar al completar todas las transferencias
		if( requestId == msgs->total ) {
			requestId = 0;
			total     = 0;
			cuenta    = 0;
		}

		msgs->operationId = suma;  
		int s = res;  
		memcpy( msgs->arguments, (char*)&s, sizeof(int) ); 
		cout << "Enviando respuesta" << endl;
		
		resp.sendReply( (char*)msgs );

	} // end while
	
	return 0;
} // end main