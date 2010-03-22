#ifndef SRSDLCANVAS_H
#define SRSDLCANVAS_H
#include <SRCanvas.h>
#include <SDL.h>

class SRSDLCanvas : public SRCanvas
{
private:
protected:
	SDL_Surface* m_pCanvas;
public:
	virtual void create(int w, int h);
	virtual u8* getData();
	virtual const CSRectangle<u32> getRectangle();
	virtual void drawRectangle(CSRectangle<u32>& rectangle, CSColor<u32>& color);
	virtual void drawFilledRectangle(CSRectangle<u32>& rectangle, CSColor<u32>& color);
	virtual void drawRoundRectangle(CSRectangle<u32>& rectangle, u32 radius, CSColor<u32>& color);
	virtual void drawCircle(CSPoint<u32>& center, u32 radius, CSColor<u32>& color);
	virtual void drawFilledCircle(CSPoint<u32>& center, u32 radius, CSColor<u32>& color);
	virtual void drawLine(CSLine<u32>& line, CSColor<u32>& color);
	virtual void drawPixel(CSPoint<u32>& point, CSColor<u32>& color);
};
#endif