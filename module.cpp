#include "zagolovok1.h"
#include <iostream>
#include <climits>

using namespace std;

/* КОНСТРУКТОР УЗЕЛ С ID И ВЗЯТКОЙ*/
OfficialNode::OfficialNode(int id, int sum) {
    idUzla = (id <= 0) ? -1 : id;
    sumSbor = (id <= 0) ? 0 : sum;
    if (id <= 0) {
        cout << "ОШИБКА АЙДИ УЗЛА ОТСЧЁТ С 1!\n";
    }
    nodeChin = nullptr;
    countChin = 0;
    superior = nullptr;
}

/*ОСВОБОЖДАЕМ ПАМЯТЬ*/
OfficialNode::~OfficialNode() {
    int i = 0;
    while (i < countChin) {
        if (nodeChin[i]) {
            delete nodeChin[i];
        }
        i++;
    }
    if (nodeChin) {
        delete[] nodeChin;
    }
}

/*ДОБАВЛЕНИЕ УЗЛА В МАССИВ*/
void OfficialNode::addNode(OfficialNode* node) {
    if (!node || node->idUzla == -1) {
        cout << "ОШИБКА! НЕЛЬЗЯ ДОБАВИТЬ ПОТОМКА.\n";
        return;
    }
    OfficialNode** newNodeChin = new OfficialNode * [countChin + 1];
    int i = 0;
    while (i < countChin) {
        newNodeChin[i] = nodeChin[i];
        i++;
    }
    newNodeChin[countChin] = node;
    delete[] nodeChin;
    nodeChin = newNodeChin;
    countChin++;
}

/*КОРЕНЬ ПУСТОЙ*/
derevo::derevo() {
    root = nullptr;
    allNode = nullptr;
    officials_count = 0;
    optimalPath = nullptr;
    pathLength = 0;
    minSum = -1;
}

/*ОСВОБОЖДАЕМ ПАМЯТЬ*/
derevo::~derevo() {
    int i = 0;
    while (i < officials_count) {
        if (allNode[i]) {
            delete allNode[i];
        }
        i++;
    }
    delete[] allNode;
    delete[] optimalPath;
}

/*ДОБАВЛЕНИЕ НОВГОО УЗЛА В ДЕРЕВО,ПРОВЕРКА НА ДУРАКА*/
int derevo::addDerevo(int id, int sum, int countChin) {
    if (id <= 0) {
        cout << "ОШИБКА: ID ДОЛЖЕН БЫТЬ БОЛЬШЕ 0!\n";
        return 1;
    }
    if (sum < 0) {
        cout << "ОШИБКА: СУММА ВЗЯТКИ НЕ МОЖЕТ БЫТЬ МЕНЬШЕ 0!\n";
        return 1;
    }
    if (countChin < 0) {
        cout << "ОШИБКА! ПОТОМКОВ НЕ МОЖЕТ БЫТЬ МЕНЬШЕ 0\n";
        return 1;
    }
    int i = 0;
    while (i < officials_count) {
        if (allNode[i]->idUzla == id) {
            cout << "ОШИБКА: ID " << id << " УЖЕ СУЩЕСТВУЕТ!\n";
            return 1;
        }
        i++;
    }
    OfficialNode* newNode = new OfficialNode(id, sum);
    if (newNode->idUzla == -1) {
        delete newNode;
        return 1;
    }
    OfficialNode** mas = new OfficialNode * [officials_count + 1];
    i = 0;
    while (i < officials_count) {
        mas[i] = allNode[i];
        i++;
    }
    mas[officials_count] = newNode;
    delete[] allNode;
    allNode = mas;
    officials_count++;
    if (!root) {
        root = newNode;
    }
    newNode->countChin = countChin;
    if (countChin > 0) {
        newNode->nodeChin = new OfficialNode * [countChin];
        i = 0;
        while (i < countChin) {
            newNode->nodeChin[i] = nullptr;
            i++;
        }
    }
    return 0;
}

/*РЕКУРСИВНЫЙ ОБХОД */
void derevo::spusk(OfficialNode* node, bool* visited, int& count) {
    if (!node || node->idUzla == -1) {
        if (node && node->idUzla == -1) {
            cout << "ОШИБКА УЗЕЛ ОТРИЦАТЕЛЬНЫЙ!\n";
        }
        return;
    }
    if (visited[node->idUzla - 1]) {
        cout << "ОШИБКА ID=" << node->idUzla << "!\n";
        return;
    }
    visited[node->idUzla - 1] = true;
    count++;
    int i = 0;
    while (i < node->countChin) {
        if (node->nodeChin[i]) {
            spusk(node->nodeChin[i], visited, count);
        }
        i++;
    }
}

