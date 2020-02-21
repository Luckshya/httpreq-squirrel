// ------------------------------------------------------------------------------------------------
#include "CallbackHandler.h"
#include "main.h"

// ------------------------------------------------------------------------------------------------
#include <iostream>
#include <sstream>

// ------------------------------------------------------------------------------------------------
using namespace Sqrat;

// ------------------------------------------------------------------------------------------------
namespace SqHTTP
{
	void Event_onDataReceived(std::string regTag, std::string url, std::string text, unsigned int statusCode)
	{
		OutputDebug("Callback received for SqHTTP event [onDataReceived]");

		HSQUIRRELVM vm = DefaultVM::Get();

		Function callback = RootTable(vm).GetFunction("HTTP_onDataReceived");

		if (callback.IsNull())
		{
			OutputDebug("Could not find SqHTTP event [onDataReceived]");
			callback.Release();
			return;
		}

		try
		{
			OutputDebug("Calling HTTP event [onDataReceived]");

			callback.Execute(regTag, url, statusCode, text);

			OutputDebug("Called HTTP event [onDataReceived]");
		}
		catch (Sqrat::Exception& e)
		{
			std::ostringstream error;
			error << "Discord event [DATA RECEIVED] => Squirrel error [" << e.what() << "]";

			OutputErr(error.str().c_str());
		}
		catch (const std::exception& e)
		{
			std::ostringstream error;
			error << "Discord event [DATA RECEIVED] => Program error [" << e.what() << "]";

			OutputErr(error.str().c_str());
		}
		catch (...)
		{
			OutputErr("Discord event [DATA RECEIVED] => Unknown error");
		}

		OutputDebug("Releasing callback of [onDataReceived]");

		callback.Release();

		OutputDebug("Released callback of [onDataReceived]");

		// Refresh future to remove the elements that are ready ?
		refreshFutureHolder();
	}
} // Namespace - SqHTTP
