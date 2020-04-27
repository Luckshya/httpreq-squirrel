add_library(SqHTTP SHARED
	Misc.h
	Misc.cpp
	CRequest.cpp
	CRequest.h
	CResponse.cpp
	CResponse.h
	CallbackHandler.cpp
	CallbackHandler.h
	includes.h
	main.cpp
	main.h
	SQFunctions.cpp
)

# Force 32-bit binaries when necessary
if(FORCE_32BIT_BIN)
	set_target_properties(SqHTTP PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")
	message("FORCING 32 BIT BINARIES")
endif()

# Size of a pointer in bytes. To identify CPU architecture.
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	target_compile_definitions(SqHTTP PRIVATE _SQ64)
	message("DEFAULTING TO 64 BIT BINARIES")
endif()

# Don't prefix the module binary.
set_target_properties(SqHTTP PROPERTIES PREFIX "")

# Custmize module binary name/
if(WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8 AND NOT FORCE_32BIT_BIN)
		set_target_properties(SqHTTP PROPERTIES OUTPUT_NAME "httprequest04rel64")
	else()
		set_target_properties(SqHTTP PROPERTIES OUTPUT_NAME "httprequest04rel32")
	endif()
else(WIN32)
	if(CMAKE_SIZEOF_VOID_P EQUAL 8 AND NOT FORCE_32BIT_BIN)
		set_target_properties(SqHTTP PROPERTIES OUTPUT_NAME "httprequest04rel64")
	else()
		set_target_properties(SqHTTP PROPERTIES OUTPUT_NAME "httprequest04rel32")
	endif()
endif(WIN32)

target_include_directories(SqHTTP
	PRIVATE
		${PROJECT_SOURCE_DIR}/src
		${PROJECT_SOURCE_DIR}/include
		${CPR_INCLUDE_DIRS}
)

target_compile_definitions(${CPR_LIBRARIES} PUBLIC CURL_STATICLIB)
target_link_libraries(SqHTTP ${CPR_LIBRARIES})