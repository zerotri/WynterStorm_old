///////////////
//
// File: 
// Description:
//
///////////////

#ifndef WSRTTI_H
#define WSRTTI_H

#include <stdarg.h>
#include <string>
//#include <core/ws_Types.h>

//class: WSRTTI
//	A custom Run Time Type Identification class.
//	Used quite a bit throughout the WS engine.
//	By adding a few macros into your class, you can give it
//	RTTI properties.
//	To use, create a new class, based on imaginary classes 'A' and 'C':
//
//		class BaseClass : public A, public C{
//			RTTI_DECLARE();
//		};
//
//	Then, in that classes' implementation file, place the following macro:
//
//		RTTI_IMPLEMENTATION(BaseClass,0);
//
//	But WAIT! RTTI doesn't know anything about BaseClass' parents!
//
//	NOTE: if the class being given RTTI properties derives from any classes,
//	you must add class info to the end of the RTTI_IMPLEMENTATION macro
//	as follows:
//
//		RTTI_IMPLEMENTATION(BaseClass, 2, CLASS(A), CLASS(C));
//
//	And now you have a fully functioning class with RTTI properties.
//	To check the classes type, you can now do the following:
//
//		if(a_class->RTTI().IsA(CLASS(BaseClass)))
//		{
//			//Do something since we know 'a_class' IS a BaseClass
//		}
class WSRTTI
{
public:
	//ctor
	WSRTTI(const std::string& a_sName, int a_iNumParents, ...);

	//Used to return a std::string with the class' name
	const std::string& GetClassName() const;

	//Used to compare a class' RTTI to this class' RTTI and see if they are the same
	bool IsA(const WSRTTI* a_cOtherRTTI) const;
	static bool CompareClasses(const WSRTTI* a_cRTTI1, const WSRTTI* a_cRTTI2);
private:
	const std::string m_strClassName;
	int m_iNumParents;
	const WSRTTI** m_pRTTIParents;
};
#define RunType(object) \
	&(object.WSRTTI())
#define RunTypeP(object) \
	&(object->WSRTTI())

#define CLASS(class) \
	&(class::m_rtti)
#define PCLASS(class) \
	&(class->m_rtti)

#define RTTI_DECLARE() \
	public: \
		static const WSRTTI m_rtti; \
		virtual const WSRTTI& WSRTTI() const { return m_rtti; };

#define RTTI_IMPLEMENTATION(name, ...) \
const ws::core::WSRTTI name::m_rtti(std::string(#name), __VA_ARGS__);
#endif
