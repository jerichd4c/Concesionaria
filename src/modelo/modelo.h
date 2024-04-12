#ifndef MODELO_H
#define MODELO_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdlib>

const int MAX_CLIENTS = 150;
const int MAX_CARS = 1050;

class Client {
public:
    int getId() const { return id; }
    void setId(int newId) { id = newId; }
    std::string getFirstName() const { return first_name; }
    void setFirstName(const std::string& newFirstName) { first_name = newFirstName; }
    std::string getLastName() const { return last_name; }
    void setLastName(const std::string& newLastName) { last_name = newLastName; }
    std::string getEmail() const { return email; }
    void setEmail(const std::string& newEmail) { email = newEmail; }
    int getAge() const { return age; }
    void setAge(int newAge) { age = newAge; }
    int id;
    std::string first_name;
    std::string last_name;
    std::string email;
    int age;
};

class Cars {
public:
    int getId() const { return id; }
    void setId(int newId) { id = newId; }
    std::string getMaker() const { return maker; }
    void setMaker(const std::string& newMaker) { maker = newMaker; }
    std::string getModel() const { return model; }
    void setModel(const std::string& newModel) { model = newModel; }
    int getYear() const { return year; }
    void setYear(int newYear) { year = newYear; }
    int getSoldTo() const { return sold_to; }
    void setSoldTo(int newSoldTo) { sold_to = newSoldTo; }
    int getBoughtTo() const { return bought_to; }
    void setBoughtTo(int newBoughtTo) { bought_to = newBoughtTo; }
    int getSoldFor() const { return sold_for; }
    void setSoldFor(int newSoldFor) { sold_for = newSoldFor; }
    int getBoughtFor() const { return bought_for; }
    void setBoughtFor(int newBoughtFor) { bought_for = newBoughtFor; }

private:
    int id;
    std::string maker;
    std::string model;
    int year;
    int sold_to;
    int bought_to;
    int sold_for;
    int bought_for;
};

void writeCurrentCar(std::fstream& file, const Cars& car);
void writeCurrentClient(std::fstream& file2, const Client& client, bool isFirstLine);
void readClientsFromFile(const std::string& filename, Client clients[], int& size);
void readCarsFromFile(const std::string& filename, Cars cars[], int& size);
void readCurrentCar(std::fstream& file);
void readCurrentClient(std::fstream& file);

#endif /* MODELO_H */