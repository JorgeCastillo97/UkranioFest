#include<bits/stdc++.h>
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
typedef long long int lli;
lli h1ng=0;
lli  h1n1g=0;
lli  h2ng=0;
lli h2n1g=0;
lli h3ng=0;
lli h3n1g=0;

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
	//if (argc != 5 /* 8*/){
	//	printf("Forma de uso: %s ip_servidorA puertoA ip_servidorB puertoB ip_servidorC puertoC n\n", argv[0]);
	//	exit(0);
	//}
	//srand(time(NULL));
    cout<<"entre" <<endl;
	char* s1Ip = argv[1];
	int s1Port = atoi(argv[2]);

	char* s2Ip = argv[3];
	int s2Port = atoi(argv[4]);
    
   char* s3Ip = argv[5];
int s3Port = atoi(argv[6]);
    //string ips [2];
    //ips[0]=string(s1Ip);
    //ips[1]=string(s2Ip); 
	int cont = 0;
	std::ifstream file("libro.txt");
    std::string str;
    string sp = "";
    while (std::getline(file, str)) {
        //std::cout << str << "\n";
        sp += str;
        sp += " ";
    }
   
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
		//	t1.detach();
	//	}
         auxindi =buscaindice(indice , sp, toma);
        //cout << "auxindi " <<  auxindi <<endl;
        aux =sp.substr(indice, auxindi);
            //cout << aux << endl; 
        indice=indice+auxindi;
        //if(conectado() )
		//{
			//enviar(s2Ip, s2Port, r, s);
			thread t2(enviar, s2Ip, s2Port, aux, s, 1);
		//	t2.detach();
	
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
    return 0;
    
}