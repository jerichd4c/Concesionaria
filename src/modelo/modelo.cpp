#include "modelo.h"

Cars readCurrentCar(std::fstream& file) {
    Cars car;
    std::string line;
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        std::getline(iss, token, ';');
        car.setId(std::atoi(token.c_str()));

        // Leer el fabricante y establecerlo en el carro
        std::getline(iss, token, ';');
        car.setMaker(token);

        // Leer el modelo y establecerlo en el carro
        std::getline(iss, token, ';');
        car.setModel(token);

        // Leer el año y establecerlo en el carro
        std::getline(iss, token, ';');
        car.setYear(std::atoi(token.c_str()));

        // Leer el ID del cliente al que se vendió y establecerlo en el carro
        std::getline(iss, token, ';');
        car.setSoldTo(std::atoi(token.c_str()));

        // Leer el ID del cliente que lo compró y establecerlo en el carro
        std::getline(iss, token, ';');
        car.setBoughtTo(std::atoi(token.c_str()));

        // Leer el precio de venta y establecerlo en el carro
        std::getline(iss, token, ';');
        car.setSoldFor(std::atoi(token.c_str()));

        // Leer el precio de compra y establecerlo en el carro
        std::getline(iss, token, ';');
        car.setBoughtFor(std::atoi(token.c_str()));
    }
    return car;
}

void writeCurrentCar(std::fstream& file, const Cars& car) {
    file << car.getId() << ';' << car.getMaker() << ';' << car.getModel() << ';'
         << car.getYear() << ';' << car.getSoldTo() << ';' << car.getBoughtTo() << ';' << car.getSoldFor() << ';' << car.getBoughtFor() << '\n';
}

Client readCurrentClient(std::fstream& file) {
    Client client;
    std::string line;
    if (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;

        std::getline(iss, token, ';');
        client.setId(std::atoi(token.c_str()));

        // Leer el primer nombre y establecerlo en el cliente
        std::getline(iss, token, ';');
        client.setFirstName(token);

        // Leer el apellido y establecerlo en el cliente
        std::getline(iss, token, ';');
        client.setLastName(token);

        // Leer el correo electrónico y establecerlo en el cliente
        std::getline(iss, token, ';');
        client.setEmail(token);

        // Leer la edad y establecerla en el cliente
        std::getline(iss, token, ';');
        client.setAge(std::atoi(token.c_str()));
    }
    return client;
}

void writeCurrentClient(std::fstream& file2, const Client& client) {
    file2 << client.getId() << ';' << client.getFirstName() << ';' << client.getLastName() << ';' << client.getEmail() << ';' << client.getAge() << '\n';
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
            int id;
            std::string firstName, lastName, email;
            int age;

            iss >> id >> delimiter;
            std::getline(iss, firstName, delimiter);
            std::getline(iss, lastName, delimiter);
            std::getline(iss, email, delimiter);
            iss >> age;

            clients[size].setId(id);
            clients[size].setFirstName(firstName);
            clients[size].setLastName(lastName);
            clients[size].setEmail(email);
            clients[size].setAge(age);

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

            // Leer los datos desde el archivo CSV
            int id, year, soldTo, boughtTo, soldFor, boughtFor;
            std::string maker, model;

            iss >> id >> delimiter;
            std::getline(iss, maker, delimiter);
            std::getline(iss, model, delimiter);
            iss >> year >> delimiter;
            iss >> soldTo >> delimiter;
            iss >> boughtTo >> delimiter;
            iss >> soldFor >> delimiter;
            iss >> boughtFor;

            cars[size].setId(id);
            cars[size].setMaker(maker);
            cars[size].setModel(model);
            cars[size].setYear(year);
            cars[size].setSoldTo(soldTo);
            cars[size].setBoughtTo(boughtTo);
            cars[size].setSoldFor(soldFor);
            cars[size].setBoughtFor(boughtFor);

            size++;
        }

        file.close();
    } else {
        std::cerr << "No se pudo abrir el archivo: " << filename << std::endl;
    }
}