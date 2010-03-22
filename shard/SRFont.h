#ifndef SRFONT_H
#define SRFONT_H
#include <SRImage.h>
class SRFont : public CSObject<SRFont>
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
	};
	Metrics m_charMetrics[256];
	SRImage* m_charGlyphs[256];
private:
public:
	virtual void load(unsigned char* data) = 0;
	virtual void load(const char* fileName) = 0;
	virtual void draw(int x, int y) = 0;
	virtual void drawChar(unsigned char character, int x, int y) = 0;
	virtual void drawString( std::string outputString, int x, int y) = 0;
};
#endif