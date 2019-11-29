#include "Solicitud.h"
#include "mongoose.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <thread>
using namespace std;

void cliente(char *ip, char *port, char *registros);
void servidorWeb();

static const char *s_http_port = "8081";
static struct mg_serve_http_opts s_http_server_opts;
int banderaDominio = false;
char * dominio = "192.168.8.";
int calidad = 100;


static void handle_size(struct mg_connection *nc, struct http_message *hm) {
		char query[256];
		if(banderaDominio){
			sprintf(query, dominio, (int)strlen(dominio));
			mg_send_head(nc,200,strlen(query), "Content-Type: text/plain");
			mg_printf(nc, "%s", query);
			banderaDominio = false;
		}
		else{
			mg_get_http_var(&hm->body, "query", query, sizeof(query));
			sprintf(query, "Longitud de la cadena = %d caracteres", (int)strlen(query));
			printf("Cadena enviada: %s\n", query);
			mg_send_head(nc,200,strlen(query), "Content-Type: text/plain");
			mg_printf(nc, "%s", query);
		}
}

static void ev_handler(struct mg_connection *nc, int ev, void *p) {
	char query[256];
 	struct http_message *hm = (struct http_message *) p;

	if (ev == MG_EV_HTTP_REQUEST) {
		if (mg_vcmp(&hm->uri, "/search") == 0) {

			mg_get_http_var(&hm->body, "query", query, sizeof(query));
			printf("Cadena introducida: %s\n",query);
			calidad = atoi(query);
		    handle_size(nc, hm);

		}else if (mg_vcmp(&hm->uri, "/dominio") == 0) {

			banderaDominio = true;
			handle_size(nc, hm);

		}else if (mg_vcmp(&hm->uri, "/actualiza") == 0) {

			s_http_server_opts.document_root = "www";

		}else{
			mg_serve_http(nc, (struct http_message *) p, s_http_server_opts);
		}
	}

}


int main(int argc, char*argv[]) {
	if (argc != 4) {
		cout << "Ejecución: ./Cliente ipServidor puerto noRegistros" << endl;
		exit(-1);
	}

	thread th1(cliente, argv[1], argv[2], argv[3]);
	thread th2(servidorWeb);
	th1.join();
	usleep(3000000);
	cout << "Servidor web corriendo..." << endl;
	th2.join();
	return 0;
}

void cliente(char *ip, char *port, char *registros){
	struct timeval timeout;
  timeout.tv_sec = 2;
  timeout.tv_usec = 500000;

	string auxIp = ip, auxRegistros = registros;
	char arreglo[100]="";
	char *ipServer, *reg;
	int puerto;
	int operacion = 1;
	ipServer = const_cast<char *>(auxIp.c_str());
	puerto = atoi(port);
	reg = const_cast<char *>(auxRegistros.c_str());
	cout << ipServer << endl << puerto << endl << reg << endl;

	memcpy(arreglo, reg, sizeof(strlen(reg) + 1));

	// arreglo contiene el numero de registros que serán leidos para ser enviados al servidor
	Solicitud cliente = Solicitud(timeout);
	cliente.doOperation(ipServer, puerto, operacion, arreglo);
}

void servidorWeb(){
	struct mg_mgr mgr;
	struct mg_connection *nc;
	mg_mgr_init(&mgr, NULL);

	printf("Starting web server on port %s\n", s_http_port);
	nc = mg_bind(&mgr, s_http_port, ev_handler);
	if (nc == NULL) {
		printf("Failed to create listener\n");
		exit(1);
	}
	// Set up HTTP server parameters
	mg_set_protocol_http_websocket(nc);
	s_http_server_opts.document_root = "www"; // Serve current directory
	s_http_server_opts.enable_directory_listing = "yes";
	for (;;) {
		mg_mgr_poll(&mgr, 1000);
	}
	mg_mgr_free(&mgr);
}
