#include <SRSDLCanvas.h>

template<> SRCanvas* CSObject<SRCanvas>::alloc()
{
	return new SRSDLCanvas();
}

void SRSDLCanvas::create(int w, int h)
{
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		Uint32 rmask = 0xff000000;
		Uint32 gmask = 0x00ff0000;
		Uint32 bmask = 0x0000ff00;
		Uint32 amask = 0x000000ff;
	#else
		Uint32 rmask = 0x000000ff;
		Uint32 gmask = 0x0000ff00;
		Uint32 bmask = 0x00ff0000;
		Uint32 amask = 0xff000000;
	#endif
	m_pCanvas = SDL_CreateRGBSurface(NULL, w, h, 32, rmask, gmask, bmask, amask);
}
u8* SRSDLCanvas::getData()
{
	return (0);
}
const CSRectangle<u32> SRSDLCanvas::getRectangle()
{
	const CSRectangle<u32> dimensions = {0,0,m_pCanvas->w,m_pCanvas->h};
	return dimensions;
}
void SRSDLCanvas::drawRectangle(CSRectangle<u32>& rectangle, CSColor<u32>& color)
{
}
void SRSDLCanvas::drawFilledRectangle(CSRectangle<u32>& rectangle, CSColor<u32>& color)
{
}
void SRSDLCanvas::drawRoundRectangle(CSRectangle<u32>& rectangle, u32 radius, CSColor<u32>& color)
{
}
void SRSDLCanvas::drawCircle(CSPoint<u32>& center, u32 radius, CSColor<u32>& color)
{
}
void SRSDLCanvas::drawFilledCircle(CSPoint<u32>& center, u32 radius, CSColor<u32>& color)
{
}
void SRSDLCanvas::drawLine(CSLine<u32>& line, CSColor<u32>& color)
{
}
void SRSDLCanvas::drawPixel(CSPoint<u32>& point, CSColor<u32>& color)
{
}