#include <WSTransition.h>

WSTransition::WSTransition(float incremental)
	:	m_fIncremental(incremental),
		m_fCurrentValue(0.0f)
{
}

WSTransition::~WSTransition()
{
}


bool WSTransition::isComplete()
{
	return false;
}

float WSTransition::getCurrentValue()
{
	return 1.0f;
}