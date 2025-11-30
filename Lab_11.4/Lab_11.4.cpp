#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>

using namespace std;

void Menu();
void CreateFile(const string fileName);
int ProcessFile(const string fileName, int minLen);
int GetInt(string msg);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Menu();
    return 0;
}

void Menu()
{
    string fileName;
    while (true)
    {
        cout << "\n1. Створити файл\n2. Виконати завдання (Вар. 21)\n0. Вихід\n>> ";
        int choice = GetInt("");

        if (choice == 0) break;

        if (choice == 1) {
            cout << "Введіть ім'я файлу: ";
            cin >> fileName;
            CreateFile(fileName);
        }
        else if (choice == 2) {
            cout << "Введіть ім'я файлу: ";
            cin >> fileName;
            int len = GetInt("Введіть мін. довжину слова: ");
            int count = ProcessFile(fileName, len);
            if (count != -1)
                cout << "Оброблено. Вилучено слів: " << count << endl;
        }
    }
}

void CreateFile(const string fileName)
{
    ofstream f(fileName);
    string line;
    cout << "Вводьте рядки (введіть 'end' для завершення):" << endl;
    cin.ignore();
    while (getline(cin, line) && line != "end")
    {
        f << line << endl;
    }
}

int ProcessFile(const string fileName, int minLen)
{
    ifstream f(fileName);
    if (!f.is_open()) { cout << "Помилка відкриття!" << endl; return -1; }

    ofstream t("temp.txt");
    string line, word, newLine;
    int count = 0;

    while (getline(f, line))
    {
        if (line.empty()) continue;

        stringstream ss(line);
        newLine = "";
        bool first = true, hasWords = false;

        while (ss >> word)
        {
            if (word.length() < minLen) count++;
            else {
                if (!first) newLine += " ";
                newLine += word;
                first = false;
                hasWords = true;
            }
        }
        if (hasWords) t << newLine << endl;
    }

    f.close(); t.close();

    if (remove(fileName.c_str()) != 0)
    {
        cout << "Помилка видалення старого файлу!" << endl;
    }

    if (rename("temp.txt", fileName.c_str()) != 0)
    {
        cout << "Помилка перейменування (можливо файл відкритий іншою програмою)!" << endl;
    }

    ofstream f_res(fileName, ios::app);
    f_res << "\nВилучено слів: " << count << endl;

    return count;
}

int GetInt(string msg)
{
    int val;
    while (true) {
        if (!msg.empty()) cout << msg;
        if (cin >> val) return val;
        cout << "Помилка! Введіть число." << endl;
        cin.clear();
        cin.ignore(1000, '\n');
    }
}