#include "./modelo/modelo.h"
#include "./vista/vista.h"
#include "./controlador/controlador.h"
using namespace std;

int main() {
    const std::string clientsFile = "../assets/clients.csv";
    const std::string carsFile = "../assets/cars_data.csv";
 	Client clients[MAX_CLIENTS];
    Cars cars[MAX_CARS];
    int numClients = 0;
    int numCars = 0;
    
    std::fstream file("../assets/cars_data.csv", std::ios::in | std::ios::out | std::ios::app);
    std::fstream file2("../assets/clients.csv", std::ios::in | std::ios::out | std::ios::app);

    int choice;
    int clientId;
    do {
        displayMenu();
        while (!(std::cin >> choice) || choice < 0) {
            std::cout << "Dato invalido, introduzca un valor numerico: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        switch (choice) {
            case 1:
                std::cout << "Introduzca ID del cliente: ";
                while (!(std::cin >> clientId) || clientId <= 0) {
                    std::cout << "Dato invalido, introduzca un valor numerico: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
                displayClientCarsInfo(clientId, clients, numClients, cars, numCars);
                break;
            case 2:
                addBoughtCar(cars, numCars, clients, numClients);
                break;
            case 3:
                updateSoldCar(cars, numCars, clients, numClients);
                break;
            case 4:
                getProfit(cars, numCars);
                break;
            case 5:
                deleteItem(file, file2, numClients, numCars, cars, clients);
                break;
            case 0:
                std::cout << "Saliendo del programa..." << std::endl;
                break;
            default:
                std::cout << "Opcion invalida, intente nuevamente." << std::endl;
        }
    } while (choice != 0);
    
    return 0;
}