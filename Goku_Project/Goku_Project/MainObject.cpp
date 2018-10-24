#include "MainObject.h"



MainObject::MainObject()
{
	x_val_ = 0;
	y_val_ = 0;
	rect_.w = WIDTH_SOKU1;
	rect_.h = HEIGHT_SOKU1;
	type_goku = 0;
	trans_goku = 0;
	Index_trans = 500; 
	HP_goku = 100;
}

MainObject::~MainObject()
{
	
}


void MainObject::HandleInputAction(SDL_Event events, Mix_Chunk *g_sound_[2])
{
	if (events.type == SDL_KEYDOWN)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			y_val_ -= HEIGHT_SOKU1 / 8;
			break;
		case SDLK_DOWN:
			y_val_ += HEIGHT_SOKU1 / 8;
			break;
		case SDLK_LEFT:
			x_val_ -= WIDTH_SOKU1/4;
			break;
		case SDLK_RIGHT:
			x_val_ += WIDTH_SOKU1/4;
			break;
		case SDLK_RETURN:
			if (Index_trans >= 2500)
			{
				trans_goku = 1;
				type_goku = -1;
			}
			break;

		default:
			break;

		}
	}
	else if (events.type == SDL_KEYUP)
	{
		switch (events.key.keysym.sym)
		{
		case SDLK_UP:
			y_val_ += HEIGHT_SOKU1 / 8;
			break;
		case SDLK_DOWN:
			y_val_ -= HEIGHT_SOKU1 / 8;
			break;
		case SDLK_LEFT:
			x_val_ += WIDTH_SOKU1 / 4;
			break;
		case SDLK_RIGHT:
			x_val_ -= WIDTH_SOKU1 / 4;
			break;
		default:
			break;

		}
	}
	else if (events.type == SDL_MOUSEBUTTONDOWN)
	{

		// shoot kameha
		if (events.button.button == SDL_BUTTON_LEFT)
		{
			if(trans_goku==0) type_goku = 1;
			else if (trans_goku == 1) type_goku = 1;
		}
		// shoot bullet
		else if (events.button.button == SDL_BUTTON_RIGHT)
		{
			if (trans_goku == 0)
			{
				BulletObject *p_bullet = new BulletObject;
				type_goku = 2;
				p_bullet->SetWidthHeight(WIDTH_BULLET, HEIGHT_BULLET);
				p_bullet->LoadImg("normal_bullet.png");
				p_bullet->set_type(BulletObject::SPHERE);
				p_bullet->SetRect(this->rect_.x + WIDTH_SOKU1, this->rect_.y + HEIGHT_SOKU1*0.6);
				p_bullet->set_is_move(true);
				p_bullet_list_goku1.push_back(p_bullet);
			}
			else if(trans_goku == 1)
			{
				BulletObject *p_bullet = new BulletObject;
				type_goku = 2;
				p_bullet->SetWidthHeight(WIDTH_BULLET2, HEIGHT_BULLET2);
				p_bullet->LoadImg("normal_bullet2.png");
				p_bullet->set_type(BulletObject::DRAGON);
				p_bullet->SetRect(this->rect_.x + WIDTH_SOKU1, this->rect_.y + HEIGHT_SOKU1*0.5);
				p_bullet->set_is_move(true);
				p_bullet_list_goku2.push_back(p_bullet);
			}
		}
	}
	else if (events.type == SDL_MOUSEBUTTONUP)
	{
		
	}
}


void MainObject::RemoveBullet(const int &idx)
{
		for (int i = 0; i < p_bullet_list_goku1.size(); i++)
		{
			if (idx<p_bullet_list_goku1.size())
			{
				BulletObject *p_bullet = p_bullet_list_goku1.at(idx);
				p_bullet_list_goku1.erase(p_bullet_list_goku1.begin() + idx);

				if (p_bullet != NULL)
				{
					delete p_bullet;
					p_bullet = NULL;
				}
			}
		}
}

void MainObject::RemoveBullet2(const int& ixd)
{
	for (int i = 0; i < p_bullet_list_goku2.size(); i++)
	{
		if (ixd<p_bullet_list_goku2.size())
		{
			BulletObject *p_bullet = p_bullet_list_goku2.at(ixd);
			p_bullet_list_goku2.erase(p_bullet_list_goku2.begin() + ixd);

			if (p_bullet != NULL)
			{
				delete p_bullet;
				p_bullet = NULL;
			}
		}
	}
}

