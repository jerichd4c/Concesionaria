//Librerias utilizadas
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <cstdlib>

using namespace std;

//Tamaño de arreglos
const int MAX_CLIENTS = 150;
const int MAX_CARS = 1050;

//Estructura Client
struct Client {
    int id;
    string first_name;
    string last_name;
    string email;
    int age;
};

//Estructura Cars
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

//Función leer carros 
Cars readCurrentCar(fstream& file) {
    Cars car;
    string line;
    if (getline(file, line)) {
        istringstream iss(line);
        string token;

        getline(iss, token, ';');
        car.id = atoi(token.c_str());

        getline(iss, car.maker, ';');
        getline(iss, car.model, ';');

        getline(iss, token, ';');
        car.year = atoi(token.c_str());

        getline(iss, token, ';');
        car.sold_to = atoi(token.c_str());

        getline(iss, token, ';');
        car.bought_to = atoi(token.c_str());

        getline(iss, token, ';');
        car.sold_for = atoi(token.c_str());

        getline(iss, token, ';');
        car.bought_for = atoi(token.c_str());
    }
    return car;
}

//Función escribir carros
void writeCurrentCar(fstream& file, const Cars& car) {
    file << car.id << ';' << car.maker << ';' << car.model << ';'
         << car.year << ';' << car.sold_to << ';' << car.bought_to << ';' << car.sold_for << ';' << car.bought_for << '\n';
}

//Función leer clientes
Client readCurrentClient(fstream& file) {
    Client client;
    string line;
    if (getline(file, line)) {
        istringstream iss(line);
        string token;

        getline(iss, token, ';');
        client.id = atoi(token.c_str());

        getline(iss, client.first_name , ';');
        getline(iss, client.last_name , ';');
        getline(iss, client.email , ';');

        getline(iss, token, ';');
        client.age = atoi(token.c_str());
    }
    return client;
}

//Función escribir clientes
void writeCurrentClient(fstream& file, const Client& client) {
    file << client.id << ';' << client.first_name << ';' << client.last_name << ';' << client.email << ';' << client.age << '\n';
}

//Función para leer datos desde el archivo CSV para la estructura Client
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

//Función para leer datos desde el archivo CSV para la estructura Cars
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

//Función mostrar carros de clientes 
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

