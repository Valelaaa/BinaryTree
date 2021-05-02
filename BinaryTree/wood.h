#pragma once
#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include <iomanip>
#include <string>
#include <cstdio>
#include <fstream>
using namespace std;
struct Node {
	char data[40];
	Node* left, * right;
};
typedef Node* PNode;
struct Product
{
	string name = "";
	string country = "";
	string fabricator = "";
	string articul = "";
	float cost = 0;

	void Print()
	{
		cout << "| " << setw(25) << left << name;
		cout << "  " << setw(17) << left << country;
		cout << "  " << setw(16) << left << fabricator;
		cout << "  " << setw(11) << left << articul;
		cout << "  " << setw(14) << left << cost << "|\n";
	}
};
struct Tree {
	Product pro;
	Tree* left, * right;
};
int main_menu();
int Priority(char c);
PNode MakeTree(char Expr[], int first, int last);
float CalcTree(PNode Tree);
void printLKP(Tree* tree); void printLKP(Node* tree);
void printLPK(Tree* tree); void printLPK(Node* tree);
void printKLP(Tree* tree); void printKLP(Node* tree);
void AddToTree(Tree*& tree, Product data);
int FileBackUntillEnd(Tree*& tree);
int FileBack(Tree*& tree);
void search(Tree* tree,string osu);
void heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);
void loading(int n, double f);
int maining();
int arrayn();
int BinaryTree();
int TREEEE();
int arrrray();