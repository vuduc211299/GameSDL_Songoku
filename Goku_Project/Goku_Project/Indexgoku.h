#ifndef INDEXOBJECT_H_

#define INDEXOBJECT_H_


#include"BaseObject.h"
#include"CommonFunction.h"

class IndexObject : public BaseObject
{
public:
	IndexObject();
	~IndexObject();
	void Get_HP(int hp) { HP = hp; }
	void Show_HP(SDL_Surface *des);

private:
	int HP;
	int Mana;
};

#endif // !INDEXOBJECT_H_
