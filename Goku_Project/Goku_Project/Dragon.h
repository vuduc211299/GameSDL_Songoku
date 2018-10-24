#ifndef DRAGON_OBJECT_H

#include"BaseObject.h"
#include"BullletObject.h"
#include<vector>

const int WIDTH_Dragon = 177;
const int HEIGHT_Dragon = 138;
const int WIDTH_BULLET_DRAGON = 81;
const int HEIGHT_BULLET_DRAGON = 64;


class DragonObject : public BaseObject
{
public:
	DragonObject();
	~DragonObject();

	int get_x_val() { return x_val; }
	int get_y_val() { return y_val; }
	void Set_x_val(const int &x) { x_val = x; }
	void Set_y_val(const int &y) { y_val = y; }
	void HandleMove(const int &x_border, const int &y_border);

	void ResetBullet(BulletObject *p_bullet);
	std::vector<BulletObject*> GetbulletListDragon() const { return p_list_bullet; }
	void SetBullet(std::vector<BulletObject*> bullet_list) { p_list_bullet = bullet_list; }
	void Set_HP_Dragon(int &HP) { HP_Dragon = HP; }
	void Show_HP_Dragon(SDL_Surface *des);
	void InitVideoDragon();
	void clearVideoDragon();
	void MakeBullet(SDL_Surface *des);
	void InitBullet(BulletObject *p_bullet);
	int Get_HPDragon () const { return HP_Dragon; }

private:
	int x_val;
	int y_val;
	std::vector<BulletObject*> p_list_bullet;
	std::vector<SDL_Surface*> video_dragon;
	std::vector<SDL_Surface*> video_collision;
	int HP_Dragon;
};

#endif // !DRAGON_OBJECT_H
