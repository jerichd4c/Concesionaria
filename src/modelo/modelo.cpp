#include "modelo.h"

Cars readCurrentCar(std::fstream& file) {
    Cars car;
    std::string line;
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        std::getline(iss, token, ';');
        car.id = std::atoi(token.c_str());

        std::getline(iss, car.maker, ';');
        std::getline(iss, car.model, ';');

        std::getline(iss, token, ';');
        car.year = std::atoi(token.c_str());

        std::getline(iss, token, ';');
        car.sold_to = std::atoi(token.c_str());

        std::getline(iss, token, ';');
        car.bought_to = std::atoi(token.c_str());

        std::getline(iss, token, ';');
        car.sold_for = std::atoi(token.c_str());

        std::getline(iss, token, ';');
        car.bought_for = std::atoi(token.c_str());
    }
    return car;
}

void writeCurrentCar(std::fstream& file, const Cars& car) {
    file << car.id << ';' << car.maker << ';' << car.model << ';'
         << car.year << ';' << car.sold_to << ';' << car.bought_to << ';' << car.sold_for << ';' << car.bought_for << '\n';
}

Client readCurrentClient(std::fstream& file) {
    Client client;
    std::string line;
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        std::getline(iss, token, ';');
        client.id = std::atoi(token.c_str());

        std::getline(iss, client.first_name , ';');
        std::getline(iss, client.last_name , ';');
        std::getline(iss, client.email , ';');

        std::getline(iss, token, ';');
        client.age = std::atoi(token.c_str());
    }
    return client;
}

void writeCurrentClient(std::fstream& file, const Client& client) {
    file << client.id << ';' << client.first_name << ';' << client.last_name << ';' << client.email << ';' << client.age << '\n';
}

void readClientsFromFile(const std::string& filename, Client clients[], int& size) {
    std::ifstream file(filename.c_str());

    if (file.is_open()) {
        std::string line;
        size = 0;

        while (std::getline(file, line) && size < MAX_CLIENTS) {
            std::istringstream iss(line);
            char delimiter = ';';

            // Se leen los datos desde el archivo CSV
            iss >> clients[size].id >> delimiter;
            std::getline(iss, clients[size].first_name, delimiter);
            std::getline(iss, clients[size].last_name, delimiter);
            std::getline(iss, clients[size].email, delimiter);
            iss >> clients[size].age;

            size++;
        }

        file.close();
    } else {
        std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
    }
}

void readCarsFromFile(const std::string& filename, Cars cars[], int& size) {
    std::ifstream file(filename.c_str());

    if (file.is_open()) {
        std::string line;
        size = 0;

        while (std::getline(file, line) && size < MAX_CARS) {
            std::istringstream iss(line);
            char delimiter = ';';

            // Leemos los datos desde el archivo CSV
            iss >> cars[size].id >> delimiter;
            std::getline(iss, cars[size].maker, delimiter);
            std::getline(iss, cars[size].model, delimiter);
            iss >> cars[size].year >> delimiter;
            iss >> cars[size].sold_to >> delimiter;
            iss >> cars[size].bought_to >> delimiter;
            iss >> cars[size].sold_for >> delimiter;
            iss >> cars[size].bought_for;

            size++;
        }

        file.close();
    } else {
        std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
    }
}