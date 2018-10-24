#include "Indexgoku.h"

IndexObject::IndexObject()
{
	//
}

IndexObject::~IndexObject()
{
	//
}

void IndexObject::Show_HP(SDL_Surface *des)
{
	IndexObject p_index;
    p_index.LoadImg("HP.png");
	for (int i = 20; i < HP +20; i += 20)
	{
		p_index.SetRect(i, 10);
		p_index.Show(des);
	}
}