/*ЗАЩИТА ОТ ДУРАКА ЕСТЬ ЛИ ГЛАВНЫЙ ЧИНОВНИК(КОРЕНЬ ДЕРЕВА)*/
int derevo::validateHierarchy() {
    if (!root) {
        cout << "ОШИБКА; НЕТ КОРНЯ ДЕРЕВА! \n";
        return 1;
    }
    if (officials_count == 0) {
        cout << "ОШИБКА:ДЕРЕВО ПУСТОЕ\n";
        return 1;
    }
    bool* visited = new bool[officials_count]();
    int count = 0;
    spusk(root, visited, count);
    if (count != officials_count) {
        cout << "ОШИБКА НЕ ВСЕ УЗЛЫ (" << count << "/" << officials_count << ")\n";
        delete[] visited;
        return 1;
    }
    delete[] visited;
    return 0;
}

/*МИНИМАЛЬНАЯ СУММА УЗЛА И ЕГО ПОТОМКОВ,ТРАЙ КЭЧ*/
/*МИНИМАЛЬНАЯ СУММА УЗЛА И ЕГО ПОТОМКОВ,ТРАЙ КЭЧ*/
int derevo::nodeRes(OfficialNode* node, int* path, int& path_index) {
    if (!node || node->idUzla == -1) {
        cout << "ОШИБКА ОТРИЦАТЕЛЬНЫЙ УЗЕЛ!\n";
        return INT_MAX;
    }
    bool has_subordinates = false;
    int i = 0;
    while (i < node->countChin) {
        if (node->nodeChin[i]) {
            has_subordinates = true;
            break;
        }
        i++;
    }
    if (!has_subordinates) {
        path[path_index++] = node->idUzla;
        return node->sumSbor;
    }
    int minSum = INT_MAX;
    int best_sub = -1;
    int* temp_path = new int[officials_count];
    int* best_path = new int[officials_count];
    int best_index = 0; // Объявляем best_index
    try {
        int temp_index = 0;
        i = 0;
        while (i < node->countChin) {
            if (node->nodeChin[i]) {
                temp_index = 0;
                int cost = nodeRes(node->nodeChin[i], temp_path, temp_index);
                if (cost < minSum && cost != INT_MAX) {
                    minSum = cost;
                    best_sub = i;
                    best_index = temp_index; // Устанавливаем best_index
                    int j = 0;
                    while (j < temp_index) {
                        best_path[j] = temp_path[j];
                        j++;
                    }
                }
            }
            i++;
        }
    }
    catch (const std::bad_alloc& e) {
        cout << "   " << e.what() << "\n";
        delete[] temp_path;
        delete[] best_path;
        return INT_MAX;
    }
    i = 0;
    while (i < best_index) {
        path[path_index++] = best_path[i];
        i++;
    }
    path[path_index++] = node->idUzla;
    int total = node->sumSbor;
    if (minSum != INT_MAX && total <= INT_MAX - minSum) {
        total += minSum;
    }
    else {
        total = INT_MAX;
    }
    delete[] temp_path;
    delete[] best_path;
    return total;
}

/*МИНИМАЛЬНАЯ СУММА ДЛЯ ВСЕГО ДЕРЕВА*/
int derevo::minCalc() {
    if (validateHierarchy()) {
        return 1;
    }
    delete[] optimalPath;
    optimalPath = new int[officials_count];
    pathLength = 0;
    minSum = nodeRes(root, optimalPath, pathLength);
    if (minSum == INT_MAX) {
        cout << "ОШИБКА НЕ ВОЗМОЖНО ПОСЧИТАТЬ СТОИМОСТЬ\n";
        return 1;
    }
    return 0;
}

/*ВЫВОД РЕЗУЛЬТАТА*/
void derevo::printRes(OfficialNode* node, string indent, bool is_last) {
    if (!node) return;
    if (node->idUzla == -1) {
        cout << indent << "|----------- ОТРИЦАТЕЛЬНЫЙ УЗЕЛ\n";
        return;
    }
    cout << indent;
    cout << (indent.empty() ? "" : "|----------- ") << "ID: " << node->idUzla << "   " << node->sumSbor << " \n";
    int i = 0;
    while (i < node->countChin) {
        if (node->nodeChin[i]) {
            string new_indent = indent + (is_last && i == node->countChin - 1 ? "             " : "|            ");
            printRes(node->nodeChin[i], new_indent, i == node->countChin - 1);
        }
        i++;
    }
}

/*ВЫВОД ДЕРЕВА*/
void derevo::printTree() {
    if (!root) {
        cout << "ДЕРЕВО ПУСТОЕ\n";
        return;
    }
    cout << "ДЕРЕВО БОКОМ \n";
    printRes(root, "", true);
}

/*ИТОГОВАЯ СУММА ВЗЯТКИ*/
int derevo::finalSumm() {
    return minSum;
}

/*ОПТИМАЛЬНОЕ РЕШЕНИЕ*/
const int* derevo::optimal_Path() {
    return optimalPath;
}

/*ДЛИНА ПУТИ В УЗЛАХ*/
int derevo::getPathLength() {
    return pathLength;
}