#ifndef  EXPLOSION_OBJECT_H_

#define EXPLOSION_OBJECT_H_

#include "BaseObject.h"
#include "CommonFunction.h"

const int  WIDTH_EXP = 70;
const int HEIGHT_EXP = 70;

const int WIDTH_DEATH = 90;
const int HEIGHT_DEATH = 80;

class ExplosionObject : public BaseObject
{
public:
	ExplosionObject();
	~ExplosionObject();

	void SetClipExplosion();
	void Setframe(const int &fr) { frame = fr; }
	void ShowEX(SDL_Surface *des);
	
private:
	int frame;
	SDL_Rect clip_[4];
};

#endif // ! EXPLOSION_OBJECT_H_
