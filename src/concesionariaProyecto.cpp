#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

const int MAX_CLIENTS = 101;
const int MAX_CARS = 1003;

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

// Funcion X1 
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
        car.year = atoi(token.c_str());
        car.sold_to = atoi(token.c_str());
        car.bought_to = atoi(token.c_str());
        car.sold_for = atoi(token.c_str());
    	car.bought_for = atoi(token.c_str());
    }
    return car;
}

//Funcion X2
void writeCurrentCar(fstream& file, const Cars& car) {
    file << car.id << ';' << car.maker << ';' << car.model << ';'
         << car.year << ';' << car.sold_to << ';' << car.bought_to << ';' << car.sold_for << ';' << car.bought_for << '\n';
}

// Funcion X3
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
        client.age = atoi(token.c_str());
    }
    return client;
}

//Funcion X4
void writeCurrentClient(fstream& file, const Client& client) {
    file << client.id << ';' << client.first_name << ';' << client.last_name << ';' << client.email << ';' << client.age << '\n';
}

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

void displayClientCarsInfo(int clientId, const Client clients[], int numClients, const Cars cars[], int numCars) {
    // Find the client with the given ID
    int clientIndex = -1;
    for (int i = 0; i < numClients; ++i) {
        if (clients[i].id == clientId) {
            clientIndex = i;
            break;
        }
    }

    if (clientIndex == -1) {
        cout << "Client with ID " << clientId << " not found." << endl;
        return;
    }

    // Display client information
    cout << "ID: " << clients[clientIndex].id << endl;
    cout << "Name: " << clients[clientIndex].first_name << " " << clients[clientIndex].last_name << endl;
    cout << "Email: " << clients[clientIndex].email << endl;
    cout << "Age: " << clients[clientIndex].age << endl;

    // Count and display cars bought and sold by the client
    int carsBought = 0;
    int carsSold = 0;

    cout << "\nCars bought by the client: \n" << endl;
    for (int i = 0; i < numCars; ++i) {
        if (cars[i].bought_to == clientId) {
            carsBought++;
            cout << cars[i].id << " " << cars[i].maker << " " << cars[i].model << ", " << cars[i].year << endl;
        }
    }

    cout << "\nCars sold by the client: \n" << endl;
    for (int i = 0; i < numCars; ++i) {
        if (cars[i].sold_to == clientId) {
            carsSold++;
            cout << cars[i].maker << " " << cars[i].model << ", " << cars[i].year << endl;
        }
    }

    // Display the total count of cars bought and sold
    cout << "\n\n";
    cout << "Total cars bought by the client: " << carsBought << endl;
    cout << "Total cars sold by the client: " << carsSold << endl;
    cout << "\n\n";
}

void addClient(Client clients[], int& numClients) {
    // Take input for the new client's details
    Client newClient;
    // ... (Input details for the new client)

    // Find the next available client ID
    int nextClientId = numClients + 1;

    // Update the new client's information
    newClient.id = nextClientId;
    // ... (Update other details if needed)

    // Add the new client to the array
    clients[numClients] = newClient;
    numClients++;

    // Write the updated client data to the file
    ofstream clientsFile("clients.csv", ios::app);
    clientsFile << newClient.id << ';' << newClient.first_name << ';' << newClient.last_name << ';'
                << newClient.email << ';' << newClient.age << endl;
    clientsFile.close();

    cout << "Client information added successfully." << endl;
}

