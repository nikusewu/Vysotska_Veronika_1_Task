#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>

using namespace std;

const int max_sentences = 1000;

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);


    ifstream inFile("input.txt");   // звідси читаємо
    ofstream outFile("output.txt"); // сюди записуємо


    if (!inFile)
    {
        cout << "помилка: не вдалося відкрити файл input.txt!" << endl;
        return -1;
    }

    string longestWords[max_sentences];
    int wordsCount = 0;
    string line;

    // пропускаємо порожні рядки
    while (getline(inFile, line))
    {
        if (line.length() == 0)
            continue;

        string currentWord = "";
        string maxWordInLine = "";


        // пробігаємось по кожному символу в реченні, будуємо слова
        for (int i = 0; i <= line.length(); i++)
        {
            if (i == line.length() || line[i] == ' ' || line[i] == '.' || line[i] == ',' || line[i] == '!' || line[i] == '?' || line[i] == ';')
            {
                if (currentWord.length() > maxWordInLine.length())
                {
                    maxWordInLine = currentWord;
                }
                currentWord = "";

            }
            else
            {
                currentWord += line[i];
            }
        }
        if (maxWordInLine.length() > 0)
        {
            longestWords[wordsCount] = maxWordInLine;
            wordsCount++;
        }

    }
    inFile.close();

    // сортуємо масив слів за довжиною за допомогою сортування бульбашкою
    for (int i = 0; i < wordsCount - 1; i++) {
        for (int j = 0; j < wordsCount - i - 1; j++)
        {
            if (longestWords[j].length() > longestWords[j + 1].length())
            {
                swap(longestWords[j], longestWords[j + 1]);
            }
        }
    }

    // записуємо відсортовані слова у вихідний файл
    outFile << "                        результат обробки тексту" << endl;
    outFile << "-------------------------------------------------------------------------------" << endl;
    outFile << "найдовші слова з кожного речення (відсортовані за довжиною):" << endl;

    for (int i = 0; i < wordsCount; i++)
    {
        outFile << i + 1 << ". " << longestWords[i] << endl;
    }

    outFile << "-------------------------------------------------------------------------------" << endl;
    outFile << "всього оброблено речень: " << wordsCount << endl;

    outFile.close();

    cout << "найдовші слова знайдено, відсортовано і записано в output.txt." << endl;

    return 0;
}