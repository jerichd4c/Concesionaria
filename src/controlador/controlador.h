#ifndef CONTROLADOR_H
#define CONTROLADOR_H

#include "../modelo/modelo.h"

void addClient(Client clients[], int& numClients);
void addBoughtCar(Cars cars[], int& numCars, Client clients[], int& numClients);
void updateSoldCar(Cars cars[], int& numCars, Client clients[], int& numClients);
void getProfit(const Cars cars[], int size);
void deleteItem(std::fstream& file, std::fstream& file2, int numClients, int numCars, const Cars cars[], const Client clients[]);

#endif // CONTROLADOR_H
