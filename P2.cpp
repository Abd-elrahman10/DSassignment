#include <iostream>
#include <cmath>
#include <limits>
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
            else if (coeff < 0)
                cout << "- ";
            if (i == 0) {
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
            cin >> coeffsPolynomial[i];
        }
        cout << endl;
}

int main() {
    int Firstorder = 0, Secondorder = 0;
    cout << "Order of first polynomial: ";
    cin >> Firstorder;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    int* coeffsFirstpolynomial = new int[Firstorder + 1];
    cout << "Enter coefficients for the first polynomial: ";
    FillPolynomial(Firstorder, coeffsFirstpolynomial);

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Order of second polynomial: ";
    cin >> Secondorder;
    int* coeffsSecondpolynomial = new int[Secondorder + 1];
    cout << "Enter coefficients for the second polynomial: ";
    FillPolynomial(Secondorder, coeffsSecondpolynomial);
    Polynomial P1(Firstorder, coeffsFirstpolynomial);
    Polynomial P2(Secondorder, coeffsSecondpolynomial);
    cout << "First Polynomial: ";
    P1.Display();
    cout << "Second Polynomial: ";
    P2.Display();
    cout << "Sum of polynomials: ";
    (P1 + P2).Display();
    cout << "Difference of polynomials: ";
    (P2 - P1).Display();


    delete[] coeffsFirstpolynomial;
    delete[] coeffsSecondpolynomial;
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
