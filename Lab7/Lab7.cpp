// Lab7.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

template <class Type>
class SegmentTree
{
	public:
		SegmentTree();
		void FillDataArray();
		void OutputTree();
		void ChangeElement(Type NewElementValue);
		Type RSQ();
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
		void BuildSegTree();
		void Output(SegTreeNode<Type>* tree, int lvl);
		SegTreeNode<Type>* InitializeNode();
		Type BuildNode(SegTreeNode<Type>* Node, int REndLeft, int REndRight);
};

template<class Type>
SegmentTree<Type>::SegmentTree()
{
	InitialNode = InitializeNode();
	FillDataArray();
	BuildSegTree();
}

template<class Type>
void SegmentTree<Type>::FillDataArray()
{
	int ArraySize;
	cin >> ArraySize;
	for (unsigned int i = 0; i < ArraySize; i++)
	{
		Type NewArrayElement;
		cin >> NewArrayElement;
		DataArray.push_back(NewArrayElement);
	}
}

template<class Type>
void SegmentTree<Type>::OutputTree()
{
	Output(InitialNode, 0);
	cout << endl;
}

template<class Type>
void SegmentTree<Type>::ChangeElement(Type NewElementValue)
{

}

template<class Type>
Type SegmentTree<Type>::RSQ()
{
	return Type();
}

template<class Type>
void SegmentTree<Type>::BuildSegTree()
{
	unsigned int i = 0;
	while (int(pow(2, i)) < DataArray.size())
	{
		i++;
	}
	InitialNode->RangeEndLeft = 0;
	InitialNode->RangeEndRight = int(pow(2, i)) - 1;
	InitialNode->LeftNode = InitializeNode();
	InitialNode->RightNode = InitializeNode();
	int MidIndex = InitialNode->RangeEndRight / 2;
	InitialNode->Value = BuildNode(InitialNode->LeftNode, InitialNode->RangeEndLeft, MidIndex) + BuildNode(InitialNode->RightNode, MidIndex + 1, InitialNode->RangeEndRight);
}

template<class Type>
void SegmentTree<Type>::Output(SegTreeNode<Type>* tree, int lvl)
{
	if (tree != NULL)
	{
		Output(tree->RightNode, lvl + 1);
		for (int i = 0; i < lvl; i++) cout << "   ";
		cout << tree->Value << endl;
		Output(tree->LeftNode, lvl + 1);
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

int main()
{
	setlocale(LC_CTYPE, "Russian");
	SegmentTree<int> Tree;
	Tree.OutputTree();
	system("pause");
	return 0;
}
