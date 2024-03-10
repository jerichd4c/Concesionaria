#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

const int MAX_CLIENTS = 101;
const int MAX_CARS = 1001;

// Estructura Client
struct Client {
    int id;
    string first_name;
    string last_name;
    string email;
    int age;
};

// Estructura Cars
struct Cars {
    int id;
    string maker;
    string model;
    int year;
    int sold_to;
    int bought_to;
    int sold_for;
    int bought_for;
};

// Función para leer datos desde el archivo CSV para la estructura Client
void readClientsFromFile(const string& filename, Client clients[], int& size) {
    ifstream file(filename.c_str());

    if (file.is_open()) {
        string line;
        size = 0;

        while (getline(file, line) && size < MAX_CLIENTS) {
            istringstream iss(line);
            char delimiter = ';';

            // Se leen los datos desde el archivo CSV
            iss >> clients[size].id >> delimiter;
            getline(iss, clients[size].first_name, delimiter);
            getline(iss, clients[size].last_name, delimiter);
            getline(iss, clients[size].email, delimiter);
            iss >> clients[size].age;

            size++;
        }

        file.close();
    } else {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
    }
}

// Función para leer datos desde el archivo CSV para la estructura Cars
void readCarsFromFile(const string& filename, Cars cars[], int& size) {
    ifstream file(filename.c_str());

    if (file.is_open()) {
        string line;
        size = 0;

        while (getline(file, line) && size < MAX_CARS) {
            istringstream iss(line);
            char delimiter = ';';

            // Leemos los datos desde el archivo CSV
            iss >> cars[size].id >> delimiter;
            getline(iss, cars[size].maker, delimiter);
            getline(iss, cars[size].model, delimiter);
            iss >> cars[size].year >> delimiter;
            iss >> cars[size].sold_to >> delimiter;
            iss >> cars[size].bought_to >> delimiter;
            iss >> cars[size].sold_for >> delimiter;
            iss >> cars[size].bought_for;

            size++;
        }

        file.close();
    } else {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
    }
}

// Función para mostrar datos de la estructura Client
void showClients(const Client clients[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "ID: " << clients[i].id << "\t"
             << "Nombre: " << clients[i].first_name << " " << clients[i].last_name << "\t"
             << "Email: " << clients[i].email << "\t"
             << "Edad: " << clients[i].age << endl;
    }
}

// Función para mostrar datos de la estructura Cars
void showCars(const Cars cars[], int size) {
    for (int i = 0; i < size; i++) {
        cout << "ID: " << cars[i].id << "\t"
             << "Fabricante: " << cars[i].maker << "\t"
             << "Modelo: " << cars[i].model << "\t"
             << "Año: " << cars[i].year << "\t"
             << "Vendido a: " << cars[i].sold_to << "\t"
             << "Comprado a: " << cars[i].bought_to << "\t"
             << "Precio de venta: " << cars[i].sold_for << "\t"
             << "Precio de compra: " << cars[i].bought_for << endl;
    }
}

// Función para mostrar los carros comprados por cliente
void showCarsBoughtByClient(const Cars cars[], int size, int clientId) {
    cout << "Carros comprados por el Cliente " << clientId << ":" << endl;

    int count = 0;  // Contador de carros comprados por el cliente

    for (int i = 0; i < size; i++) {
        // Verifica si el carro actual fue comprado por el clienteX
        if (cars[i].bought_to == clientId) {
            count++;
            cout << cars[i].maker << " " << cars[i].model << ", " << cars[i].year << endl;
        }
    }

    if (count == 0) {
        cout << "El Cliente " << clientId << " no ha comprado ningún carro." << endl;
    } else {
        cout << "\nTotal de carros comprados por el Cliente " << clientId << ": " << count << endl;
    }
}

// Función general para TODOS los clientes
void showAllCarsByClients(const Client clients[], int numClients, const Cars cars[], int numCars, bool boughtCars) {
    cout << "Carros " << (boughtCars ? "comprados" : "vendidos") << " por todos los clientes:" << endl;

    for (int i = 0; i < numClients; i++) {
        int clientId = clients[i].id;
        cout << "\nCliente " << clientId << ":" << endl;

        int count = 0;  // Contador de carros comprados o vendidos por el cliente

        for (int j = 0; j < numCars; j++) {
            // Verifica si el carro actual coincide con la condición y pertenece al cliente actual
            if ((boughtCars && cars[j].sold_to == clientId) || (!boughtCars && cars[j].bought_to == clientId)) {
                count++;
                cout << cars[j].maker << " " << cars[j].model << ", " << cars[j].year << endl;
            }
        }

        if (count == 0) {
            cout << "El Cliente " << clientId << " no ha " << (boughtCars ? "comprado" : "vendido") << " ningún carro." << endl;
        } else {
            cout << "Total de carros " << (boughtCars ? "comprados" : "vendidos") << " por el Cliente " << clientId << ": " << count << endl;
        }
    }
}

//  Función para mostrar carros totales y vendidos
void getTotalCarsBoughtAndSold(const Cars cars[], int numCars, int& totalBought, int& totalSold) {
    totalBought = 0;
    totalSold = 0;

    for (int i = 0; i < numCars; i++) {
        // Verifica si el carro ha sido comprado
        if (cars[i].bought_to != 0) {
            totalBought++;
        }

        // Verifica si el carro ha sido vendido
        if (cars[i].sold_to != 0) {
            totalSold++;
        }
    }
}

int main() {
    // Nombre de los archivos CSV
    const string clientsFilename = "clients.csv";
    const string carsFilename = "cars_data.csv";

    // Arreglos para almacenar datos
    Client clients[MAX_CLIENTS];
    Cars cars[MAX_CARS];

    // Tamaños de los arreglos
    int clientSize = 0;
    int carSize = 0;

    // Leer datos desde los archivos CSV
    readClientsFromFile(clientsFilename, clients, clientSize);
    readCarsFromFile(carsFilename, cars, carSize);
    
    // Mostrar carros comprados y vendidos a un cliente
	showAllCarsByClients(clients, MAX_CLIENTS, cars, MAX_CARS, true);  // Mostrar carros comprados por todos los clientes
	showAllCarsByClients(clients, MAX_CLIENTS, cars, MAX_CARS, false);  // Mostrar carros vendidos por todos los clientes
	
	// Mostrar carros TOTALES 
	int totalBought, totalSold;
	getTotalCarsBoughtAndSold(cars, MAX_CARS, totalBought, totalSold);
	cout<<" "<<endl;
	cout << "Total de carros comprados: " << totalBought << endl;
	cout << "Total de carros vendidos: " << totalSold << endl;
	
}
