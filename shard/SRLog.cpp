#include "SRLog.h"
#include <ctime>
SRLog::_Flush SRLog::Flush;
static SRLog* _Log = NULL;
	SRLog& GetLog()
	{
		if(_Log != NULL)
		{
			return (*_Log);
		}
		else
		{
			_Log = new SRLog();
			return (*_Log);
		}
	}
#ifdef _DEBUG
	SRLog::SRLog(void)
	{
		m_fOutputFile.open("WynterStorm.log");
		m_fOutputFile << "------------------------ WynterStorm ------------------------" << std::endl << std::endl;
		m_fOutputFile.flush();
		m_vStrings.clear();
		m_bWroteTime = false;
	}

	SRLog::~SRLog(void)
	{
		std::vector<std::string>::iterator itStrings = m_vStrings.begin();
		for(;itStrings != m_vStrings.end(); itStrings++)
		{
			m_fOutputFile << (*itStrings) << std::endl;
		}
		m_vStrings.clear();
		m_fOutputFile.flush();
		m_fOutputFile.close();
	}

	inline void SRLog::__writeLogIfNeeded()
	{
		static char dateTimeBuffer[32];
		if( m_bWroteTime == false )
		{
			m_sCurrentStream.str(std::string());
			time_t t(time(NULL));   // current time
			const tm* curTime = localtime(&t);
			strftime( &dateTimeBuffer[0], 32, "%I:%M:%S", curTime );
			m_sCurrentStream << "[" << dateTimeBuffer << "]  ";
			m_bWroteTime = true;
		}
		else return;
	}

	SRLog&	SRLog::operator<<(const char* string)
	{
		__writeLogIfNeeded();
		m_sCurrentStream << string;
		return (*this);
	}
	SRLog& SRLog::operator<<(const std::string& string)
	{
		__writeLogIfNeeded();
		m_sCurrentStream << string;
		return (*this);
	}
	SRLog&	SRLog::operator<<(const int& integer)
	{
		__writeLogIfNeeded();
		m_sCurrentStream << integer;
		return (*this);
	}
SRLog&	SRLog::operator<<(const void* pointer)
{
	__writeLogIfNeeded();
	m_sCurrentStream << pointer;
	return (*this);
}
	SRLog&	SRLog::operator<<(const _Flush& flush)
	{
		//exit early if empty string (implied by m_bWroteTime being false)
		if( m_bWroteTime == false )
			return (*this);

		//write stream to list of strings
		m_fOutputFile << m_sCurrentStream.str() << std::endl;
		m_fOutputFile.flush();
		m_vStrings.push_back(m_sCurrentStream.str());
		m_bWroteTime = false;
		return (*this);
	}
#else
	SRLog::SRLog(void)
	{
	}

	SRLog::~SRLog(void)
	{
	}

	inline void SRLog::__writeLogIfNeeded()
	{
	}

	SRLog&	SRLog::operator<<(const char* string)
	{
		return (*this);
	}
	SRLog& SRLog::operator<<(const std::string& string)
	{
		return (*this);
	}
	SRLog&	SRLog::operator<<(const int& integer)
	{
		return (*this);
	}
	SRLog&	SRLog::operator<<(const _Flush& flush)
	{
		return (*this);
	}
#endif