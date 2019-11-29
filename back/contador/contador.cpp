#include<bits/stdc++.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream> 
#include "Respuesta.h"
#include <thread>  
#define MAX 20000
#define tamDiccionario 10000
#define tamFrase 31
using namespace std;

void cargarDiccicionario(set<string> &diccionario);        // Cargar archivo de palabras
void cargarAbecedario(set<unsigned char> &abecedario);     // Cargar abecedario
void convertirAMinuscula(unsigned char &c);                     // Convertir a minuscula
void convertirAMinusculaAcento(unsigned char &c);               // Convertir a minuscula con acento
vector<string> obtenerPalabras(set<string> &diccionario, set<unsigned char> &abecedario, string &frase);
int contar(set<string> &diccionario, vector<string> &palabras);

int main(int argc, char *argv[]) {
    int existen, noExisten, nbd;
	set<string> diccionario;
    set<unsigned char> abecedario;

    cargarDiccicionario(diccionario);    // Inicializar diccionario
    cargarAbecedario(abecedario);        // Inicializar abecedario
    
    // Recibir solicitud
    Respuesta resp(atoi(argv[1]));
    //Respuesta resp(7200);
    while (true) {
        struct mensaje *msj = resp.getRequest();
        if(msj != NULL) {
            int size = msj->operationId;
            char datos[MAX];
            memcpy(datos, msj->arguments, sizeof(char)*size);
            string frase = "";
            for(int i = 0; i < size; i++) {
                unsigned char auxChar = datos[i];
                //printf("char: %d\n", auxChar);
                frase += auxChar;
            }
            //cout << "Recibi frase: " << frase << endl;
            // Obtener palabras
            vector<string> palabras;
            palabras = obtenerPalabras(diccionario, abecedario, frase);

            // Contar palabras que existen en el diccionario
            existen = contar(diccionario, palabras);
            noExisten = tamDiccionario - existen;

            cout << "Existen: " << existen << endl;
            // cout << "No existen: " << noExisten << endl;
            cout << "Palabras leidas: " << palabras.size() << endl;
            int palabrasContadas[2];
            palabrasContadas[0] = existen;
            palabrasContadas[1] = palabras.size();
            resp.sendReply((char *) palabrasContadas);
        }
    }
    // Recibir palabra
    //string frase = "La última pregunta es la más embarazosa, pues la única respuesta que puedo dar es ésta: «Tal vez. Eso lo verá usted leyendo la novela.» ¿Pero y si, después de leerla, el lector no ve en mi héroe nada de particular? Digo esto porque preveo que puede ocurrir así. A mis ojos, el personaje es notable, pero no tengo ninguna confianza en convencer de ello al lector. Es un hombre que procede con seguridad, pero de un modo vago y oscuro. Sin embargo, resultaría sorprendente, en nuestra época, pedir a las personas claridad. De lo que no hay duda es de que es un ser extraño, incluso original. Pero estas características, lejos de conferir el derecho de atraer la atención, representan un perjuicio, especialmente cuando todo el mundo se esfuerza en coordinar las individualidades y extraer un sentido general del absurdo colectivo. El hombre original es, en la mayoría de los casos, un individuo que se aísla de los demás. ¿No es cierto?";
    //cout << "string size: " << frase.size() << endl;
}

// Cargar el archivo de palabras:
void cargarDiccicionario(set<string> &diccionario) {
    std::ifstream file("academia.txt");
    std::string str, aux;
    while (std::getline(file, str)) {
        stringstream s(str);
        while(s >> str) {
            diccionario.insert(str);
        }
    }
}

//    Cargar abecedario valido
void cargarAbecedario(set<unsigned char> &abecedario) {
    // abecedario.insert(195);         // Agregar 195 de acentos:
    // abecedario.insert(161);         // Agregar a con acento:
    // abecedario.insert(169);         // Agregar e con acento:
    // abecedario.insert(173);         // Agregar i con acento:
    // abecedario.insert(179);         // Agregar o con acento:
    // abecedario.insert(186);         // Agregar u con acento:
    // abecedario.insert(129);         // Agregar A con acento:
    // abecedario.insert(137);         // Agregar E con acento:
    // abecedario.insert(141);         // Agregar I con acento:
    // abecedario.insert(147);         // Agregar O con acento:
    // abecedario.insert(154);         // Agregar U con acento:
    // abecedario.insert(164);         // Agregar ñ:
    // abecedario.insert(165);         // Agregar Ñ:

    // Cargar mayusculas y minusculas
    for(int i = 65; i <= 90; i++) {
        abecedario.insert(i);
        abecedario.insert(i + 32);
    }
}

// Convertir a minuscula
void convertirAMinuscula(unsigned char &c) {
    c += 32;
}

// Convertir a minuscula con acento
void convertirAMinusculaAcento(unsigned char &c) {
    c += 32;
}

// Obtener palabras
vector<string> obtenerPalabras(set<string> &diccionario, set<unsigned char> &abecedario, string &frase) {
    vector<string> palabras;
    string palabra = "";
    for(int i = 0; i < frase.size(); i++) {
        unsigned char c = frase[i]; 
        //printf("char: %c : %d\n", c, c);      
        // Caracter existe en el abecedario
        if(abecedario.find(c) != abecedario.end()) {
            // Mayusculas
            if((c >= 65) && (c <= 90)) convertirAMinuscula(c);
            if((c == 129) or (c == 137) or (c == 141) or (c == 147) or (c == 154)) convertirAMinusculaAcento(c);
            palabra += c;
        }
        else { // Ya tengo una palabra
            if(palabra.size() > 0) palabras.push_back(palabra);
            palabra = "";              // Limpiar la variable de palabra 
        }
    }
    // Verificar si hay una palabra:
    if(palabra.size() > 0) palabras.push_back(palabra);

    return palabras;
}

// Contar palabras que existen en el diccionario
int contar(set<string> &diccionario, vector<string> &palabras) {
    int existen = 0;
    for(int i = 0; i < palabras.size(); i++) {
        //cout << palabras[i] << endl;
        if(diccionario.find(palabras[i]) != diccionario.end()) existen++;
    }
    return existen; 
}