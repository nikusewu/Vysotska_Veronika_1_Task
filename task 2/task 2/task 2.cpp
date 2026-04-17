#include <iostream>
#include <cmath>
#include <Windows.h>

using namespace std;

//обчислення факторіалу
double factorial(int num) {
    double result = 1;
    for (int i = 1; i <= num; i++) {
        result *= i;
    }
    return result;
}

//обчислення суми квадратів
double sumOfSquares(double arr[], int count) {
    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += pow(arr[i], 2);
    }
    return sum;
}

//обчислення суми елементів масиву
double sumOfElements(double arr[], int count) {
    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += arr[i];
    }
    return sum;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    double a = 3.68;
    int m = 9;
    int n = 3;
    double b[8] = { 3.5, 4.0, 2.5, 3.3, 2.1, 1.5, 7.3, 8.5 };

    //перший дріб
    double fraction1 = factorial(m) / factorial(m + n);

    //чисельник другого дробу
    double numerator = pow(a, 2) * sumOfSquares(b, 8);

    //знаменник другого дробу
    double sum6 = sumOfElements(b, 6);
    double denominator = factorial(m - 1) - pow(sum6, 2);

    //другий дріб
    double fraction2 = numerator / denominator;

    //фінальний результат
    double P = fraction1 - fraction2;

    cout << "----- результати обчислень -----" << endl;
    cout << "перший дріб: " << fraction1 << endl;
    cout << "другий дріб: " << fraction2 << endl;
    cout << "кінцеве значення P = " << P << endl;
    cout << "--------------------------------" << endl;

    return 0;
}