#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "Solicitud.h"
#include <unistd.h>
#include <iostream> 
//#include <list> 
#include <thread>  
using namespace std;




void enviar(char* ip, int puerto,  string ca, Solicitud s){
	int res [2];
    int na=ca.length();
     char char_array[ca.length() + 1]; 
  
    // copying the contents of the 
    // string to char array 
    strcpy(char_array, ca.c_str()); 
	memcpy(&res, s.doOperation(ip, puerto, na,char_array, na ),8);
	if(res[0]==-1)
    "un servicio no disponible";
    cout << res[0] <<endl;
    
}
int  buscaindice(int indice, string cadena, int  salto )
{
    int indiceFinal =indice;
    for(int i=indice ;i <cadena.length() ; i++ )
    {
        //cout << "caracter " << cadena[i] << endl;
        //cout << "i  " << i-indice << endl;
        if((i-indice)>=salto &  cadena[i]== ' '  ) 
        {
            return (i-indice);
        }
    }

    return (cadena.length()-indice) ;
} 
bool conectado()
{
    
    return true;
}
int main(int argc, char *argv[]){
	//if (argc != 5 /* 8*/){
	//	printf("Forma de uso: %s ip_servidorA puertoA ip_servidorB puertoB ip_servidorC puertoC n\n", argv[0]);
	//	exit(0);
	//}
	//srand(time(NULL));
    cout<<"entre" <<endl;
	char* s1Ip = argv[1];
	int s1Port = atoi(argv[2]);

	//char* s2Ip = argv[3];
	//int s2Port = atoi(argv[4]);
    string ips [2];
    ips[0]=string(s1Ip);
    //ips[1]=string(s2Ip); 
	int cont = 0;
	Solicitud s; 
    string sp ="hola como estas quiero preguntarte algo  de la perorata, es que tuve una  analepsis";
    cout<< sp.length()<<endl;
    int indice=0;
    int toma= 10;

	while(indice< sp.length()) {
        //exit(0);
        int auxindi =buscaindice(indice , sp, toma);
        cout << "auxindi " <<  auxindi <<endl;
        string aux =sp.substr(indice, auxindi);
        indice=indice+auxindi;
        cout << aux << endl; 
        cout <<"indice " << indice <<endl;

		if(conectado()){
            
			//enviar(s1Ip, s1Port, r, s);
			thread t(enviar, s1Ip, s1Port, aux, s);
			t.detach();
		}
       /* if(conectado() )
		{
			//enviar(s2Ip, s2Port, r, s);
			thread t(enviar, s2Ip, s2Port, aux, s);
			t.detach();
		}*/
		
		usleep(1000);
	
	}
	//cout << cont << endl;
	return 0;
}