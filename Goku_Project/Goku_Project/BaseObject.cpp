#include "BaseObject.h"
#include "CommonFunction.h"

BaseObject::BaseObject()
{
	rect_.x = 0;
	rect_.y = 0;
	p_Object_ = NULL;
}

BaseObject::~BaseObject()
{
	//
}

bool BaseObject::LoadImg(const char *path_file)
{
	p_Object_ = SDLCommonFunc::LoadImageA(path_file);
	if (p_Object_ == NULL)
	{
		return false;
	}
	return true;
}

void BaseObject::Show(SDL_Surface *des)
{
	if (p_Object_ != NULL)
	{
		 SDLCommonFunc::ApplySurface(p_Object_, des, rect_.x, rect_.y);
	}
}