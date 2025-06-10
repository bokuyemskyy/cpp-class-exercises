#include <iostream>
#include <string>
#include <vector>

class HotelBookingSystem {
    struct Reservation {
        std::string inhabitantName;
    };
    struct Room {
        int number;

        int inhabitantsLeft;
        std::vector<Reservation> reservations;
    };

    std::vector<Room> rooms;

   public:
    HotelBookingSystem() {
        rooms.push_back({1, 4});
        rooms.push_back({2, 3});
        rooms.push_back({3, 4});
    }

    void listRooms() {
        for (const auto& r : rooms) {
            std::cout << "Room number " << r.number << " | Seats left: " << r.inhabitantsLeft
                      << "\n";
        }
    }

    void bookRoom(int roomNumber, const std::string& name) {
        for (auto& r : rooms) {
            if (r.number == roomNumber) {
                if (r.inhabitantsLeft > 0) {
                    r.inhabitantsLeft--;
                    r.reservations.push_back({name});
                    std::cout << "Reservation was made for: " << name << "\n";
                } else {
                    std::cout << "No space available\n";
                }
                return;
            }
        }
        std::cout << "Room not found\n";
    }

    void showReservations(int roomNumber) {
        for (auto& r : rooms) {
            if (r.number == roomNumber) {
                for (const auto& res : r.reservations) {
                    std::cout << "Reservation: Room " << r.number
                              << " | Name: " << res.inhabitantName << "\n";
                }
                return;
            }
        }
        std::cout << "Room not found\n";
    }
    void cancelReservation(int roomNumber, const std::string& name) {
        for (auto& r : rooms) {
            if (r.number == roomNumber) {
                for (auto it = r.reservations.begin(); it != r.reservations.end(); ++it) {
                    if (it->inhabitantName == name) {
                        r.reservations.erase(it);
                        r.inhabitantsLeft++;
                        std::cout << "Reservation for " << name << " was canceled\n";
                        return;
                    }
                }
                std::cout << "No reservation found for this person in room " << roomNumber << "\n";
                return;
            }
        }
        std::cout << "Room not found\n";
    }
    void menu() {
        int choice;
        while (true) {
            std::cout << "\n1. List rooms\n2. Book room\n3. Show reservations\n4. Cancel "
                         "reservation\n5. Exit\nChoice: ";
            std::cin >> choice;

            if (choice == 1) {
                std::cout << "\033[2J\033[1;1H";
                listRooms();
            } else if (choice == 2) {
                int roomNumber;
                std::string name;
                std::cout << "Enter room number: ";
                std::cin >> roomNumber;
                std::cout << "Enter inhabitant name: ";
                std::cin >> name;
                std::cout << "\033[2J\033[1;1H";
                bookRoom(roomNumber, name);
            } else if (choice == 3) {
                int roomNumber;
                std::cout << "Enter room number: ";
                std::cin >> roomNumber;
                std::cout << "\033[2J\033[1;1H";
                showReservations(roomNumber);
            } else if (choice == 4) {
                int roomNumber;
                std::string name;
                std::cout << "Enter room number: ";
                std::cin >> roomNumber;
                std::cout << "Enter inhabitant name: ";
                std::cin >> name;
                std::cout << "\033[2J\033[1;1H";
                cancelReservation(roomNumber, name);
            } else {
                break;
            }
        }
    }
};

int main() {
    HotelBookingSystem hotel;
    hotel.menu();
    return 0;
}