void MainObject::HandleMove(Mix_Chunk *g_sound_kameha[2])
{
	if (HP_goku <= 0)
	{
		trans_goku = -1;
	}

	Index_trans+=2;
	rect_.x += x_val_;
	if (rect_.x >= WIDTH_BACKGROUND - WIDTH_SOKU1 || rect_.x <= -WIDTH_SOKU1*0.5)
	{
		rect_.x -= x_val_;
	}
	rect_.y += y_val_;
	if (rect_.y >= HEIGHT_BACKGROUND - HEIGHT_SOKU1 || rect_.y <= -HEIGHT_SOKU1*0.6)
	{
		rect_.y -= y_val_;
	}
	// when go_ku does nothing
	if (type_goku == 0&&trans_goku == 0) {
		static int index0 = 0;
		switch (index0/10)
		{
		case 0:
			p_Object_ = video_fly.at(0);
			break;
		default:
			p_Object_ = video_fly.at(1);
			break;
		}
		index0 ++;
		if (index0 == 20)
		{
			index0 = 0;
		}
	}
	//when go_ku shoot kameha
	if (type_goku == 1 && trans_goku == 0) {

		Mix_PlayChannel(-1, g_sound_kameha[0], 0);
		
		static int index = 0; 
		// Load movement
		switch (index / 10)
		{
		case 0: {
			p_Object_ = video_kameha.at(0);
			break;
		}
		case 1: {
			p_Object_ = video_kameha.at(1);
			break;
		}
		case 2: {
			p_Object_ = video_kameha.at(2);
			break;
		}
		case 3: {
			p_Object_ = video_kameha.at(3);
			break;
		}
		case 4: {
			p_Object_ = video_kameha.at(4);
			break;
		}
		case 5: {
			p_Object_ = video_kameha.at(5);
			break;
		}
		case 6: {
			p_Object_ = video_kameha.at(6);
			break;
		}
		case 7: {
			p_Object_ = video_kameha.at(7);
			break;
		}
		case 8: {
			p_Object_ = video_kameha.at(8);
			break;
		}

		}
		index++;
		if (index == 90) {
			type_goku = 0; 
			index = 0; 
		}
		
		
	}
	// when go_ku shoot normal bullet
	 else if (type_goku == 2 && trans_goku ==0)
	{
		static int index1 = 0;
		switch (index1/10)
		{
		case 0:
			p_Object_ = video_bullet_normal.at(0);
			break;

		case 1:
			p_Object_ = video_bullet_normal.at(1);
			break;
		}
		index1++;
		if (index1 == 20)
		{
			index1 = 0;
			type_goku = 0;
		}
	}
	
	// goku 2 
	if (Index_trans >= 2500)
	{
		static int time = 0;
		// transform goku2
		if (trans_goku == 1 && type_goku == -1)
		{
			static int index2 = 0;
			switch (index2 / 10)
			{
			case 0:
				p_Object_ = video_kameha_goku2.at(0);
				break;
			case 1:
				p_Object_ = video_kameha_goku2.at(1);
				break;
			case 2:
				p_Object_ = video_kameha_goku2.at(2);
				break;
			case 3:
				p_Object_ = video_kameha_goku2.at(3);
				break;
			case 4:
				p_Object_ = video_kameha_goku2.at(4);
				break;
			case 5:
				p_Object_ = video_kameha_goku2.at(5);
				break;
			case 6:
				p_Object_ = video_kameha_goku2.at(6);
				break;
			case 7:
				p_Object_ = video_kameha_goku2.at(7);
				break;
			case 8:
				p_Object_ = video_kameha_goku2.at(8);
				break;
			case 9:
				p_Object_ = video_kameha_goku2.at(9);
				break;
			case 10:
				p_Object_ = video_kameha_goku2.at(10);
				break;
			case 11:
				p_Object_ = video_kameha_goku2.at(11);
				break;
			}
			index2++;
			if (index2 >= 120)
			{
				index2 = 0;
				type_goku = 0;
			}

		}

		// goku2 shoot kameha

		else if (trans_goku == 1 && type_goku == 1)
		{
			Mix_PlayChannel(-1, g_sound_kameha[0], 0);

			static int index_1 = 0;
			switch (index_1 / 10)
			{
			case 0:
				p_Object_ = video_kameha_trans.at(0);
				break;
			case 1:
				p_Object_ = video_kameha_trans.at(1);
				break;
			case 2:
				p_Object_ = video_kameha_trans.at(2);
				break;
			case 3:
				p_Object_ = video_kameha_trans.at(3);
				break;
			case 4:
				p_Object_ = video_kameha_trans.at(4);
				break;
			case 5:
				p_Object_ = video_kameha_trans.at(5);
				break;
			case 6:
				p_Object_ = video_kameha_trans.at(6);
				break;
			case 7:
				p_Object_ = video_kameha_trans.at(7);
				break;
			case 8:
				p_Object_ = video_kameha_trans.at(8);
				break;
			case 9:
				p_Object_ = video_kameha_trans.at(9);
				break;

			}
			index_1++;
			if (index_1 >= 100)
			{
				index_1 = 0;
				type_goku = 0;
			}
		}

		//goku2 stand

		else if (trans_goku == 1 && type_goku == 0)
		{
			static int index3=0;
			switch (index3/10)
			{
			case 0:
				p_Object_ = video_goku2_stand.at(0);
				break;
			case 1:
				p_Object_ = video_goku2_stand.at(1);
				break;
			}
			index3++;
			if (index3 >= 20)
			{
				index3 = 0;
			}
		}

		// goku2 shoot bullets
		else if (trans_goku == 1 && type_goku == 2)
		{
			static int index_2 = 0;
			switch (index_2 / 10)
			{
			case 0:
				p_Object_ = video_bullet_normal_goku2.at(0);
				break;
			}
			index_2++;
			if (index_2 >= 10)
			{
				type_goku = 0;
				index_2 = 0;
			}
		}
		time++;
		if (time >= 1000)
		{
			Index_trans = 500;
			time = 0;
			trans_goku = 0;
		}
	}

	// when goku die

	 if (trans_goku == -1)
	 {
		static int index_ = 0;
		switch (index_/10)
		{
		case 0:
			p_Object_ = video_death.at(0);
			break;
		case 1:
			p_Object_ = video_death.at(1);
			break;
		case 2:
			p_Object_ = video_death.at(2);
			break;
		case 3:
			p_Object_ = video_death.at(3);
			break;
		case 4:
			p_Object_ = video_death.at(4);
			break;
		default:
			break;
		}
		index_++;
		
	}
}

