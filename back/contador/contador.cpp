#include<bits/stdc++.h>
using namespace std;
typedef pair<string, int> pairDic;
typedef pair<char, int> pairAbe;

void cargarDiccicionario(map<string, int> &diccionario);        // Cargar archivo de palabras
void cargarAbecedario(map<unsigned char, int> &abecedario);     // Cargar abecedario
void convertirAMinuscula(unsigned char &c);                     // Convertir a minuscula
void convertirAMinusculaAcento(unsigned char &c);               // Convertir a minuscula con acento
vector<string> obtenerPalabras(map<string, int> &diccionario, map<unsigned char, int> &abecedario, string &frase);

int main() {
    int existen, noExisten;
	map<string, int> diccionario;
    map<unsigned char, int> abecedario;
    vector<string> palabras;

    cargarDiccicionario(diccionario);    // Inicializar diccionario
    cargarAbecedario(abecedario);        // Inicializar abecedario
    
    // Recibir palabra
    string frase = "hola, cómo estas, yo muy bien CÓmo h ";
    cout << "string size: " << frase.size() << endl;

    // Obtener palabras
    palabras = obtenerPalabras(diccionario, abecedario, frase);

    // ---------------------------------
    //       Obtener contadores
    // ---------------------------------
    // Verificar si la palabra existe en el diccionario
    existen = 0; noExisten = 0;
    for(int i = 0; i < palabras.size(); i++) {
        cout << palabras[i] << endl;
        if(diccionario.find(palabras[i]) != diccionario.end())
           existen++;
        else 
            noExisten++;
    }
    cout << "Existen: " << existen << endl;
    cout << "No existen: " << noExisten << endl;
}



// Cargar el archivo de palabras:
void cargarDiccicionario(map<string, int> &diccionario) {
    std::ifstream file("academia.txt");
    std::string str;
    while (std::getline(file, str)) {
        //std::cout << str << "\n";
        diccionario.insert(pairDic(str, 0));
    }
}

//    Cargar abecedario valido
void cargarAbecedario(map<unsigned char, int> &abecedario) {
    abecedario.insert(pairAbe(195, 0));         // Agregar 195 de acentos:
    abecedario.insert(pairAbe(161, 0));         // Agregar a con acento:
    abecedario.insert(pairAbe(169, 0));         // Agregar e con acento:
    abecedario.insert(pairAbe(173, 0));         // Agregar i con acento:
    abecedario.insert(pairAbe(179, 0));         // Agregar o con acento:
    abecedario.insert(pairAbe(186, 0));         // Agregar u con acento:
    abecedario.insert(pairAbe(129, 0));         // Agregar A con acento:
    abecedario.insert(pairAbe(137, 0));         // Agregar E con acento:
    abecedario.insert(pairAbe(141, 0));         // Agregar I con acento:
    abecedario.insert(pairAbe(147, 0));         // Agregar O con acento:
    abecedario.insert(pairAbe(154, 0));         // Agregar U con acento:
    abecedario.insert(pairAbe(164, 0));         // Agregar ñ:
    abecedario.insert(pairAbe(165, 0));         // Agregar Ñ:


    // Cargar mayusculas y minusculas
    for(int i = 65; i <= 90; i++) {
        abecedario.insert(pairAbe(i, 0));
        abecedario.insert(pairAbe(i + 32, 0));
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
vector<string> obtenerPalabras(map<string, int> &diccionario, map<unsigned char, int> &abecedario, string &frase) {
    vector<string> palabras;
    string palabra = "";
    for(int i = 0; i < frase.size(); i++) {
        unsigned char c = frase[i]; 
        printf("char: %c : %d\n", c, c);      
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
