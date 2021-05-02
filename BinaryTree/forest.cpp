#include "wood.h"
int Priority(char c) 
{
	switch (c) 
	{
	case '+': case '-': return 1;
	case '*': case '/': return 2;
	case '^':return 3;
	}
	return(2020);
}
PNode MakeTree(char Expr[], int first, int last)
{
	int MinPrt, i, k, prt;
	PNode Tree = new Node;
	MinPrt = 100;
	int nest = 0;
	for (i = first; i <= last; i++) {
		if (Expr[i] == '(') 
		{
			nest++; continue;
		}
		if (Expr[i] == ')') 
		{
			nest--; continue;
		}
		if (nest > 0) continue; 
		prt = Priority(Expr[i]);
		if (prt <= MinPrt) {
			MinPrt = prt;
			k = i;
		}
	}
	if (MinPrt == 100)
		if (Expr[first] == '(' && Expr[last] == ')') {
			delete Tree;
			return MakeTree(Expr, first + 1, last - 1);
		}
		else { // ����� ��� ����������
			k = last - first + 1;
			strncpy(Tree->data, Expr + first, k);
			Tree->data[k] = '\0';
			Tree->left = NULL;
			Tree->right = NULL;
			return Tree;
		}
	Tree->data[0] = Expr[k]; //���� ��������
	Tree->data[1] = '\0';
	Tree->left = MakeTree(Expr, first, k - 1);
	Tree->right = MakeTree(Expr, k + 1, last);
	return Tree;
}
float CalcTree(PNode Tree)
{
	float num1, num2;
	if (!Tree->left) // ���� ��� ��������,
		return atoi(Tree->data);
	num1 = CalcTree(Tree->left); // ��������� ����������
	num2 = CalcTree(Tree->right);
	switch (Tree->data[0]) 
	{ //��������� ��������
	case '+': return num1 + num2;
	case '-': return num1 - num2;
	case '*': return num1 * num2;
	case '/': return num1 / num2;
	case '^':
	{
		for (int i = 0; i < num2 - 1; i++) {
			num1 *= num1;
		}
		return(num1);
	}
		return 32767;
	}
}
void printLKP(Tree* tree) 
{	
	if (!tree) return;
	printLKP(tree->left);
	tree->pro.Print();
	printLKP(tree->right);
}
void printLKP(Node* tree)
{
	if (!tree) return;
	printLKP(tree->left);
	
	printLKP(tree->right);
}
void printLPK(Tree* tree) 
{
	if (!tree) return;
	printLPK(tree->left);
	printLPK(tree->right);
	tree->pro.Print();
}
void printLPK(Node* tree)
{
	if (!tree) return;
	printLPK(tree->left);
	printLPK(tree->right);
	cout << tree->data;
}
void printKLP(Tree* tree) 
{
	if (!tree) return;
	tree->pro.Print();
	printKLP(tree->left);
	printKLP(tree->right);
}
void printKLP(Node* tree)
{
	if (!tree) return;
	cout << tree->data;
	printKLP(tree->left);
	printKLP(tree->right);
}
void AddToTree(Tree *&tree, Product data) // ����������� ����
{
	if (!tree) {
		tree = new Tree(); // ������� ����� ����
		tree->pro = data;
		tree->left = NULL;
		tree->right = NULL;
		return;
	}
	if (data.name < tree->pro.name) // �������� � ������ ���������
		AddToTree(tree->left, data);
	else AddToTree(tree->right, data);
}
int FileBackUntillEnd(Tree*&tree)
{
	int sn;
	string sin;
	cout << endl << "� ������ ����� ���������� ����?" << endl;
	cout << "1. - ���� �� ��������� Input.txt" << endl;
	cout << "2. - ���� �� ��������� Input1.txt" << endl;
	cout << "3. - ��������� ���� (������� ���� � �����������) " << endl;
	cout << ">>> "; if (cin >> sn, !cin.good())
	{
		cout << "���������� ������ �����!"; return(0);
	}
	if (sn == 1) sin = "Input.txt";
	else if (sn == 2) sin = "Input1.txt";
	else {
		cin.ignore();
		getline(cin, sin);
	}
	ifstream file(sin);
	if (!file.is_open())
	{
		cout << "������! ���� �� ������!" << endl;
		return 0;
	}
	Product data;
	while (file)
	{
		getline(file, data.name);
		getline(file, data.country);
		getline(file, data.fabricator);
		getline(file, data.articul);
		(file >> data.cost).get();
		string space;
		getline(file, space);
		AddToTree(tree,data);
	}
	file.close();
	return 1;
}
int FileBack(Tree*& tree) {
	int sn;
	string sin;
	cout << endl << "� ������ ����� ���������� ����?" << endl;
	cout << "1. - ���� �� ��������� Input.txt" << endl;
	cout << "2. - ���� �� ��������� Input1.txt" << endl;
	cout << "3. - ��������� ���� (������� ���� � �����������) " << endl;
	cout << ">>> "; if (cin >> sn, !cin.good())
	{
		cout << "���������� ������ �����!"; return(0);
	}
	if (sn == 1) sin = "Input.txt";
	else if (sn == 2) sin = "Input1.txt";
	else {
		cin.ignore();
		getline(cin, sin);
	}
	ifstream file(sin);
	if (!file.is_open())
	{
		cout << "������! ���� �� ������!" << endl;
		return 0;
	}
	Product data;
	getline(file, data.name);
	getline(file, data.country);
	getline(file, data.fabricator);
	getline(file, data.articul);
	(file >> data.cost).get();
	string space;
	getline(file, space);
	AddToTree(tree, data);
	file.close();
	return 1;
}
void search(Tree* tree,string osu) 
{
	if (!tree)
		return;
	search(tree->left,osu);
	if (tree->pro.name == osu)
		tree->pro.Print();
	search(tree->right, osu);
}
void heapify(int arr[], int n, int i)
{
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2; 
	if (l < n && arr[l] > arr[largest])
		largest = l;
	if (r < n && arr[r] > arr[largest])
		largest = r;
	if (largest != i)
	{
		swap(arr[i], arr[largest]);
		heapify(arr, n, largest);
	}
}
void heapSort(int arr[], int n)
{
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);
	for (int i = n - 1; i >= 0; i--)
	{
		swap(arr[0], arr[i]);
		heapify(arr, i, 0);
	}
}
void loading(int n, double f)
{
	for (int i = 0; i < n; i++)
	{
		cout << "."; Sleep(1000 * f);;
	}
	return;
}
int main_menu() {
	int var;
	cout << "�������������������������������������" << endl;
	cout << "|           ������� ����            |" << endl;
	cout << "�������������������������������������" << endl;
	cout << "| 1. - �������������� ���������     |" << endl;
	cout << "| 2. - �������� ������ ������       |" << endl;
	cout << "| 3. - ������������� ����������     |" << endl;
	cout << "| 4. - ���������� ���������         |" << endl;
	cout << "�������������������������������������" << endl;
	cout << ">>> "; if (cin >> var, !cin.good()) 
	{
		cout << "������, ������� �����!"; loading(4, 0.4); return NULL;
	}
	return(var);
}
int BinaryTree() 
{
	int var;
	cout << "�������������������������������������" << endl;
	cout << "|       �������� ������ ������      |" << endl;
	cout << "�������������������������������������" << endl;
	cout << "| 1. - ���������� ������ �� �����   |" << endl;
	cout << "| 2. - ������ ������ ������         |" << endl;
	cout << "| 3. - ����� � ������ ������        |" << endl;
	cout << "| 4. - �������� ������� � ������    |" << endl;
	cout << "| 5. - ������������ ������ ������   |" << endl;
	cout << "| 6. - ���������� ���������         |" << endl;
	cout << "�������������������������������������" << endl;
	cout << ">>> "; if (cin >> var, !cin.good())
	{
		cout << "������, ������� �����!"; loading(4, 0.4); return NULL;
	}
	return(var);
}
int arrayn() 
{
	int var;
	cout << "�������������������������������������" << endl;
	cout << "|     ������������� ����������      |" << endl;
	cout << "�������������������������������������" << endl;
	cout << "| 1. - �������� �������             |" << endl;
	cout << "| 2. - ������ �������               |" << endl;
	cout << "| 3. - ������������� ����������     |" << endl;
	cout << "| 4. - � ������� ����               |" << endl;
	cout << "�������������������������������������" << endl;
	cout << ">>> "; if (cin >> var, !cin.good())
	{
		cout << "������, ������� �����!"; loading(4, 0.4); return NULL;
	}
	return(var);
}
int maining() {
	while (true) {
		system("cls");
		switch (main_menu())
		{
		case 1:
		{
			char str[80];
			Node* free;
			cout << "������� ���������" << endl << ">>> ";
			int k = 1000;
			cin.get();
			cin.getline(str, 80);
			free = MakeTree(str, 0, strlen(str) - 1);
			cout << str << " = " << CalcTree(free) << endl;
		/*	cout << "����� ���:" << endl;
			printLKP(free);
			cout << endl << "����� ���:" << endl;
			printKLP(free);
			cout << endl << "����� ���:" << endl;
			printLPK(free);*/
			system("pause");
			break;
		}
		case 2: 
		{
			TREEEE();
			break;
		}
		case 3:
		{
			arrrray();
			break;
		}
		default: {return 0; }
		}
	}
}
int TREEEE() {
	Tree* tree = NULL;
	while (true) 
	{
		system("cls");
		switch (BinaryTree())
		{
		case 1:
		{
			FileBackUntillEnd(tree);
			 cout << "������ ������� "; loading(3, 0.4);
			break;
		}
		case 2:
		{
			if (!tree || !tree->left && !tree->right)
			{
				cout << "���� ������"; loading(3, 0.4);
				break;
			}
			int var;
			cout << "����� ������� �������� ?" << endl << "1. ��� �����" << endl << "2. ��� �����" << endl << "3. ��� �����" << endl << "4. �����" << endl << ">>> ";
			if (cin >> var, !cin.good())
			{
				cout << "������, ������� �����!"; loading(4, 0.4); return NULL;
			}
			switch (var)
			{
			case 1:
			{

				cout << "����������������������������������������������������������������������������������������������" << endl;
				cout << "|                                 �������� ������ ������                                     |" << endl;
				cout << "����������������������������������������������������������������������������������������������" << endl;
				printLKP(tree);
				cout << "����������������������������������������������������������������������������������������������" << endl;
				system("pause");
				break;
			}
			case 2:
			{

				cout << "����������������������������������������������������������������������������������������������" << endl;
				cout << "|                                 �������� ������ ������                                     |" << endl;
				cout << "����������������������������������������������������������������������������������������������" << endl;
				printLPK(tree);
				cout << "����������������������������������������������������������������������������������������������" << endl;
				system("pause");
				break;
			}
			case 3: 
			{

				cout << "����������������������������������������������������������������������������������������������" << endl;
				cout << "|                                 �������� ������ ������                                     |" << endl;
				cout << "����������������������������������������������������������������������������������������������" << endl;
				printKLP(tree);
				cout << "����������������������������������������������������������������������������������������������" << endl;
				system("pause");
				break;
			}
			default:
			{
				break;
			}
			}
			break;
		}
		case 3:
		{
			if (!tree || !tree->left && !tree->right)
			{
				cout << "���� ������"; loading(3, 0.4);
				break;
			}
			string osu;
			cin.get();
			cout << "������� ���� ����� �����:" << endl << ">>> ";
			getline(cin, osu);
			cout << "����������������������������������������������������������������������������������������������" << endl;
			search(tree, osu);
			cout << "����������������������������������������������������������������������������������������������" << endl;
			system("pause");
			break;
		}
		case 4:
		{
			FileBack(tree);
			break;
		}
		case 5:
		{
			if (!tree || !tree->left && ! tree->right)
			{
				cout << "����� ���� ��� ����? ��� ��� ������"; loading(3, 0.4);
				break;
			}
			delete(tree);
			cout << "������ �������"; loading(3, 0.4);
			break;
		}
		default: {
			return(0);
		}
		}
	}
}
int arrrray() {
	int* arr = NULL;
	int n;
	srand(time(NULL));
	while (true) {
		system("cls");
		switch (arrayn())
		{
		case 1:
		{
			cout << "������ �������: " << endl << ">>> "; cin >> n;
			arr = new int(n);
			for (int i = 0; i < n; i++)
			{
				arr[i] = rand() % 201 - 100;
			}
			break;
		}
		case 2:
		{
			for (int i = 0; i < n; i++)
			{
				cout << arr[i] << " ";
			}
			cout << endl;
			system("pause");
			break;
		}
		case 3:
		{
			heapSort(arr, n);
			cout << "���������������"; loading(3, 0.4);
			break;
		}
		default:
			return(0);
		}
	}
}