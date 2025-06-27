#ifndef zagolovok1_h
#define zagolovok1_h
using namespace std;



/*УЗЕЛ(ЧИНОВНИК) КОНСТРУКТОР - НОМЕР И СУММА УЗЛА */
class TreeNode {

public:

	TreeNode* parent;
	TreeNode* sin;
	TreeNode* brat;
	int nomer;
	int vzyatka;
	TreeNode(int id, int summa);
};


/*ДЕРЕВО(МЕТОДЫ- ДОБАВЛЕНИЕ УЗЛА,ВВОД С КОНСОЛИ,ПОСТРОЕНИЕ ДЕРЕВА,ПОСЛЕДОВАТЕЛЬНОСТЬ ПУТИ И ФИНАЛЬНАЯ ВЗЯТКА-МНИМАЛЬНАЯ*/
class Derevo {

private:

	TreeNode* root;
	TreeNode** allNodes;
	int sizeTree;
	int usedNodes;
	int* finalPath;
	int finalDlina;
	int countVzyatka;


public:

	Derevo(int n);
	~Derevo();
	int addNode(int vzyatka, int parentID);
	void vvodConsole();
	void vivodDerevo();
	void printFinalPath();
	int minVzyatka();

private:

	void addSon(TreeNode* parent, TreeNode* sin);
	int recObhod(TreeNode* node, int* path, int& dlina);
	void printDerevo(TreeNode* node, int glubina);
};

#endif
