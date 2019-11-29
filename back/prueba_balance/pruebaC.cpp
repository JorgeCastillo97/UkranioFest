#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
//#include "Solicitud.h"
#include <unistd.h>
#include <iostream> 
#include "Respuesta.h"
//#include <list> 
#include <thread>  
using namespace std;
 int main (int argc, char *argv[])
 {
     Respuesta resp(atoi(argv[1]));
    while (true) {
        struct mensaje *msj = resp.getRequest();
        if(msj!=NULL)
        {
        int size =msj->operationId;
        //printf("sms id %d",  msj->operationId);
        char datos[1000];
            //string re= string(msj->arguments);
        memcpy(datos, msj->arguments, sizeof(char)*size);
            //cout<<datos<<endl;
            for(int i = 0; i < size; i++) {
                cout << datos[i];
            }
            cout << endl;
            int n2[2];
            n2[0]=10;
            n2[1]=11;
            resp.sendReply((char * ) n2);
        }
 }
 }