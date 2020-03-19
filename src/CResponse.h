#pragma once

// ------------------------------------------------------------------------------------------------
#include <string>
#include <vector>
#include <mutex>
#include <future>

// ------------------------------------------------------------------------------------------------
// Container to hold futures
extern std::vector<std::future<bool>> future_holder;

// ------------------------------------------------------------------------------------------------
namespace SqHTTP {
	class Response {
	public :
		std::string regTag;
		std::string url;
		std::string text;
		unsigned int statusCode;

		Response(std::string, std::string, std::string, unsigned int);

		static void Update();
		static void Clear();
	};
} // Namespace - SqHTTP