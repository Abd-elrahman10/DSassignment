#include <iostream>
#include <chrono>
#include <cmath>
#include <type_traits>

using namespace std;
using namespace std ::chrono;
template <typename T>
class SortingSystem {
private:
    T* data;
    int size;

    int getMaximum(int n);
    int getMinimum();
public:

    SortingSystem(int n);
    ~SortingSystem();

    void insertionSort();
    void selectionSort();
    void bubbleSort();
    void shellSort();
    void mergeSort(int left,int right);
    void quickSort(int left,int right);
    void countSort();
    void radixSort();
    void bucketSort();

    void merge(int left, int mid, int right);
    int partition(int low, int high);

    void displayData();
    void measureSortTime(void (SortingSystem::*sortFunc)());
    void measureSortTime(void (SortingSystem::*sortFunc)(int, int), int low, int high);
    void showMenu();

};

template<typename T>
SortingSystem<T> ::SortingSystem(int n) { // insert the size of the data and insert data elements

    size = n;
    data = new T[size];

    for (int i = 0; i < size; ++i) {
        cout << "Enter data " << i+1 << " : " ;
        cin >> data[i];
    }

    showMenu();
}

template<typename T>
SortingSystem<T> ::~SortingSystem()  { // ending the object by delete the dynamic array of data
    delete[] data;
}

template<typename T>
void SortingSystem<T>::insertionSort() {

    cout<< "Unsorted data:";
    displayData();

    for (int i = 1; i < size; ++i) { // start at first element as sorted , create temp of elements
        T key = data[i];
        bool insert = false;
        cout << "Iteration at element number " << i+1 << " Processing ..." << endl;
        for (int j = i-1; j >= 0; --j) { // searching for the right position for the temp
            if (data[j] > key ){
                cout << "  Inserting :" << endl;
                data[j+1] = data[j];
                displayData();
                data[j] = key;
                displayData();
                insert = true;
            }
        }

        if (!insert){
            cout << "No Insertion :" << endl;
            displayData();
        }
    }

    cout << "Sorted data:";
    displayData();

}

template<typename T>
void SortingSystem<T>::selectionSort() {

    cout << "Unsorted data:";
    displayData();

    int PrintCount = 1; // the number of current loop
    for (int i = size-1; i > 0; --i) { // selecting the highest element to sort it in last index i

        cout << "Selection " << PrintCount++ << ": " << endl; // the selection loop
        int lastIndex = getMaximum(i); // get the highest element at the range of 0 to i
        cout << "Selected element " << data[lastIndex] << endl;

        T tmp = data[lastIndex];
        data[lastIndex] = data[i];
        data[i] = tmp;

        displayData();
    }

    cout << "Sorted data:";
    displayData();
}

template<typename T>
void SortingSystem<T>::bubbleSort() {

    cout << "Unsorted data:";
    displayData();

    int attempt = 0; // the number of the loop until ensure sorting

    while(true){ // a while loop to ensure that the elements are sorted correctly

        cout << "Attempt " << ++attempt << ":" << endl ;
        bool swap = false;
        for (int i = 0; i < size-attempt ; ++i) {

            if (data[i] > data[i+1] ){
                cout << "Swapping between " << data[i] << ", " << data[i+1] << " :" << endl;
                T tmp = data[i];
                data[i] = data[i+1];
                data[i+1] = tmp;
                displayData();

                swap = true;
            }

        }

        if (!swap){
            cout << "No Swapping :" << endl;
            displayData();
        }

        if (attempt == size-1){
            break;
        }
    }

    cout << "Sorted data:";
    displayData();
}

template<typename T>
void SortingSystem<T>::shellSort() {// sorting by comparing the elements according to the gap

    cout << "Unsorted data: ";
    displayData();

    for (int gap = size/2; gap > 0 ; gap /=2) { // sort by dividing the size by 2 every time

        cout << "Shell Sort at gap of" << gap << "Processing ..." << endl;


        for (int i = 0; i < size - gap; ++i) {

            if (data[i] > data[gap + i]) {
                cout << "Shell Sort between " << data[i] << ", " << data[gap + i] << ":" << endl;
                swap(data[i], data[gap + i]);
                displayData();
            }

        }
    }
    cout << "Sorted data:";
    displayData();
}

