#pragma once

// ------------------------------------------------------------------------------------------------
#include <mutex>
#include <future>
#include <vector>

// ------------------------------------------------------------------------------------------------
namespace SqHTTP {
	
	void refreshFutureHolder();
	void clearFuture();

} // Namespace - SqHTTP