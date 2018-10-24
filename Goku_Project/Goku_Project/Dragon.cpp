#include "Dragon.h"
#include "CommonFunction.h"
#include "MainObject.h"
#include "Indexgoku.h"

DragonObject::DragonObject()
{
	x_val = 5;
	y_val = 0;
	rect_.x = WIDTH_BACKGROUND;
	rect_.y = HEIGHT_BACKGROUND;
	rect_.w = WIDTH_Dragon;
	rect_.h = HEIGHT_Dragon;
	HP_Dragon = 2000;
}

DragonObject::~DragonObject()
{
	//
}

void DragonObject::ResetBullet(BulletObject *p_bullet)
{
	p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.3);
}

void DragonObject::HandleMove(const int &x_border, const int &y_border)
{
	if (HP_Dragon <= 0)
	{
		static int index_ = 0;
		switch (index_/10)
		{
		case 0:
			p_Object_ = video_collision.at(0);
			break;
		case 1:
			p_Object_ = video_collision.at(1);
			break;
		case 2:
			p_Object_ = video_collision.at(2);
			break;
		case 3:
			p_Object_ = video_collision.at(3);
			break;
		case 4:
			p_Object_ = video_collision.at(4);
			break;
		case 5:
			p_Object_ = video_collision.at(5);
			break;
		case 6:
			p_Object_ = video_collision.at(6);
			break;
		case 7:
			p_Object_ = video_collision.at(7);
			break;
		case 8:
			p_Object_ = video_collision.at(8);
			break;
		case 9:
			p_Object_ = video_collision.at(9);
			break;

		default:
			break;
		}
		index_++;
		if (index_ >= 100)
		{
			index_ = 0;
		}
	}
	else if (HP_Dragon > 0)
	{
		rect_.x -= x_val;
		if (rect_.x <= WIDTH_BACKGROUND * 2 / 3)
		{
			rect_.x += x_val;
		}
		MainObject p_goku;
		//rect_.y-p_goku.Get_Rect().y
		static int index = 0;
		switch (index / 10) {
		case 0:
			p_Object_ = video_dragon.at(0);
			break;
		case 1:
			p_Object_ = video_dragon.at(1);
			break;
		case 2:
			p_Object_ = video_dragon.at(2);
			break;
		}
		index++;
		if (index >= 30)
		{
			index = 0;
		}
	}
	
}

void DragonObject::Show_HP_Dragon(SDL_Surface *des)
{
	DragonObject index;
	index.LoadImg("HP.png");
	for (int i =200;i<=HP_Dragon+200;i+=200)
	{
		index.SetRect(rect_.x + i/20, rect_.y);
		index.Show(des);
	}
}

void DragonObject::InitVideoDragon()
{
	// Dragon fly
	SDL_Surface* temp = new SDL_Surface;
	temp = SDLCommonFunc::LoadImage("dragon1.png");
	video_dragon.push_back(temp);
	temp = SDLCommonFunc::LoadImage("dragon2.png");
	video_dragon.push_back(temp);
	temp = SDLCommonFunc::LoadImage("dragon3.png");
	video_dragon.push_back(temp);

    // collision of dragon

	temp = SDLCommonFunc::LoadImage("BombBlu1.png");
	video_collision.push_back(temp);
	temp = SDLCommonFunc::LoadImage("BombBlu2.png");
	video_collision.push_back(temp);
	temp = SDLCommonFunc::LoadImage("BombBlu3.png");
	video_collision.push_back(temp);
	temp = SDLCommonFunc::LoadImage("BombBlu4.png");
	video_collision.push_back(temp);
	temp = SDLCommonFunc::LoadImage("BombBlu5.png");
	video_collision.push_back(temp);
	temp = SDLCommonFunc::LoadImage("BombBlu6.png");
	video_collision.push_back(temp);
	temp = SDLCommonFunc::LoadImage("BombBlu7.png");
	video_collision.push_back(temp);
	temp = SDLCommonFunc::LoadImage("BombBlu8.png");
	video_collision.push_back(temp);
	temp = SDLCommonFunc::LoadImage("BombBlu9.png");
	video_collision.push_back(temp);
	temp = SDLCommonFunc::LoadImage("BombBlu10.png");
	video_collision.push_back(temp);
}

void DragonObject::clearVideoDragon()
{
	// clear video fly
	for (int i = 0; i < video_dragon.size(); i++)
	{
		if (video_dragon.at(i) != NULL)
		{
			SDL_FreeSurface(video_dragon.at(i));
			video_dragon.at(i) = NULL;
		}
	}
	// clear video death
	for (int i = 0; i < video_collision.size(); i++)
	{
		if (video_collision.at(i) != NULL)
		{
			SDL_FreeSurface(video_collision.at(i));
			video_collision.at(i) = NULL;
		}
	}

}

void DragonObject::InitBullet(BulletObject *p_bullet)
{
	if (p_bullet != NULL)
	{
		bool ret=p_bullet->LoadImg("bullet_dragon.png");
		if (ret)
		{
			p_bullet->set_is_move(true);
			p_bullet->SetWidthHeight(WIDTH_BULLET_DRAGON, HEIGHT_BULLET_DRAGON);
			p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.3);
			p_list_bullet.push_back(p_bullet);
		}
	}
}

void DragonObject::MakeBullet(SDL_Surface *des)
{
	for (int i = 0; i < p_list_bullet.size(); i++)
	{
		BulletObject *p_bullet = p_list_bullet.at(i);
		if (p_bullet)
		{
			if (p_bullet->get_is_move())
			{
				p_bullet->Show(des);
				p_bullet->HandleMoveRighttoLeft();
			}
			else
			{
				p_bullet->set_is_move(true);
				p_bullet->SetRect(rect_.x, rect_.y + rect_.h*0.5);
			}
		}
	}
}