#include<bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "Solicitud.h"
#include "mongoose.h"
#include <unistd.h>
#include <iostream> 
//#include <list> 
#include <thread>  
using namespace std;

char * argsvv[7];

static const char *s_http_port = "8000";
static struct mg_serve_http_opts s_http_server_opts;
struct file_writer_data {
  FILE *fp;
  size_t bytes_written;
};
typedef long long int lli;
lli h1ng=0;
lli  h1n1g=0;
lli  h2ng=0;
lli h2n1g=0;
lli h3ng=0;
lli h3n1g=0;


void cliente( string cp );


static void handle_upload(struct mg_connection *nc, int ev, void *p) {
  struct file_writer_data *data = (struct file_writer_data *) nc->user_data;
  struct mg_http_multipart_part *mp = (struct mg_http_multipart_part *) p;
  // printf("%d\n", ev);
  switch (ev) {
    case MG_EV_HTTP_PART_BEGIN: {
      if (data == NULL) {
        data = (struct file_writer_data *)calloc(1, sizeof(struct file_writer_data));
        data->fp = tmpfile();
        data->bytes_written = 0;

        if (data->fp == NULL) {
          mg_printf(nc, "%s",
                    "HTTP/1.1 500 Failed to open a file\r\n"
                    "Content-Length: 0\r\n\r\n");
          nc->flags |= MG_F_SEND_AND_CLOSE;
          free(data);
          return;
        }
        nc->user_data = (void *) data;
      }
      break;
    }
    case MG_EV_HTTP_PART_DATA: {
      if (fwrite(mp->data.p, 1, mp->data.len, data->fp) != mp->data.len) {
        mg_printf(nc, "%s",
                  "HTTP/1.1 500 Failed to write to a file\r\n"
                  "Content-Length: 0\r\n\r\n");
        nc->flags |= MG_F_SEND_AND_CLOSE;
        return;
      }
      data->bytes_written += mp->data.len;
      break;
    }
    case MG_EV_HTTP_PART_END: {
      mg_printf(nc,
                "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/plain\r\n"
                "Connection: close\r\n\r\n"
                "Written %ld of POST data to a temp file\n\n",
                (long) ftell(data->fp));
        
        int c;
        string cp;
        fseek(data->fp, 0, SEEK_SET);
        while ((c = fgetc(data->fp)) != EOF)
        {
            cp += (char) c;
            // cout << (char) c << endl;
        }

        cout << cp << endl;
        cliente(cp);
        nc->flags |= MG_F_SEND_AND_CLOSE;

      /*Leer el archivo*/
      fclose(data->fp);
      free(data);
      nc->user_data = NULL;
      break;
    }
  }
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
  if (ev == MG_EV_HTTP_REQUEST) {
    mg_serve_http(nc, (struct http_message*)ev_data, s_http_server_opts);
  }
}


void enviar(char* ip, int puerto,  string ca, Solicitud s, int hilo) {
	int res [2];
    int na = ca.length();
     char char_array[ca.length() + 1]; 
  
    // copying the contents of the 
    // string to char array 
    strcpy(char_array, ca.c_str()); 
    //cout<< <<endl;
	memcpy(&res, s.doOperation(ip, puerto, na,char_array, na ),8);
	if(res[0]==-1)
    "un servicio no disponible";
    //cout <<"el mensaje" << res[1] <<endl;
    if(hilo==0) {
        h1ng=h1ng + res[0];
        h1n1g=h1n1g+res[1];
    }
    else if(hilo==1) {
        h2ng=h2ng + res[0];
        h2n1g=h2n1g+res[1];
    }
    else if(hilo==2) {
        h3ng=h3ng + res[0];
        h3n1g=h3n1g+res[1];
    }
}
int  buscaindice(int indice, string cadena, int  salto ) {
    int indiceFinal =indice;
    for(int i=indice ;i <cadena.length()-1 ; i++ ) {
        //cout << "caracter " << cadena[i] << endl;
        //cout << "i  " << i-indice << endl;
        if((i-indice)>=salto &  cadena[i]== ' '  ) {
            return (i-indice-1);
        }
    }
    return (cadena.length()-indice) ;
} 
bool conectado() {
    return true;
}
int main(int argc, char *argv[]){

    // argsvv = argv;
    argsvv[0] = argv[0];
    argsvv[1] = argv[1];
    argsvv[2] = argv[2];
    argsvv[3] = argv[3];
    argsvv[4] = argv[4];
    argsvv[5] = argv[5];
    argsvv[6] = argv[6];
	//if (argc != 5 /* 8*/){
	//	printf("Forma de uso: %s ip_servidorA puertoA ip_servidorB puertoB ip_servidorC puertoC n\n", argv[0]);
	//	exit(0);
	//}
	//srand(time(NULL));

    //string ips [2];
    //ips[0]=string(s1Ip);
    //ips[1]=string(s2Ip); 
	int cont = 0;
	// std::ifstream file("libro.txt");
 //    std::string str;
 //    string sp = "";
 //    while (std::getline(file, str)) {
 //        //std::cout << str << "\n";
 //        sp += str;
 //        sp += " ";
 //    }

    struct mg_mgr mgr;
    struct mg_connection *c;

    mg_mgr_init(&mgr, NULL);
    c = mg_bind(&mgr, s_http_port, ev_handler);
    if (c == NULL) {
        fprintf(stderr, "Cannot start server on port %s\n", s_http_port);
        exit(EXIT_FAILURE);
    }

    s_http_server_opts.document_root = "../../Cliente/www";  // Serve current directory
    mg_register_http_endpoint(c, "/upload", handle_upload MG_UD_ARG(NULL));

    // Set up HTTP server parameters
    mg_set_protocol_http_websocket(c);

    printf("Starting web server on port %s\n", s_http_port);
    for (;;) {
    mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);
   
   return 0;
    
}


