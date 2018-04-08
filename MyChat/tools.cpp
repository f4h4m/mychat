#include "stdafx.h"
#include "tools.h"


string tools::GetTime()
{
	struct tm tstruct;
	char buffer[26];
	time_t now = time(0);
	localtime_s(&tstruct, &now);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d.%X", &tstruct);
	return buffer;
}