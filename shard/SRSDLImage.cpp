#include <SRSDLImage.h>
#include <SRLog.h>
#include <SDL.h>
#include <SOIL.h>

template<> SRImage* CSObject<SRImage>::alloc()
{
	return SRSDLImage::loadImage();
}

SRSDLImage::SRSDLImage()
{
	m_eState = CSImgState_empty;
}
SRSDLImage::~SRSDLImage()
{
	if(m_pTexture != 0)
		SDL_DestroyTexture(m_pTexture);
}
SRImage* SRSDLImage::loadImage()
{
	SRSDLImage* img = new SRSDLImage();
	return (SRImage*) img;
}
void SRSDLImage::load(unsigned char* data, int width, int height, int depth)
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
	SDL_Surface* surf;
	surf = SDL_CreateRGBSurfaceFrom(data,width,height, depth, width*(depth/8), rmask, gmask, bmask, amask);
	m_pTexture = SDL_CreateTextureFromSurface(0,surf);
	m_sRect.x = 0;
	m_sRect.y = 0;
	m_sRect.w = surf->w;
	m_sRect.h = surf->h;
	if (!m_pTexture) {
		Log << "Couldn't create texture: " << SDL_GetError() << SRLog::Flush;
		SDL_SetColorKey(surf, 0, 0);
		m_pTexture = SDL_CreateTextureFromSurface(0, surf);
		m_eState = CSImgState_error;
	}
	if (!m_pTexture) {
		Log << "Couldn't create texture: " << SDL_GetError() << SRLog::Flush;
		SDL_FreeSurface(surf);
		m_eState = CSImgState_error;
		return;
	}
	Log << "Created texture: " << (void*)m_pTexture << SRLog::Flush;
	SDL_FreeSurface(surf);
	m_eState = CSImgState_loaded;
}
void SRSDLImage::load(const char* filename)
{
	int width, height, channels;
	unsigned char* loaded_buffer = SOIL_load_image(filename,&width, &height, &channels, 4);
	if(!loaded_buffer)
	{
		Log << "Couldn't load image [" << filename << "]: " << SOIL_last_result() << SRLog::Flush;
		m_eState = CSImgState_error;
		return;
	}
	load(loaded_buffer, width, height, channels*8);
	free(loaded_buffer);
}
void SRSDLImage::draw(int x, int y)
{
	CSRectangle<int> dstRect = {x,y,m_sRect.w,m_sRect.h};
	SDL_RenderCopy(m_pTexture, NULL, (SDL_Rect*)&dstRect);
}
void SRSDLImage::draw(CSRectangle<int>& rect, int x, int y)
{
	CSRectangle<int> dstRect = {x,y,m_sRect.w,m_sRect.h};
	SDL_RenderCopy(m_pTexture, (SDL_Rect*)&rect, (SDL_Rect*)&dstRect);
}
void SRSDLImage::draw(CSRectangle<int>& rectA, CSRectangle<int>& rectB)
{
	SDL_RenderCopy(m_pTexture, (SDL_Rect*)&rectA, (SDL_Rect*)&rectB);
}
void SRSDLImage::setDrawingColor(unsigned char red, unsigned char green, unsigned char blue)
{
	SDL_SetTextureColorMod(m_pTexture, red, green, blue);
}
const CSRectangle<int>& SRSDLImage::getRect()
{
	return m_sRect;
}