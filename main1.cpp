#include "zagolovok1.h"
#include "module.cpp"
#include <iostream>
#include <string>  
#include <cctype>  

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    string input;
    int n;
    while (true) {
        cout << "ВВЕДИТЕ ОБЩЕЕ КОЛИЧЕСТВО ЧИНОВНИКОВ = ";
        cin >> input;

        if (!input.empty() && input[0] == '-') {
            cout << "КОЛИЧЕСТВО ЧИНОВНИКОВ НЕ МОЖЕТ БЫТЬ ОТРИЦАТЕЛЬНЫМ. ВВЕДИТЕ ЗАНОВО!" << endl;
            continue;
        }

        bool cifra = true;
        for (char c : input) {
            if (!isdigit(c)) {
                cifra = false;
                break;
            }
        }

        if (!cifra) {
            cout << "ОШИБКА: ВВЕДИТЕ ЧИСЛО, А НЕ БУКВУ ИЛИ СИМВОЛ!" << endl;
            continue;
        }

        n = stoi(input);

        if (n == 1) {
            cout << "НЕЛЬЗЯ РЕШИТЬ ЗАДАЧУ С ОДНИМ ЧИНОВНИКОМ,НЕТ ПОДПИСИ ПОДЧИНЁННОГО!" << endl;
            continue;
        }

        if (n < 2) {
            cout << "НЕДОСТАТОЧНО ЧИНОВНИКОВ ДЛЯ РЕШЕНИЯ ЗАДАЧИ" << endl;
            continue;
        }

        break;
    }




    Derevo tree(n);
    tree.vvodConsole();
    tree.minVzyatka();
    tree.printFinalPath();
    tree.vivodDerevo();
    return 0;
}
