#include <iostream>
#include <vector>
#include <string>

// In the naive approach, each Aircraft must communicate directly with all other Aircraft.
class Aircraft {
private:
    std::string flightNumber;
    // Each aircraft maintains a list of all other aircraft (direct mesh connections)
    std::vector<Aircraft*> otherAircrafts;

public:
    Aircraft(const std::string& flightNum) : flightNumber(flightNum) {}

    // Add reference to another aircraft (creates the O(N^2) dependency web)
    void addAircraft(Aircraft* aircraft) {
        otherAircrafts.push_back(aircraft);
    }

    std::string getFlightNumber() const {
        return flightNumber;
    }

    // Aircraft attempts to coordinate runway access by communicating with EVERY other plane
    void requestLanding() {
        std::cout << "Aircraft " << flightNumber << " is requesting to land.\n";
        bool canLand = true;
        
        for (Aircraft* other : otherAircrafts) {
            std::cout << "  " << flightNumber << " asking " << other->getFlightNumber() << " for clearance.\n";
            
            // Direct communication to check if the route is clear
            if (!other->giveClearance()) {
                canLand = false;
                break;
            }
        }

        if (canLand) {
            std::cout << "Aircraft " << flightNumber << " has been cleared to land. Landing...\n";
        } else {
            std::cout << "Aircraft " << flightNumber << " cannot land. Airspace is busy.\n";
        }
    }

    // Aircraft processes clearance requests from other planes
    bool giveClearance() {
        // In a more complex scenario, this would check altitude, speed, and trajectory
        std::cout << "    " << flightNumber << " gives clearance.\n";
        return true;
    }
};

int main() {
    Aircraft* flight1 = new Aircraft("Commercial-101");
    Aircraft* flight2 = new Aircraft("Cargo-202");
    Aircraft* flight3 = new Aircraft("PrivateJet-303");

    // The Problem: Setting up the direct mesh of communications
    // As N grows, the number of connections grows at O(N^2).
    
    // Flight 1 needs to know about Flight 2 and 3
    flight1->addAircraft(flight2);
    flight1->addAircraft(flight3);

    // Flight 2 needs to know about Flight 1 and 3
    flight2->addAircraft(flight1);
    flight2->addAircraft(flight3);

    // Flight 3 needs to know about Flight 1 and 2
    flight3->addAircraft(flight1);
    flight3->addAircraft(flight2);

    std::cout << "--- Air Traffic Control (Naive Approach) ---\n\n";

    // Simulating landing coordination
    flight1->requestLanding();
    
    std::cout << "\n---------------------------------------------\n\n";
    
    flight3->requestLanding();

    delete flight1;
    delete flight2;
    delete flight3;

    return 0;
}
