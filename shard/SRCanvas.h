#ifndef SRCANVAS_H
#define SRCANVAS_H
#include <Crystal.h>

class SRCanvas : public CSObject<SRCanvas>
{
private:
protected:
public:
	virtual void create(int w, int h) = 0;
	virtual u8* getData() = 0;
	virtual const CSRectangle<u32> getRectangle() = 0;
	
	//drawing functions
	virtual void drawRectangle(CSRectangle<u32>& rectangle, CSColor<u32>& color) = 0;
	virtual void drawFilledRectangle(CSRectangle<u32>& rectangle, CSColor<u32>& color) = 0;
	virtual void drawRoundRectangle(CSRectangle<u32>& rectangle, u32 radius, CSColor<u32>& color) = 0;
	virtual void drawCircle(CSPoint<u32>& center, u32 radius, CSColor<u32>& color) = 0;
	virtual void drawFilledCircle(CSPoint<u32>& center, u32 radius, CSColor<u32>& color) = 0;
	virtual void drawLine(CSLine<u32>& line, CSColor<u32>& color) = 0;
	virtual void drawPixel(CSPoint<u32>& point, CSColor<u32>& color) = 0;
};
#endif