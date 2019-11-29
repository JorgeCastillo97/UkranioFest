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
		if (f == NULL) {
			cout << "Error al abrir el archivo (SERVIDOR)" << endl;
		}

		cout << "\nEsperando conexion : " << endl;
		cout << "Se espera recibir id mensaje: " << idEsperado << endl;
		memcpy(&msj, respuesta.getRequest(), sizeof(struct mensaje));
		
		FILE *fp;
		fp = fopen("file.txt", "a");
   		/* Write data to the file */
		fwrite(msj.arguments, strlen(msj.arguments), 1, fp);
		fclose( fp );
	}
	return 0;
}
