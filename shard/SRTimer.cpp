#include <SRTimer.h>
#include <SRCore.h>

template<> SRTimer* CSObject<SRTimer>::alloc()
{
	return new SRTimer();
}
SRTimer::SRTimer()
{
	this->Reset();
}

void SRTimer::Reset()
{
	m_dLastReset = SRCore::getTime();
}

double SRTimer::Get()
{
	double t_dCurrentTime = SRCore::getTime();
	return (t_dCurrentTime - m_dLastReset);
}