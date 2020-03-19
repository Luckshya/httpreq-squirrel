// ------------------------------------------------------------------------------------------------
#include "main.h"
#include "Misc.h"

// ------------------------------------------------------------------------------------------------
#include <iostream>
#include <sstream>
#include <algorithm>

// ------------------------------------------------------------------------------------------------
// Mutex guard for future container
std::mutex m_futureGuard;

// Container to hold futures
std::vector<std::future<bool>> future_holder;

// ------------------------------------------------------------------------------------------------
namespace SqHTTP {

	void refreshFutureHolder() {

		if (!future_holder.empty())
		{
			std::ostringstream msg;
			msg << "[FUTURE HOLDER] Before clearing: " << future_holder.size();
			OutputDebug(msg.str().c_str());

			{
				std::lock_guard<std::mutex> lock(m_futureGuard);
				future_holder.erase(
					std::remove_if(future_holder.begin(), future_holder.end(), [](std::future<bool> & fr) {
					return fr.wait_for(std::chrono::seconds(0)) == std::future_status::ready;
				}),
					future_holder.end()
					);
			}

			std::ostringstream msg2;
			msg2 << "[FUTURE HOLDER] After clearing: " << future_holder.size();
			OutputDebug(msg2.str().c_str());
		}
	}

	void clearFuture() {
		if (!future_holder.empty()) {
			std::lock_guard<std::mutex> lock(m_futureGuard);
			future_holder.clear();
		}
	}

} // Namespace - SqHTTP