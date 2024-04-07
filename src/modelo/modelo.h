#ifndef MODELO_H
#define MODELO_H

// Incluir librerías y definir constantes necesarias
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdlib>

const int MAX_CLIENTS = 150;
const int MAX_CARS = 1050;

// Definir estructuras
struct Client {
    int id;
    std::string first_name;
    std::string last_name;
    std::string email;
    int age;
};

struct Cars {
    int id;
    std::string maker;
    std::string model;
    int year;
    int sold_to;
    int bought_to;
    int sold_for;
    int bought_for;
};

// Declarar funciones del modelo
Cars readCurrentCar(std::fstream& file);
void writeCurrentCar(std::fstream& file, const Cars& car);
Client readCurrentClient(std::fstream& file);
void writeCurrentClient(std::fstream& file, const Client& client);
void readClientsFromFile(const std::string& filename, Client clients[], int& size);
void readCarsFromFile(const std::string& filename, Cars cars[], int& size);

#endif /* MODELO_H */