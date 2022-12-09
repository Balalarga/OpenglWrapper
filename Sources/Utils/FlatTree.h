#pragma once
#include <vector>


template<class T, T* T::* ParentRef>
class FlatTree
{
public:
	struct Node
	{
		T Value;
	};

	std::vector<Node> _nodes;
};
