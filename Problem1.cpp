#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Guest {
private:
    string name, contact, iftar_date;

public:
    Guest() {}
    Guest(string n, string c, string d) : name(n), contact(c), iftar_date(d) {}

    string getName() { return name; }
    string getDate() { return iftar_date; }

    void updateInvitation(string new_date) {
        iftar_date = new_date;
        cout << name << "'s invitation updated to " << new_date << endl;
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
        return d1 < d2; // Lexicographic comparison (works for YYYY-MM-DD format)
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
            cout << "No guests added.\n";
            return;
        }
        for (int i = 0; i < size; i++)
            guestList[i].displayGuest();
    }

    void updateGuestInvitation(string name, string new_date) {
        for (int i = 0; i < size; i++) {
            if (guestList[i].getName() == name) {
                guestList[i].updateInvitation(new_date);
                return;
            }
        }
        cout << "Guest " << name << " not found.\n";
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
                cout << "Reminder: " << guestList[i].getName() << ", your Iftar is on " << date << endl;
                found = true;
            }
        }
        if (!found) cout << "No guests scheduled for " << date << ".\n";
    }

    void runTestCases(string filename) {
        ifstream file(filename.c_str());
        if (!file) {
            cout << "Error opening file.\n";
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
    manager.addGuest(Guest("Aisha", "1234567890", "2025-03-15"));
    manager.addGuest(Guest("Bilal", "0987654321", "2025-03-10"));
    manager.addGuest(Guest("Zara", "5550001111", "2025-03-20"));

    // Test Case 2: Displaying all guests
    cout << "\nDisplaying All Guests:\n";
    manager.displayAllGuests();

    // Test Case 3: Updating a guest's invitation date
    cout << "\nUpdating Zara's invitation date to 2025-03-25:\n";
    manager.updateGuestInvitation("Zara", "2025-03-25");

    // Test Case 4: Sorting guest list by date
    cout << "\nSorting Guests by Date:\n";
    manager.sortGuestList();

    // Display after sort
    cout << "\nGuests after sorting:\n";
    manager.displayAllGuests();

    // Test Case 5: Sending reminders for a specific date
    cout << "\nSending Reminder for 2025-03-25:\n";
    manager.sendReminder("2025-03-25");

    // Test Case 6: Try to add duplicate guest
    cout << "\nAttempting to add Aisha again:\n";
    manager.addGuest(Guest("Aisha", "1234567890", "2025-03-30"));
   // manager.runTestCases("Problem1_testcases.txt");
    return 0;
}
