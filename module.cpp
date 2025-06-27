#include "zagolovok1.h"
#include <iostream>
#include<climits>
using namespace std;


TreeNode::TreeNode(int id, int summa) {
	nomer = id;
	vzyatka = summa;
	parent = nullptr;
	sin = nullptr;
	brat = nullptr;

}


Derevo::Derevo(int n) {
	sizeTree = n;
	usedNodes = 0;
	root = nullptr;
	allNodes = new TreeNode * [n];
	finalPath = new int[n];
	finalDlina = 0;
	countVzyatka = 0;


}

/*МЕТОДЫ ДЛЯ РЕШЕНИЯ ЗАДАЧИ*/


/**/
void Derevo::addSon(TreeNode* parent, TreeNode* sin) {
	if (!parent->sin) {
		parent->sin = sin;
	}
	else {
		TreeNode* temp = parent->sin;
		while (temp->brat) {
			temp = temp->brat;
		}
		temp->brat = sin;
	}
	sin->parent = parent;
}





/*ДОБАВЛЕНИЕ НОВОГО УЗЛА,КОТОРЫЙ ХРАНИТ ЧИСЛО(СУММУ ВЗЯТКИ)*/
int Derevo::addNode(int vzyatka, int parentID) {
	if (usedNodes >= sizeTree) {
		return 1;
	}
	TreeNode* newNode = new TreeNode(usedNodes + 1, vzyatka);
	if (parentID == 0) {
		root = newNode;
	}
	else {
		TreeNode* parent = nullptr;
		for (int i = 0; i < usedNodes; i++) {
			if (allNodes[i]->nomer == parentID) {
				parent = allNodes[i];
				break;
			}
		}

		if (!parent) return 2;
		addSon(parent, newNode);
	}

	allNodes[usedNodes++] = newNode;
	return 0;

}





/*ВВОД С КЛАВИАТУРЫ В КОНСОЛИ ПОКА НЕ ДОБАВИМ N УЗЛОВ*/
void Derevo::vvodConsole() {
	cout << "ВВЕДИТЕ РАЗМЕР ВЗЯТКИ ГЛАВНОГО ЧИНОВНИКА =   ";
	int rootSum;
	while (!(cin >> rootSum) || rootSum < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "ОШИБКА! ВЗЯТКА НЕ МОЖЕТ БЫТЬ ОТРИЦАТЕЛЬНОЙ. ";
	}
	addNode(rootSum, 0);


	for (int i = 1; i < sizeTree; i++) {
		int parentID, sum;
		cout << "ОСТАЛОСЬ ЧИНОВНИКОВ ДЛЯ ВВОДА =  " << (sizeTree - usedNodes) << endl;
		cout << "ВВЕДИТЕ ПОРЯДКОВЫЙ НОМЕР РОДИТЕЛЯ И ЗНАЧЕНИЕ ВЗЯТКИ ДЛЯ ЧИНОВНИКА" << i + 1 << " =";
		while (!(cin >> parentID) || parentID <= 0) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "ОШИБКА ПОРЯДКОВЫЙ НОМЕР РОДИТЕЛЬСКОГО УЗЛА НЕ МОЖЕТ БЫТЬ ОТРИЦАТЕЛЬНЫМ!";
		}
		while (!(cin >> sum) || sum < 0) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "ОШИБКА! ВЗЯТКА НЕ МОЖЕТ БЫТЬ ОТРИЦАТЕЛЬНОЙ! ";
		}

		if (addNode(sum, parentID) != 0) {
			cout << "НЕ ПОЛУЧИЛОСЬ ДОБАВИТЬ УЗЕЛ!";
			i--;
		}
	}
}


/*ОБХОД ДЕРЕВА ДЛЯ ПОИСКА ОПТИМАЛЬНОГО ПУТИ*/
int Derevo::recObhod(TreeNode* node, int* path, int& len) {
	if (!node) {
		return INT_MAX;
	}

	if (!node->sin) {
		path[len++] = node->nomer;
		return node->vzyatka;

	}

	int minSum = INT_MAX, bestLen = 0;
	int* bestPath = new int[sizeTree];
	for (TreeNode* potomok = node->sin; potomok; potomok = potomok->brat) {
		int* tempPath = new int[sizeTree];
		int tempLen = 0;
		int sum = recObhod(potomok, tempPath, tempLen);
		if (sum < minSum) {
			minSum = sum;
			bestLen = tempLen;
			for (int i = 0; i < tempLen; i++) {
				bestPath[i] = tempPath[i];
			}
		}
		delete[] tempPath;
	}

	for (int i = 0; i < bestLen; i++) {
		path[len++] = bestPath[i];


	}
	path[len++] = node->nomer;
	delete[]bestPath;

	return minSum + node->vzyatka;

}


/*ОПРЕДЕЛЯЕМ НАИМЕНЬШУЮ СУММУ ВЗЯТКИ*/
int Derevo::minVzyatka() {
	finalDlina = 0;
	countVzyatka = recObhod(root, finalPath, finalDlina);
	return countVzyatka;

}


/*СТРОИМ ДЕРЕВО ЧИНОВНИКОВ*/
void Derevo::printDerevo(TreeNode* node, int glubina) {
	if (!node) {
		return;

	}
	for (int i = 0; i < glubina; i++)
		cout << "         ";
	cout << "(" << node->nomer << " ; " << node->vzyatka << ")" << "\n";
	cout << endl;
	cout << endl;
	printDerevo(node->sin, glubina + 1);
	printDerevo(node->brat, glubina);

}

/*ВЫВОД ДЕРЕВА В КОНСОЛИ*/
void Derevo::vivodDerevo() {
	printDerevo(root, 0);
}


/*ФУНКЦИЯ ВЫВОДИТ В КОНСОЛЬ ИТОГОВУЮ СУММУ ВЗЯТКИ И ПРОДЕЛАННЫЙ ПУТЬ*/
void Derevo::printFinalPath() {
	cout << "МИНИМАЛЬНАЯ СУММА ВЗЯТКИ = " << countVzyatka << "\nПРОЙДЕННЫЙ ПУТЬ :";
	for (int i = 0; i < finalDlina; i++) {
		cout << finalPath[i];
		if (i < finalDlina - 1) {
			cout << "  -->  ";
		}

	}
	cout << endl;
}

/*ОЧИСТКА ПАМЯТИ*/
Derevo::~Derevo() {
	for (int i = 0; i < usedNodes; i++) {
		delete allNodes[i];
	}
	delete[] allNodes;
	delete[] finalPath;

}
