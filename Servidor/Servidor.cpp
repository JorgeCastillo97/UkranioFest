#include <cstdlib>
#include <iostream>
#include <string>
#include "Respuesta.h"
#include "Solicitud.h"
#include <unistd.h>
#include <thread>

using namespace std;
#define numServidores 3
#define archivo "palabras.txt"

void envioSolicitud(char *ipAenviar, struct mensaje msj, Respuesta res){
	cout << "[ Envio de la peticion al servidor ] "<< endl;
	struct timeval timeout;
  timeout.tv_sec = 2;
  timeout.tv_usec = 500000;
	// Creación de archivo a procesar
	FILE *f = fopen(archivo, "w");
	if (f==NULL) {
		cout << "Error al crear el archivo (w) " << archivo << endl;
		exit(-1);
	}
	fclose(f);

	f = fopen(archivo, "a+");
  if (f == NULL) {
    cout << "Error al abrir el archivo (SERVIDOR)" << endl;
		exit(-1);
  }
	char *ip = ipAenviar;
	int puerto = 9999;
	int operacion = 2;
	Solicitud cliente = Solicitud(timeout);
	char *respuesta = cliente.doOperation(ip, puerto, operacion, msj.arguments);
	struct timeval tv;
  gettimeofday(&tv,NULL);
	string segundos = std::to_string(tv.tv_sec);
	string microsec = std::to_string(tv.tv_usec);
	char tmbuf[64];
	char tmbuf2[64];
	strcpy(tmbuf,segundos.c_str());
	fflush(f);
	strcpy(tmbuf2,microsec.c_str());
	fflush(f);
	struct mensaje m1;
	cout << "respuesta dentro de envio solicitud " << respuesta << endl;
	memcpy(m1.arguments, respuesta, strlen(respuesta)+1);
	cout << "m1.arguments " << m1.arguments << endl;
	m1.messageType = 1;
	memcpy(m1.IP, msj.IP, 16);
	m1.puerto = msj.puerto;
	m1.requestId = msj.requestId;
	cout << "[ Envio de la respuesta al cliente ] " <<endl;
	res.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
	fclose(f);
}

int main(int argc, char const *argv[]) {
	long int idEsperado =0, idAnterior = -1;
	int carga[numServidores];
	struct timeval timeout;
  timeout.tv_sec = 100;
  timeout.tv_usec = 500000;
	char *ipSend;

	if (argc != 2) {
		cout << "Ejecucion: ./Servidor puerto" << endl;
		exit(-1);
	}

	char confirmacion[] = "Solicitud procesada";
	cout << "[ Configurando balanceador de carga ] " << endl;
	for(int index=0; index<numServidores; index++)
		carga[index] = 0;
	cout << "[ Servidor iniciado ] " << endl;
	Respuesta respuesta(atoi(argv[1]),timeout);

	while(1) {
	struct mensaje msj;
  struct mensaje m1;
  // f = fopen(argv[2], "a+");
  // if (f == NULL) {
  //   cout << "Error al abrir el archivo (SERVIDOR)" << endl;
  // }

	// cout << "\nEsperando conexion : " << endl;
	// cout << "Se espera recibir id mensaje: " << idEsperado << endl;
	// memcpy(&msj, respuesta.getRequest(), sizeof(struct mensaje));
	cout << "[ Esperando conexion ]" << endl;
	cout << "[ ID del mensaje que se espera : " <<(idAnterior+1)  <<" ]" << endl;
	memcpy(&msj, respuesta.getRequest(), sizeof(struct mensaje));
	cout << "[ Mensaje recibido ]" << endl;

		switch(msj.operationId) {
			case 1:
			{
				cout << "[ BALANCEADOR ]" << endl;
				if(msj.requestId > idAnterior){
					int indiceIPServidor = 0;
					int historicoCarga = 0;
					for(int i=0; i<numServidores; i++){
						if(i==0 && carga[i]==0){
							indiceIPServidor = 0;
							break;
						}else{
							historicoCarga = carga[i];
						}
						if(carga[i]>=historicoCarga){
							historicoCarga = carga[i];
							indiceIPServidor = i;
						}
					}
					carga[indiceIPServidor] = carga[indiceIPServidor] + 1;
					switch(indiceIPServidor){
						case 0:
						{
							//char *ipAenviar = "192.168.28.91";
							//ipSend = "192.168.28.91";
							ipSend = "10.100.73.101";
							break;
						}
						case 1:
						{
							//ipSend = "192.168.32.23";
							ipSend = "10.100.73.101";
							break;
						}
						case 2:
						{
							//ipSend = "192.168.43.54";
							ipSend = "10.100.73.101";
							break;
						}
						default:
						{
							//ipSend = "192.168.28.91";
							ipSend = "10.100.73.101";
							break;
						}
					}
					thread th1(envioSolicitud, ipSend, msj, respuesta);
					th1.join();
					idAnterior = msj.requestId;
				} else if(msj.requestId == idAnterior) {
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					m1.messageType = 1;
					memcpy(m1.IP, msj.IP, 16);
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				} else {
					memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
					m1.messageType = 1;
					memcpy(m1.IP, msj.IP, 16);
					m1.puerto = msj.puerto;
					m1.requestId = msj.requestId;
					respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				}
				break;
			}
				// if(msj.requestId == idEsperado){
				// 	fputs(msj.arguments,f);
				// 	fclose(f);
				// 	idAnterior = idEsperado;
				// 	idEsperado++;
				// 	memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
				// 	//memcpy(m1.arguments, suma(msj.arguments), strlen(msj.arguments));
				// 	m1.messageType = 1;
				// 	memcpy(m1.IP, msj.IP, 16);//------------------
				// 	m1.puerto = msj.puerto;
				// 	m1.requestId = msj.requestId;
				// 	respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				// } else if(msj.requestId == idAnterior) {
				// 	fclose(f);
				// 	memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
				// 	//memcpy(m1.arguments, suma(msj.arguments), strlen(msj.arguments));
				// 	m1.messageType = 1;
				// 	memcpy(m1.IP, msj.IP, 16);//------------------
				// 	m1.puerto = msj.puerto;
				// 	m1.requestId = msj.requestId;
				// 	respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				// } else {
				// 	// Caso en que los id son anteriores
				// 	cout << "id antiguo guardado en bd servidor." << endl;
				// 	fclose(f);
				// 	memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
				// 	//memcpy(m1.arguments, suma(msj.arguments), strlen(msj.arguments));
				// 	m1.messageType = 1;
				// 	memcpy(m1.IP, msj.IP, 16);//------------------
				// 	m1.puerto = msj.puerto;
				// 	m1.requestId = msj.requestId;
				// 	respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				// }
				// break;
			case 2:
			{
				cout << "[ SERVIDOR ]" << endl;
				memcpy(m1.arguments, confirmacion, strlen(confirmacion)+1);
				m1.messageType = 1;
				memcpy(m1.IP, msj.IP, 16);
				cout << "Servidor envia respuesta a maestro: " << m1.IP << endl;
				m1.puerto = msj.puerto;
				cout << "m1 puerto: " << m1.puerto << endl;
				m1.requestId = msj.requestId;
				respuesta.sendReply((char*) m1.arguments,m1.IP, msj.puerto);
				break;
			}
			default:
			{
				cout << "Error en el numero de operación" << endl;
				cout << "Numero operación: " << msj.operationId << endl;
				exit(-1);
			}
		}
	}
	return 0;
}
