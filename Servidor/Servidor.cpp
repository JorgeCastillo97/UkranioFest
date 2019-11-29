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
		FILE *fp;
		fp = fopen("file.txt", "w+");
   		/* Write data to the file */
		fwrite(c, strlen(c) + 1, 1, fp);
	}
	return 0;
}
