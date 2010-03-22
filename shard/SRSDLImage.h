#ifndef SRSDLIMAGE_H
#define SRSDLIMAGE_H
#include <SRImage.h>
#include <SDL/SDL.h>

class SRSDLImage : SRImage
{
public:
	SDL_Texture* m_pTexture;
	static SRImage* loadImage();
	SRSDLImage();
	virtual ~SRSDLImage();
	virtual void load(const char* fileName);
	virtual void load(unsigned char* data, int width, int height, int depth);
	virtual void draw(int x, int y);
	virtual void draw(CSRectangle<int>& rect, int x, int y);
	virtual void draw(CSRectangle<int>& rectA, CSRectangle<int>& rectB);
	virtual void setDrawingColor(unsigned char red, unsigned char green, unsigned char blue);
	virtual const CSRectangle<int>& getRect();
};
#endif