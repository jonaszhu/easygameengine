#include "stdafx.h"

#include "Mole2dLogger.h"

#include <fstream>
#include <iomanip>
#include <iostream>

//#include <windows.h>

static std::ofstream mLogFile;     
bool CMolLogger::mHasTimestamp = true; 
bool CMolLogger::mTeeMode = false;     
Level CMolLogger::mVerbosity = INFO; 

static std::string getCurrentTime()
{
    time_t now;
    tm local;

    time(&now);

    local = *(localtime(&now));

    using namespace std;
	std::ostringstream os;
    os << "[" << setw(2) << setfill('0') << local.tm_hour
       << ":" << setw(2) << setfill('0') << local.tm_min
       << ":" << setw(2) << setfill('0') << local.tm_sec
       << "]";

    return os.str();
}

void CMolLogger::output(std::ostream &os, std::string const &msg, char const *prefix)
{
    if (mHasTimestamp)
    {
        os << getCurrentTime() << ' ';
    }

    if (prefix)
    {
        os << prefix << ' ';
    }

    os << msg << std::endl;
}

void CMolLogger::setLogFile(std::string const &logFile)
{
    if (mLogFile.is_open())
    {
        mLogFile.close();
    }

    mLogFile.open(logFile.c_str(), std::ios::trunc);

    if (!mLogFile.is_open())
    {
        throw std::ios::failure("unable to open " + logFile + "for writing");
    }
    else
    {
        mLogFile.exceptions(std::ios::failbit | std::ios::badbit);
    }
}

std::string CMolLogger::output(std::string const& msg, Level atVerbosity)
{
	std::string temp;

    static char const *prefixes[] =
        { "[致命]", "[错误]", "[警告]", "[信息]", "[调试]" };

    if (mVerbosity >= atVerbosity)
    {
        bool open = mLogFile.is_open();

        if (open)
        {
            output(mLogFile, msg, prefixes[atVerbosity]);
        }

        if (!open || mTeeMode)
        {
            output(atVerbosity <= WARN ? std::cerr : std::cout,
                   msg, prefixes[atVerbosity]);
        }

		if (mHasTimestamp)
		{
			temp = getCurrentTime() + " ";
		}

		temp += (std::string(prefixes[atVerbosity]) +  " ");
		temp += (msg + "\n");
    }

	return temp;
}
