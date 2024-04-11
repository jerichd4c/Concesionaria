#include "vista.h"
#include <iostream>

void displayMenu() {
    std::cout << "Menu:" << std::endl;
    std::cout << "1. Mostrar información del cliente" << std::endl;
    std::cout << "2. Registrar carro nuevo" << std::endl;
    std::cout << "3. Actualizar información del carro" << std::endl;
    std::cout << "4. Sacar ganancias de un carro" << std::endl;
    std::cout << "5. Borrar carro o cliente" << std::endl;
    std::cout << "0. Salir del programa" << std::endl;
    std::cout << "Opción: ";
}

void displayClientCarsInfo(int clientId, const Client clients[], int numClients, const Cars cars[], int numCars) {
	
    // Encontrar el cliente con un ID
    int clientIndex = -1;
    for (int i = 0; i < numClients; ++i) {
        if (clients[i].getId() == clientId) {
            clientIndex = i;
            break;
        }
    }

    if (clientIndex == -1) {
        std::cout << "Cliente con ID " << clientId << " no encontrado." << std::endl;
        return;
    }

    // Mostrar información del cliente
    std::cout << "ID: " << clients[clientIndex].getId() << std::endl;
    std::cout << "Nombre: " << clients[clientIndex].getFirstName() << " " << clients[clientIndex].getLastName() << std::endl;
    std::cout << "Email: " << clients[clientIndex].getEmail() << std::endl;
    std::cout << "Edad: " << clients[clientIndex].getAge() << std::endl;

    // Contar y mostrar carros comprados y vendidos por el cliente
    int carsBought = 0;
    int carsSold = 0;

    std::cout << "\nCarros comprados por el cliente: \n" << std::endl;
    for (int i = 0; i < numCars; ++i) {
        if (cars[i].getBoughtTo() == clientId) {
            carsBought++;
            std::cout << cars[i].getId() << " " << cars[i].getMaker() << " " << cars[i].getModel() << ", " << cars[i].getYear() << std::endl;
        }
    }

    std::cout << "\nCars vendidos por el cliente: \n" << std::endl;
    for (int i = 0; i < numCars; ++i) {
        if (cars[i].getSoldTo() == clientId) {
            carsSold++;
            std::cout << cars[i].getMaker() << " " << cars[i].getModel() << ", " << cars[i].getYear() << std::endl;
        }
    }

    // Mostrar el total de carros comprados y vendidos
    std::cout << "\n\n";
    std::cout << "Total de carros comprados por el cliente: " << carsBought << std::endl;
    std::cout << "Total de carros vendidos por el cliente: " << carsSold << std::endl;
    std::cout << "\n\n";
}