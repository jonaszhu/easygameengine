#ifndef _MOLE2D_LOGGER_H
#define _MOLE2D_LOGGER_H

/** 
* Mole2d ͼ������
*
* author: akinggw
* date: 2009.11.10
*/

#include <iosfwd>
#include <sstream>
#include <string>

//namespace mole2d
//{
//namespace graphics
//{

enum Level
{
	FATAL = 0,
	ERRORR,
	WARN,
	INFO,
	DEBUGG
};

class CMolLogger
{
public:
	/// ������־�ļ�
    static void setLogFile(std::string const &logFile);
	/// �����Ƿ��ӡ��־
    static void setTimestamp(bool flag = true)
    { mHasTimestamp = flag; }
	
	/// �������ģʽ
    static void setTeeMode(bool flag = true)
    { mTeeMode = flag; }

	/// ������־�ȼ�
    static void setVerbosity(Level verbosity)
    { mVerbosity = verbosity; }

	/// �����־
	static std::string output(std::string const &msg, Level atVerbosity);

    static Level mVerbosity;   
private:
    static bool mHasTimestamp; 
    static bool mTeeMode;      

    static void output(std::ostream &os, std::string const &msg, char const *prefix);
};

//}
//}

#define LOG(level, msg)                                                \
	do if (::CMolLogger::mVerbosity >= ::level) {    \
	std::ostringstream os;                                         \
	os << msg;                                                     \
	::CMolLogger::output(os.str(), ::level);     \
	} while (0)

#define LOG_DEBUG(msg)  LOG(DEBUG, msg)
#define LOG_INFO(msg)   LOG(INFO, msg)
#define LOG_WARN(msg)   LOG(WARN, msg)
#define LOG_ERRORR(msg)  LOG(ERRORR, msg)
#define LOG_FATAL(msg)  LOG(FATAL, msg)

#endif
