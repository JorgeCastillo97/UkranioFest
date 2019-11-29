/*@brief cliente.cpp
*  Este programa envia números aleatorios simulando ser depósitos bancarios
*  y recibe la cuenta total de dichos depósitos que el servidor le retorna. 
*  Sincronizando con el servidor, evitando envíos repetidos y
*  recuperandose de los paquetes perdidos mediante sockets por el protocolo UDP.
*  @autor José Pach Delgado
*/
#include <iostream>
#include "Solicitud.h"
#include <cstring>
#include <ctime>
#include <thread>

using namespace std;

int  debug = 0;
void progress_bar( int, int );
void forever( int );

/********************************
*            CLIENTE            *
*********************************/
int main( int argc, char * argv[] ) {


   if( argc < 3 ) {
      perror("Indique el número de depósitos y si desea mensajes de DEBUG (0 = no, 1 = si)\n");
      exit(EXIT_FAILURE);
   }

   srand( time(NULL) );
   int depositos = atoi( argv[1] );
   debug     = atoi( argv[2] );

 	forever( depositos );
   return 0;
} // end main

void forever( int depositos ) {
   Solicitud s;
   int cuentas    = 0;
   int only       = 0;
   register int i = 0;
    for( ; i < depositos; i++ ) {
      int num[1];
      
      num[0] = rand() % 100;
      cuentas += num[0];

      msg msgs, msgR;
      
    
   	msgs.requestId = i;
      msgs.operationId = suma;
      msgs.messageType = 0;
      msgs.total = depositos;

      char arguments[TAM_MAX_DATA];
      memcpy( msgs.arguments, num, 2*sizeof(int) );
      memcpy( &msgR, s.doOperation((char *)"192.168.1.73", 7200, 0, (char *)&msgs), sizeof( msg ) );
      int res = msgR.cuenta;

      if( debug ) {
         cout << endl;
         cout << endl;
         cout << "------------------------" << endl;
         cout << "Id     Cliente :" << msgs.requestId << endl;
         cout << "Id     Servidor:" << msgR.requestId << endl;
         cout << "Cuenta Local   :" << cuentas << endl;
         cout << "Cuenta Server  :" << res << endl;
         cout << "Total peticion :" << depositos << endl;
         cout << "------------------------" << endl;
      } // end debug
      
      if( msgR.requestId != msgs.requestId ) {
         i = msgR.requestId;
         cout << "CLIENTE : " << msgs.requestId << endl;
         cout << "SERVIDOR: " << msgR.requestId << endl;
         cout << "Las cuentas son distintas" << endl;
         cout << "reenviando..." << endl;
      	// exit(0);
      } // end if
      if( !debug )
      	progress_bar(i, depositos);
   } // end for
   printf("\n");
} // end forever

/* Esta función dibuja una barra de progreso.
*  @params <int>total_paquetes <int>paquete_actual
*  @return <void> 
*/
void progress_bar( int actual, int depositos ) {
   

   actual = actual + 1;
   int average = ((float)(actual)/(float)(depositos))*100;
   printf("\e[?25l");
   char str[] = "                                        ";   
   for( int i = 0; i <= ((float)average/100.00)*40; i++ )
      if( str[i] == ' ' ) {
      	str[i] = '|';
      	printf("\r[%s] %d%%", str, average);
      }
   printf("\e[?25h");

   // if( average == 64 ) exit(1);
} // end progress_bar