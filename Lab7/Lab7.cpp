// Lab7.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

template <class Type>
class SegmentTree
{
	public:
		bool InputIsCorrect;
		SegmentTree() { InitialNode = InitializeNode();	TreeIsBuilt = false; ArrayIsFilled = false; };
		void FillDataArray();
		void BuildSegTree();
		void OutputTree();
		void UpdateElement(Type NewElementValue, int ElementID);
		Type RangeSumQuery(int REndLeft, int REndRight);
	private:
		template <typename Type>
		struct SegTreeNode
		{
			Type Value;
			SegTreeNode<Type>* LeftNode;
			SegTreeNode<Type>* RightNode;
			int RangeEndLeft, RangeEndRight;
		};	
		SegTreeNode<Type>* InitialNode;
		vector<Type> DataArray;
		bool TreeIsBuilt, ArrayIsFilled;
		void Output(SegTreeNode<Type>* Node, int Level);
		SegTreeNode<Type>* InitializeNode();
		Type BuildNode(SegTreeNode<Type>* Node, int REndLeft, int REndRight);
		Type RSQ(SegTreeNode<Type>* Node, int REndLeft, int REndRight);
		Type UpdElement(SegTreeNode<Type>* Node, Type NewElementValue, int ElementID);
};

template<class Type>
void SegmentTree<Type>::FillDataArray()
{
	unsigned int ArraySize;
	cout << "Введите количество элементов в массиве исходных данных: ";
	cin >> ArraySize;
	cout << "Введите содержимое массива исходных данных: " << endl;
	for (unsigned int i = 0; i < ArraySize; i++)
	{
		Type NewArrayElement;
		cin >> NewArrayElement;
		DataArray.push_back(NewArrayElement);
	}
	ArrayIsFilled = true;
}

template<class Type>
void SegmentTree<Type>::OutputTree()
{
	try
	{
		if (TreeIsBuilt)
		{
			cout << "Дерево имеет следующий вид:" << endl << endl;
			Output(InitialNode, 0);
		}
		else
		{
			string error = "Дерево не построено!";
			throw error;
		}
	}
	catch (string error)
	{
		cout << error << endl;
	}
}

template<class Type>
void SegmentTree<Type>::UpdateElement(Type NewElementValue, int ElementID)
{
	if (ElementID < 0 || ElementID > DataArray.size() - 1)
	{
		InputIsCorrect = false;
	}
	else
	{
		InputIsCorrect = true;
	}
	try
	{
		if (TreeIsBuilt && InputIsCorrect)
		{
			Type Result;
			Result = UpdElement(InitialNode, NewElementValue, ElementID);
			cout << endl << "Новая сумма последовательности: " << Result << endl;
			OutputTree();
		}
		else
		{
			string error; 
			if (!TreeIsBuilt) error = "Дерево не построено!";
			else if (!InputIsCorrect) error = "Номер обновляемого элемента введён некорректно!";
			throw error;
		}
	}
	catch (string error)
	{
		cout << error << endl << endl;
	}
}

template<class Type>
Type SegmentTree<Type>::RangeSumQuery(int REndLeft, int REndRight)
{
	if (REndLeft < 0 || REndRight > InitialNode->RangeEndRight || REndLeft > REndRight)
	{
		InputIsCorrect = false;
	}
	else
	{
		InputIsCorrect = true;
	}
	Type Result = 0;
	try
	{
		if (InputIsCorrect)
		{
			Result = RSQ(InitialNode, REndLeft, REndRight);
		}
		else
		{
			string error = "Интервал введён некорректно!";
			throw error;
		}
	}
	catch (string error)
	{
		cout << error << endl << endl;
	}
	return Result;
}

template<class Type>
void SegmentTree<Type>::BuildSegTree()
{
	try
	{
		if (ArrayIsFilled)
		{
			InitialNode->RangeEndLeft = 0;
			InitialNode->RangeEndRight = DataArray.size() - 1;
			InitialNode->LeftNode = InitializeNode();
			InitialNode->RightNode = InitializeNode();
			int MidIndex = InitialNode->RangeEndRight / 2;
			InitialNode->Value = BuildNode(InitialNode->LeftNode, InitialNode->RangeEndLeft, MidIndex) + BuildNode(InitialNode->RightNode, MidIndex + 1, InitialNode->RangeEndRight);
			TreeIsBuilt = true;
		}
		else
		{
			string error = "Массив исходных данных не заполнен!";
			throw error;
		}
	}
	catch (string error)
	{
		cout << error << endl;
	}
}

template<class Type>
void SegmentTree<Type>::Output(SegTreeNode<Type>* Node, int Level)
{
	if (Node != NULL)
	{
		Output(Node->RightNode, Level + 1);
		for (int i = 0; i < Level; i++)
		{
			cout << "   ";
		}
		cout << Node->Value << endl;
		Output(Node->LeftNode, Level + 1);
	}
}

