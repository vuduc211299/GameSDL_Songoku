#include "CommonFunction.h"
#include "MainObject.h"
#include "BullletObject.h"
#include "ThreatsObject.h"
#include "Explosion.h"
#include "Indexgoku.h"
#include "Dragon.h"

#undef main


TTF_Font *g_font_text = NULL;

bool Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		return false;
	}

	g_screen = SDL_SetVideoMode(WIDTH_BACKGROUND, HEIGHT_BACKGROUND, BFF_BACKGROUND, SDL_SWSURFACE);
	SDL_WM_SetCaption("sogoku", nullptr);
	if (g_screen == NULL) {
		return false;
	}

	if (TTF_Init() == -1)
	{
		return false;
	}

	g_font_text = TTF_OpenFont("SAF.otf",40);
	if (g_font_text == NULL)
	{
		return false;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) return false;
	g_sound_soku[0] = Mix_LoadWAV("goku_kamehameha.wav");


	if (g_sound_soku[0] == NULL)
	{
		return false;
	}
	return true;
}

int main(int argc, char *argv[])
{
	
    bool is_quit = false;

	if (Init() == false)
	{
		return 1;
	}
	
	g_background = SDLCommonFunc::LoadImageA("background.png");
	if (g_background == NULL)
	{
		return 1;
	}
	g_endgame = SDLCommonFunc::LoadImageA("gameover.png");
	if (g_endgame == NULL)
	{
		return 1;
	}

	bool check;
	// Init MainObject

	MainObject p_soku;
	p_soku.initVideo();

	bool ret = p_soku.LoadImg("stand1.png");
	p_soku.SetRect(200, 100);
	if (ret == false)
	{
		return 0;
	}

	// Index of goku

	IndexObject p_index;
	static int HP_goku = 100;

// Init Threats

	ThreatsObject *p_threats = new ThreatsObject[NUMBER_THREATS];

	for (int i_ = 0; i_ < NUMBER_THREATS; i_++)
	{
		ThreatsObject *p_threat = (p_threats + i_);
		ret=p_threat->LoadImg("threats.png");
		if (!ret)
		{
			return 0;
		}
		int y_val_ = rand() % HEIGHT_BACKGROUND;
		if (y_val_ >= HEIGHT_BACKGROUND - 50 || y_val_==0)
		{
			y_val_ = HEIGHT_BACKGROUND * 0.6;
		}
		p_threat->SetRect(WIDTH_BACKGROUND + i_ * 200, y_val_);
		p_threat->Set_x_val(NUMBER_THREATS);
	}

	// Init Explosion

	ExplosionObject p_exp;
	ret=p_exp.LoadImg("goku_exp.png");
	if (!ret)
	{
		return 0;
	}
	p_exp.SetClipExplosion();

	// Init dragon
	bool app_dragon = true;
	static int HP_dragon = 2000;
	DragonObject *p_dragon = new DragonObject;

		p_dragon->InitVideoDragon();
		p_dragon->SetRect(WIDTH_BACKGROUND-200 , HEIGHT_BACKGROUND *0.3 );
		p_dragon->LoadImg("dragon1.png");
		BulletObject *p_bullet_dr = new BulletObject;
		p_dragon->InitBullet(p_bullet_dr);
	
	int ret_menu = SDLCommonFunc::ShowMenu(g_screen, g_font_text);
	if (ret_menu == 1)
	{
		is_quit = true;
	}

	static int time_real = 0;

	clock_t time = 0;

	while (!is_quit)
	{
		time = clock();

		while (SDL_PollEvent(&g_even))
		{
			if (g_even.type == SDL_QUIT)
			{
				is_quit = true;
				break;
			}
			p_soku.HandleInputAction(g_even, g_sound_soku);
		}

		SDLCommonFunc::ApplySurface(g_background, g_screen, 0, 0);
		
	    
		if (time_real > 500)
		{
			if (app_dragon == true)
			{
				p_dragon->HandleMove(WIDTH_BACKGROUND, HEIGHT_BACKGROUND);
				p_dragon->Show(g_screen);
				p_dragon->MakeBullet(g_screen);

				// check collision between bullet dragon vs songoku

				std::vector<BulletObject*> p_bullet_list = p_dragon->GetbulletListDragon();
				for (int i = 0; i < p_bullet_list.size(); i++)
				{
					BulletObject *p_bullet = p_bullet_list.at(i);
					if (p_bullet->Get_Rect().y > p_soku.Get_Rect().y + HEIGHT_SOKU1 * 0.3)
					{
						bool col = SDLCommonFunc::CheckCollision(p_soku.Get_Rect(), p_bullet->Get_Rect());
						if (col == true)
						{
							// Show explosion
							for (int id = 0; id < 4; id++)
							{
								int x_pos = p_soku.Get_Rect().x + WIDTH_SOKU1 * 0.3;
								int y_pos = p_soku.Get_Rect().y + HEIGHT_SOKU1 * 0.4;

								p_exp.Setframe(id);
								p_exp.SetRect(x_pos, y_pos);
								p_exp.ShowEX(g_screen);
								//SDL_Delay(100);
								// Update screen
								if (SDL_Flip(g_screen) == -1)
								{
									return 1;
								}
							}
							p_dragon->ResetBullet(p_bullet);
							HP_goku -= 40;
						}
					}
				}

				// Check collision kameha goku1 voi dragon
				static int check_time1 = 0;
				if (p_soku.getTransGoku() == 0 && p_soku.getTypeGoku() == 1)
				{
					check_time1++;
					if (p_dragon->Get_Rect().y >= p_soku.Get_Rect().y + HEIGHT_SOKU1 / 4 &&
						p_dragon->Get_Rect().y <= p_soku.Get_Rect().y + HEIGHT_SOKU1)
					{
						//check_time1++;
						if (check_time1 >= 150)
						{
							HP_dragon -= 200;
							for (int id = 0; id < 4; id++)
							{
								int x_pos = p_dragon->Get_Rect().x + WIDTH_Dragon * 0.3;
								int y_pos = p_dragon->Get_Rect().y + HEIGHT_Dragon * 0.5;

								p_exp.Setframe(id);
								p_exp.SetRect(x_pos, y_pos);
								p_exp.ShowEX(g_screen);

								// Update screen
								if (SDL_Flip(g_screen) == -1)
								{
									return 1;
								}
							}
							p_dragon->Set_HP_Dragon(HP_dragon);
							check_time1 = 0;
						}
					}
				}

				static int check_time = 0;
				if (p_soku.getTransGoku() == 1 && p_soku.getTypeGoku() == 1)
				{
					check_time++;
					if (p_dragon->Get_Rect().y >= p_soku.Get_Rect().y + HEIGHT_SOKU1 / 4 &&
						p_dragon->Get_Rect().y <= p_soku.Get_Rect().y + HEIGHT_SOKU1)
					{
						if (check_time >= 500)
						{
							HP_dragon -= 50;
							for (int id = 0; id < 4; id++)
							{
								int x_pos = p_dragon->Get_Rect().x + WIDTH_Dragon * 0.3;
								int y_pos = p_dragon->Get_Rect().y + HEIGHT_Dragon * 0.5;

								p_exp.Setframe(id);
								p_exp.SetRect(x_pos, y_pos);
								p_exp.ShowEX(g_screen);

								// Update screen
								if (SDL_Flip(g_screen) == -1)
								{
									return 1;
								}
							}
							p_dragon->Set_HP_Dragon(HP_dragon);
						}
					}
				}

				// check colllision between bullet of goku2 with dragon
				std::vector<BulletObject*> p_bullet_listgoku2 = p_soku.GetbulletListgoku2();
				for (int i = 0; i <p_bullet_listgoku2.size(); i++)
				{
					BulletObject *p_bullet = p_bullet_listgoku2.at(i);
					bool col = SDLCommonFunc::CheckCollision(p_bullet->Get_Rect(), p_dragon->Get_Rect());
					if (col)
					{
						HP_dragon -= 50;
						for (int id = 0; id < 4; id++)
						{
							int x_pos = p_dragon->Get_Rect().x + WIDTH_Dragon * 0.3;
							int y_pos = p_dragon->Get_Rect().y + HEIGHT_Dragon * 0.5;

							p_exp.Setframe(id);
							p_exp.SetRect(x_pos, y_pos);
							p_exp.ShowEX(g_screen);

							// Update screen
							if (SDL_Flip(g_screen) == -1)
							{
								return 1;
							}
						}
						p_dragon->Set_HP_Dragon(HP_dragon);
						p_soku.RemoveBullet2(i);
					}
				}

				// check colllision between bullet of goku1 with dragon
				std::vector<BulletObject*> p_bullet_listgoku1 = p_soku.GetbulletListgoku1();
				for (int i = 0; i <p_bullet_listgoku1.size(); i++)
				{
					BulletObject *p_bullet = p_bullet_listgoku1.at(i);
					bool col = SDLCommonFunc::CheckCollision(p_bullet->Get_Rect(), p_dragon->Get_Rect());
					if (col)
					{
						HP_dragon -= 20;
						for (int id = 0; id < 4; id++)
						{
							int x_pos = p_dragon->Get_Rect().x + WIDTH_Dragon * 0.3;
							int y_pos = p_dragon->Get_Rect().y + HEIGHT_Dragon * 0.5;

							p_exp.Setframe(id);
							p_exp.SetRect(x_pos, y_pos);
							p_exp.ShowEX(g_screen);

							// Update screen
							if (SDL_Flip(g_screen) == -1)
							{
								return 1;
							}
						}
						p_dragon->Set_HP_Dragon(HP_dragon);
						p_soku.RemoveBullet(i);
					}
				}
				p_dragon->Show_HP_Dragon(g_screen);// SHOW HP
				SDL_Flip(g_screen);
				if (HP_dragon <= 0)
				{
					for (int i = 0; i < p_bullet_list.size(); i++)
					{
						BulletObject *p_bullet = p_bullet_list.at(i);
						if (p_bullet != NULL)
						{
							delete p_bullet;
							p_bullet = NULL;
						}
					}
					p_dragon->clearVideoDragon();
					delete p_dragon;
					p_dragon = NULL;
					app_dragon = false;
				}
			}
		}

		p_soku.HandleMove(g_sound_soku);
		p_soku.Show(g_screen);

		// Init Bullet

		for (int i = 0; i < p_soku.GetbulletListgoku1().size(); i++)
		{
			std::vector<BulletObject*> bulletlist = p_soku.GetbulletListgoku1();
			BulletObject *p_bullet = bulletlist.at(i);
			if (p_bullet != NULL)
			{

				if (p_bullet->get_is_move())
				{
					p_bullet->HandleMove(WIDTH_BACKGROUND, HEIGHT_BACKGROUND);
					p_bullet->Show(g_screen);
				}
				// erase p_bullet when p_bullet goes overs the Width of Screen
				else
				{
					if (p_bullet != NULL)
					{
						bulletlist.erase(bulletlist.begin() + i);
						p_soku.SetAmoBullet(bulletlist);

						delete p_bullet;
						p_bullet = NULL;
					}
				}
			}

		}

		// Init bullet 2

		for (int i = 0; i < p_soku.GetbulletListgoku2().size(); i++)
		{
			std::vector<BulletObject*> bulletlist2 = p_soku.GetbulletListgoku2();
			BulletObject *p_bullet = bulletlist2.at(i);
			if (p_bullet != NULL)
			{

				if (p_bullet->get_is_move())
				{
					p_bullet->HandleMove(WIDTH_BACKGROUND, HEIGHT_BACKGROUND);
					p_bullet->Show(g_screen);
				}
				// erase p_bullet when p_bullet goes overs the Width of Screen
				else
				{
					if (p_bullet != NULL)
					{
						bulletlist2.erase(bulletlist2.begin() + i);
						p_soku.SetAmoBullet2(bulletlist2);

						delete p_bullet;
						p_bullet = NULL;
					}
				}
			}

		}

		// run Threats
			for (int i = 0; i < NUMBER_THREATS; i++)
			{
				static int check_bullet;// check when enemies were destroyed  
				static int check_bullet2;

				ThreatsObject *p_threat = (p_threats + i);

				p_threat->HandleMove(WIDTH_BACKGROUND, HEIGHT_BACKGROUND);
				p_threat->Show(g_screen);
				// Check collision kameha
				static int index = 0;
				if (p_soku.getTypeGoku() == 1 && p_soku.getTransGoku() == 0) {
					index++;
					if (p_threat->Get_Rect().y > p_soku.Get_Rect().y
						&& p_threat->Get_Rect().y < p_soku.Get_Rect().y + HEIGHT_SOKU1) {
						if (index >= 300) {
							// Set explosion

							for (int id = 0; id < 4; id++)
							{
								int x_pos = p_threat->Get_Rect().x + WIDTH_THREAT * 0.3;
								int y_pos = p_threat->Get_Rect().y - HEIGHT_THREAT * 0.5;

								p_exp.Setframe(id);
								p_exp.SetRect(x_pos, y_pos);
								p_exp.ShowEX(g_screen);

								// Update screen
								if (SDL_Flip(g_screen) == -1)
								{
									return 1;
								}
							}

							p_threat->Resetthreats(WIDTH_BACKGROUND + i * 200);
						}
					}
				}
				else {
					index = 0;
				}


				// Check collison kameha2 with threats

				static int index_ = 0;
				if (p_soku.getTypeGoku() == 1 && p_soku.getTransGoku() == 1) {
					index_++;
					if (p_threat->Get_Rect().y > p_soku.Get_Rect().y
						&& p_threat->Get_Rect().y < p_soku.Get_Rect().y + HEIGHT_SOKU1) {
						if (index_ >= 350) {
							// Set explosion

							for (int id = 0; id < 4; id++)
							{
								int x_pos = p_threat->Get_Rect().x + WIDTH_THREAT * 0.3;
								int y_pos = p_threat->Get_Rect().y - HEIGHT_THREAT * 0.5;

								p_exp.Setframe(id);
								p_exp.SetRect(x_pos, y_pos);
								p_exp.ShowEX(g_screen);

								// Update screen
								if (SDL_Flip(g_screen) == -1)
								{
									return 1;
								}
							}

							p_threat->Resetthreats(WIDTH_BACKGROUND + i * 200);
						}
					}
				}
				else {
					index_ = 0;
				}

				// check collision between threats and bullet of go_ku1
				std::vector<BulletObject*> p_bullet_list = p_soku.GetbulletListgoku1();
				for (int im = 0; im < p_bullet_list.size(); im++)
				{
					BulletObject *p_bullet = p_bullet_list.at(im);
					bool check_col = SDLCommonFunc::CheckCollision(p_bullet->Get_Rect(), p_threat->Get_Rect());
					if (check_col == true)
					{

						// show explosion
						check_bullet++;
						for (int id = 0; id < 4; id++)
						{
							int x_pos = p_threat->Get_Rect().x + WIDTH_THREAT * 0.3;
							int y_pos = p_threat->Get_Rect().y - HEIGHT_THREAT * 0.5;

							p_exp.Setframe(id);
							p_exp.SetRect(x_pos, y_pos);
							p_exp.ShowEX(g_screen);

							// Update screen
							if (SDL_Flip(g_screen) == -1)
							{
								return 1;
							}
						}

						p_soku.RemoveBullet(im);

						if (check_bullet >= 4)
						{
							p_threat->Resetthreats(WIDTH_BACKGROUND + i * 200);
							check_bullet = 0;
						}
					}
				}

				// Check collision between bullet of goku2 with enemies

				std::vector<BulletObject*> p_bullet_list2 = p_soku.GetbulletListgoku2();
				for (int im = 0; im < p_bullet_list2.size(); im++)
				{
					BulletObject *p_bullet = p_bullet_list2.at(im);
					bool check_col = SDLCommonFunc::CheckCollision(p_bullet->Get_Rect(), p_threat->Get_Rect());
					if (check_col == true)
					{
						check_bullet2++;
						// show explosion
						for (int id = 0; id < 4; id++)
						{
							int x_pos = p_threat->Get_Rect().x + WIDTH_THREAT * 0.3;
							int y_pos = p_threat->Get_Rect().y - HEIGHT_THREAT * 0.5;

							p_exp.Setframe(id);
							p_exp.SetRect(x_pos, y_pos);
							p_exp.ShowEX(g_screen);

							// Update screen
							if (SDL_Flip(g_screen) == -1)
							{
								return 1;
							}
						}

						p_soku.RemoveBullet2(im);
						if (check_bullet2 >= 2)
						{
							p_threat->Resetthreats(WIDTH_BACKGROUND + i * 200);
							check_bullet2 = 0;
						}
					}
				}

				// Check collision between songoku with enemies

				if (p_threat->Get_Rect().y >= p_soku.Get_Rect().y + 115 &&
					p_threat->Get_Rect().x <= p_soku.Get_Rect().x + 130)
				{
					ret = SDLCommonFunc::CheckCollision(p_soku.Get_Rect(), p_threat->Get_Rect());

					if (ret)
					{
						HP_goku -= 20;
						//p_soku.Get_HP(HP_goku);
						// Show explosion
						for (int id = 0; id < 4; id++)
						{
							int x_pos = p_threat->Get_Rect().x + WIDTH_THREAT * 0.3;
							int y_pos = p_threat->Get_Rect().y - HEIGHT_THREAT * 0.5;

							p_exp.Setframe(id);
							p_exp.SetRect(x_pos, y_pos);
							p_exp.ShowEX(g_screen);

							// Update screen
							if (SDL_Flip(g_screen) == -1)
							{
								return 1;
							}
						}
						p_threat->Resetthreats(WIDTH_BACKGROUND + i * 200);

					}
				}
				p_index.Get_HP(HP_goku);
				p_index.Show_HP(g_screen);

				// When HP of goku is lower than 0

				if (HP_goku <= 0)
				{
					for (int i = 0; i < 150; i++)
					{
						SDLCommonFunc::ApplySurface(g_endgame, g_screen, 0, 0);
						if (SDL_Flip(g_screen) == -1)
						{
							return 1;
						}
					}
					delete[] p_threats;
					SDLCommonFunc::CleanUp();
					p_soku.clearVideo();
					SDL_Quit();
					return 0;
				}
				p_soku.Show_Index(g_screen);
				// Update screen
				if (SDL_Flip(g_screen) == -1)
				{
					return 1;
				}
			}
		time_real++;
	}
	SDLCommonFunc::CleanUp();
	p_soku.clearVideo();
	p_dragon->clearVideoDragon();
	SDL_Quit();
	return 0;
}
