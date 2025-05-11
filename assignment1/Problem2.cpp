#include <iostream>
#include <cmath>
#include <limits>
#include <fstream>
using namespace std;

class Polynomial {
private:
    int* coeffsPolynomial;
    int OrderOfPolynomial;

public:
    Polynomial(int order, int poly[]) : OrderOfPolynomial(order) {

        coeffsPolynomial = new int [OrderOfPolynomial + 1];

        for(int i = 0; i <= OrderOfPolynomial + 1; i++){
            coeffsPolynomial[i] = poly[i];
        }
    }
    ~Polynomial() {
        delete[] coeffsPolynomial;
    }

    bool isInvalid() const {
        bool allZeroLHS = true;
        for (int i = OrderOfPolynomial + 1; i > 0; --i) {
            if (coeffsPolynomial[i] != 0) {
                allZeroLHS = false;
                break;
            }
        }
        int rhs = coeffsPolynomial[0];
        return allZeroLHS && (rhs != 0);
    }

    void Display() {
        bool firstTerm = true;
        for (int i = OrderOfPolynomial + 1; i >= 0; i--) {
            int coeff = coeffsPolynomial[i];
            if (coeff == 0 && i != 0) {
                continue;
            }
            if (!firstTerm && i != 0) {
                (coeff > 0)? cout << " + " : cout << " - ";
            }
            else if (coeff < 0 && coeff != 0)
                cout << " - ";
            if (i == 0 ) {
                cout << " = " << coeff;
            }
            else if (i == 1) cout << abs(coeff);
            else if (i == 2) {
                if ((abs(coeff)) == 1) cout << "x";
                else cout << abs(coeff) << "x";
            }
            else if (i > 2){
                if ((abs(coeff)) == 1)
                    cout << "x^" << i - 1;
                else
                    cout << abs(coeff) << "x^" << i - 1;
            }

            firstTerm = false;
        }
        if (firstTerm) {
            cout << "0";
        }
        cout << endl;
    }

    Polynomial operator+(const Polynomial& other) const {
        int maxDegree = max(OrderOfPolynomial, other.OrderOfPolynomial);
        int* resultCoeffs = new int[maxDegree + 2]();

        for (int i = 0; i <= OrderOfPolynomial + 1; i++) {
            resultCoeffs[i] += coeffsPolynomial[i];
        }
        for (int i = 0; i <= other.OrderOfPolynomial + 1; i++) {
            resultCoeffs[i] += other.coeffsPolynomial[i];
        }

        Polynomial result(maxDegree, resultCoeffs);
        delete[] resultCoeffs;
        return result;
    }

    Polynomial operator-(const Polynomial& other) const {
        int maxDegree = max(OrderOfPolynomial, other.OrderOfPolynomial);
        int* resultCoeffs = new int[maxDegree + 2]();

        for (int i = 0; i <= OrderOfPolynomial + 1; i++) {
            resultCoeffs[i] += coeffsPolynomial[i];
        }
        for (int i = 0; i <= other.OrderOfPolynomial + 1; i++) {
            resultCoeffs[i] -= other.coeffsPolynomial[i];
        }
        Polynomial result(maxDegree, resultCoeffs);
        delete[] resultCoeffs;
        return result;
    }


};


