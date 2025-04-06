#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

class IftarGuest
{
private:
    string guestName;
    string contactNumber;
    string eventDate;

    bool isValidDate(const string &date)
    {
        int day, month, year;
        if (sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year) != 3)
            return false;
        if (day < 1 || day > 31 || month < 1 || month > 12 || year < 2025 || year > 2030)
            return false;
        if (month == 4 || month == 6 || month == 9 || month == 11)
            return day <= 30;
        if (month == 2)
            return day <= 28;
        return true;
    }

public:
    IftarGuest() : guestName(""), contactNumber(""), eventDate("01/01/2025") {}

    IftarGuest(string name, string phone, string date)
    {
        guestName = name;
        contactNumber = phone;
        eventDate = isValidDate(date) ? date : "01/01/2025";
    }

    string getName() const { return guestName; }
    string getPhone() const { return contactNumber; }
    string getDate() const { return eventDate; }

    void changeDate(string newDate)
    {
        if (isValidDate(newDate))
        {
            eventDate = newDate;
            cout << "Updated invitation date for " << guestName << " to: " << eventDate << "\n";
        }
        else
        {
            cout << "Error: Invalid date format! Keeping previous date: " << eventDate << "\n";
        }
    }

    void showDetails() const
    {
        cout << "Name: " << guestName << " | Phone: " << contactNumber
             << " | Iftar Date: " << eventDate << "\n";
    }
};

class IftarManager
{
private:
    vector<IftarGuest> guestList;

    string normalizeText(const string &text) const
    {
        string trimmed;
        size_t start = text.find_first_not_of(" \t");
        size_t end = text.find_last_not_of(" \t");

        if (start != string::npos && end != string::npos)
            trimmed = text.substr(start, end - start + 1);
        else
            trimmed = text;

        for (char &c : trimmed)
            c = tolower(c);

        return trimmed;
    }

    bool isAlphaOnly(const string &text) const
    {
        for (char c : text)
        {
            if (!isalpha(c) && c != ' ')
                return false;
        }
        return true;
    }

    void parseDate(const string &date, int &day, int &month, int &year) const
    {
        sscanf(date.c_str(), "%d/%d/%d", &day, &month, &year);
    }

    bool dateLessThan(const string &date1, const string &date2) const
    {
        int d1, m1, y1, d2, m2, y2;
        parseDate(date1, d1, m1, y1);
        parseDate(date2, d2, m2, y2);
        return (y1 < y2) || (y1 == y2 && m1 < m2) || (y1 == y2 && m1 == m2 && d1 < d2);
    }

    void mergeGuests(int left, int mid, int right)
    {
        vector<IftarGuest> temp(right - left + 1);
        int i = left, j = mid + 1, k = 0;

        while (i <= mid && j <= right)
        {
            if (dateLessThan(guestList[i].getDate(), guestList[j].getDate()))
                temp[k++] = guestList[i++];
            else
                temp[k++] = guestList[j++];
        }
        while (i <= mid)
            temp[k++] = guestList[i++];
        while (j <= right)
            temp[k++] = guestList[j++];

        for (int p = 0; p < k; p++)
            guestList[left + p] = temp[p];
    }

    void sortGuests(int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;
            sortGuests(left, mid);
            sortGuests(mid + 1, right);
            mergeGuests(left, mid, right);
        }
    }

public:
    void registerGuest(const IftarGuest &guest)
    {
        string newGuestName = normalizeText(guest.getName());
        string newPhone = normalizeText(guest.getPhone());

        if (!isAlphaOnly(newGuestName))
        {
            cout << "Error: Guest name must contain letters only!\n";
            return;
        }

        for (const auto &existingGuest : guestList)
        {
            if (normalizeText(existingGuest.getName()) == newGuestName &&
                normalizeText(existingGuest.getPhone()) == newPhone)
            {
                cout << "Error: Guest with name \"" << guest.getName()
                     << "\" and phone \"" << guest.getPhone() << "\" already exists!\n";
                return;
            }
        }

        guestList.push_back(guest);
        cout << "Added " << guest.getName() << " successfully.\n";
    }

    void listGuests() const
    {
        if (guestList.empty())
        {
            cout << "No guests added yet!\n";
            return;
        }
        cout << "--- Guest List ---\n";
        for (const auto &guest : guestList)
            guest.showDetails();
        cout << "-----------------\n";
    }

    void editInvite(string name, string newDate)
    {
        string lowerName = normalizeText(name);
        for (auto &guest : guestList)
        {
            if (normalizeText(guest.getName()) == lowerName)
            {
                guest.changeDate(newDate);
                return;
            }
        }
        cout << "Error: " << name << " not found in the list!\n";
    }

    void sendReminders(string date) const
    {
        cout << "--- Sending reminders for " << date << " ---\n";
        bool found = false;
        for (const auto &guest : guestList)
        {
            if (guest.getDate() == date)
            {
                cout << "Reminder for " << guest.getName() << ": Iftar is on " << date << "\n";
                found = true;
            }
        }
        if (!found)
            cout << "No guests scheduled for this date.\n";
    }

    void arrangeByDate()
    {
        if (guestList.size() > 1)
        {
            sortGuests(0, guestList.size() - 1);
            cout << "Guest list sorted by date successfully.\n";
        }
        else
        {
            cout << "List is too small, no sorting needed.\n";
        }
    }
};

int main()
{
    IftarManager manager;
    int choice;
    string name, phone, date;

    cout << "===== Iftar Invitation Manager =====\n";
    while (true)
    {
        cout << "\n1. Add Guest\n2. Show List\n3. Edit Date\n4. Send Reminders\n5. Sort List\n6. Exit\n";
        cout << "Your choice: ";
        if (!(cin >> choice))
        {
            cout << "Invalid input! Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }
        cin.ignore();

        if (choice == 1)
        {
            cout << "Guest name: ";
            getline(cin, name);
            cout << "Phone number: ";
            getline(cin, phone);
            cout << "Invitation date (dd/mm/yyyy): ";
            getline(cin, date);
            manager.registerGuest(IftarGuest(name, phone, date));
        }
        else if (choice == 2)
        {
            manager.listGuests();
        }
        else if (choice == 3)
        {
            cout << "Guest name: ";
            getline(cin, name);
            cout << "New date (dd/mm/yyyy): ";
            getline(cin, date);
            manager.editInvite(name, date);
        }
        else if (choice == 4)
        {
            cout << "Reminder date (dd/mm/yyyy): ";
            getline(cin, date);
            manager.sendReminders(date);
        }
        else if (choice == 5)
        {
            manager.arrangeByDate();
        }
        else if (choice == 6)
        {
            cout << "Thank you for using the program!\n";
            break;
        }
        else
        {
            cout << "Invalid choice, please try again.\n";
        }
    }

    return 0;
}
