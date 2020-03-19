#pragma once

// ------------------------------------------------------------------------------------------------
#include "includes.h"
#include "CResponse.h"

// ------------------------------------------------------------------------------------------------
// Mutex guard for future container
extern std::mutex m_futureGuard;

// Container to hold futures
extern std::vector<std::future<bool>> future_holder;

// ------------------------------------------------------------------------------------------------
namespace SqHTTP {

	extern std::vector<Response> m_Responses;
	extern std::mutex m_ResponseGuard;

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

} // Namespace - SqHTTP