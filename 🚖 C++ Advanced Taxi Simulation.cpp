#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

class Vehicle {
protected:
    string plate;
    string driverName;
    double baseFare;
    double rating;
    bool available;

public:
    Vehicle(string p, string d, double fare, double r)
        : plate(p), driverName(d), baseFare(fare), rating(r), available(true) {
    }

    virtual double calculateFare(double distance) = 0;
    virtual string getType() const = 0;

    virtual void showInfo() {
        cout << left << setw(12) << driverName
            << setw(10) << plate
            << setw(10) << fixed << setprecision(1) << rating
            << setw(10) << (available ? "Available" : "Busy") << endl;
    }

    bool isAvailable() const { return available; }
    void setAvailable(bool status) { available = status; }

    string getDriver() const { return driverName; }
    string getPlate() const { return plate; }

    virtual ~Vehicle() {}
};

class Taxi : public Vehicle {
public:
    Taxi(string p, string d, double fare, double r)
        : Vehicle(p, d, fare, r) {
    }

    double calculateFare(double distance) override {
        double fare = baseFare * distance;
        fare *= (1 + (1 - rating / 5.0));
        return fare;
    }

    string getType() const override { return "Standard Taxi"; }
};

class VIPTaxi : public Vehicle {
private:
    double luxuryFee;
public:
    VIPTaxi(string p, string d, double fare, double r, double lFee)
        : Vehicle(p, d, fare, r), luxuryFee(lFee) {
    }

    double calculateFare(double distance) override {
        double fare = (baseFare * distance + luxuryFee);
        fare *= (1 + (1 - rating / 5.0));
        return fare;
    }

    string getType() const override { return "VIP Taxi"; }
};

class Passenger {
private:
    string name;
    string destination;
    double distance;

public:
    Passenger(string n, string dest, double dist)
        : name(n), destination(dest), distance(dist) {
    }

    string getName() const { return name; }
    string getDestination() const { return destination; }
    double getDistance() const { return distance; }
};

class Ride {
private:
    Passenger passenger;
    Vehicle* vehicle;
    double fare;

public:
    Ride(Passenger p, Vehicle* v) : passenger(p), vehicle(v) {
        fare = vehicle->calculateFare(passenger.getDistance());
        vehicle->setAvailable(false);
    }

    void start() {
        cout << "\nRide started!" << endl;
        cout << "Passenger: " << passenger.getName() << endl;
        cout << "Destination: " << passenger.getDestination() << endl;
        cout << "Distance: " << passenger.getDistance() << " km" << endl;
        cout << "Driver: " << vehicle->getDriver()
            << " (" << vehicle->getType() << ")" << endl;
        cout << fixed << setprecision(2);
        cout << "Total fare: " << fare << " USD" << endl;
        cout << "Ride completed!\n" << endl;
    }

    void saveToFile() {
        ofstream file("rides.txt", ios::app);
        if (file.is_open()) {
            file << passenger.getName() << ","
                << passenger.getDestination() << ","
                << passenger.getDistance() << "km,"
                << vehicle->getDriver() << ","
                << vehicle->getType() << ","
                << vehicle->getPlate() << ","
                << fare << " USD\n";
            file.close();
        }
    }

    void end() {
        vehicle->setAvailable(true);
    }
};

int main() {
    srand(time(0));

    vector<Vehicle*> taxis = {
        new Taxi("NYC123", "Alex", 10, 4.5),
        new Taxi("NYC456", "Emma", 9.5, 4.0),
        new VIPTaxi("NYC777", "John", 12, 4.8, 40),
        new VIPTaxi("NYC999", "Sophia", 11.5, 5.0, 50)
    };

    cout << "=== TAXI DISPATCH SYSTEM ===" << endl;

    while (true) {
        cout << "\nAvailable taxis:\n";
        cout << left << setw(12) << "Driver" << setw(10) << "Plate"
            << setw(10) << "Rating" << setw(10) << "Status" << endl;
        cout << string(45, '-') << endl;
        for (auto v : taxis) v->showInfo();

        string name, destination;
        double distance;
        cout << "\nEnter passenger name (or 'exit' to quit): ";
        getline(cin, name);
        if (name == "exit") break;

        cout << "Enter destination: ";
        getline(cin, destination);
        cout << "Enter distance (km): ";
        cin >> distance;
        cin.ignore();

        vector<Vehicle*> availableTaxis;
        for (auto v : taxis)
            if (v->isAvailable()) availableTaxis.push_back(v);

        if (availableTaxis.empty()) {
            cout << "No taxis available at the moment.\n";
            continue;
        }

        Vehicle* chosen = availableTaxis[rand() % availableTaxis.size()];
        Passenger passenger(name, destination, distance);
        Ride ride(passenger, chosen);

        ride.start();
        ride.saveToFile();
        ride.end();
    }

    for (auto v : taxis) delete v;

    cout << "\nAll rides saved to rides.txt" << endl;
    return 0;
}
