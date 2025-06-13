#include "zagolovok1.h"
#include <iostream>

using namespace std;

/*ВВОД ЧИСЛА ОТ ПОЛЬЗОВАТЕЛЯ*/
    int getCifra(const char* simvol) {
    int n;
    cout << simvol;
    while (!(cin >> n)) {
        cout << "НЕКОРРЕКТНЫЙ ВВОД ,ВВОДИТЕ ЧИСЛА! ";
        char c;
        while ((c = cin.get()) != '\n') {}
    }
    return n;
}

/*ДИАПАЗОН ЧИСЛА*/
int check_num(int x, int min, int max) {
    return (x >= min && x <= max);
}

/*ДОБАВЛЕНИЕ УЗЛОВ ДЛЯ ПОТОМКОВ И ИХ ВЗЯТКИ*/
int add_subordinates(derevo& ministry, OfficialNode* parent, int& used, int& current_id, int total_officials, OfficialNode** next_level, int& next_size) {
    if (used >= total_officials) return 0;
    int remaining = total_officials - used;
    cout << "ВВЕДИТЕ КОЛИЧЕСТВО ПОТОМКВОВ ДЛЯ  ID=" << parent->idUzla << " (0 до " << remaining << ") ";
    int num = getCifra("");
    while (!check_num(num, 0, remaining)) {
        cout << "НЕПРАВИЛЬНО! ВВЕДИТЕ ОТ 0 ДО N " << remaining << "- ";
        num = getCifra("");
    }
    parent->countChin = num; 
    if (num > 0) {
        if (parent->nodeChin != nullptr) {
            delete[] parent->nodeChin;
            parent->nodeChin = nullptr; 
        }
        parent->nodeChin = new OfficialNode * [num];
        for (int i = 0; i < num; i++) {
            parent->nodeChin[i] = nullptr;
        }
    }

    for (int i = 0; i < num && used < total_officials; i++) {
        cout << "Введите сбор для подчинённого (ID=" << current_id << ") родителя ID=" << parent->idUzla << ": ";
        int sum = getCifra("");
        while (sum < 0) {
            cout << "Сбор не может быть меньше 0! Введите снова: ";
            sum = getCifra("");
        }
        if (ministry.addDerevo(current_id, sum, 0) != 0) return 1;
        parent->nodeChin[i] = ministry.allNode[used];
        ministry.allNode[used]->superior = parent;
        next_level[next_size++] = ministry.allNode[used];
        used++;
        current_id++;
    }
    return 0;
}

void removeM(OfficialNode** arr1, OfficialNode** arr2) {
    if (arr1) delete[] arr1;
    if (arr2) delete[] arr2;
}

/*МЕНЮ ВЫВОДА*/
void run_menu() {
    derevo ministry;
    int total_officials = getCifra("ВВЕДИТЕ N ЧИНОВНИКОВ: ");
    while (total_officials <= 0) {
        cout << "N ДОЛЖНО БЫТЬ БОЛЬШЕ 0,ВВЕДИТЕ СНОВА: ";
        total_officials = getCifra("");
    }

    OfficialNode** current_level = new OfficialNode * [total_officials];
    OfficialNode** next_level = new OfficialNode * [total_officials];
    int current_size = 0, next_size = 0, used = 0, current_id = 1;

    cout << "Введите сбор для главного (ID=1): ";
    int sum = getCifra("");
    while (sum < 0) {
        cout << "Сбор не меньше 0! Введите снова: ";
        sum = getCifra("");
    }

    int num = 0;
    if (total_officials == 1) {
        cout << "Других чиновников нет, подчинённых быть не может.\n";
    }
    else {
        int remaining = total_officials - 1;
        cout << "Введите количество подчинённых для главного (0 до " << remaining << "): ";
        num = getCifra("");
        while (!check_num(num, 0, remaining)) {
            cout << "Неправильно! Введите от 0 до " << remaining << ": ";
            num = getCifra("");
        }
    }

    if (ministry.addDerevo(current_id, sum, num) != 0) {
        removeM(current_level, next_level);
        return;
    }

    used++;
    current_id++;

    if (num > 0) {
        ministry.allNode[0]->nodeChin = new OfficialNode * [num];
        for (int i = 0; i < num; i++) ministry.allNode[0]->nodeChin[i] = nullptr;

        for (int i = 0; i < num && used < total_officials; i++) {
            cout << "Введите сбор для подчинённого (ID=" << current_id << ") родителя ID=1: ";
            int sub_sum = getCifra("");
            while (sub_sum < 0) {
                cout << "Сбор не меньше 0! Введите снова: ";
                sub_sum = getCifra("");
            }
            if (ministry.addDerevo(current_id, sub_sum, 0) != 0) {
                removeM(current_level, next_level);
                return;
            }

            ministry.allNode[0]->nodeChin[i] = ministry.allNode[used];
            ministry.allNode[used]->superior = ministry.allNode[0];
            next_level[next_size++] = ministry.allNode[used];
            used++;
            current_id++;
        }
        ministry.allNode[0]->countChin = num;
    }

    while (next_size > 0 && used < total_officials) {
        current_size = next_size;
        for (int i = 0; i < next_size; i++) current_level[i] = next_level[i];
        next_size = 0;

        for (int i = 0; i < current_size && used < total_officials; i++) {
            if (add_subordinates(ministry, current_level[i], used, current_id, total_officials, next_level, next_size) != 0) {
                removeM(current_level, next_level);
                return;
            }
        }
    }

    while (used < total_officials) {
        if (ministry.addDerevo(current_id, 0, 0) != 0) {
            cout << "НЕХВАТАЕТ УЗЛОВ ID=" << current_id << "\n";
            break;
        }
        used++;
        current_id++;
    }

    cout << "ВСЕ УЗЛЫ РАСПРЕДЕЛЕНЫ,ДЕРЕВО ПОСТРОЕНО НЕТ СВОБОДНЫХ УЗЛОВ!\n";
    if (ministry.minCalc() == 0) {
        cout << "Минимальная стоимость: " << ministry.finalSumm() << " у.е.\n";
        cout << "Путь: ";
        for (int i = 0; i < ministry.getPathLength(); i++) {
            cout << ministry.optimal_Path()[i] << " ";
        }
        cout << "\n";

        cout << "\nГОТОВОЕ ДЕРЕВО\n";
        ministry.printTree();
    }

    removeM(current_level, next_level);
    /*ИНТЕРФЕЙС*/
    while (true) {
        cout << "\nМЕНЮ  ВЫБОРА ОПЦИИ n";
        cout << "1. Посчитать стоимость\n";
        cout << "2. Показать дерево\n";
        cout << "3. Выход\n";
        cout << "Выберите: ";
        int choice = getCifra("");
        if (choice == 1) {
            if (ministry.minCalc() == 0) {
                cout << "Минимальная стоимость: " << ministry.finalSumm() << "\n";
                cout << "Путь: ";
                for (int i = 0; i < ministry.getPathLength(); i++) {
                    cout << ministry.optimal_Path()[i] << " ";
                }
                cout << "\n";
            }
        }
        else if (choice == 2) {
            ministry.printTree();
        }
        else if (choice == 3) {
            cout << "ХОРОШЕГО ДНЯ!\n";
            return;
        }
        else {
            cout << "НЕПРАВИЛЬНЫЙ ВЫБОР ОТ 1 ДО 3!\n";
        }

        char c;
        while ((c = cin.get()) != '\n') {}
    }
}

int main() {
    setlocale(LC_ALL, "RU");
    run_menu();
    return 0;
}