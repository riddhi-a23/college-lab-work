#include <iostream>
#include <string>
#include <fstream>

namespace FleetManagement {
    class Vehicle {
    protected:
        std::string make;
        std::string model;
        int year;

    public:
        Vehicle(const std::string& mk = "Unknown", const std::string& md = "Unknown", int yr = 0)
            : make(mk), model(md), year(yr) {}

        virtual ~Vehicle() {}

        virtual std::string getType() const = 0; // Used to identify object type during file loading
        
        virtual void start() const = 0;
        virtual void stop() const = 0;
        
        virtual void displayInfo() const; 
        virtual void saveInfo(std::ofstream& outFile) const = 0;
        virtual void loadInfo(std::ifstream& inFile) = 0;
    };

    class Car : public Vehicle {
    private:
        int numDoors;

    public:
        Car(const std::string& mk = "Unknown", const std::string& md = "Unknown", int yr = 0, int doors = 4)
            : Vehicle(mk, md, yr), numDoors(doors) {}

        std::string getType() const override { return "Car"; }
        void start() const override { std::cout << "Car (" << make << " " << model << "): Car started.\n"; }
        void stop() const override { std::cout << "Car (" << make << " " << model << "): Car stopped.\n"; }

        void displayInfo() const override;
        void saveInfo(std::ofstream& outFile) const override;
        void loadInfo(std::ifstream& inFile) override;
    };

    class Truck : public Vehicle {
    private:
        double payloadCapacityTonnes;

    public:
        Truck(const std::string& mk = "Unknown", const std::string& md = "Unknown", int yr = 0, double payload = 0.0)
            : Vehicle(mk, md, yr), payloadCapacityTonnes(payload) {}

        std::string getType() const override { return "Truck"; }
        void start() const override { std::cout << "Truck (" << make << " " << model << "): Truck started.\n"; }
        void stop() const override { std::cout << "Truck (" << make << " " << model << "): Truck stopped.\n"; }

        void displayInfo() const override;
        void saveInfo(std::ofstream& outFile) const override;
        void loadInfo(std::ifstream& inFile) override;
    };

    class Bus : public Vehicle {
    private:
        int passengerCapacity;

    public:
        Bus(const std::string& mk = "Unknown", const std::string& md = "Unknown", int yr = 0, int passengers = 0)
            : Vehicle(mk, md, yr), passengerCapacity(passengers) {}

        std::string getType() const override { return "Bus"; }
        void start() const override { std::cout << "Bus (" << make << " " << model << "): Bus started.\n"; }
        void stop() const override { std::cout << "Bus (" << make << " " << model << "): Bus stopped.\n"; }

        void displayInfo() const override;
        void saveInfo(std::ofstream& outFile) const override;
        void loadInfo(std::ifstream& inFile) override;
    };


    void Vehicle::displayInfo() const {
        std::cout << "Make: " << make << ", Model: " << model << ", Year: " << year;
    }

    // --- Car Methods ---
    void Car::displayInfo() const {
        std::cout << "[Car] ";
        Vehicle::displayInfo();
        std::cout << ", Doors: " << numDoors << "\n";
    }

    void Car::saveInfo(std::ofstream& outFile) const {
        outFile << getType() << "\n" << make << "\n" << model << "\n" << year << "\n" << numDoors << "\n";
    }

    void Car::loadInfo(std::ifstream& inFile) {
        std::getline(inFile >> std::ws, make);
        std::getline(inFile >> std::ws, model);
        inFile >> year >> numDoors;
    }

    // --- Truck Methods ---
    void Truck::displayInfo() const {
        std::cout << "[Truck] ";
        Vehicle::displayInfo();
        std::cout << ", Payload: " << payloadCapacityTonnes << " Tonnes\n";
    }

    void Truck::saveInfo(std::ofstream& outFile) const {
        outFile << getType() << "\n" << make << "\n" << model << "\n" << year << "\n" << payloadCapacityTonnes << "\n";
    }

    void Truck::loadInfo(std::ifstream& inFile) {
        std::getline(inFile >> std::ws, make);
        std::getline(inFile >> std::ws, model);
        inFile >> year >> payloadCapacityTonnes;
    }

    // --- Bus Methods ---
    void Bus::displayInfo() const {
        std::cout << "[Bus] ";
        Vehicle::displayInfo();
        std::cout << ", Capacity: " << passengerCapacity << " Passengers\n";
    }

    void Bus::saveInfo(std::ofstream& outFile) const {
        outFile << getType() << "\n" << make << "\n" << model << "\n" << year << "\n" << passengerCapacity << "\n";
    }

    void Bus::loadInfo(std::ifstream& inFile) {
        std::getline(inFile >> std::ws, make);
        std::getline(inFile >> std::ws, model);
        inFile >> year >> passengerCapacity;
    }

} 

using namespace FleetManagement;

int main() {
    const std::string filename = "fleet_data.txt";
    const int MAX_VEHICLES = 100;
    
    Vehicle* fleet[MAX_VEHICLES];
    int vehicleCount = 0;

    std::cout << "=== Populating Initial Fleet ===\n";
    fleet[vehicleCount++] = new Car("Toyota", "123", 2022, 4);
    fleet[vehicleCount++] = new Truck("Mahindra", "456", 2020, 25);
    fleet[vehicleCount++] = new Bus("Volvo", "789", 2019, 50);

    for (int i = 0; i < vehicleCount; ++i) {
        fleet[i]->displayInfo();
        fleet[i]->start();
    }

    std::cout << "\n=== Saving Fleet to File ===\n";
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (int i = 0; i < vehicleCount; ++i) {
            fleet[i]->saveInfo(outFile);
        }
        outFile.close();
        std::cout << "Data saved successfully to " << filename << ".\n";
    }

    for (int i = 0; i < vehicleCount; ++i) {
        delete fleet[i];
    }
    vehicleCount = 0;

    std::cout << "\n=== Loading Fleet from File Dynamically ===\n";
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::string type;
        while (std::getline(inFile >> std::ws, type)) {
            if (type == "Car") {
                fleet[vehicleCount] = new Car();
            } else if (type == "Truck") {
                fleet[vehicleCount] = new Truck();
            } else if (type == "Bus") {
                fleet[vehicleCount] = new Bus();
            } else {
                continue;
            }
            
            fleet[vehicleCount]->loadInfo(inFile);
            vehicleCount++;
        }
        inFile.close();
        std::cout << "Data loaded successfully.\n";
    }

    std::cout << "\n=== Displaying Loaded Fleet ===\n";
    for (int i = 0; i < vehicleCount; ++i) {
        fleet[i]->displayInfo();
        fleet[i]->stop();
    }

    for (int i = 0; i < vehicleCount; ++i) {
        delete fleet[i];
    }

    return 0;
}