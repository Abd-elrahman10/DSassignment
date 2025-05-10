#include <iostream>
#include <fstream>
using namespace std;

class SegmentFlip {
    int arrSize, segmentLength;
    int* arr;

public:
    SegmentFlip(int size, int k, int* inputArr) {
        arrSize = size;
        segmentLength = k;
        arr = new int[arrSize];
        for (int i = 0; i < arrSize; i++) {
            arr[i] = inputArr[i];
        }
    }

    ~SegmentFlip() {
        delete[] arr;
    }
    /*3
0 0 0 1 0 1 1 0
*/
    int MinFlips() {
        if (!arr) return -1;

        int* isFlipped = new int[arrSize]();
        int flipCount = 0, flips = 0;

        for (int i = 0; i < arrSize; i++) {
            if (i >= segmentLength) {
                flipCount -= isFlipped[i - segmentLength];
            }

            if ((arr[i] + flipCount) % 2 == 0) {
                if (i + segmentLength > arrSize) {
                    delete[] isFlipped;
                    return -1;
                }
                isFlipped[i] = 1;
                flipCount++;
                flips++;
            }
        }

        delete[] isFlipped;
        return flips;
    }
};

int main() {
    ifstream inputFile("P3_test_casses.txt");
    if (!inputFile) {
        cout << "Error: File not found.\n";
        return 0;
    }

    int testNumber = 1;
    int n, k;
    while (inputFile >> n >> k) {
        int* inputArr = new int[n];
        for (int i = 0; i < n; i++) {
            inputFile >> inputArr[i];
        }

        SegmentFlip flipper(n, k, inputArr);
        int result = flipper.MinFlips();

        cout << "Test Case " << testNumber++ << ": Minimum flips = " << result << "\n\n";

        delete[] inputArr;
    }

    inputFile.close();
    return 0;
}