template<typename T>
void SortingSystem<T>::mergeSort(int left, int right) {

    if (left >= right){
        return;
    }

    int mid = left + (right-left)/2; // calculate the middle of every section

    mergeSort(left,mid); // responsible for the merge of the left section
    mergeSort(mid+1,right); // responsible for the merge of the right section
    merge(left,mid,right); // the merging process for the section

    cout << "Sorted data: ";
    displayData();
}

template<typename T>
void SortingSystem<T>::quickSort(int left, int right) {

    if (left >= right){
        return;
    }

    int PivotIndex = partition(left,right); // calculate the pivot of the section

    cout << "Pivot ->" << data[PivotIndex] << ": "; // print the partition and pivot by []

    for (int i = 0; i <= right-left; ++i) {
        if (left+i == PivotIndex){
            cout << "[";
        }
        cout << data[left+i];
        if (left+i != PivotIndex){
            cout << "| ";
        }else if(left+i == PivotIndex){
            cout << "] " ;
        }
    }

    cout << endl;

    quickSort(left,PivotIndex-1); // responsible for the left partition
    quickSort(PivotIndex+1,right); // responsible for the right partition

}

template<typename T>
void SortingSystem<T>::countSort() {


    cout << "Unsorted data:";
    displayData();

    T output[size]; // array to sort the final results
    int n = data[getMaximum(size - 1)]; // getting the size for counting frequency of element
    T CountInput[n + 1]; // array to count the frequency of element below n+1

    for (int i = 0; i < n+1; ++i) {
        CountInput[i] = 0;
    }

    for (int i = 0; i < size; ++i) {
        output[i] = 0;
    }

    cout << "Calculating Frequencies :" << endl;
    for (int i = 0; i < size; ++i) { // counting the frequency and print them
        cout << "Element: " << data[i] << ", Frequency = ";
        CountInput[data[i]]++;
        cout << CountInput[data[i]] << endl;
    }

    for (int i = 0; i < n+1; ++i) { // increase the frequency of i+1 with frequency of i to indicate the position of the element
        CountInput[i + 1] = CountInput[i+1] + CountInput[i];
    }

    for (int i = 0; i < size; ++i) { // placing the element according to their frequency - 1 every time
        output[--(CountInput[data[i]])] = data[i];
        cout << "Element: " << data[i] << " put at index " << CountInput[data[i]] << endl;
        for (int j = 0; j < size; ++j) {
            cout << output[j] << "| ";
        }
        cout << endl;
    }

    for (int i = 0; i < size; ++i) { // filling the final result to the original dataset
        data[i] = output[i];
    }

    cout << "Sorted data: ";
    displayData();

}

template<typename T>
void SortingSystem<T>::radixSort() { // sorting according to the digits with the help of count sort algorithm


    cout << "Unsorted data: ";
    displayData();
    int lastIndex = data[getMaximum(size - 1)]; // getting the highest element index

    for (int factor = 1; lastIndex / factor > 0; factor *= 10) { // loop until the highest element digit reach the end
        cout << lastIndex / factor;
        cout << "Sorting by digit " << factor << " Processing :" << endl;
        cout << "Before: ";
        displayData();

        T output[size]; // store the results every loop according to the current digit
        int CountInput[10]; // store frequency of the digits

        for (int i = 0; i < 10; ++i) {
            CountInput[i] = 0;
        }

        for (int i = 0; i < size; ++i) {
            output[i] = 0;
        }

        for (int i = 0; i < size; ++i) { // count the frequency of the digits
            CountInput[int((data[i] / factor)) % 10]++;
        }

        for (int i = 0; i < 10; ++i) { // increase the frequency of i+1 with frequency of i to indicate the position
            CountInput[i + 1] += CountInput[i];
        }

        for (int i = size - 1; i >= 0; --i) { // placing the element of the digit by frequency - 1
            output[--(CountInput[int((data[i] / factor)) % 10])] = data[i];
        }

        for (int i = 0; i < size; ++i) { // filling the current results to the original dataset
            data[i] = output[i];
        }
        cout << "After: ";
        displayData();

    }
    cout << "Sorted data:";
    displayData();
}

