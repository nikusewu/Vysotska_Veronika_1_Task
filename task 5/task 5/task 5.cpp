#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

// структура викладача
struct Teacher
{
    string surname;
    string name;
    string degree;
    int birthYear;
    int publications;
    double salary;
};

// додавання нового викладача
void addTeacher()
{
    Teacher t;
    cout << "\n----- введення даних про викладача -----" << endl;
    cout << "прізвище: ";
    cin >> t.surname;
    cout << "ім'я: ";
    cin >> t.name;
    cout << "наукова ступінь: ";
    cin.ignore();
    getline(cin, t.degree);
    cout << "рік народження: ";
    cin >> t.birthYear;
    cout << "кількість публікацій: ";
    cin >> t.publications;
    cout << "заробітна плата: ";
    cin >> t.salary;

    ofstream outFile("teachers.txt", ios::app);
    if (outFile.is_open())
    {
        outFile << t.surname << "," << t.name << "," << t.degree << ","
            << t.birthYear << "," << t.publications << "," << t.salary << endl;
        outFile.close();
        cout << "викладача збережено у файл!" << endl;
    }
    else
    {
        cout << "помилка відкриття файлу!" << endl;
    }
}

// показати всіх викладачів
void showAllTeachers()
{
    ifstream inFile("teachers.txt");
    if (!inFile.is_open())
    {
        cout << "файл порожній або ще не створений." << endl;
        return;
    }

    Teacher t;
    char comma;

    cout << "\nсписок всіх викладачів:" << endl;

    while (getline(inFile, t.surname, ','))
    {
        getline(inFile, t.name, ',');
        getline(inFile, t.degree, ',');
        inFile >> t.birthYear >> comma >> t.publications >> comma >> t.salary;
        inFile.ignore();


        cout << "прізвище: " << t.surname << ", ім'я: " << t.name << ", ступінь: " << t.degree
            << ", рік: " << t.birthYear << ", публікацій: " << t.publications << ", зарплата: " << t.salary << endl;
    }
    inFile.close();
}

// фільтр викладачів за віком (старші за 45 років)
void filterByAge()
{
    ifstream inFile("teachers.txt");
    if (!inFile.is_open())
    {
        cout << "файл порожній." << endl;
        return;
    }

    Teacher t;
    bool found = false;
    char comma;

    SYSTEMTIME st;
    GetLocalTime(&st);
    int currentYear = st.wYear;

    cout << "\nвикладачі, старші за 45 років:" << endl;

    while (getline(inFile, t.surname, ','))
    {
        getline(inFile, t.name, ',');
        getline(inFile, t.degree, ',');
        inFile >> t.birthYear >> comma >> t.publications >> comma >> t.salary;
        inFile.ignore();

        if (currentYear - t.birthYear > 45)
        {
            cout << "прізвище: " << t.surname << ", ім'я: " << t.name << ", ступінь: " << t.degree
                << ", рік: " << t.birthYear << ", публікацій: " << t.publications << ", зарплата: " << t.salary << endl;
            found = true;
        }
    }

    if (found == false)
    {
        cout << "викладачів, старших за 45 років, не знайдено." << endl;
    }
    inFile.close();
}

int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    int choice;
    do
    {
        cout << "\n--------------- ВИКЛАДАЧІ ---------------" << endl;
        cout << "1. додати нового викладача" << endl;
        cout << "2. переглянути весь список" << endl;
        cout << "3. знайти викладачів, яким більше 45 років" << endl;
        cout << "4. вийти" << endl;
        cout << "ваш вибір: ";
        cin >> choice;
        cout << "-----------------------------------------" << endl;

        if (choice == 1)
            addTeacher();
        else if (choice == 2)
            showAllTeachers();
        else if (choice == 3)
            filterByAge();
        else if (choice == 4)
            cout << "завершення роботи..." << endl;
        else cout << "неправильний вибір!" << endl;

    } while (choice != 4);
    return 0;
}