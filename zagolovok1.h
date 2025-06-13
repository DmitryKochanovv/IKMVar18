#ifndef zagolovok1_h
#define zagolovok1_h
using namespace std;
#include <string>

class OfficialNode {
public:
    int idUzla;
    int sumSbor;
    OfficialNode** nodeChin;
    int countChin;
    OfficialNode* superior;

    /*Конструктор*/
    OfficialNode(int id, int sum);
    ~OfficialNode();
    void addNode(OfficialNode* node);
};

class derevo {
public:
    OfficialNode* root;
    OfficialNode** allNode;
    int officials_count;
    int* optimalPath;
    int pathLength;
    int minSum;

    /*Конструктор класса*/
    derevo();
    ~derevo();
    /*Добавить узел*/
    int addDerevo(int id, int sum, int countChin);
    /*Расчет минимума*/
    int minCalc();
    /*Вывод в консоль*/
    void printTree();
    /*Получить итоговую сумму*/
    int finalSumm();
    /*ID оптимального пути*/
    const int* optimal_Path();
    /*Получить длину пути : количество элементов в оптимальном пути*/
    int getPathLength();

private:
    int validateHierarchy();
    /*Метод обхода в глубину*/
    void spusk(OfficialNode* node, bool* visited, int& count);
    /*Рекурсивный поиск : функция возвращает оптимальную сумму для узла и его поддерева*/
    int nodeRes(OfficialNode* node, int* path, int& path_index);
    /*Вывод информации по узлу : рекурсивный вывод дерева и его поддерева*/
    void printRes(OfficialNode* node,string indent, bool is_last);
};
#endif