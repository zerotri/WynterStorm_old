#include <WSGame.h>
#include <SDL.h>
#include <algorithm>

WSGame::WSGame()
{
	m_dDeltaFramesPerSecond = 0;
	m_pCore = allocate<SRCore>();
	m_pWindow = allocate<SRWindow>();
}

WSGame::~WSGame()
{
	m_pWindow->destroy();
	delete m_pWindow;
	delete m_pCore;
}
void WSGame::Run()
{
	m_pCore->Initialize();
	m_dLastFrameTime = m_dDeltaFramesPerSecond = m_pCore->getTime();
	m_bGameEnding = false;
	m_pWindow->create(640, 480);
	m_pWindow->setTitle(std::string("WynterStorm Engine"));
    SDL_Event event;
    //SDL_bool done=SDL_FALSE;
	Initialize();
	do
	{
		  // handle the events in the queue
		  while (SDL_PollEvent(&event))
		  {
				switch(event.type)
				{
					case SDL_USEREVENT:
						onUserEvent(event.user.code, event.user.data1, event.user.data2);
						break;
					case SDL_MOUSEMOTION:
						onMouseMove(event.motion.x, event.motion.y);
						break;
					case SDL_MOUSEBUTTONDOWN:
						onMousePress((MouseButtons)event.button.button, event.button.x, event.button.y);
						break;
					case SDL_MOUSEBUTTONUP:
						onMouseRelease((MouseButtons)event.button.button, event.button.x, event.button.y);
						break;
					case SDL_MOUSEWHEEL:
						onMouseWheel(event.wheel.x, event.wheel.y);
						break;
					case SDL_WINDOWEVENT:
						switch (event.window.event)
						{
							case SDL_WINDOWEVENT_CLOSE:
								 m_bGameEnding = true;
								 break;
							case SDL_WINDOWEVENT_RESIZED:
								 //resize(event.window.data1, event.window.data2);
								 break;
						}
						break;
					case SDL_KEYDOWN:
						onKeyPress(event.key.keysym.sym, event.key.keysym.mod, event.key.keysym.scancode);
						break;
					case SDL_KEYUP:
						if(event.key.keysym.sym == SDLK_ESCAPE)
							m_bGameEnding = true;
						else onKeyRelease(event.key.keysym.sym, event.key.keysym.mod, event.key.keysym.scancode);
						break;
					case SDL_QUIT:
						 m_bGameEnding = true;
						 break;
				 }
		  }
		double dFrameTime = m_pCore->getTime();
		m_dDeltaFramesPerSecond = (dFrameTime - m_dLastFrameTime);
		m_dLastFrameTime = dFrameTime;
		Render();
		m_pWindow->swap();
	} while(m_bGameEnding == false);
	Shutdown();
	m_pCore->Shutdown();
}
fp64 WSGame::getFramesPerSecond()
{
	return 1.0 / m_dDeltaFramesPerSecond;
}