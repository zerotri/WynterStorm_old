#include <SRSDLWindow.h>
#include <SDL/SDL.h>

CSObjectAllocator(SRWindow, SRSDLWindow);
/*template<> SRWindow* CSObject<SRWindow>::alloc()
{
	return new SRSDLWindow();
}*/
SRSDLWindow::SRSDLWindow()
{
}
SRSDLWindow::~SRSDLWindow()
{
	if((m_pWindow != 0))
		destroy();
}


void SRSDLWindow::create(int width, int height)
{
	m_iWidth = width;
	m_iHeight = height;
	m_pWindow = SDL_CreateWindow("WynterStorm", SDL_WINDOWPOS_UNDEFINED,
												  SDL_WINDOWPOS_UNDEFINED,
												  m_iWidth, m_iHeight,
												  SDL_WINDOW_SHOWN);
	if (m_pWindow == 0)
	{
		Log << "Can't create window:" << SDL_GetError() << SRLog::Flush;
	}

	SDL_SetRenderDrawColor(0xA0, 0xA0, 0xA0, 0xFF);
	SDL_RenderClear();
	SDL_SetRenderDrawColor(0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderLine(32,32,48,128);
	
}
void SRSDLWindow::destroy()
{
	SDL_DestroyWindow(m_pWindow);
}
void SRSDLWindow::swap()
{
	SDL_RenderPresent();
	SDL_SetRenderDrawColor(0xA0, 0xA0, 0xA0, 0xFF);
	SDL_RenderClear();
}
void SRSDLWindow::setFocused()
{
	/*if (SDL_GL_MakeCurrent(m_iWindowID, m_pGLContext)<0)
	{
		Log << "Can't set current OpenGL context:" << SDL_GetError() << WSLog::Flush;
	}*/
}
void SRSDLWindow::setTitle(std::string title)
{
	SDL_SetWindowTitle(m_pWindow, title.c_str());
}