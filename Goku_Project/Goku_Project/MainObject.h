#ifndef MAIN_OBJECT_H_

#define MAIN_OBJECT_H_

#include "BaseObject.h"
#include "CommonFunction.h"
#include <vector>
#include "BullletObject.h"
#include "Indexgoku.h"
#include "Explosion.h"

#define WIDTH_SOKU1 180
#define HEIGHT_SOKU1 250


class MainObject : public BaseObject
{
public:
	MainObject();
	~MainObject();

	void HandleMove(Mix_Chunk *g_sound_kameha[2]);
	void HandleInputAction(SDL_Event evevts, Mix_Chunk *g_sound_kameha[2]);
	void SetAmoBullet(std::vector<BulletObject*> bullet_list) { p_bullet_list_goku1 = bullet_list; }
	void SetAmoBullet2(std::vector<BulletObject*> bullet_list2) { p_bullet_list_goku2 = bullet_list2; }
	std::vector<BulletObject*> GetbulletListgoku1() const { return p_bullet_list_goku1; }
	std::vector<BulletObject*> GetbulletListgoku2() const { return p_bullet_list_goku2; }
	void RemoveBullet(const int& ixd);
	void RemoveBullet2(const int& ixd);
	void initVideo(); // Initialize video
	void clearVideo(); // clear video
	int getTypeGoku() const { return type_goku; }
	int getTransGoku() const { return trans_goku; }

	void Show_Index(SDL_Surface *des);
	void Get_Index(int index) { Index_trans = index; }

	void Get_HP(int HP) { HP_goku = HP; }

private:
	int x_val_;
	int y_val_;
	int type_goku; // Trạng thai goku 
	int trans_goku; // Transform goku
	int Index_trans;
	int HP_goku;

	std::vector<SDL_Surface*> video_death;
	std::vector<BulletObject*> p_bullet_list_goku1;
	std::vector<BulletObject*> p_bullet_list_goku2;
	std::vector<SDL_Surface*> video_kameha; 
	std::vector<SDL_Surface*> video_fly;
	std::vector<SDL_Surface*> video_bullet_normal;
	std::vector<SDL_Surface*> video_goku2_stand;
	std::vector<SDL_Surface*> video_kameha_goku2;
	std::vector<SDL_Surface*> video_bullet_normal_goku2;
	std::vector<SDL_Surface*> video_kameha_trans;

};

#endif