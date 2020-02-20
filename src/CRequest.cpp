// ------------------------------------------------------------------------------------------------
#include "CRequest.h"
#include "CallbackHandler.h"
#include <string>

// ------------------------------------------------------------------------------------------------
namespace HTTP {

    GetRequest::GetRequest() { }

    void GetRequest::setURL(std::string url) {
		this->url = url;
    }

	void GetRequest::setTimeout(long int timeout) {
		this->timeout = timeout;
	}

	void GetRequest::setTag(std::string tag) {
		this->_tag = tag;
	}

	SQInteger GetRequest::sendGet(HSQUIRRELVM vm) {
		const int top = sq_gettop(vm);

		GetRequest * request = nullptr;

		try {
			request = Sqrat::Var< GetRequest * >(vm, 1).value;
		}
		catch (const Sqrat::Exception& e) {
			return sq_throwerror(vm, e.what());
		}

		if (!request) {
			return sq_throwerror(vm, "Invalid HTTP::Request instance");
		}

		else if ((request->url).empty()) {
			return sq_throwerror(vm, "Invalid URL in request object");
		}

		try
		{
			std::string url			= request->url;
			std::string tag			= request->_tag;
			unsigned int timeout	= request->timeout;

			// Make an async call using in-built async function that uses internal thread pool
			// Push the returned in a vector to make it really an ASYNC call
			// Copy url, tag and timeout variables by value for async call
			::future_holder.push_back(std::async(std::launch::async, [url, tag, timeout]()
			{
				try {
					cpr::Session session;
					session.SetUrl(url);

					if (timeout > 0) {
						session.SetTimeout(cpr::Timeout(timeout));
					}

					// Send and wait for the request to comeback with the returned data
					cpr::Response r = session.Get();

					// Lock the mutex to not allow parallel calling of squirrel functions
					// If locked, it waits for it to get unlocked if being locked by another thread
					std::lock_guard<std::mutex> lock(sq_guard);

					OutputDebug("Calling [Event_onDataReceived]");

					// Call squirrel event callback
					Event_onDataReceived(tag, r.url, r.text, r.status_code);

					OutputDebug("Called [Event_onDataReceived]");
				}
				catch (...) {
					OutputErr("An Error has occured at [GetRequest] async function => [sendGet]");
				}

				// Specify that the request is complete and value is returned
				return true;
			}));
		}
		catch (...)
		{
			OutputErr("An Error has occured at [GetRequest] function => [sendGet]");
		}

		return 0;
	}

	void GetRequest::Register(Sqrat::Table tb) {

		using namespace Sqrat;

		tb.Bind("GetRequest",
			Class< GetRequest >(tb.GetVM(), "GetRequest")
			
			.Func("setURL", &GetRequest::setURL)
			.Func("setTimeout", &GetRequest::setTimeout)
			.Func("setTag", &GetRequest::setTag)

			.SquirrelFunc("sendGet", &GetRequest::sendGet)
		);
	}

} // Namespace - HTTP