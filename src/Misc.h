#pragma once

// ------------------------------------------------------------------------------------------------
#include <mutex>
#include <future>
#include <vector>

// ------------------------------------------------------------------------------------------------
namespace HTTP {
	
	void refreshFutureHolder();
	void clearFuture();

} // Namespace - HTTP