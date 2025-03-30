#include <bits/stdc++.h>
using namespace std;

template <typename T>
class StatisticalCalculation {
private:
    T* data;
    int size;

public:
    StatisticalCalculation() {
        this->size = 0;
        data = nullptr;
    }

    ~StatisticalCalculation() {
        delete[] data;
    }

    void inputData(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error: File not found!\n";
            return;
        }
        if (!(file >> size) || size <= 0) {
            cout << "Error: Invalid size in file! Must be a positive integer.\n";
            return;
        }
        data = new T[size];
        for (int i = 0; i < size; i++) {
            if (!(file >> data[i])) {
                cout << "Error: Invalid data in file! Expected " << size << " numeric values.\n";
                delete[] data;
                data = nullptr;
                return;
            }
        }
        file.close();
        cout << "Data successfully loaded from file: " << filename << endl;
    }

    void sort() {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (data[j] > data[j + 1]) {
                    swap(data[j], data[j + 1]);
                }
            }
        }
    }

    T findMin() {
        T minVal = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] < minVal) 
            {
                minVal = data[i];
            }
        }
        return minVal;
    }

    T findMax() {
        T maxVal = data[0];
        for (int i = 1; i < size; i++) {
            if (data[i] > maxVal) {
                maxVal = data[i];
            }
        }
        return maxVal;
    }

    double findMedian() {
        sort();
        if (size % 2 == 0) {
            return (data[size / 2 - 1] + data[size / 2]) / 2.0;
        } else {
            return data[size / 2];
        }
    }

    double findMean() {
        return findSummation() / static_cast<double>(size);
    }

    T findSummation() {
        T sum = 0;
        for (int i = 0; i < size; i++) {
            sum += data[i];
        }
        return sum;
    }
    

    void displayArray() {
        cout << "Array elements: ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    void statisticsMenu() {
        if (data == nullptr) {
            cout << "No valid data available! Exiting...\n";
            return;
        }
        int choice;
        do {
            cout << "\nSelect a statistical operation:\n";
            cout << "1. Find Minimum\n";
            cout << "2. Find Maximum\n";
            cout << "3. Find Median\n";
            cout << "4. Find Mean\n";
            cout << "5. Find Summation\n";
            cout << "6. Display Sorted Data\n";
            cout << "7. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice! Please enter a number from 1 to 7.\n";
                continue;
            }
            switch (choice) {
                case 1:
                    cout << "Minimum: " << findMin() << endl;
                    break;
                case 2:
                    cout << "Maximum: " << findMax() << endl;
                    break;
                case 3:
                    cout << "Median: " << findMedian() << endl;
                    break;
                case 4:
                    cout << "Mean: " << findMean() << endl;
                    break;
                case 5:
                    cout << "Summation: " << findSummation() << endl;
                    break;
                case 6:
                    sort();
                    displayArray();
                    break;
                case 7:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice! Please enter a number from 1 to 7.\n";
            }
        } while (choice != 7);
    }
};

int main() {
    cout << "##########################################################\n";
    cout << "Welcome to the Statistical Calculation Program\n";
    cout << "The input is read from a file.\n";
    cout << "Your file should contain two lines:\n";
    cout << "1. The first line is the size of the array.\n";
    cout << "2. The second line contains the elements of the array.\n";
    cout << "Example file (data.txt):\n";
    cout << "5\n10 5 8 3 7\n";
    cout << "##########################################################\n";

    string fileName;
    cout << "Enter your file name (e.g., test_data.txt): ";
    cin >> fileName;
    
    StatisticalCalculation<double> stats;
    stats.inputData(fileName);
    stats.statisticsMenu();

    return 0;
}
