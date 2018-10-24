#include"Explosion.h"

ExplosionObject::ExplosionObject()
{

}

ExplosionObject::~ExplosionObject()
{

}

void ExplosionObject::SetClipExplosion()
{
	clip_[0].x = 0;
	clip_[0].y = 0;
	clip_[0].w = WIDTH_EXP;
	clip_[0].h = HEIGHT_EXP;

	clip_[1].x = WIDTH_EXP;
	clip_[1].y = 0;
	clip_[1].w = WIDTH_EXP;
	clip_[1].h = HEIGHT_EXP;

	clip_[2].x = WIDTH_EXP*2;
	clip_[2].y = 0;
	clip_[2].w = WIDTH_EXP;
	clip_[2].h = HEIGHT_EXP;

	clip_[3].x = WIDTH_EXP*3;
	clip_[3].y = 0;
	clip_[3].w = WIDTH_EXP;
	clip_[3].h = HEIGHT_EXP;

}


void ExplosionObject::ShowEX(SDL_Surface *des)
{
	if (frame >= 4)
	{
		frame = 0;
	}
	SDLCommonFunc::ApplySurfaceClip(this->p_Object_, des, &clip_[frame], rect_.x, rect_.y);
}
