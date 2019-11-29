#include<bits/stdc++.h>
using namespace std;

int main() {
	
	// Cargar el archivo de palabras:
	map<string, int> diccionario;
    std::ifstream file("academia.txt");
    std::string str;
    while (std::getline(file, str)) {
        std::cout << str << "\n";
        diccionario.insert(pair<string, int>(str, 0));
    }

	while(true) {	// Esperando solicitudes todo el tiempo
		Respuesta resp(7200);
    cout << "Servidor iniciado....\n";
    std::ofstream file1("registros.txt", std::ofstream::out | std::ofstream::trunc);
    file1.close();
    ofstream output;
    while (true) {
        struct mensaje *msj = resp.getRequest();
        if(msj != NULL) {
            output.open("registros.txt", ios::out | ios::app );
        	char registro[31];
	        memcpy(registro, &msj->arguments, 31);
            output.write(registro,31);
            output.write("\n",1);
            int nbd=1;
	        resp.sendReply((char *)&nbd);
            output.close();
        }
    }
	}
}