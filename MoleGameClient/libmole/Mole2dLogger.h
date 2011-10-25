#ifndef _MOLE2D_LOGGER_H
#define _MOLE2D_LOGGER_H

/** 
* Mole2d 图像引擎
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
	/// 设置日志文件
    static void setLogFile(std::string const &logFile);
	/// 设置是否打印日志
    static void setTimestamp(bool flag = true)
    { mHasTimestamp = flag; }
	
	/// 设置输出模式
    static void setTeeMode(bool flag = true)
    { mTeeMode = flag; }

	/// 设置日志等级
    static void setVerbosity(Level verbosity)
    { mVerbosity = verbosity; }

	/// 输出日志
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
