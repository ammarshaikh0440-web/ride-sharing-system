#include <iostream>
#include <string>
using namespace std;

/* ============================================
   RIDER QUEUE (Linked List)
   ============================================ */
class RiderNode {
public:
    string name;
    RiderNode* next;
    RiderNode(string n) {
        name = n;
        next = nullptr;
    }
};

class RiderQueue {
public:
    RiderNode* front;
    RiderNode* rear;

    RiderQueue() {
        front = rear = nullptr;
    }

    void addRider(string name) {
        RiderNode* newNode = new RiderNode(name);
        if (!rear) {
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }

    string getRider() {
        if (!front) return "";
        RiderNode* temp = front;
        string nm = temp->name;
        front = front->next;
        if (!front) rear = nullptr;
        delete temp;
        return nm;
    }

    bool empty() {
        return front == nullptr;
    }

    void display() {
        RiderNode* temp = front;
        cout << "Pending Rider Requests: ";
        while (temp) {
            cout << "[" << temp->name << "] ";
            temp = temp->next;
        }
        cout << "\n";
    }
};

/* ============================================
   FIXED ROUTE TREE
   ============================================ */
class ZoneNode {
public:
    string zone;
    ZoneNode* left;
    ZoneNode* right;

    ZoneNode(string z) {
        zone = z;
        left = right = nullptr;
    }
};

class CityTree {
public:
    ZoneNode* root;

    CityTree() {
        root = nullptr;
    }

    void buildFixedRoutes() {
        root = new ZoneNode("Sadar");
        root->left = new ZoneNode("Lalkurti");
        root->left->left = new ZoneNode("Islamabad");
        root->left->left->left = new ZoneNode("FaisalMasjid");
    }

    void displayRoutes() {
        cout << "\n--- FIXED ROUTES ---\n";
        cout << " Available Movements:\n";
        cout << " 1. Lalkurti -> Sadar\n";
        cout << " 2. Lalkurti -> Islamabad\n";
        cout << " 3. Islamabad -> Lalkurti\n";
        cout << " 4. Islamabad -> FaisalMasjid\n\n";
    }
};

/* ============================================
   CIRCULAR LINKED LIST FOR 4 DRIVERS
   ============================================ */
class DriverNode {
public:
    string name;
    DriverNode* next;

    DriverNode(string n) {
        name = n;
        next = nullptr;
    }
};

class DriverCircle {
public:
    DriverNode* head;

    DriverCircle() {
        head = nullptr;
    }

    void addDriver(string name) {
        DriverNode* newDriver = new DriverNode(name);

        if (!head) {
            head = newDriver;
            newDriver->next = newDriver;
            return;
        }

        DriverNode* temp = head;
        while (temp->next != head)
            temp = temp->next;

        temp->next = newDriver;
        newDriver->next = head;
    }

    string getDriver(int number) {
        if (!head) return "";

        DriverNode* temp = head;
        int count = 1;

        while (count < number) {
            temp = temp->next;
            count++;
        }

        return temp->name;
    }

    void display() {
        if (!head) {
            cout << "No drivers.\n";
            return;
        }
        DriverNode* temp = head;
        cout << "Available Drivers: ";
        do {
            cout << "[" << temp->name << "] ";
            temp = temp->next;
        } while (temp != head);
        cout << "\n";
    }
};

/* ============================================
   MATCHING + ETA + OPTIMIZATION
   ============================================ */
class RideSystem {
public:
    RiderQueue queue;
    DriverCircle drivers;
    CityTree city;

    // Distance between major points
    int getDistance(string start, string end) {
        if (start == "Lalkurti" && end == "Sadar") return 10;
        if (start == "Sadar" && end == "Lalkurti") return 10;

        if (start == "Lalkurti" && end == "Islamabad") return 15;
        if (start == "Islamabad" && end == "Lalkurti") return 15;

        if (start == "Islamabad" && end == "FaisalMasjid") return 5;
        if (start == "FaisalMasjid" && end == "Islamabad") return 5;

        return -1; // invalid
    }

    int calculateETA(int distance) {
        int speed = 40; // km/h
        double eta = (double)distance / speed * 60;
        return (int)eta;
    }

    void assignRide(string start, string end) {
        if (queue.empty()) {
            cout << "No riders waiting.\n";
            return;
        }

        int distance = getDistance(start, end);
        if (distance == -1) {
            cout << "Invalid route.\n";
            return;
        }

        int eta = calculateETA(distance);

        string rider = queue.getRider();
        string assignedDriver = "";

        // FIXED CONDITIONS
        if (start == "Lalkurti" && end == "Sadar")
            assignedDriver = drivers.getDriver(1);

        else if (start == "Lalkurti" && end == "Islamabad")
            assignedDriver = drivers.getDriver(2);

        else if (start == "Islamabad" && end == "Lalkurti")
            assignedDriver = drivers.getDriver(3);

        else if (start == "Islamabad" && end == "FaisalMasjid")
            assignedDriver = drivers.getDriver(4);

        cout << "\n✔ Ride Matched!\n";
        cout << " Passenger: " << rider << "\n";
        cout << " From: " << start << "  To: " << end << "\n";
        cout << " Assigned Driver: " << assignedDriver << "\n";
        cout << " Distance: " << distance << " km\n";
        cout << " ETA: " << eta << " minutes\n";
        cout << " Route Optimization: Direct optimal path selected.\n\n";
    }
};

/* ============================================
   MAIN MENU SYSTEM
   ============================================ */
int main() {
    RideSystem sys;

    sys.city.buildFixedRoutes();

    sys.drivers.addDriver("Ali");
    sys.drivers.addDriver("Bilal");
    sys.drivers.addDriver("Usman");
    sys.drivers.addDriver("Hamza");

    int choice;
    string name, start, end;

    while (true) {
        cout << "\n========= RIDE SHARING MENU =========\n";
        cout << "1. Add Passenger\n";
        cout << "2. Show Passenger\n";
        cout << "3. Show Drivers\n";
        cout << "4. Show Routes\n";
        cout << "5. Request a Ride\n";
        cout << "6. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        if (choice == 1) {
            cout << "Enter Passenger Name: ";
            cin >> name;
            sys.queue.addRider(name);
        }
        else if (choice == 2) sys.queue.display();
        else if (choice == 3) sys.drivers.display();
        else if (choice == 4) sys.city.displayRoutes();

        else if (choice == 5) {
            cout << "Enter Start Location: ";
            cin >> start;
            cout << "Enter End Location: ";
            cin >> end;
            sys.assignRide(start, end);
        }
        else if (choice == 6) break;
        else cout << "Invalid choice.\n";
    }

    return 0;
}
