#include "vista.h"
#include <iostream>
using namespace std;

void displayMenu() {
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Mostrar informacion del cliente" << std::endl;
    std::cout << "2. Registrar carro nuevo" << std::endl;
    std::cout << "3. Actualizar informacion del carro" << std::endl;
    std::cout << "4. Sacar ganancias de un carro" << std::endl;
    std::cout << "5. Borrar carro o cliente" << std::endl;
    std::cout << "0. Salir del programa" << std::endl;
    std::cout << "Opción: ";
}

void displayClientCarsInfo(int clientId, const Client clients[], int numClients, const Cars cars[], int numCars) {
    //Encontrar el cliente con un ID
    int clientIndex = -1;
    for (int i = 0; i < numClients; ++i) {
        if (clients[i].id == clientId) {
            clientIndex = i;
            break;
        }
    }

    if (clientIndex == -1) {
        cout << "Cliente con ID " << clientId << " no encontrado." << endl;
        return;
    }

    //Mostrar información del cliente
    cout << "ID: " << clients[clientIndex].id << endl;
    cout << "Nombre: " << clients[clientIndex].first_name << " " << clients[clientIndex].last_name << endl;
    cout << "Email: " << clients[clientIndex].email << endl;
    cout << "Edad: " << clients[clientIndex].age << endl;

    //Contar y mostrar carros comprados y vendidos por el cliente
    int carsBought = 0;
    int carsSold = 0;

    cout << "\nCarros comprados por el cliente: \n" << endl;
    for (int i = 0; i < numCars; ++i) {
        if (cars[i].bought_to == clientId) {
            carsBought++;
            cout << cars[i].id << " " << cars[i].maker << " " << cars[i].model << ", " << cars[i].year << endl;
        }
    }

    cout << "\nCars vendidos por el cliente: \n" << endl;
    for (int i = 0; i < numCars; ++i) {
        if (cars[i].sold_to == clientId) {
            carsSold++;
            cout << cars[i].maker << " " << cars[i].model << ", " << cars[i].year << endl;
        }
    }

    //Mostrar el total de carros comprados y vendidos
    cout << "\n\n";
    cout << "Total de carros comprados por el cliente: " << carsBought << endl;
    cout << "Total de carros vendidos por el cliente: " << carsSold << endl;
    cout << "\n\n";
}