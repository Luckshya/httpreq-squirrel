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
	void Event_OnResponse(std::string regTag, std::string url, std::string text, unsigned int statusCode)
	{
		HSQUIRRELVM vm = DefaultVM::Get();

		Function callback = RootTable(vm).GetFunction("HTTP_OnResponse");

		if (callback.IsNull())
		{
			callback.Release();
			return;
		}

		try
		{
			callback.Execute(regTag, url, statusCode, text);
		}
		catch (Sqrat::Exception& e)
		{
			std::ostringstream error;
			error << "HTTP event [ON RESPONSE] => Squirrel error [" << e.what() << "]";

			OutputErr(error.str().c_str());
		}
		catch (const std::exception& e)
		{
			std::ostringstream error;
			error << "HTTP event [ON RESPONSE] => Program error [" << e.what() << "]";

			OutputErr(error.str().c_str());
		}
		catch (...)
		{
			OutputErr("HTTP event [ON RESPONSE] => Unknown error");
		}

		callback.Release();
	}
} // Namespace - SqHTTP
