#ifndef WSTRANSITION_H
#define WSTRANSITION_H

///
/// WSTransition: Implements a simple 0..1 floating point transition that updates
/// only when needed.
///
class WSTransition
{
private:
	/// The current value of the transition.
	float	m_fCurrentValue;

	/// The incremental value of the transition in seconds
	/// default is 1.0f (transition completes in one second)
	float	m_fIncremental;
public:
			/// \param incremental The value to increment every second.
			WSTransition(float incremental = 1.0f);
	virtual~WSTransition();
	
	bool	isComplete();
	float	getCurrentValue();
};
#endif