void FillPolynomial(int OrderOfPolynomial, int coeffsPolynomial[]) {
    for (int i = 0; i <= OrderOfPolynomial + 1; i++) {
        while (!(cin >> coeffsPolynomial[i])) {
            cout << "Invalid input. Please enter a coeff: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
    cout << endl;
}

int getOrder()
{
    int order;
    while (!(cin >> order)) {
        cout << "Invalid input. Please enter an Order: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return order;
}

int main() {

    // input by file
    ifstream inputFile("Problem2_testcases.txt");
    if (!inputFile) {
        cout << "Error: Cannot open Problem2_testcases.txt" << endl;
        return 0;
    }

    int Firstorder, Secondorder;
    while (inputFile >> Firstorder) {
        int* coeffsFirstpolynomial = new int[Firstorder + 1];
        for (int i = 0; i <= Firstorder + 1; i++) {
            inputFile >> coeffsFirstpolynomial[i];
        }

        inputFile >> Secondorder;
        int* coeffsSecondpolynomial = new int[Secondorder + 1];
        for (int i = 0; i <= Secondorder + 1; i++) {
            inputFile >> coeffsSecondpolynomial[i];
        }

        Polynomial P1(Firstorder, coeffsFirstpolynomial);
        Polynomial P2(Secondorder, coeffsSecondpolynomial);

        cout << "First Polynomial: ";
        if (P1.isInvalid()) {
            cout << "Error: Invalid polynomial (left-hand side is zero but right-hand side is not zero)." << endl;
        } else {
            P1.Display();
        }

        cout << "Second Polynomial: ";
        if (P2.isInvalid()) {
            cout << "Error: Invalid polynomial (left-hand side is zero but right-hand side is not zero)." << endl;
        } else {
            P2.Display();
        }

        Polynomial sum = P1 + P2;
        Polynomial diff = P2 - P1;

        cout << "Sum of polynomials: ";
        if (sum.isInvalid()) {
            cout << "Error: Invalid polynomial (left-hand side is zero but right-hand side is not zero)." << endl;
        } else {
            sum.Display();
        }

        cout << "Difference of polynomials: ";
        if (diff.isInvalid()) {
            cout << "Error: Invalid polynomial (left-hand side is zero but right-hand side is not zero)." << endl;
        } else {
            diff.Display();
        }

        cout << "----------------------------" << endl;

        delete[] coeffsFirstpolynomial;
        delete[] coeffsSecondpolynomial;
    }

    inputFile.close();

    // input by user

    /*int Firstorder = 0, Secondorder = 0;
    cout << "Order of first polynomial: ";
    Firstorder = getOrder();
    int* coeffsFirstpolynomial = new int[Firstorder + 1];
    cout << "Enter coefficients for the first polynomial: ";
    FillPolynomial(Firstorder, coeffsFirstpolynomial);

    cout << "Order of second polynomial: ";
    Secondorder = getOrder();
    int* coeffsSecondpolynomial = new int[Secondorder + 1];
    cout << "Enter coefficients for the second polynomial: ";
    FillPolynomial(Secondorder, coeffsSecondpolynomial);

    Polynomial P1(Firstorder, coeffsFirstpolynomial);
    Polynomial P2(Secondorder, coeffsSecondpolynomial);

    cout << "First polynomial: ";
    if (P1.isInvalid())
    {
        cout << "Error: Invalid polynomial (left-hand side is zero but right-hand side is not zero)." << endl;

    }
    else{
        P1.Display();
    }

    cout << "Second polynomial: ";
     if (P2.isInvalid())
    {
        cout << "Error: Invalid polynomial (left-hand side is zero but right-hand side is not zero)." << endl;

    }
    else{
        P2.Display();
    }

    Polynomial sum(P1 + P2);
    Polynomial diff(P2 - P1);

    cout << "Sum of polynomials: ";
    if (sum.isInvalid()) {
        cout << "Error: Invalid polynomial (left-hand side is zero but right-hand side is not zero)." << endl;
    }
    else {
        sum.Display();
    }

    cout << "Difference of polynomials: ";
    if (diff.isInvalid()) {
        cout << "Error: Invalid polynomial (left-hand side is zero but right-hand side is not zero)." << endl;
    }
    else {
        diff.Display();
    }
    delete[] coeffsFirstpolynomial;
    delete[] coeffsSecondpolynomial;
    */

    return 0;
}

/*
test1:
Input:
Order of first polynomial: 2
Enter polynomial: 0 1 3 2
Order of second polynomial: 4
Enter polynomial: 8 0 4 0 0 3
Output:
First polynomial: 2x^2 + 3x + 1 = 0
Second polynomial: 3x^4 + 4x = 8
Sum of polynomials: 3x^4 + 2x^2 + 7x + 1 = 8
Difference of polynomials: 3x^4 - 2x^2 + x - 1 = 8



test2:
Input:
Order of first polynomial: 3
Enter polynomial: 0 5 0 1 4
Order of second polynomial: 3
Enter polynomial: 0 2 3 0 6
Output:
First polynomial: 4x^3 + x^2 + 5 = 0
Second polynomial: 6x^3 + 3x + 2 = 0
Sum of polynomials: 10x^3 + x^2 + 3x + 7 = 0
Difference of polynomials: 2x^3 - x^2 + 3x - 3 = 0
*/
