#pragma once

// ------------------------------------------------------------------------------------------------
#include "includes.h"

// ------------------------------------------------------------------------------------------------
// Mutex lock to guard squirrel functionss
extern std::mutex sq_guard;

// Container to hold futures
extern std::vector<std::future<bool>> future_holder;

// ------------------------------------------------------------------------------------------------
namespace HTTP {

   class GetRequest {

    public :
		std::string url;
		std::string _tag;
		long int timeout = -1;

		GetRequest();

		void setURL(std::string);
		void setTimeout(long int);
		void setTag(std::string);

		static void Register(Sqrat::Table tb);
		static SQInteger sendGet(HSQUIRRELVM vm);

    }; // Class - Request

} // Namespace - HTTP