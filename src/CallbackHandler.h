#pragma once

// ------------------------------------------------------------------------------------------------
#include "sqrat.h"
#include "Misc.h"

// ------------------------------------------------------------------------------------------------
// Mutex lock to guard squirrel functionss
extern std::mutex sq_guard;

// Container to hold futures
extern std::vector<std::future<bool>> future_holder;

// ------------------------------------------------------------------------------------------------
namespace SqHTTP
{
	void Event_onDataReceived(std::string regTag, std::string url, std::string text, unsigned int statusCode);
} // Namespace - SqHTTP