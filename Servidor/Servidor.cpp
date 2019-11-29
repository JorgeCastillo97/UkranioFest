#include <cstdlib>
#include <iostream>
#include <string>
#include "Respuesta.h"

using namespace std;

int main(int argc, char const *argv[]) {
	long int idEsperado =0, idAnterior = -1;
	struct timeval timeout;
  timeout.tv_sec = 100;
  timeout.tv_usec = 500000;

	if (argc != 3) {
		cout << "Ejecucion: ./Servidor puerto nombreArchivoBD.txt" << endl;
		exit(-1);
	}
	Respuesta respuesta(atoi(argv[1]),timeout);
  char confirmacion[] = "Registro guardado en bd servidor.";
  FILE *f = fopen(argv[2], "w");
	if (f==NULL) {
		cout << "error al abrir el archivo (w) " << argv[2] << endl;
		exit(-1);
	}
	fclose(f);


	while(1) {
	struct mensaje msj;
  struct mensaje m1;
  f = fopen(argv[2], "a+");
  if (f == NULL) {
    cout << "Error al abrir el archivo (SERVIDOR)" << endl;
  }

	cout << "\nEsperando conexion : " << endl;
	cout << "Se espera recibir id mensaje: " << idEsperado << endl;
	memcpy(&msj, respuesta.getRequest(), sizeof(struct mensaje));
    //cout << "Estos son los argumentos antes de la operacion: " << msj.arguments << endl;
		//cout << "id: " << msj.operationId << endl;
		//cout<< "IP: " <<msj.IP<<endl;
		switch(msj.operationId) {
			case 1:
				if(msj.requestId == idEsperado){
					fputs(msj.arguments,f);
					fclose(f);
					idAnterior = idEsperado;
					idEsperado++;
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					//memcpy(m1.arguments, suma(msj.arguments), strlen(msj.arguments));
					m1.messageType = 1;
					memcpy(m1.IP, msj.IP, 16);//------------------
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				} else if(msj.requestId == idAnterior) {
					fclose(f);
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					//memcpy(m1.arguments, suma(msj.arguments), strlen(msj.arguments));
					m1.messageType = 1;
					memcpy(m1.IP, msj.IP, 16);//------------------
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				} else {
					// Caso en que los id son anteriores
					cout << "id antiguo guardado en bd servidor." << endl;
					fclose(f);
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					//memcpy(m1.arguments, suma(msj.arguments), strlen(msj.arguments));
					m1.messageType = 1;
					memcpy(m1.IP, msj.IP, 16);//------------------
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				}
				break;
			default:
				cout << "Error en el numero de operación" << endl;
				cout << "Numero operación: " << msj.operationId << endl;
				exit(-1);
		}
	}
	return 0;
}
