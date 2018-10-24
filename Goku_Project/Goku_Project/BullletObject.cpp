#include "BullletObject.h"

BulletObject::BulletObject()
{
	x_val_ = 0;
	y_val_ = 0;
	is_move_ = false;
	bullet_type = NONE;
}

BulletObject::~BulletObject()
{

}

void BulletObject::HandleActionInput(SDL_Event events)
{

}

// function check when coordinate of bullet over the screen

void BulletObject::HandleMove(const int &x_border, const int &y_border)
{
	rect_.x += 20;
	if (rect_.x > x_border)
	{
		is_move_ = false;
	}
}


void BulletObject::HandleMoveRighttoLeft()
{
	rect_.x -= 8;
	if (rect_.x < 0)
	{
		is_move_ = false;
	}
}
