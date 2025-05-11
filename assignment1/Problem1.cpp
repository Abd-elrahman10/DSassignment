#include <iostream>
#include <string>
#include <fstream>
#include<sstream>

using namespace std;
class Guest {
private:
    string name, contact, iftar_date;

    // Helper function to check if the date is valid
    bool isValidDate(const string& date) {
        int day, month, year;
        // Check for the correct date format (dd-mm-yyyy)
        char dash1, dash2;
        stringstream ss(date);
        ss >> day >> dash1 >> month >> dash2 >> year;

        // Validate the date format
        if (ss.fail() || dash1 != '-' || dash2 != '-' || day < 1 || month < 1 || year < 2024) {
            return false;
        }

        // Check for valid months and days
        if (month > 12 || (month == 2 && (year % 4 == 0 ? day > 29 : day > 28)) ||
            ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) || day > 31) {
            return false;
        }
        return true;
    }

public:
    Guest() : name("Nobody"), contact("aaaa@gmail.com"), iftar_date("01-05-2024") {}

    Guest(string n, string c, string d) : name(n), contact(c), iftar_date(d) {
        if (!isValidDate(iftar_date)) {
            cout << "Invalid date provided, setting to default (01-05-2024).\n";
            iftar_date = "01-05-2024";
        }
    }

    string getName() { return name; }
    string getDate() { return iftar_date; }

    void updateInvitation(string new_date) {
        if (isValidDate(new_date)) {
            iftar_date = new_date;
            cout << name << "'s invitation updated to " << new_date << endl;
        } else {
            cout << "Error: Invalid date format.\n";
        }
    }

    void displayGuest() {
        cout << "Name: " << name << ", Contact: " << contact << ", Iftar Date: " << iftar_date << endl;
    }
};

class IftarManager {
private:
    Guest* guestList;
    int size;
    int capacity;

    void resize() {
        capacity = (capacity == 0) ? 1 : capacity * 2;
        Guest* newList = new Guest[capacity];
        for (int i = 0; i < size; i++) {
            newList[i] = guestList[i];
        }
        delete[] guestList;
        guestList = newList;
    }

    bool dateLess(string d1, string d2) {
        return d1 < d2;
    }

public:
    IftarManager() : guestList(nullptr), size(0), capacity(0) {}

    ~IftarManager() {
        delete[] guestList;

    }

    void addGuest(Guest g) {
        for (int i = 0; i < size; i++) {
            if (guestList[i].getName() == g.getName()) {
                cout << "Guest " << g.getName() << " already exists!\n";
                return;
            }
        }
        if (size == capacity) resize();
        guestList[size++] = g;
        cout << "Guest " << g.getName() << " added.\n";
    }

    void displayAllGuests() {
        if (size == 0) {
            cout << "No guests have been invited yet.\n";
            return;
        }
        cout << "----- Guest List -----\n";
        for (int i = 0; i < size; i++)
            guestList[i].displayGuest();
        cout << "----------------------\n";
    }

    void updateGuestInvitation(string name, string new_date) {
        for (int i = 0; i < size; i++) {
            if (guestList[i].getName() == name) {
                guestList[i].updateInvitation(new_date);
                return;
            }
        }
        cout << "Guest " << name << " not found. Cannot update invitation.\n";
    }

    void sortGuestList() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = i + 1; j < size; j++) {
                if (dateLess(guestList[j].getDate(), guestList[i].getDate())) {
                    Guest temp = guestList[i];
                    guestList[i] = guestList[j];
                    guestList[j] = temp;
                }
            }
        }
        cout << "Guests sorted by date.\n";
    }

    void sendReminder(string date) {
        bool found = false;
        for (int i = 0; i < size; i++) {
            if (guestList[i].getDate() == date) {
                cout << "Reminder: " << guestList[i].getName()
                     << ", your Iftar is on " << date << endl;
                found = true;
            }
        }
        if (!found)
            cout << "No guests scheduled for " << date << ".\n";
    }

    void runTestCases(string filename) {
        ifstream file(filename.c_str());
        if (!file) {
            cout << "Error opening file: " << filename << endl;
            return;
        }

        string command;
        while (file >> command) {
            if (command == "ADD") {
                string name, contact, date;
                file >> name >> contact >> date;
                addGuest(Guest(name, contact, date));
            } else if (command == "DISPLAY") {
                displayAllGuests();
            } else if (command == "UPDATE") {
                string name, new_date;
                file >> name >> new_date;
                updateGuestInvitation(name, new_date);
            } else if (command == "SORT") {
                sortGuestList();
            } else if (command == "REMIND") {
                string date;
                file >> date;
                sendReminder(date);
            }
        }

        file.close();
    }
};

int main() {
    IftarManager manager;
/*
    manager.addGuest(Guest("Aisha", "1234567890", "15-03-2024"));
    manager.addGuest(Guest("Bilal", "0987654321", "10-03-2025"));
    manager.addGuest(Guest("Zara", "5550001111", "20-03-2025"));

    // Test Case 2:
    cout << "\nDisplaying All Guests:\n";
    manager.displayAllGuests();

    // Test Case 3:
    cout << "\nUpdating Zara's invitation date to 25-03-2025:\n";
    manager.updateGuestInvitation("Zara", "25-03-2025");

    // Test Case 4:
    cout << "\nSorting Guests by Date:\n";
    manager.sortGuestList();

    // Display after sort
    cout << "\nGuests after sorting:\n";
    manager.displayAllGuests();

    // Test Case 5:
    cout << "\nSending Reminder for 25-03-2025:\n";
    manager.sendReminder("25-03-2025");

    // Test Case 6:
    cout << "\nAttempting to add Aisha again:\n";
    manager.addGuest(Guest("Aisha", "1234567890", "30-03-2025"));

*/



    //Test from file
  manager.runTestCases("Problem1_testcases.txt");
    return 0;
}
