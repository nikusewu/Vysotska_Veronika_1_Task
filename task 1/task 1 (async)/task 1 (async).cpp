#include <iostream>
#include <ctime>
#include <chrono>
#include <Windows.h>
#include <future>

using namespace std;
using namespace std::chrono;

void print_array(int arr[], int n) {
    if (n <= 15) {
        for (int i = 0; i < n; i++) cout << arr[i] << " ";
    }
    else {
        for (int i = 0; i < 5; i++) cout << arr[i] << " ";
        cout << "... ";
        for (int i = n - 5; i < n; i++) cout << arr[i] << " ";
    }
    cout << "\n";
}

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1]) swap(arr[j], arr[j + 1]);
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i], j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void shellSort(int arr[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2)
        for (int i = gap; i < n; i++) {
            int temp = arr[i], j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
}

int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }
    return -1;
}

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    srand(time(0));

    while (true) {
        int n;
        cout << "введіть розмір масиву: ";
        cin >> n;

        if (n <= 0)
            break;

        int* arr1 = new int[n];
        int* arr2 = new int[n];
        int* arr3 = new int[n];

        for (int i = 0; i < n; i++) {
            int val = rand() % 10000;
            arr1[i] = arr2[i] = arr3[i] = val;
        }

        cout << "початковий масив:\n";
        print_array(arr1, n);
        cout << "\n";

        // запуск потоків асинхронно
        auto fut1 = async(launch::async, [&]() {
            auto start = high_resolution_clock::now();
            bubbleSort(arr1, n);
            auto end = high_resolution_clock::now();
            return duration_cast<microseconds>(end - start).count();
            });

        auto fut2 = async(launch::async, [&]() {
            auto start = high_resolution_clock::now();
            insertionSort(arr2, n);
            auto end = high_resolution_clock::now();
            return duration_cast<microseconds>(end - start).count();
            });

        auto fut3 = async(launch::async, [&]() {
            auto start = high_resolution_clock::now();
            shellSort(arr3, n);
            auto end = high_resolution_clock::now();
            return duration_cast<microseconds>(end - start).count();
            });

        // отримуємо час з кожного потоку
        long long time1 = fut1.get();
        long long time2 = fut2.get();
        long long time3 = fut3.get();

        cout << "після сортування бульбашкою:\n";
        print_array(arr1, n);
        cout << "час: " << time1 << " мкс\n\n";

        cout << "після сортування вставками:\n";
        print_array(arr2, n);
        cout << "час: " << time2 << " мкс\n\n";
        cout << "після сортування Шелла:\n";
        print_array(arr3, n);
        cout << "час: " << time3 << " мкс\n\n";

        int number;
        cout << "введіть число для пошуку: ";
        cin >> number;
        int pos = binarySearch(arr3, n, number);

        if (pos != -1)
            cout << "число знайдено на індексі: " << pos << "\n\n";
        else
            cout << "число не знайдено.\n\n";

        delete[] arr1;
        delete[] arr2;
        delete[] arr3;
    }

    return 0;
}