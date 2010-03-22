#include <SRSDLCore.h>
#include <SDL.h>
#ifdef __APPLE__
	#include <sys/time.h>
#endif

template<> SRCore* CSObject<SRCore>::alloc()
{
	return new SRSDLCore();
}
SRSDLCore::SRSDLCore()
{
}

SRSDLCore::~SRSDLCore()
{
}
void SRSDLCore::Initialize()
{
	if((SDL_Init(SDL_INIT_EVERYTHING)==-1))
	{ 
        Log << "Could not initialize SDL: " << SDL_GetError() << SRLog::Flush;
	}
    Log << "SDL initialized." << SRLog::Flush;

	// Select first display
   if (SDL_SelectVideoDisplay(0) < 0)
   {
      Log << "Can't attach to first display: " << SDL_GetError() << SRLog::Flush;
   }
}
void SRSDLCore::Shutdown()
{
	Log << "Quitting SDL." << SRLog::Flush;
}
fp64 SRCore::getTime()
{
#ifdef __APPLE__
	timeval Time = {0, 0};
    gettimeofday(&Time, NULL);
	
    return Time.tv_sec + Time.tv_usec / 1000000.;
#else
	return ((double)SDL_GetTicks() / 1000.0);
#endif
}
/*
 void sleep(float time)
 {
	usleep(static_cast<unsigned long>(time * 1000000));
 }
 */
void SRSDLCore::drawPixel(s32 x, s32 y, CSColor<u8> color)
{
}