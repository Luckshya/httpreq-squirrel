// Main include
#include "main.h"

#if defined(WIN32) || defined(_WIN32)
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>
#endif

#include "SqImports.h"

#include "sqrat.h"
#include "CRequest.h"

// Definitions
HSQAPI sq;
HSQUIRRELVM v;

// Global variables (meh)
PluginFuncs * gFuncs;

uint8_t HTTP_OnSquirrelScriptLoad()
{
	// See if we have any imports from Squirrel
	size_t size;
	int     sqId      = gFuncs->FindPlugin( "SQHost2" );
	// Is there a squirrel host plugin?
	if (sqId < 0)
	{
		OutputMsg("Unable to locate the host plug-in");
		return 0;
	}
	const void ** sqExports = gFuncs->GetPluginExports( sqId, &size );

	// We do!
	if( sqExports != NULL && size > 0 )
	{
		// Cast to a SquirrelImports structure
		SquirrelImports ** sqDerefFuncs = (SquirrelImports **)sqExports;

		// Now let's change that to a SquirrelImports pointer
		SquirrelImports * sqFuncs       = (SquirrelImports *)(*sqDerefFuncs);

		// Now we get the virtual machine
		if( sqFuncs )
		{
			// Get a pointer to the VM and API
			sq = *(sqFuncs->GetSquirrelAPI());
			v = *(sqFuncs->GetSquirrelVM());

			Sqrat::ErrorHandling::Enable(true);
			Sqrat::DefaultVM::Set(v);

			Sqrat::Table HTTPcn(v);

			Sqrat::RootTable(v).Bind("HTTP", HTTPcn);
			HTTP::GetRequest::Register(HTTPcn);

			return 1;
		}
	}
	else
	{
		OutputMsg( "Failed to attach to SQHost2." );
	}
	return 0;
}

uint8_t HTTP_OnPluginCommand(uint32_t command_identifier, const char* /*message*/)
{
	switch( command_identifier )
	{
		case 0x7D6E22D8: return HTTP_OnSquirrelScriptLoad();

		default:
			break;
	}

	return 1;
}

uint8_t HTTP_OnServerInitialise()
{
	printf( "\n" );
	OutputMsg( "Loaded HTTP Requests module for VC:MP 0.4 by Luckshya." );

	return 1;
}

EXPORT unsigned int VcmpPluginInit( PluginFuncs* functions, PluginCallbacks* callbacks, PluginInfo* info )
{
	// Set our plugin information
	info->pluginVersion = 0x1001; // 1.0.01
    info->apiMajorVersion = PLUGIN_API_MAJOR;
    info->apiMinorVersion = PLUGIN_API_MINOR;
    sprintf(info->name, "%s", "HTTP Requests for VC:MP");

	// Store functions for later use
	gFuncs = functions;

	// Store callback
	callbacks->OnServerInitialise = HTTP_OnServerInitialise;
	callbacks->OnPluginCommand = HTTP_OnPluginCommand;

	// Done!
	return 1;
}

void OutputDebug( const char * msg )
{
	#ifdef _DEBUG
		OutputMsg( msg );
	#endif
}

void OutputMsg( const char * msg )
{
	#if defined(WIN32) || defined(_WIN32)
		HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );

		CONSOLE_SCREEN_BUFFER_INFO csbBefore;
		GetConsoleScreenBufferInfo( hstdout, &csbBefore );
		SetConsoleTextAttribute( hstdout, FOREGROUND_GREEN );
		printf("[MODULE]  ");

		SetConsoleTextAttribute( hstdout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY );
		printf("%s\n", msg);

		SetConsoleTextAttribute( hstdout, csbBefore.wAttributes );
	#else
		printf( "%c[0;32m[MODULE]%c[0;37m %s\n", 27, 27, msg );
	#endif
}

void OutputErr(const char * msg)
{
#ifdef WIN32
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbBefore;
	GetConsoleScreenBufferInfo(hstdout, &csbBefore);
	SetConsoleTextAttribute(hstdout, FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("[ERROR]  ");

	SetConsoleTextAttribute(hstdout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	printf("%s\n", msg);

	SetConsoleTextAttribute(hstdout, csbBefore.wAttributes);
#else
	printf("%c[0;31m[ERROR]%c[0;37m %s\n", 27, 27, msg);
#endif
}

void OutputWarn(const char * msg)
{
#ifdef WIN32
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbBefore;
	GetConsoleScreenBufferInfo(hstdout, &csbBefore);
	SetConsoleTextAttribute(hstdout, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << "[WARNING] ";

	SetConsoleTextAttribute(hstdout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY);
	std::cout << msg << std::endl;

	SetConsoleTextAttribute(hstdout, csbBefore.wAttributes);
#else
	printf("%c[1;33m[WARNING]%c[0;37m %s\n", 27, 27, msg);
#endif
}