void MainObject::initVideo()
{
	SDL_Surface* temp = new SDL_Surface;

	//goku1 shoot kameha
	temp = SDLCommonFunc::LoadImage("kame1.png");
	video_kameha.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame2.png");
	video_kameha.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame3.png");
	video_kameha.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame4.png");
	video_kameha.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame5.png");
	video_kameha.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame6.png");
	video_kameha.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame7.png");
	video_kameha.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame8.png");
	video_kameha.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame9.png");
	video_kameha.push_back(temp);


	temp = SDLCommonFunc::LoadImage("stand1.png");
	video_fly.push_back(temp);
	temp = SDLCommonFunc::LoadImage("stand2.png");
	video_fly.push_back(temp);

	temp = SDLCommonFunc::LoadImage("bullet1.png");
	video_bullet_normal.push_back(temp);
	temp = SDLCommonFunc::LoadImage("bullet2.png");
	video_bullet_normal.push_back(temp);

	/*Init video for goku_2*/

	temp = SDLCommonFunc::LoadImage("goku_trans1.png");
	video_kameha_goku2.push_back(temp);
	temp = SDLCommonFunc::LoadImage("goku_trans2.png");
	video_kameha_goku2.push_back(temp);
	temp = SDLCommonFunc::LoadImage("goku_trans3.png");
	video_kameha_goku2.push_back(temp);
	temp = SDLCommonFunc::LoadImage("goku_trans4.png");
	video_kameha_goku2.push_back(temp);
	temp = SDLCommonFunc::LoadImage("goku_trans5.png");
	video_kameha_goku2.push_back(temp);
	temp = SDLCommonFunc::LoadImage("goku_trans6.png");
	video_kameha_goku2.push_back(temp);
	temp = SDLCommonFunc::LoadImage("goku_trans7.png");
	video_kameha_goku2.push_back(temp);
	temp = SDLCommonFunc::LoadImage("goku_trans8.png");
	video_kameha_goku2.push_back(temp);
	temp = SDLCommonFunc::LoadImage("goku_trans9.png");
	video_kameha_goku2.push_back(temp);
	temp = SDLCommonFunc::LoadImage("goku_trans10.png");
	video_kameha_goku2.push_back(temp);
	temp = SDLCommonFunc::LoadImage("goku_trans11.png");
	video_kameha_goku2.push_back(temp);
	temp = SDLCommonFunc::LoadImage("goku_trans12.png");
	video_kameha_goku2.push_back(temp);
	
	//goku2 stand

	temp = SDLCommonFunc::LoadImage("stand1.1.png");
	video_goku2_stand.push_back(temp);
	temp = SDLCommonFunc::LoadImage("stand1.2.png");
	video_goku2_stand.push_back(temp);



	temp = SDLCommonFunc::LoadImage("bullet1.1.png");
	video_bullet_normal_goku2.push_back(temp);
	

	// goku2 shoot kameha
	temp = SDLCommonFunc::LoadImage("kame1.1.png");
	video_kameha_trans.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame1.2.png");
	video_kameha_trans.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame1.3.png");
	video_kameha_trans.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame1.4.png");
	video_kameha_trans.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame1.5.png");
	video_kameha_trans.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame1.6.png");
	video_kameha_trans.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame1.7.png");
	video_kameha_trans.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame1.8.png");
	video_kameha_trans.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame1.9.png");
	video_kameha_trans.push_back(temp);
	temp = SDLCommonFunc::LoadImage("kame1.10.png");
	video_kameha_trans.push_back(temp);

	// Init video death

	temp = SDLCommonFunc::LoadImage("death1");
	video_death.push_back(temp);
	temp = SDLCommonFunc::LoadImage("death2");
	video_death.push_back(temp);
	temp = SDLCommonFunc::LoadImage("death3");
	video_death.push_back(temp);
	temp = SDLCommonFunc::LoadImage("death4");
	video_death.push_back(temp);
	temp = SDLCommonFunc::LoadImage("death5");
	video_death.push_back(temp);
}

