#pragma once

#include <memory>

template<class T>
class CMyList
{
public:
	CMyList()
	{
				
	}

	~CMyList()
	{

	}

private:
	struct Node
	{
		T item;
		std::unique_ptr prev;
		std::unique_ptr next;
	};
};