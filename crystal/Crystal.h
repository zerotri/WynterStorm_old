#ifndef CRYSTAL_H
#define CRYSTAL_H
#include <string>
#include <vector>
typedef unsigned char			u8;
typedef unsigned short			u16;
typedef unsigned int			u32;
typedef unsigned long long int	u64;
typedef signed char				s8;
typedef signed short			s16;
typedef signed int				s32;
typedef signed long long int	s64;
typedef float					fp32;
typedef double					fp64;

template <typename _T>
class CSObject
{
public:
	static _T* alloc();
};
template <typename _T>
_T* allocate()
{
	return CSObject<_T>::alloc();
}

#define CSObjectAllocator(_base, _imp) \
template<> _base* CSObject<_base>::alloc() \
{ \
	return new _imp(); \
};

//<-- Primitives
template <typename _T>
struct CSPoint
{
	_T x;
	_T y;
	CSPoint()
	{
	}
	CSPoint(_T _x, _T _y)
	: x(_x), y(_y)
	{
	}
};

template <typename _T>
struct CSRectangle
{
	_T x, y;
	_T w, h;
};
template <typename _T>
struct CSLine
{
	_T x1, y1;
	_T x2, y2;
};
template <typename _T>
struct CSColor
{
	_T r;
	_T g;
	_T b;
	_T a;
};

template <typename _T>
struct CSVector
{
	_T x;
	_T y;
	_T z;
};

class CSBezier
{
public:
	CSPoint<double> m_a, m_b, m_c;
	CSBezier(CSPoint<double> a, CSPoint<double> b, CSPoint<double> c)
	: m_a(a), m_b(b), m_c(c)
	{
	}
	CSPoint<double> Plot(double point) //from [0.0]...[1.0]
	{
		CSPoint<double> pt;
		double a = point, b = 1.0 - a;
		
		//	X(a) = Ax·a² + Bx·2·a·b + Cx·b²
		//	Y(a) = Ay·a² + By·2·a·b + Cy·b²
		double aa = a*a;
		double ab2 = 2*a*b;
		double bb = b*b;
		pt.x = (m_a.x*aa) + (m_b.x*ab2) + (m_c.x * bb);
		pt.y = (m_a.y*aa) + (m_b.y*ab2) + (m_c.y * bb);
		return pt;
	}
};
//<-- Exceptions
/*class CrystalException
{
public:
	CrystalException(int lineNumber, const char* fileName);
	CrystalException(int lineNumber, const char* fileName, const char* error);
	CrystalException(int lineNumber, std::string fileName);
	CrystalException(int lineNumber, std::string fileName, std::string error);
private:
protected:
	int m_lineNumber;
	std::string m_fileName;
	std::string m_error;
};*/
#endif