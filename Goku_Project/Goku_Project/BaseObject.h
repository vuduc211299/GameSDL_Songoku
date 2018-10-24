#ifndef BASEOBJECT_H_

#define BASEOBJECT_H_

#include "CommonFunction.h"

class BaseObject
{
public:
	BaseObject();
	~BaseObject();
	
	void Show(SDL_Surface *des);
	bool LoadImg(const char *path_flie);
	void SetRect(const int & x, const int & y) { rect_.x = x; rect_.y = y; }
	SDL_Rect Get_Rect() const { return rect_; }
	SDL_Surface *GetObject() { return p_Object_; }

protected:
	SDL_Rect rect_;
	SDL_Surface *p_Object_;
};

#endif // !BASEOBJECT_H_