template<typename T>
void SortingSystem<T>::bucketSort() {
    cout << "Unsorted data:";
    displayData();
    T **BucketList; // array of Buckets to sort

    T high = data[getMaximum(size - 1)];
    T low = data[getMinimum()];

    int classes = int(log2(size)); // get the number of classes to sort the elements according to the range
    if ((log2(size) * 10) / 1 != 0) {// if the classes is zero then increase it by 1
        classes += 1;
    }

    T range = (high - low) / classes; // getting the range of the classes
    if (int(range)%1 != 0 || int(range) != 0) { // if the range has fractions then increase it by 1 or the range is zero then increment it
        range += 1;
    }

    BucketList = new T *[classes];
    int CountBuckets[classes]; // array to store the sizes of the classes
    int Buckets_size[classes]; // array to help in running on every element of each bucket

    for (int i = 0; i < classes; ++i) {
        CountBuckets[i] = 0;
    }

    for (int i = 0; i < size; ++i) { // count the size of the classes

        int index = (int) (data[i] - low) / range;
        if (index == classes) {
            index = classes - 1;
        }

        CountBuckets[index]++;
    }

    for (int i = 0; i < classes; ++i) { // insert the sizes of the classes

        BucketList[i] = new T[CountBuckets[i]];
        Buckets_size[i] = CountBuckets[i];

        cout << "Bucket " << i << ":";
        for (int j = 0; j < Buckets_size[i]; ++j) {
            cout << "  |";
        }
        cout << endl;
    }

    for (int i = 0; i < size; ++i) {// insert the elements to their right class

        int index = (int) (data[i] - low) / range;
        if (index == classes) {
            index = classes - 1;
        }

        BucketList[index][--(CountBuckets[index])] = data[i];
        cout << "Inserting element " << data[i] << "at Bucket" << index << endl;
    }

    for (int i = 0; i < classes; ++i) { // sorting the classes by insertion sort
        for (int j = 1; j < Buckets_size[i]; ++j) {

            T elem = BucketList[i][j];
            for (int k = j - 1; k >= 0; --k) {
                if (BucketList[i][k] > elem) {
                    BucketList[i][k + 1] = BucketList[i][k];
                    BucketList[i][k] = elem;
                }
            }
        }

        cout << "Bucket " << i << ":";
        for (int p = 0; p < Buckets_size[i]; ++p) {
            cout << BucketList[i][p] << " |";
        }
        cout << endl;
    }


    int place = 0;// the place of insertion
    cout << "Emptying the Buckets :" << endl;

    for (int i = 0; i < classes; ++i) { // emptying the classes in the dataset

        for (int j = 0; j < Buckets_size[i]; ++j) {
            data[place++] = BucketList[i][j];
        }
        if (Buckets_size[i] != 0) {
            cout << "Emptying Bucket " << i << ":" << endl;
            displayData();
        }
    }
    // deleting the BucketList
    for (int i = 0; i < classes; ++i) {
        delete[] BucketList[i];
    }
    delete[] BucketList;
    cout << "Sorted data: ";
    displayData();
}

