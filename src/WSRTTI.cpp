///////////////
//
// File: 
// Description:
//
///////////////

#include <WSRTTI.h>

// ----------------------------------------------
// ctor() - set up the class RTTI info, including
//          the name and parents' names
// ----------------------------------------------
WSRTTI::WSRTTI(const std::string& a_sName, int a_iNumParents, ...) :
				m_strClassName(a_sName)
{
	//Check if this class has any parents.
	if(a_iNumParents < 1)
	{
		//If not, not much needs to be done
		m_iNumParents = 0;
		m_pRTTIParents = NULL;
	}
	else
	{
		//If it does though, load the parent info into this RTTI class
		m_iNumParents = a_iNumParents;
		m_pRTTIParents = new const WSRTTI*[a_iNumParents];

		//Since we're using a variable arguments contructor, we get to
		//have fun with va_lists
		va_list v;
		va_start(v, a_iNumParents);

		//Iterate over va_list
		for(int t_iParentalIterator = 0; t_iParentalIterator < a_iNumParents; ++t_iParentalIterator)
		{
			//Loading parent info into 'm_pRTTIParents' array
			m_pRTTIParents[t_iParentalIterator] = va_arg(v, const WSRTTI*);
		}
	}
};

// ----------------------------------------------
// GetClassName() - return the name of the class
// ----------------------------------------------
const std::string& WSRTTI::GetClassName() const
{
	return m_strClassName;
};

// ----------------------------------------------
// IsA() - return if the class is a class of type
//          [a_cOtherRTTI], or if it even derives
//			from it
// ----------------------------------------------
bool WSRTTI::IsA(const WSRTTI* a_cOtherRTTI) const
{
	const WSRTTI * pCompare = this;

	if(pCompare == a_cOtherRTTI)
		return true;

	//If not, let's check this class' parents
	for(int t_iRTTIIterator = 0; t_iRTTIIterator < m_iNumParents; ++t_iRTTIIterator)
	{
		//And while we're at it, all the ancestors will be taken into account as well
		if(m_pRTTIParents[t_iRTTIIterator]->IsA(a_cOtherRTTI))
			return true;
	}
	//Oops!
	//These classes are NOT the same, or even related
	//Why are you comparing them then?
	return false;
}

bool WSRTTI::CompareClasses(const WSRTTI* a_cRTTI1, const WSRTTI* a_cRTTI2)
{
	return (a_cRTTI1->IsA(a_cRTTI2));
}
