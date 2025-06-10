#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class RailwaySystem {
    struct Reservation {
        std::string passengerName;
    };
    struct Train {
        int id;

        std::string origin;
        std::string destination;

        int seatsLeft;
        std::vector<Reservation> reservations;
    };

    std::vector<Train> trains;

   public:
    RailwaySystem() {
        trains.push_back({2001, "Warsaw", "Gdansk", 120});
        trains.push_back({2002, "Krakow", "Wroclaw", 60});
        trains.push_back({2003, "Lodz", "Poznan", 80});
    }

    void listTrains() {
        for (const auto& t : trains) {
            std::cout << "Train ID " << t.id << ": From " << t.origin << " to " << t.destination
                      << " | Seats left: " << t.seatsLeft << "\n";
        }
    }

    void bookSeat(int trainID, const std::string& name) {
        for (auto& t : trains) {
            if (t.id == trainID) {
                if (t.seatsLeft > 0) {
                    t.seatsLeft--;
                    t.reservations.push_back({name});
                    std::cout << "Reservation was made for: " << name << "\n";
                } else {
                    std::cout << "No seats available\n";
                }
                return;
            }
        }
        std::cout << "Train not found\n";
    }

    void showReservations(int trainID) {
        for (auto& t : trains) {
            if (t.id == trainID) {
                for (const auto& r : t.reservations) {
                    std::cout << "Reservation: Train " << t.id << " | Name: " << r.passengerName
                              << "\n";
                }
                return;
            }
        }
        std::cout << "Train not found\n";
    }
    void cancelReservation(int trainID, const std::string& name) {
        for (auto& t : trains) {
            if (t.id == trainID) {
                for (auto it = t.reservations.begin(); it != t.reservations.end(); ++it) {
                    if (it->passengerName == name) {
                        t.reservations.erase(it);
                        t.seatsLeft++;
                        std::cout << "Reservation for " << name << " was canceled\n";
                        return;
                    }
                }
                std::cout << "No reservation found for this passenger on train " << trainID << "\n";
                return;
            }
        }
        std::cout << "Train not found\n";
    }

    void menu() {
        int choice;
        while (true) {
            std::cout << "\n1. List trains\n2. Book seat\n3. Show reservations\n4. Cancel "
                         "reservation\n5. Exit\nChoice: ";
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "\033[2J\033[1;1H";
                listTrains();
            } else if (choice == 2) {
                int trainID;
                std::string name;
                std::cout << "Enter train ID: ";
                std::cin >> trainID;
                std::cout << "Enter passenger name: ";
                std::cin >> name;
                std::cout << "\033[2J\033[1;1H";
                bookSeat(trainID, name);
            } else if (choice == 3) {
                int trainID;
                std::cout << "Enter train ID: ";
                std::cin >> trainID;
                std::cout << "\033[2J\033[1;1H";
                showReservations(trainID);
            } else if (choice == 4) {
                int trainID;
                std::string name;
                std::cout << "Enter train ID: ";
                std::cin >> trainID;
                std::cout << "Enter passenger name: ";
                std::cin >> name;
                std::cout << "\033[2J\033[1;1H";
                cancelReservation(trainID, name);
            } else {
                break;
            }
        }
    }
};

int main() {
    RailwaySystem rs;
    rs.menu();
    return 0;
}
