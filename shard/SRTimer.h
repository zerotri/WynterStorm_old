#ifndef SRTIMER_H
#define SRTIMER_H
#include <Crystal.h>

class SRTimer : public CSObject<SRTimer>
{
public:
	SRTimer();
	void Reset();
	fp64 Get();
private:
	fp64 m_dLastReset;
};
#endif