#include <iostream>
#include <string>
#include <vector>

class Airplane; // Forward declaration

// ==========================================
// 1. Mediator Interface
// ==========================================
class AirTrafficControlTower {
public:
    virtual ~AirTrafficControlTower() {}
    virtual void requestTakeoff(Airplane* airplane) = 0;
    virtual void requestLanding(Airplane* airplane) = 0;
};

// ==========================================
// 2. Colleague Interface
// ==========================================
class Airplane {
protected:
    // Every colleague holds a reference to the mediator
    AirTrafficControlTower* mediator;
    std::string flightNumber;

public:
    Airplane(AirTrafficControlTower* mediator, const std::string& flightNum) 
        : mediator(mediator), flightNumber(flightNum) {}
    virtual ~Airplane() {}

    virtual void requestTakeoff() = 0;
    virtual void requestLanding() = 0;
    
    virtual void notifyAirTrafficControl(const std::string& message) {
        std::cout << "Airplane " << flightNumber << " sends message: " << message << "\n";
    }

    std::string getFlightNumber() const { return flightNumber; }
    
    // Method to allow the mediator to send instructions to this plane
    virtual void receiveInstruction(const std::string& instruction) {
        std::cout << "  -> Airplane " << flightNumber << " receives instruction: " << instruction << "\n";
    }
};

// ==========================================
// 3. Concrete Mediator
// ==========================================
class AirportControlTower : public AirTrafficControlTower {
private:
    // The mediator keeps track of all registered colleagues
    std::vector<Airplane*> airplanes;

public:
    void registerAirplane(Airplane* airplane) {
        airplanes.push_back(airplane);
    }

    // Coordinating takeoff logic
    void requestTakeoff(Airplane* airplane) override {
        std::cout << "[Tower] received takeoff request from " << airplane->getFlightNumber() << ".\n";
        std::cout << "[Tower] checking runway availability and clearing airspace...\n";
        
        // Notify all OTHER airplanes to hold position
        for (Airplane* a : airplanes) {
            if (a != airplane) {
                a->receiveInstruction("Hold position, " + airplane->getFlightNumber() + " is taking off.");
            }
        }
        std::cout << "[Tower] grants takeoff clearance to " << airplane->getFlightNumber() << ".\n\n";
    }

    // Coordinating landing logic
    void requestLanding(Airplane* airplane) override {
        std::cout << "[Tower] received landing request from " << airplane->getFlightNumber() << ".\n";
        std::cout << "[Tower] checking runway availability and clearing airspace...\n";
        
        // Notify all OTHER airplanes to maintain altitude
        for (Airplane* a : airplanes) {
            if (a != airplane) {
                a->receiveInstruction("Maintain altitude, runway is being used by " + airplane->getFlightNumber() + ".");
            }
        }
        std::cout << "[Tower] grants landing clearance to " << airplane->getFlightNumber() << ".\n\n";
    }
};

// ==========================================
// 4. Concrete Colleagues
// ==========================================
class CommercialAirplane : public Airplane {
public:
    CommercialAirplane(AirTrafficControlTower* mediator, const std::string& flightNum) 
        : Airplane(mediator, flightNum) {}

    void requestTakeoff() override {
        std::cout << "Commercial Airplane " << flightNumber << " requesting takeoff.\n";
        // Communication is handed over to the mediator
        mediator->requestTakeoff(this);
    }

    void requestLanding() override {
        std::cout << "Commercial Airplane " << flightNumber << " requesting landing.\n";
        // Communication is handed over to the mediator
        mediator->requestLanding(this);
    }
};

class CargoAirplane : public Airplane {
public:
    CargoAirplane(AirTrafficControlTower* mediator, const std::string& flightNum) 
        : Airplane(mediator, flightNum) {}

    void requestTakeoff() override {
        std::cout << "Cargo Airplane " << flightNumber << " requesting takeoff.\n";
        mediator->requestTakeoff(this);
    }

    void requestLanding() override {
        std::cout << "Cargo Airplane " << flightNumber << " requesting landing.\n";
        mediator->requestLanding(this);
    }
};

class PrivateJet : public Airplane {
public:
    PrivateJet(AirTrafficControlTower* mediator, const std::string& flightNum) 
        : Airplane(mediator, flightNum) {}

    void requestTakeoff() override {
        std::cout << "Private Jet " << flightNumber << " requesting takeoff.\n";
        mediator->requestTakeoff(this);
    }

    void requestLanding() override {
        std::cout << "Private Jet " << flightNumber << " requesting landing.\n";
        mediator->requestLanding(this);
    }
};

// ==========================================
// 5. Client Code
// ==========================================
int main() {
    std::cout << "--- Air Traffic Control (Mediator Pattern Approach) ---\n\n";

    // 1. Create the central Mediator (Control Tower)
    AirportControlTower* tower = new AirportControlTower();

    // 2. Create Colleagues (Airplanes) and link them to the mediator
    CommercialAirplane* flight1 = new CommercialAirplane(tower, "Commercial-101");
    CargoAirplane* flight2 = new CargoAirplane(tower, "Cargo-202");
    PrivateJet* flight3 = new PrivateJet(tower, "PrivateJet-303");

    // 3. Register airplanes with the tower.
    // Notice that airplanes NO LONGER maintain references to each other.
    tower->registerAirplane(flight1);
    tower->registerAirplane(flight2);
    tower->registerAirplane(flight3);

    // 4. Simulate coordinating operations.
    // Airplanes communicate exclusively through the Tower.
    flight1->requestLanding();
    
    std::cout << "---------------------------------------------\n\n";
    
    flight3->requestTakeoff();

    // Clean up
    delete flight1;
    delete flight2;
    delete flight3;
    delete tower;

    return 0;
}
