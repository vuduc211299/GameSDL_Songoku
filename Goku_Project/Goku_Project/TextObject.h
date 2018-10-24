#ifndef TEXT_OBJECT_H_

#define TEXT_OBJECT_H_

#include "BaseObject.h"
#include "CommonFunction.h"
#include <string>



class TextObject : public BaseObject
{
public:
    
	enum TextColor {
	RED_TEXT = 0,
	BLACK_TEXT = 1,
	WHITE_TEXT=2
	};
	TextObject();
	~TextObject();

	void SetText(const std::string text) { str_val_ = text; }
	void SetColor(const int &type);
	void CreatGameText(SDL_Surface *des, TTF_Font *font);

private:
	std::string str_val_;
	SDL_Color text_color_;
};

#endif // !TEXT_OBJECT_H_