void addBoughtCar(Cars cars[], int& numCars, Client clients[], int& numClients) {
    // Take input for the new car's details
    Cars newCar;

    cout << "Enter the details of the new car:" << endl;

    // Maker input
    cout << "Maker: ";
    cin.ignore(); // Ignore the newline character left in the stream
    getline(cin, newCar.maker);

    // Model input
    cout << "Model: ";
    getline(cin, newCar.model);

    // Year input with validation
    cout << "Year: ";
    while (!(cin >> newCar.year) || newCar.year < 1900 || newCar.year > 2024) {
        cout << "Invalid input. Please enter a valid year: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cout << newCar.year;
    
    // Bought_for input with validation
    cout << "Enter the amount the car was bought for: ";
    while (!(cin >> newCar.bought_for) || newCar.bought_for <= 0) {
        cout << "Invalid input. Please enter a valid amount: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cout << newCar.bought_for;

    // Bought_to value will be the clientId
    int buyerClientId;
    cout << "Enter the ID of the client who bought the car: ";
    while (!(cin >> buyerClientId) || buyerClientId <= 0) {
        cout << "Invalid input. Please enter a valid client ID: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    cout << buyerClientId;

    // Validate that the buyer client ID exists
    bool buyerExists = false;
    for (int i = 0; i < numClients; ++i) {
        if (clients[i].id == buyerClientId) {
            buyerExists = true;
            break;
        }
    }

    if (!buyerExists) {
        cout << "Client with ID " << buyerClientId << " not found. Car not added." << endl;
        return;
    }

// Update the new car's information
newCar.id = numCars + 1;
newCar.bought_to = buyerClientId;
newCar.sold_to = 0; // No one has bought it yet
newCar.sold_for = 0; 

// Add the new car to the array
cout << numCars;
cars[numCars++] = newCar;

cout << numCars;


    // Write the updated car data to the file
	ofstream carsFile("cars_data.csv", ios::out | ios::app);
	if (!carsFile) {
	    cerr << "Error opening file for writing." << endl;
	    return;
	}
	
	carsFile << newCar.id << ';' << newCar.maker << ';' << newCar.model << ';' << newCar.year << ';'
	         << newCar.sold_to << ';' << newCar.bought_to << ';' << newCar.sold_for << ';' << newCar.bought_for << endl;
	
	if (carsFile.fail()) {
	    cerr << "Error writing data to file." << endl;
	    carsFile.close();
	    return;
	}

carsFile.close();
}

void updateSoldCar(Cars cars[], int& numCars, Client clients[], int& numClients) {
    // Take input for the car's ID that was sold
    int soldCarId;
    cout << "Enter the ID of the car that was sold: ";
    cin >> soldCarId;

    // Find the car in the array
    for (int i = 0; i < numCars; ++i) {
        if (cars[i].id == soldCarId) {
            // Check if the buyer is registered
            int isRegistered;
            cout << "Is the buyer a registered user? (Yes: 1, No: 0): ";
            cin >> isRegistered;

            if (isRegistered == 0) {
                // If the buyer is not a registered user, register a new client
                addClient(clients, numClients);

                // Update the car's information with the new client's ID
                cars[i].sold_to = numClients;
            } else {
                // If the buyer is registered, ask for the client's ID
                int buyerClientId;
                cout << "Enter the ID of the client who bought the car: ";
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
                    cout << "Client with ID " << buyerClientId << " not found. Car not added." << endl;
                    return;
                }

                // Update the car's information with the buyer's client ID
                cars[i].sold_to = buyerClientId;
            }

            // Input validation for the amount it was sold
            cout << "Enter the amount the car was sold for: ";
            while (!(cin >> cars[i].sold_for) || cars[i].sold_for <= 0) {
                cout << "Invalid input. Please enter a valid amount: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            // Confirm with the user
            int confirm;
            cout << "Confirm the sale? (Yes: 1, No: 0): ";
            cin >> confirm;

            if (confirm == 1) {
                // Write the updated car data to the file
                ofstream carsFile("cars_data.csv");
                for (int j = 0; j < numCars; ++j) {
                    carsFile << cars[j].id << ';' << cars[j].maker << ';' << cars[j].model << ';' << cars[j].year << ';'
                             << cars[j].sold_to << ';' << cars[j].bought_to << ';' << cars[j].sold_for << ';' << cars[j].bought_for << endl;
                }
                carsFile.close();

                cout << "Car information updated successfully." << endl;
            } else {
                cout << "Sale canceled. Car information not updated." << endl;
            }

            return;
        }
    }

    cout << "Car with ID " << soldCarId << " not found. No update performed." << endl;
}

// Función menu
void displayMenu() {
    cout << "Menu:" << endl;
    cout << "1. Show Client Info" << endl;
    cout << "2. Register New Car" << endl;
    cout << "3. Update Car Status" << endl;
    cout << "4. Get profit from car" << endl; // Planificandose todavia
    cout << "5. Delete car or client" << endl;
    cout << "0. Exit" << endl;
    cout << "Enter your choice: ";
}

// Funcion para borrar carro o cliente
void deleteItem(fstream& file , fstream& file2) {
	int opcionElegida;
	cout << "Seleccione opción"<<endl;
	cout << "1. Carro ; 2. Cliente" <<endl;
	cin >> opcionElegida; 
	switch (opcionElegida) {
		case 1: {
	//carros 
	int carIdToDelete;
    cout << "Ingrese el ID del carro: ";
    cin >> carIdToDelete;
    
    fstream tempFile("temp.csv", ios::out | ios::app); 

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

    remove("cars_data.csv");
    rename("temp.csv", "cars_data.csv");

    file.open("cars_data.csv", ios::in | ios::out | ios::app);
    cout << "El Carro ha sido eliminado exitosamente" <<endl;
		break; 
}
		case 2: {
	//clientes
	int clientIdToDelete;
	cout << "Ingrese el ID del cliente: ";
	cin >> clientIdToDelete;
	
	fstream tempFile("temp.csv", ios::out | ios::app);
	
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
	
	remove("clients.csv");
	rename("temp.csv", "clients.csv");
	
	file2.open("clients.csv", ios::in | ios::out | ios::app);
	cout << "El Cliente ha sido eliminado exitosamente" <<endl;
		break;
	}
		default:
		cout<< "Invalid choice" <<endl;
	}
}

int main() {
    const string clientsFile = "clients.csv";
    const string carsFile = "cars_data.csv";

    Client clients[MAX_CLIENTS];
    Cars cars[MAX_CARS];
    int numClients = 0;
    int numCars = 0;

    // Read data from files
    readClientsFromFile(clientsFile, clients, numClients);
    fstream file("cars_data.csv", ios::in | ios::out | ios::app);
	fstream file2("clients.csv", ios::in | ios::out | ios::app);

    int choice;
    int clientId;
    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the ID of the client: ";
                cin >> clientId;
                displayClientCarsInfo(clientId, clients, numClients, cars, numCars);
                break;
            case 2:
            	addBoughtCar(cars, numCars, clients, numClients);
            	break;
            case 3:
            	updateSoldCar(cars, numCars, clients, numClients);
            	break;
            case 4:
            //	getProfit(cars, numCars); Planificandose todavia 
            	break;
            case 5:
            	deleteItem(file, file2);
            	break;
            case 0:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}