#ifndef SRLOG_H
#define SRLOG_H
#include <vector>
#include <string>
#include <sstream>
#include <fstream>


class SRLog
{
public:
	/// A filler class used to flush output from a WSLog stream
	class _Flush{};
	static _Flush Flush;
protected:
	bool m_bWroteTime;
	std::vector<std::string> m_vStrings;
	std::stringstream m_sCurrentStream;
	std::ofstream m_fOutputFile;
	void	__writeLogIfNeeded();
public:
	 		SRLog(void);
	 	   ~SRLog(void);
	SRLog&	operator<<(const std::string& string);
	SRLog&	operator<<(const char* string);
	SRLog&	operator<<(const int& integer);
	SRLog&	operator<<(const void* pointer);
	SRLog&	operator<<(const _Flush& flush);
};

extern SRLog& GetLog();

#define Log GetLog() << __FUNCTION__
#endif