//Función para agregar clientes
void addClient(Client clients[], int& numClients) {
    //Variable para nuevo cliente
    Client newClient;
    
    //Encontrar ID disponible para cliente
    int nextClientId = numClients + 1;

    //Actualizar informacion del ID del cliente
    newClient.id = nextClientId;

	//Agregar informacion del cliente
	cout<<"Introduzca el Nombre del cliente: "; 
	cin>> newClient.first_name;
	cout<<"Introduzca el Apellido del cliente: ";
	cin>> newClient.last_name;
	cout<<"Introduzca el email del cliente: ";
	cin>> newClient.email;
	cout<<"Introduzca la edad del cliente: ";
	//Input validation
	while (!(cin >> newClient.age) || newClient.age < 0 || newClient.age> 150) {
        cout << "Dato invalido, introduzca una edad entre 0 y 150 años: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    //Se añade nuevo cliente al arreglo
    clients[numClients] = newClient;
    numClients++;

    //Se agrega los nuevos datos del cliente al archivo
    ofstream clientsFile("../assets/clients.csv", ios::app);
    clientsFile << newClient.id << ';' << newClient.first_name << ';' << newClient.last_name << ';'
                << newClient.email << ';' << newClient.age << endl;
    clientsFile.close();

    cout << "Información del cliente agregada exitosamente." << endl;
}

//Función para agregar carros nuevos
void addBoughtCar(Cars cars[], int& numCars, Client clients[], int& numClients) {
    //Variable para carros nuevos
    Cars newCar;

    cout << "Introduzca los detalles para el carro nuevo:" << endl;

    //Introducir creador
    cout << "Maker: ";
    cin.ignore();
    getline(cin, newCar.maker);

    //Introducir model
    cout << "Model: ";
    getline(cin, newCar.model);

    //Introducir year, si no existe tiene input validation
    cout << "Year: ";
    while (!(cin >> newCar.year) || newCar.year < 1900 || newCar.year > 2024) {
        cout << "Dato invalido, introduzca un año entre 1900 y 2024: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    //Introducir Bought_for 
    cout << "Introduzca por cuanto se compro el carro: ";
    while (!(cin >> newCar.bought_for) || newCar.bought_for <= 0) {
        cout << "Dato invalido, introduzca un valor numerico: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
      
	//Validar si el comprador existe
        int isRegistered;
        int buyerClientId;
        cout << "Es el comprador un cliente registrado? (Si: 1, No: 0): ";
	while (!(cin >> isRegistered) || isRegistered < 0 || isRegistered > 1 ) {
        cout << "Opcion invalida, introduzca 1 o 0: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
        if (isRegistered == 0) {
    //Si no esta registrado, se añade el cliente
    addClient(clients, numClients);
	
    //Se actualiza el carro con la nueva informacion del cliente ID
    newCar.bought_to = numClients;

    //Input validation
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} else {
    cout << "Introduzca el ID del cliente que compro el carro: ";
    while (!(cin >> buyerClientId) || buyerClientId <= 0) {
        cout << "Opcion invalida, introduzca un ID valido: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    //Validar que el ID del comprador existe
    bool buyerExists = false;
    for (int i = 0; i < numClients; ++i) {
        if (clients[i].id == buyerClientId) {
            buyerExists = true;
            break;
        }
    }

    if (!buyerExists) {
        cout << "Cliente con ID: " << buyerClientId << " no encontrado, carro no agregado." << endl;
        return;
    }
}

//Actualizar informacion del carro nuevo
	newCar.id = numCars + 1;
	newCar.bought_to = buyerClientId;
	newCar.sold_to = 0; //Nadie lo ha comprado todavia 
	newCar.sold_for = 0; 

//Se agrega el carro nuevo al arreglo
cout << numCars;
cars[numCars++] = newCar;

    //Escribir el carro actualizado al archivo
	ofstream carsFile("../assets/cars_data.csv", ios::out | ios::app);
	if (!carsFile) {
	    cerr << "Error en abrir el archivo." << endl;
	    return;
	}
	
	carsFile << newCar.id << ';' << newCar.maker << ';' << newCar.model << ';' << newCar.year << ';'
	         << newCar.sold_to << ';' << newCar.bought_to << ';' << newCar.sold_for << ';' << newCar.bought_for << endl;
	
	if (carsFile.fail()) {
	    cerr << "Error escribiendo los datos en el archivo." << endl;
	    carsFile.close();
	    return;
	}
	cout<< "Carro agregado exitosamente" <<endl;
	carsFile.close();
}

//Función para actualizar carros vendidos
void updateSoldCar(Cars cars[], int& numCars, Client clients[], int& numClients) {
    //Variable para el precio de venta del carro
    int soldCarId;
    cout << "Introduzca el ID del carro que fue vendido: ";
    cin >> soldCarId;

    //Encontrar el carro en el arreglo
    for (int i = 0; i < numCars; ++i) {
        if (cars[i].id == soldCarId) {
            //Preguntar si el comprador es un ID registrado
            int isRegistered;
            cout << "Es el comprador un usuario registrado? (Si: 1, No: 0): ";
            cin >> isRegistered;

            if (isRegistered == 0) {
                //Si no esta registrado, se registra
                addClient(clients, numClients);

                //Actualizar informacion del carro con el ID del nuevo cliente
                cars[i].sold_to = numClients;
            } else {
                //Si esta registrado, preguntar por el ID
                int buyerClientId;
                cout << "Introduzca el ID del usuario que compro el carro: ";
                cin >> buyerClientId;

                // Validate that the buyer client ID exists
                bool buyerExists = false;
                for (int j = 0; j < numClients; ++j) {
                    if (clients[j].id == buyerClientId) {
                        buyerExists = true;
                        break;
                    }
                }

                if (!buyerExists) {
                    cout << "Cliente con ID " << buyerClientId << " no encontrado, carro no agregado." << endl;
                    return;
                }

                //Actualizar informacion con el ID del comprador
                cars[i].sold_to = buyerClientId;
            }

            // Input validation para el precio
            cout << "Introduzca por cuanto fue vendido el carro: ";
            while (!(cin >> cars[i].sold_for) || cars[i].sold_for <= 0) {
                cout << "Valor invalido, introduzca un valor valido: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            // Confirmar con el usuario
            int confirm;
            cout << "Confirmar la venta? (Si: 1, No: 0): ";
            cin >> confirm;

            if (confirm == 1) {
                //Escribir los datos del carro en el archivo
                ofstream carsFile("../assets/cars_data.csv");
                for (int j = 0; j < numCars; ++j) {
                    carsFile << cars[j].id << ';' << cars[j].maker << ';' << cars[j].model << ';' << cars[j].year << ';'
                             << cars[j].sold_to << ';' << cars[j].bought_to << ';' << cars[j].sold_for << ';' << cars[j].bought_for << endl;
                }
                carsFile.close();

                cout << "Informacion del carro agregado exitosamente." << endl;
            } else {
                cout << "Venta cancelada, informacion del carro no fue actualizada." << endl;
            }

            return;
        }
    }

    cout << "Carro con ID " << soldCarId << " no fue encontrado, no se realizo ninguna actualizacion." << endl;
}

//Función menu
void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Mostrar informacion del cliente" << endl;
    cout << "2. Registrar carro nuevo" << endl;
    cout << "3. Actualizar informacion del carro" << endl;
    cout << "4. Sacar ganancias de un carro" << endl;
    cout << "5. Borrar carro o cliente" << endl;
    cout << "0. Salir del programa" << endl;
    cout << "Opción: ";
}

//Función para sacar las perdidas y ganancias de carros 
void getProfit(const Cars cars[], int size) {
	int carId;
	cout <<"Seleccione el ID del carro: ";	
	while (!(cin >> carId) || carId <= 0) {
        			cout << "Dato invalido, introduzca un valor numerico mayor a 0: ";
        			cin.clear();
        			cin.ignore(numeric_limits<streamsize>::max(), '\n');
    			}
	bool found = false;
    for (int i = 0; i < size; ++i) {
        if (cars[i].id == carId) {
            found = true; 
    		int diferenciaCarro= cars[i].bought_for-cars[i].sold_for;
    		cout<<"el carro se compro por: "<<cars[i].bought_for<<endl;
    		cout<<"el carro se vendio por: "<<cars[i].sold_for<<endl;
    		if (diferenciaCarro>0) {
    			cout<<"La ganancia fue de: " <<diferenciaCarro<< "$"<<endl;
			} else if (diferenciaCarro<0) {
				cout<<"La perdida fue de: " <<diferenciaCarro*-1<< "$"<<endl;
			} else { 
			cout<<"No hubo ni ganancia ni perdida"<<endl;
			}
		}
	}

	if (!found) {
        cout << "Carro con ID " << carId << " no encontrado." << endl;
	}
}

//Función para borrar carro o cliente
void deleteItem(fstream& file , fstream& file2, int numClients, int numCars, const Cars cars[], const Client clients[]) {
	int opcionElegida;
	cout << "Seleccione opción"<<endl;
	cout << "1. Carro ; 2. Cliente" <<endl;
	cin >> opcionElegida; 
	switch (opcionElegida) {
		case 1: {
	//carros 
	int carIdToDelete;
    cout << "Ingrese el ID del carro: ";
    while (!(cin >> carIdToDelete) || carIdToDelete <= 0) {
        cout << "Dato invalido, introduzca un valor numerico y sea diferente de 0: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
	//input validation
    int carsIndex = -1;
    for (int i = 0; i < numCars; ++i) {
        if (cars[i].id == carIdToDelete) {
            carsIndex = i;
            break;
        }
    }

    if (carsIndex == -1) {
        cout << "Carro con ID " << carIdToDelete << " no encontrado." << endl;
        return;
    }
    
    fstream tempFile("../assets/temp.csv", ios::out | ios::app); 
    Cars currentCar;
    while (!file.eof()) {
        currentCar = readCurrentCar(file);
        if (currentCar.id != carIdToDelete) {
            writeCurrentCar(tempFile, currentCar);
        }
    }

    file.clear();  
    file.seekg(0, ios::beg);  

    file.close();
    tempFile.close();

    remove("../assets/cars_data.csv");
    rename("../assets/temp.csv", "../assets/cars_data.csv");

    file.open("cars_data.csv", ios::in | ios::out | ios::app); 
    cout<<"Carro eliminado exitosamente."<<endl;
		break; 
}
		case 2: {
	//clientes
	int clientIdToDelete;
	cout << "Ingrese el ID del cliente: ";
	while (!(cin >> clientIdToDelete) || clientIdToDelete <= 0) {
        cout << "Dato invalido, introduzca un valor numerico y sea diferente de 0: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
	//input validation
	int clientIndex = -1;
    for (int i = 0; i < numClients; ++i) {
        if (clients[i].id == clientIdToDelete) {
            clientIndex = i;
            break;
        }
    }

    if (clientIndex == -1) {
        cout << "Cliente con ID " << clientIdToDelete << " no encontrado." << endl;
        return;
    }
    
	fstream tempFile("../assets/temp.csv", ios::out | ios::app);
	
	Client currentClient; 
	while (!file2.eof()) {
		currentClient = readCurrentClient(file2);
		if (currentClient.id != clientIdToDelete) {
			writeCurrentClient(tempFile, currentClient);
		}
	}
	
	file2.clear();
	file2.seekg(0, ios::beg);
	
	file2.close();
	tempFile.close();
	
	remove("../assets/clients.csv");
	rename("../assets/temp.csv", "../assets/clients.csv");
	
	file2.open("clients.csv", ios::in | ios::out | ios::app);
	cout<<"Cliente eliminado exitosamente."<<endl;
		break;
	}
		default:
		cout<< "Opcion invalida" <<endl;
	}
}

//Implementación
int main() {
    const string clientsFile = "../assets/clients.csv";
    const string carsFile = "../assets/cars_data.csv";

    Client clients[MAX_CLIENTS];
    Cars cars[MAX_CARS];
    int numClients = 0;
    int numCars = 0;

    //Leer datos para un archivo
    readClientsFromFile(clientsFile, clients, numClients);
    readCarsFromFile(carsFile, cars, numCars);
    
    fstream file("../assets/cars_data.csv", ios::in | ios::out | ios::app);
	fstream file2("../assets/clients.csv", ios::in | ios::out | ios::app);

    int choice;
    int clientId;
    do {
        displayMenu();
        while (!(cin >> choice) || choice < 0) {
        cout << "Dato invalido, introduzca un valor numerico: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
        switch (choice) {
            case 1:
                cout << "Introduzca ID del cliente: ";
                while (!(cin >> clientId) || clientId <= 0) {
        			cout << "Dato invalido, introduzca un valor numerico: ";
        			cin.clear();
        			cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
            	deleteItem(file, file2, numClients, numCars,cars, clients);
            	break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opcion invalida, intente nuevamente." << endl;
        }
    } while (choice != 0);

    return 0;
}