void cliente( string sp ) {

    cout<<"entre" <<endl;
    char* s1Ip = argsvv[1];
    int s1Port = atoi(argsvv[2]);

    char* s2Ip = argsvv[3];
    int s2Port = atoi(argsvv[4]);
    
    char* s3Ip = argsvv[5];
    int s3Port = atoi(argsvv[6]);
   Solicitud s; 
    //string sp="hola como estas te quiero contar lo de la peorrata de la otra vez ";
   cout<< sp.length()<<endl;
   int indice=0;
   int toma= 19000;
   int auxindi=0;
   string aux="";
   while(indice< sp.length()) {
        //exit(0);
       auxindi =buscaindice(indice , sp, toma);
       // cout << "auxindi " <<  auxindi <<endl;
       aux =sp.substr(indice, auxindi);
       indice=indice+auxindi;
        //cout << aux << endl; 
    //cout <<"indice " << indice <<endl;

        //if(conectado()){

            //enviar(s1Ip, s1Port, r, s);
       thread t1 (enviar, s1Ip, s1Port, aux, s, 0);
           //enviar( s1Ip, s1Port, aux, s);
        //  t1.detach();
    //  }
       auxindi =buscaindice(indice , sp, toma);
        //cout << "auxindi " <<  auxindi <<endl;
       aux =sp.substr(indice, auxindi);
            //cout << aux << endl; 
       indice=indice+auxindi;
        //if(conectado() )
        //{
            //enviar(s2Ip, s2Port, r, s);
       thread t2(enviar, s2Ip, s2Port, aux, s, 1);
        //  t2.detach();

       auxindi =buscaindice(indice , sp, toma);
       // cout << "auxindi " <<  auxindi <<endl;
       aux =sp.substr(indice, auxindi);
          //  cout << aux << endl; 
       indice=indice+auxindi;

            //enviar(s2Ip, s2Port, r, s);
       thread t3(enviar, s3Ip, s3Port, aux, s, 2);

       t1.join();
       t2.join();
       t3.join();

       usleep(200000);

   }
   usleep(200000);
    //cout << cont << endl;
    //cout <<"la global " << h1ng<<endl;
    //cout <<"la global " << h1n1g<<endl;
    //cout <<"la global " << h2ng<<endl;
    //cout <<"la global " << h2n1g<<endl;
    //cout <<"la global " << h3ng<<endl;
    //cout <<"la global " << h3n1g<<endl;
   cout<< indice <<endl;
   cout <<sp.length()<<endl;
   lli total1=h1ng+h2ng+h3ng;
   lli total2=h1n1g +h2n1g + h3n1g ;
   cout<<"existentes  " << total1 <<endl;
   cout << "total " << total2 <<endl;
   double  porcen = ((double)total1/(double)total2)*100;
   cout << "porcentaje " <<  porcen <<endl;
   return ;
} // end cliente