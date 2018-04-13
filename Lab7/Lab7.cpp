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
};

int main()
{
    return 0;
}

template<class Type>
SegmentTree<Type>::SegmentTree()
{
}
