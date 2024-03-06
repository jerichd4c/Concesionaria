//Librerias utilizadas 

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <algorithm>

//Funciones utilizadas

using namespace std;

//Creacion de estructura "Client"

struct Client {
    int id;
    string first_name;
    string last_name;
    string email;
    int age;
};

//Creacion de funcion para leer clientes

Client readCurrentClient(fstream& file) {
    Client client;
    string line;
    if (getline(file, line)) {
        istringstream iss(line);
        string token;

        getline(iss, token, ';');
        client.id = atoi(token.c_str());
        getline(iss, client.first_name, ';');
        getline(iss, client.last_name, ';');
        getline(iss, token, ';');
        client.email = atoi(token.c_str());
        client.age = atoi(token.c_str());
        //getline(iss, client.age, ';'); ver mas tarde
    }
    return client;
}

//Funcion para crear un menu 

void displayMenu() {
    cout << "Menu:\n";
    cout << "1. Mostrar los carros comprados y vendidos\n";
    cout << "2. Mostrar los datos del vendedor de un carro\n";
    cout << "3. Mostrar los datos del comprador de un carro\n";
    cout << "4. Agregar informacion de un carro comprado o cliente\n";
    cout << "5. Modificar informacion de un carro comprado\n";
    cout << "6. Eliminar datos de un carro\n";
    cout << "7. Eliminar datos de un cliente\n";
    cout << "8. Mostrar perdidas\n";
    cout << "9. Mostrar ganancias\n";
    cout << "10. Salir\n";
    cout << "Seleccione una opcion: ";
}

//Implementancion 

int main() {
    fstream file("clients.csv", ios::in | ios::out | ios::app);

    if (!file.is_open()) {
        cerr << "Error al abrir el archivo." << endl;
        return 1;
    }
    int option;
        displayMenu();
        cin >> option;
}