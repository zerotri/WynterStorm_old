#ifndef SRIMAGE_H
#define SRIMAGE_H
#include <Crystal.h>

class SRImage : public CSObject<SRImage>
{
public:
	enum CSImgState
	{
		CSImgState_empty,
		CSImgState_error,
		CSImgState_loaded
	};
protected:
	CSRectangle<int> m_sRect;
	CSImgState m_eState;
public:
	virtual void load(const char* filename) = 0;
	virtual void load(unsigned char* data, int width, int height, int depth) = 0;
	virtual void draw(int x, int y) = 0;
	virtual void draw(CSRectangle<int>& rect, int x, int y) = 0;
	virtual void draw(CSRectangle<int>& rectA, CSRectangle<int>& rectB) = 0;
	virtual void setDrawingColor(unsigned char red, unsigned char green, unsigned char blue) = 0;
	virtual const CSRectangle<int>& getRect() = 0;
	bool isLoaded()
	{
		return (m_eState == CSImgState_loaded);
	};
	
};
typedef SRImage* (SRImageFactory)();

#endif