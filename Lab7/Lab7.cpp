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
		Type BuildNode();
};

template<class Type>
SegmentTree<Type>::SegmentTree()
{
}

template<class Type>
void SegmentTree<Type>::FillDataArray()
{
}

template<class Type>
void SegmentTree<Type>::OutputTree()
{
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
}

template<class Type>
Type SegmentTree<Type>::BuildNode()
{
	return Type();
}

int main()
{
	return 0;
}