template<typename T>
void SortingSystem<T>::merge(int left, int mid, int right) { // the merging algorithm for mergesort

    int nL = mid-left+1 , nR = right-mid;
    T L[nL]; // array for the left section
    T R[nR]; // array for the right section

    for (int i = 0; i < nL; ++i) {
        L[i] = data[left+i] ;
    }

    for (int i = 0; i < nR; ++i) {
        R[i] = data[mid+1+i];
    }
    // show the left section and right section before merge
    cout << "Before merge: " ;
    cout << "[";
    for (int i = 0; i < nL; ++i) {
        cout << L[i];
        if (i == nL-1){
            cout << "]";
        }else{
            cout << ",";
        }
    }

    cout << "   [";
    for (int i = 0; i < nR; ++i) {
        cout << R[i];
        if (i == nR-1){
            cout << "]" << endl;
        }else{
            cout << ",";
        }
    }

    int l = 0 , r=0;
    int count = left;

    while (r < nR && l < nL){ // insert the elements by comparing which is small
        if (L[l] <= R[r]){
            data[count++] = L[l++];
        } else{
            data[count++] = R[r++];
        }
    }

    if (r == nR){// check if there are any elements left in left section to empty
        for (int i = 0; i < nL-l; ++i) {
            data[count] = L[l+i];
            count++;
        }

    } else{// check if there are any elements left in right section to empty
        for (int i = 0; i < nR-r; ++i) {
            data[count] = R[r+i];
            count++;
        }
    }
    // show the merging of the left and right section
    cout << "After merge:  [";
    for (int i = 0; i <= right-left; ++i) {
        cout << data[left+i];
        if (i == right-left){
            cout << "]" << endl;
        }else{
            cout << ",";
        }
    }
}

template<typename T>
int SortingSystem<T>::partition(int low, int high) {// the partition process for quicksort

    int Pivot = high; // assume the pivot at first index

    int i = low-1; // start sorting from last index

    for (int j = low; j < high ; ++j) { // sorting the data until that all left part are less than pivot and right greater than
        if (data[j] <= data[Pivot]){
            swap(data[++i],data[j]);
        }
    }

    swap(data[++i],data[Pivot]); // swapping the assume position with the right position for pivot
    return i; // return the pivot index

}

template<typename T>
int SortingSystem<T>::getMaximum(int n) { // getting the maximum element index and with parameter n to help in selection sort

    int lastIndex = n ;
    for (int j = n ; j >= 0 ; --j) {
        if (data[j] > data[lastIndex]){
            lastIndex = j;
        }
    }

    return lastIndex;
}

template<typename T>
int SortingSystem<T>::getMinimum()  {// getting the minimum element index

    int FirstIndex = 0 ;
    for (int j = 0 ; j < size ; ++j) {
        if (data[j] < data[FirstIndex]){
            FirstIndex = j;
        }
    }

    return FirstIndex;
}

template<typename T>
void SortingSystem<T>::displayData() { // display the current dataset

    cout << "{ ";
    for (int i = 0; i < size; ++i) {
        cout << data[i];
        if (i != size -1){
            cout << ", ";
        } else {
            cout << "}" << endl;
        }
    }
}

template<typename T>
void SortingSystem<T>::measureSortTime(void (SortingSystem<T>::*sortFunc)()){ // measure the time for the sorting function

    auto start = high_resolution_clock :: now();
    (this->*sortFunc)();
    auto end = high_resolution_clock :: now();
    cout << "Execution time: " << duration_cast< duration<double> > (end-start) << " seconds" <<  endl;
}

template<typename T>
void SortingSystem<T>::measureSortTime(void (SortingSystem<T>::*sortFunc)(int, int), int low, int high)  {// overload version for quick and merge sort
    auto start = high_resolution_clock :: now();
    (this->*sortFunc)(low,high);
    auto end = high_resolution_clock :: now();
    cout << "Execution time: " << duration_cast< duration<double> > (end-start) << " seconds" <<  endl;
}

