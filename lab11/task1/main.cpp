#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class ReservationSystem {
    struct Reservation {
        std::string passengerName;
    };
    struct Flight {
        int id;

        std::string origin;
        std::string destination;

        int seatsLeft;
        std::vector<Reservation> reservations;
    };

    std::vector<Flight> flights;

   public:
    ReservationSystem() {
        flights.push_back({1001, "New York", "London", 77});
        flights.push_back({1002, "Paris", "Tokyo", 8});
        flights.push_back({1003, "Berlin", "Kiev", 56});
    }

    void listFlights() {
        for (const auto& f : flights) {
            std::cout << "Flight ID " << f.id << ": From " << f.origin << " to " << f.destination
                      << " | Seats left: " << f.seatsLeft << "\n";
        }
    }

    void bookSeat(int flightID, const std::string& name) {
        for (auto& f : flights) {
            if (f.id == flightID) {
                if (f.seatsLeft > 0) {
                    f.seatsLeft--;
                    f.reservations.push_back({name});
                    std::cout << "Reservation was made for: " << name << "\n";
                } else {
                    std::cout << "No seats available\n";
                }
                return;
            }
        }
        std::cout << "Flight not found\n";
    }

    void showReservations(int flightID) {
        for (auto& f : flights) {
            if (f.id == flightID) {
                for (const auto& r : f.reservations) {
                    std::cout << "Reservation: Flight " << f.id << " | Name: " << r.passengerName
                              << "\n";
                }
                return;
            }
        }
        std::cout << "Flight not found\n";
    }
    void cancelReservation(int flightID, const std::string& name) {
        for (auto& f : flights) {
            if (f.id == flightID) {
                for (auto it = f.reservations.begin(); it != f.reservations.end(); ++it) {
                    if (it->passengerName == name) {
                        f.reservations.erase(it);
                        f.seatsLeft++;
                        std::cout << "Reservation for " << name << " was canceled\n";
                        return;
                    }
                }
                std::cout << "No reservation found for this passenger on flight " << flightID
                          << "\n";
                return;
            }
        }
        std::cout << "Flight not found\n";
    }
    void menu() {
        int choice;
        while (true) {
            std::cout << "\n1. List flights\n2. Book seat\n3. Show reservations\n4. Cancel "
                         "reservation\n5. Exit\nChoice: ";
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "\033[2J\033[1;1H";
                listFlights();
            } else if (choice == 2) {
                int flightID;
                std::string name;
                std::cout << "Enter flight ID: ";
                std::cin >> flightID;
                std::cout << "Enter passenger name: ";
                std::cin >> name;
                std::cout << "\033[2J\033[1;1H";
                bookSeat(flightID, name);
            } else if (choice == 3) {
                int flightID;
                std::cout << "Enter flight ID: ";
                std::cin >> flightID;
                std::cout << "\033[2J\033[1;1H";
                showReservations(flightID);
            } else if (choice == 4) {
                int flightID;
                std::string name;
                std::cout << "Enter flight ID: ";
                std::cin >> flightID;
                std::cout << "Enter passenger name: ";
                std::cin >> name;
                std::cout << "\033[2J\033[1;1H";
                cancelReservation(flightID, name);
            } else {
                break;
            }
        }
    }
};

int main() {
    ReservationSystem rs;
    rs.menu();
    return 0;
}
