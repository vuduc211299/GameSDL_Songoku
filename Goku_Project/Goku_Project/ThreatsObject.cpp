#include "ThreatsObject.h"


ThreatsObject::ThreatsObject()
{
	x_val_ = 0; 
	y_val_ = 0;
	rect_.x = WIDTH_BACKGROUND;
	rect_.y = HEIGHT_BACKGROUND * 0.5;
	rect_.w = WIDTH_THREAT;
	rect_.h = HEIGHT_THREAT;
}

ThreatsObject::~ThreatsObject()
{

}

void ThreatsObject::Resetthreats(const int &xboder)
{
	rect_.x = xboder;
	int rand_y = rand() % 400;

	if (rand_y > WIDTH_BACKGROUND - 200)
	{
		rand_y = HEIGHT_BACKGROUND * 0.3;
	}
	rect_.y = rand_y;

}

void ThreatsObject::HandleMove(const int &x_border,const int &y_border)
{
	rect_.x -= x_val_;
	if (rect_.x < 0)
	{
		rect_.x = x_border;
		y_val_ = rand() % HEIGHT_BACKGROUND;
		if (y_val_ >= HEIGHT_BACKGROUND - 100)
		{
			y_val_ = HEIGHT_BACKGROUND * 0.3;
		}
		rect_.y = y_val_;
	}
	
}