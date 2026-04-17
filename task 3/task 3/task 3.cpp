#include <iostream>
#include <iomanip>
#include <ctime>
#include <cmath>
#include <Windows.h>

using namespace std;

// cтворення матриці
int** createMatrix(int n)
{
    int** matrix = new int* [n];
    for (int i = 0; i < n; i++)
    {
        matrix[i] = new int[n];
    }
    return matrix;
}

// заповнення випадковими числами
void fillMatrix(int** matrix, int n, int V)
{
    int min = -10 - V;
    int max = 10 + V;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = rand() % (max - min + 1) + min;
        }
    }
}

// виведення матриці на екран
void printMatrix(int** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << setw(5) << matrix[i][j];
        }
        cout << endl;
    }
}

// робота із сектором 7 (верхній правий трикутник без діагоналі)
void processSector7(int** matrix, int n, int k) {
    int maxDiff = -1;
    int numI = -1;
    int numJ = -1;

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int diff = abs(matrix[i][j] - k);
            if (diff > maxDiff)
            {
                maxDiff = diff;
                numI = i;
                numJ = j;
            }
        }
    }

    if (numI != -1)
    {
        cout << "у секторі 7 найбільше від заданого k = " << k << " відрізняється елемент: " << matrix[numI][numJ];
        cout << " (його індекси: [" << numI << "][" << numJ << "])\n";
    }
}

// робота із сектором 1\ (верхня чверть з діагоналлю)
int processSector1(int** matrix, int n)
{
    int minMat = matrix[0][0];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (matrix[i][j] < minMat)
            {
                minMat = matrix[i][j];
            }
        }
    }

    cout << "мінімальне значення всієї матриці: " << minMat << "\n";


    // рахуємо елементи в 1 секторі і замінюємо їх на мінімум
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i <= j && (i + j) <= (n - 1))
            {
                count++;
                matrix[i][j] = minMat;
            }
        }
    }
    return count;
}

// видалення матриці з пам'яті
void deleteMatrix(int** matrix, int n)
{
    for (int i = 0; i < n; i++)
    {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    srand(time(0));

    int n, k;
    int V = 1;

    cout << "введіть розмір матриці n: ";
    cin >> n;
    cout << "введіть число k: ";
    cin >> k;

    int** matrix = createMatrix(n);
    fillMatrix(matrix, n, V);

    cout << "\nпочаткова матриця:\n";
    printMatrix(matrix, n);

    cout << "\n--------------------------------- результати обчислень ----------------------------------\n";
    processSector7(matrix, n, k);

    int count1 = processSector1(matrix, n);
    cout << "кількість елементів у секторі 1: " << count1 << "\n";

    cout << "\nматриця після замін у секторі 1:\n";
    printMatrix(matrix, n);

    deleteMatrix(matrix, n);
    return 0;
}