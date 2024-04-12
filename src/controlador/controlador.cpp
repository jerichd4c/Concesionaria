#include "controlador.h"

void addClient(Client clients[], int& numClients) {
    if (numClients < MAX_CLIENTS) {
        Client newClient;
        int nextClientId = numClients + 1;
        newClient.setId(nextClientId);

        std::cout << "Introduzca el nombre del cliente: ";
        std::string firstName, lastName;
        std::cin >> firstName;
        std::cout << "Introduzca el apellido del cliente: ";  
        std::cin >> lastName;  
        newClient.setFirstName(firstName);
        newClient.setLastName(lastName);

        std::cout << "Introduzca el correo electrónico del cliente: ";
        std::string email;
        std::cin >> email;
        newClient.setEmail(email);

        std::cout << "Introduzca la edad del cliente: ";
        int age;
        while (!(std::cin >> age) || age < 0 || age > 150) {
            std::cout << "Dato inválido, introduzca una edad entre 0 y 150 años: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        newClient.setAge(age);

        // Agregar el nuevo cliente al arreglo
        clients[numClients] = newClient;
        numClients++;

        // Escribir el nuevo cliente en el archivo 
        std::ofstream file("../assets/clients.csv", std::ios::out | std::ios::app);
        if (file.is_open()) {
            file << newClient.getId() << ';' << newClient.getFirstName() << ';' << newClient.getLastName() << ';'
                << newClient.getEmail() << ';' << newClient.getAge() << std::endl;
            file.close();
            std::cout << "Cliente agregado exitosamente." << std::endl;
        } else {
            std::cerr << "Error al abrir el archivo." << std::endl;
        }
    } else {
        std::cout << "No se pueden agregar más clientes. Se ha alcanzado el límite máximo." << std::endl;
    }
}

void addBoughtCar(Cars cars[], int& numCars, Client clients[], int& numClients) {
    Cars newCar;

    std::cout << std::endl; // Salto de línea para separar visualmente el mensaje del encabezado

    std::cout << "Introduzca los detalles para el carro nuevo:" << std::endl;

    std::cout << "Maker: ";
    std::cin.ignore();
    std::string maker;
	std::getline(std::cin, maker);
	newCar.setMaker(maker);

    std::cout << "Model: ";
    std::string modelInput;
	std::getline(std::cin, modelInput);
	newCar.setModel(modelInput);

    std::cout << "Year: ";
    int year;
	while (!(std::cin >> year) || year < 1900 || year > 2024) {
    	std::cout << "Dato inválido, introduzca un año entre 1900 y 2024: ";
    	std::cin.clear();
    	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	newCar.setYear(year);

    std::cout << "Introduzca por cuanto se compró el carro: ";
   	int boughtFor;
	while (!(std::cin >> boughtFor) || boughtFor <= 0) {
    	std::cout << "Dato inválido, introduzca un valor numérico mayor a cero: ";
    	std::cin.clear();
    	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	newCar.setBoughtFor(boughtFor);

    int isRegistered;
    std::cout << "Es el comprador un cliente registrado? (Si: 1, No: 0): ";
    while (!(std::cin >> isRegistered) || isRegistered < 0 || isRegistered > 1 ) {
        std::cout << "Opción inválida, introduzca 1 o 0: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    if (isRegistered == 0) {
        // Si el comprador no está registrado, agregar un nuevo cliente
        addClient(clients, numClients);
        // Actualizar el carro con la información del nuevo cliente
        newCar.setBoughtTo(numClients);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } else {
        // Si el comprador está registrado, solicitar su ID
        int buyerClientId;
        std::cout << "Introduzca el ID del cliente que compró el carro: ";
        while (!(std::cin >> buyerClientId) || buyerClientId <= 0) {
            std::cout << "ID inválido, introduzca un ID válido: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        
        // Verificar que el ID del comprador existe
        bool buyerExists = false;
        for (int i = 0; i < numClients; ++i) {
            if (clients[i].getId() == buyerClientId) {
                buyerExists = true;
                break;
            }
        }

        if (!buyerExists) {
            std::cout << "Cliente con ID: " << buyerClientId << " no encontrado, carro no agregado." << std::endl;
            return;
        }
        // Actualizar el carro con el ID del comprador
        newCar.setBoughtTo(buyerClientId);
    }

   	// Agregar el nuevo carro al arreglo
	cars[numCars] = newCar;
	numCars++;

	// Escribir el nuevo carro en el archivo (esto debería manejarse en el modelo)
	std::ofstream file("../assets/cars_data.csv", std::ios::out | std::ios::app);
	if (file.is_open()) {
    	file << newCar.getId() << ';' << newCar.getMaker() << ';' << newCar.getModel() << ';'
     	   << newCar.getYear() << ';' << newCar.getSoldTo() << ';' << newCar.getBoughtTo() << ';'
     	   << newCar.getSoldFor() << ';' << newCar.getBoughtFor() << std::endl;
    	file.close();
   	 std::cout << "Carro agregado exitosamente." << std::endl;
	} else {
 	   std::cerr << "Error al abrir el archivo." << std::endl;
	}
}

void updateSoldCar(Cars cars[], int& numCars, Client clients[], int& numClients) {
    // Variable para el ID del carro vendido
    int soldCarId;
    std::cout << "Introduzca el ID del carro que fue vendido: ";
    std::cin >> soldCarId;

    // Buscar el carro en el arreglo
    for (int i = 0; i < numCars; ++i) {
        if (cars[i].getId() == soldCarId) {
            // Preguntar si el comprador es un usuario registrado
            int isRegistered;
            std::cout << "¿Es el comprador un usuario registrado? (Si: 1, No: 0): ";
            std::cin >> isRegistered;

            if (isRegistered == 0) {
                // Si el comprador no está registrado, agregarlo como nuevo cliente
                addClient(clients, numClients);
                // Actualizar la información del carro con el ID del nuevo cliente
                cars[i].setSoldTo(numClients);
            } else {
                // Si el comprador está registrado, preguntar por su ID
                int buyerClientId;
                std::cout << "Introduzca el ID del usuario que compró el carro: ";
                std::cin >> buyerClientId;

                // Validar que el ID del comprador existe
                bool buyerExists = false;
                for (int j = 0; j < numClients; ++j) {
                    if (clients[j].getId() == buyerClientId) {
                        buyerExists = true;
                        break;
                    }
                }

                if (!buyerExists) {
                    std::cout << "Cliente con ID " << buyerClientId << " no encontrado. La actualización no se realizó." << std::endl;
                    return;
                }

                // Actualizar la información del carro con el ID del comprador
                cars[i].setSoldTo(buyerClientId);
            }

            // Precio de venta del carro
            int soldCarPrice;
            // Validación de entrada para el precio
            std::cout << "Introduzca el precio de venta del carro: ";
            while (!(std::cin >> soldCarPrice) || soldCarPrice <= 0) {
                std::cout << "Valor inválido. Introduzca un valor válido: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            // Confirmación con el usuario
            int confirm;
            std::cout << "¿Confirmar la venta? (Si: 1, No: 0): ";
            std::cin >> confirm;

            if (confirm == 1) {
                // Establecer el precio de venta del carro
                cars[i].setSoldFor(soldCarPrice);

                // Actualizar el archivo CSV con los datos actualizados de los carros
                std::fstream carsFile("../assets/cars_data.csv", std::ios::in | std::ios::out);
                if (carsFile.is_open()) {
                    // Saltar la primera línea (encabezado)
                    std::string header;
                    std::getline(carsFile, header);
                    // Mover el cursor al principio de la parte de datos después del encabezado
                    carsFile.seekp(carsFile.tellg());

                    // Escribir los datos actualizados de los carros en el archivo
                    for (int j = 0; j < numCars; ++j) {
                    	if (j == 0 ) {
                    		continue;
						} else {
							carsFile << cars[j].getId() << ';' << cars[j].getMaker() << ';' << cars[j].getModel() << ';'
                                 << cars[j].getYear() << ';' << cars[j].getSoldTo() << ';' << cars[j].getBoughtTo() << ';'
                                 << cars[j].getSoldFor() << ';' << cars[j].getBoughtFor() << std::endl;
						}
                        
                    }
                    carsFile.close();
                    std::cout << "La información del carro se actualizó exitosamente." << std::endl;
                } else {
                    std::cerr << "No se pudo abrir el archivo cars_data.csv para actualizar la información del carro." << std::endl;
                }
            } else {
                std::cout << "La venta se canceló. La información del carro no se actualizó." << std::endl;
            }
            return;
        }
    }
    std::cout << "El carro con ID " << soldCarId << " no fue encontrado. No se realizó ninguna actualización." << std::endl;
}

void getProfit(const Cars cars[], int size) {
    int carId;
    std::cout << "Seleccione el ID del carro: ";
    while (!(std::cin >> carId) || carId <= 0) {
        std::cout << "Dato invalido, introduzca un valor numerico mayor a 0: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    bool found = false;
    int diferenciaCarro = 0; // Inicializa la variable fuera del bucle
    for (int i = 0; i < size; ++i) {
        if (cars[i].getId() == carId) { // Utiliza el método getId() para obtener el ID del carro
            found = true;
            diferenciaCarro = cars[i].getBoughtFor() - cars[i].getSoldFor(); // Calcula la diferencia dentro del bucle
            std::cout << "El carro se compro por: " << cars[i].getBoughtFor() << std::endl;
            std::cout << "El carro se vendio por: " << cars[i].getSoldFor() << std::endl;
            if (diferenciaCarro > 0) {
                std::cout << "La ganancia fue de: " << diferenciaCarro << "$" << std::endl;
            } else if (diferenciaCarro < 0) {
                std::cout << "La perdida fue de: " << diferenciaCarro * -1 << "$" << std::endl;
            } else {
                std::cout << "No hubo ni ganancia ni perdida" << std::endl;
            }
        }
    }

    if (!found) {
        std::cout << "Carro con ID " << carId << " no encontrado." << std::endl;
    }
}

void deleteItem(std::fstream& file, std::fstream& file2, int numClients, int numCars, const Cars cars[], const Client clients[]) {
    int opcionElegida;
    std::cout << "Seleccione opción" << std::endl;
    std::cout << "1. Carro ; 2. Cliente" << std::endl;
    std::cin >> opcionElegida;

    switch (opcionElegida) {
        case 1: {
            // Borrar carro
            int carIdToDelete;
            std::cout << "Ingrese el ID del carro: ";
            while (!(std::cin >> carIdToDelete) || carIdToDelete <= 0) {
                std::cout << "Dato invalido, introduzca un valor numerico y sea diferente de 0: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            // Validación de entrada
            int carsIndex = -1;
            for (int i = 0; i < numCars; ++i) {
                if (cars[i].getId() == carIdToDelete) {
                    carsIndex = i;
                    break;
                }
            }

            if (carsIndex == -1) {
                std::cout << "Carro con ID " << carIdToDelete << " no encontrado." << std::endl;
                return;
            }

            std::fstream tempFile("../assets/temp.csv", std::ios::out); // Open in std::ios::out mode
            
          tempFile<<"id;maker;model;year;sold_to;bought_to;sold_for;bought_for"<<std::endl;
          std::cout<<numCars<<std::endl;
            for (int i = 0; i < numCars; ++i) {
            	if(i==0) continue;
              if (cars[i].getId() != carIdToDelete) {
              	bool isFirstLine;
				    writeCurrentCar(tempFile, cars[i]);
				    if (isFirstLine)
				    isFirstLine = false;
				    
				}
            }
            tempFile.close();

            // Close the original file
            file.close();
            // Remove the original file and rename the temporary file
            std::remove("../assets/cars_data.csv");
            std::rename("../assets/temp.csv", "../assets/cars_data.csv");
            // Reopen the original file
            file.open("../assets/cars_data.csv", std::ios::in | std::ios::out);
            std::cout << "Carro eliminado exitosamente." << std::endl;
            break;
        }
        case 2: {
            // Borrar cliente
            int clientIdToDelete;
            std::cout << "Ingrese el ID del cliente: ";
            while (!(std::cin >> clientIdToDelete) || clientIdToDelete <= 0) {
                std::cout << "Dato invalido, introduzca un valor numerico y sea diferente de 0: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            // Validación de entrada
            int clientIndex = -1;
            for (int i = 0; i < numClients; ++i) {
                if (clients[i].getId() == clientIdToDelete) {
                    clientIndex = i;
                    break;
                }
            }

            if (clientIndex == -1) {
                std::cout << "Cliente con ID " << clientIdToDelete << " no encontrado." << std::endl;
                return;
            }
            std::fstream tempFile2("../assets/temp2.csv", std::ios::out); // Open in std::ios::out mode
            tempFile2<<"id;first_name;last_name;email;age"<<std::endl;
			for (int i = 0; i < numClients; ++i) {
				if(i==0) continue;
    			if (clients[i].getId() != clientIdToDelete) {
        			bool isFirstLine;
					writeCurrentClient(tempFile2, clients[i]);
        			if (isFirstLine) 
           				isFirstLine = false;
    			}
			}
            //  Close the original file
            file2.close();
            tempFile2.close();
            // Remove the original file and rename the temporary file
            std::remove("../assets/clients.csv");
            std::rename("../assets/temp2.csv", "../assets/clients.csv");
           // Reopen the original file
            std::cout << "Cliente eliminado exitosamente." << std::endl;
            break;
        }
        default:
            std::cout << "Opcion invalida" << std::endl;
            break;
    }
}