template<typename T>
void SortingSystem<T>::showMenu()  { // show the menu of the sorting algorithms
    int choose;

    cout << "Select a sorting algorithm:" << endl;
    cout << "1. Insertion Sort" << endl;
    cout << "2. Selection Sort" << endl;
    cout << "3. Bubble Sort" << endl;
    cout << "4. Shell Sort" << endl;
    cout << "5. Merge Sort" << endl;
    cout << "6. Quick Sort" << endl;
    cout << "7. Count Sort (Only for integers)" << endl;
    cout << "8. Radix Sort (Only for integers)" << endl;
    cout << "9. Bucket Sort (Only for numerical data)" << endl;
    cout << "Enter your choice (1-9): " ;
    cin >> choose;

    switch (choose) {
        case 1:
            cout << "Insertion Sort Sorting ..." << endl;
            measureSortTime(&SortingSystem<T>::insertionSort);
            break;
        case 2:
            cout << "Selection Sort Sorting ..." << endl;
            measureSortTime(&SortingSystem<T>::selectionSort);
            break;
        case 3:
            cout << "Bubble Sort Sorting ..." << endl;
            measureSortTime(&SortingSystem<T>::bubbleSort);
            break;
        case 4:
            cout << "Shell Sort Sorting ..." << endl;
            measureSortTime(&SortingSystem<T>::shellSort);
            break;
        case 5:
            cout << "Merge Sort Sorting ..." << endl;

            cout << "Unsorted data: ";
            displayData();

            measureSortTime(&SortingSystem<T>::mergeSort,0,size-1) ;

            cout << "Sorted data: ";
            displayData();
            break;
        case 6:
            cout << "Quick Sort Sorting ..." << endl;

            cout << "Unsorted data: ";
            displayData();

            measureSortTime(&SortingSystem<T>::quickSort,0,size-1);

            cout << "Sorted data: ";
            displayData();
            break;
        case 7:
            if constexpr ((std::is_integral<T> :: value && !std::is_same<T,char> :: value)) { // condition to ensure that data is integer and non_negative to sort by count sort
                if (data[getMinimum()] >= 0) {
                    cout << "Count Sort Sorting ..." << endl;

                    measureSortTime(&SortingSystem<T>::countSort);
                }else{
                    cout << "this sort is positive integers only, PLease select another sorting algorithm" << endl;
                    showMenu();
                }
            }else {
                cout << "The sort is for integers only, PLease select another sorting algorithm" << endl;
                showMenu();
            }
            break;
        case 8:
            if constexpr ((std::is_integral<T> :: value && !std::is_same<T,char> :: value)) { // condition to ensure that data is integer and non_negative to sort by radix sort
                if (data[getMinimum()] >= 0){
                cout << "Radix Sort Sorting ..." << endl;
                measureSortTime(&SortingSystem<T>::radixSort);
                }else{
                    cout << "this sort is positive integers only, PLease select another sorting algorithm" << endl;
                    showMenu();
                }
            }else {
                cout << "The sort is for integers only, PLease select another sorting algorithm" << endl;
                showMenu();
            }
            break;

        case 9:
            if constexpr ( std::is_arithmetic<T> :: value && !std::is_same<T,char> :: value) { // sorting algorithm for numerics by range
                cout << "Bucket Sort Sorting ..." << endl;
                measureSortTime(&SortingSystem<T>::bucketSort);
            }else{
                 cout << "this sorting is for numerical data only please try another sorting algorithm" << endl;
                 showMenu();
            }
            break;
        default:
            cout << "invalid choice, Please try again" << endl;
            showMenu();
    }
}

void menu(int n){

    int choice;
    cout << "Choose the type of system for sorting" << endl;
    cout << "1) integer" << endl;
    cout << "2) double " << endl;
    cout << "3) float" << endl;
    cout << "4) string" << endl;
    cout << "5) char" << endl;
    cout << "Enter your choice(1-5): " << endl;
    cin >> choice;

    if (choice == 1){
        SortingSystem<int> system1(n);
    }else if (choice == 2){
        SortingSystem<double> system1(n);
    }else if (choice == 3){
        SortingSystem<float> system1(n);
    }else if(choice == 4){
        SortingSystem<string> system1(n);
    }else if (choice == 5){
        SortingSystem<char> system1(n);
    }else{
        cout << "invalid choice, Please try again" << endl;
        menu(n);
    }
}

int main() {
    while (true){
        int n;
        while (true) {
            cout << "Enter the number of items to sort: ";
            cin >> n;
            if (n > 1){
                break;
            }
            cout << "invalid number, the number must be greater than 1" << endl;
        }
        menu(n);

        char ch;
        cout << "Do you to sort another dataset ? (y/n): ";
        cin >> ch;
        if (ch == 'n'){
            cout << "Thank you for using the sorting system! Goodbye!";
            break;
        }
    }
}
