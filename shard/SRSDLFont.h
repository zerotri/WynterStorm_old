#ifndef SRSDLFONT_H
#define SRSDLFONT_H
#include <SRFont.h>
class SRSDLFont : public SRFont
{
protected:
	struct Metrics
	{
		int  width;
		int  height;

		int  horiBearingX;
		int  horiBearingY;
		int  horiAdvance;

		int  vertBearingX;
		int  vertBearingY;
		int  vertAdvance;
		int xoff, yoff, advance_x;
		signed long  xMin, yMin;
		signed long  xMax, yMax;
	};
	Metrics m_charMetrics[256];
	Metrics m_fontMetrics;
	SRImage* m_charGlyphs[256];
private:
public:
	SRSDLFont();
	~SRSDLFont();
	virtual void load(unsigned char* data);
	virtual void load(const char* fileName);
	virtual void draw(int x, int y);
	virtual void drawChar(unsigned char character, int x, int y);
	virtual void drawString( std::string outputString, int x, int y);
};
#endif