template<class Type>
SegmentTree<Type>::SegTreeNode<Type>* SegmentTree<Type>::InitializeNode()
{
	SegTreeNode<Type>* NewTreeNode;
	NewTreeNode = new SegTreeNode<Type>;
	NewTreeNode->Value = 0;
	NewTreeNode->LeftNode = NULL;
	NewTreeNode->RightNode = NULL;
	return NewTreeNode;
}

template<class Type>
Type SegmentTree<Type>::BuildNode(SegTreeNode<Type>* Node, int REndLeft, int REndRight)
{
	Node->RangeEndLeft = REndLeft;
	Node->RangeEndRight = REndRight;
	if (REndLeft == REndRight)
	{
		if (REndLeft <= DataArray.size() - 1)
		{
			Node->Value = DataArray[REndLeft];
		}
		else
		{
			Node->Value = 0;
		}
		Node->LeftNode = NULL;
		Node->RightNode = NULL;
	}
	else
	{
		Node->LeftNode = InitializeNode();
		Node->RightNode = InitializeNode();
		int MidIndex = (REndLeft + REndRight) / 2;
		Node->Value = BuildNode(Node->LeftNode, REndLeft, MidIndex) + BuildNode(Node->RightNode, MidIndex + 1, REndRight);
	}
	return Node->Value;
}

template<class Type>
Type SegmentTree<Type>::RSQ(SegTreeNode<Type>* Node, int REndLeft, int REndRight)
{
	int LeftRangeEnd, RightRangeEnd;
	LeftRangeEnd = Node->RangeEndLeft;
	RightRangeEnd = Node->RangeEndRight;
	if (REndLeft > RightRangeEnd || REndRight < LeftRangeEnd)
	{
		return 0;
	}
	else if (REndLeft <= LeftRangeEnd && RightRangeEnd <= REndRight)
	{
		return Node->Value;
	}
	else
	{
		return RSQ(Node->LeftNode, REndLeft, REndRight) + RSQ(Node->RightNode, REndLeft, REndRight);
	}
}

template<class Type>
Type SegmentTree<Type>::UpdElement(SegTreeNode<Type>* Node, Type NewElementValue, int ElementID)
{
	unsigned int MidIndex = (Node->RangeEndLeft + Node->RangeEndRight) / 2;
	if (Node->RangeEndLeft == ElementID && Node->RangeEndRight == ElementID)
	{
		Node->Value = NewElementValue;
	}
	else 
		if (!(ElementID < Node->RangeEndLeft || ElementID > Node->RangeEndRight))
		{ 
			Node->Value = UpdElement(Node->LeftNode, NewElementValue, ElementID) + UpdElement(Node->RightNode, NewElementValue, ElementID);
		}
	return Node->Value;
}

int main()
{
	setlocale(LC_CTYPE, "Russian");
	SegmentTree<int> Tree;
	int Selector;
	Tree.FillDataArray();
	Tree.BuildSegTree();
	cout << endl << "Дерево построено. ";
	do
	{
		cout << "Доступные операции:" << endl;
		cout << "1. Вывод дерева." << endl;
		cout << "2. Подсчёт суммы на интервале." << endl;
		cout << "3. Обновление листа дерева." << endl;
		cout << "4. Выход." << endl << endl;
		cout << "Выберите операцию над деревом: ";
		cin >> Selector;
		switch (Selector)
		{
			case 1:
			{
				Tree.OutputTree();
				cout << endl;
				break;
			}
			case 2:
			{
				int LeftBorder, RightBorder;
				cout << "Введите левую границу интервала: ";
				cin >> LeftBorder;
				cout << "Введите правую границу интервала: ";
				cin >> RightBorder;
				cout << endl;
				int Result = Tree.RangeSumQuery(LeftBorder, RightBorder);
				if (Tree.InputIsCorrect)
				{
					cout << "Сумма на интервале " << LeftBorder << ".." << RightBorder << ": " << Result << endl << endl;
				}
				break;
			}
			case 3:
			{
				int LeafID, NewValue;
				cout << "Введите номер обновляемого элемента (нумерация с 0): ";
				cin >> LeafID;
				cout << "Введите новое значение элемента: ";
				cin >> NewValue;
				Tree.UpdateElement(NewValue, LeafID);
				cout << endl;
				break;
			}
			case 4:
			{
				cout << "Выход..." << endl;
				break;
			}
			default: 
			{
				cout << "Введён несуществующий номер операции." << endl;
				break;
			}
		}
	} 
	while (Selector != 4);
	system("pause");
	return 0;
}