void MainObject::clearVideo()
{
	// clear video death

	for (int i = 0; i < video_death.size(); i++)
	{
		if (video_death.at(i) != NULL)
		{
			SDL_FreeSurface(video_death.at(i));
			video_death.at(i) = NULL;
		}
	}

	// clear video kameha
	for (int i = 0; i < video_kameha.size(); ++i) {
		if (video_kameha.at(i) != NULL) {
			SDL_FreeSurface(video_kameha.at(i));
			video_kameha.at(i) = NULL;
		}
	}
	video_kameha.clear();

	// clear video_fly
	for (int i_ = 0; i_ < video_fly.size(); i_++)
	{
		if (video_fly.at(i_) != NULL)
		{
			SDL_FreeSurface(video_fly.at(i_));
			video_fly.at(i_) = NULL;
		}
	}
	video_fly.clear();

	for (int i_ = 0; i_ < video_bullet_normal_goku2.size(); i_++)
	{
		if (video_bullet_normal_goku2.at(i_) != NULL)
		{
			SDL_FreeSurface(video_bullet_normal_goku2.at(i_));
			video_bullet_normal_goku2.at(i_) = NULL;
		}
	}
	video_bullet_normal_goku2.clear();


	for (int i_ = 0; i_ < video_kameha_trans.size(); i_++)
	{
		if (video_kameha_trans.at(i_) != NULL)
		{
			SDL_FreeSurface(video_kameha_trans.at(i_));
			video_kameha_trans.at(i_) = NULL;
		}
	}
	video_kameha_trans.clear();


	for (int i_ = 0; i_ < video_kameha_goku2.size(); i_++)
	{
		if (video_kameha_goku2.at(i_) != NULL)
		{
			SDL_FreeSurface(video_kameha_goku2.at(i_));
			video_kameha_goku2.at(i_) = NULL;
		}
	}
	video_kameha_goku2.clear();

	for (int i_ = 0; i_ < video_goku2_stand.size(); i_++)
	{
		if (video_goku2_stand.at(i_) != NULL)
		{
			SDL_FreeSurface(video_goku2_stand.at(i_));
			video_goku2_stand.at(i_) = NULL;
		}
	}
	video_goku2_stand.clear();
}


void MainObject::Show_Index(SDL_Surface *des)
{
	MainObject p_index;
	p_index.LoadImg("trans.png");
	if ( Index_trans>= 2500)
	{
		Index_trans = 2500;
	}
	for (int i = 500; i <= Index_trans; i += 500)
	{
		p_index.SetRect(i / 25, 30);
		p_index.Show(des);
	}
}

