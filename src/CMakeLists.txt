add_library(httprequest04rel SHARED
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

if(BUILD_64)
	target_compile_options(httprequest04rel PRIVATE -D_SQ64)
endif()

target_include_directories(httprequest04rel
	PRIVATE
		${PROJECT_SOURCE_DIR}/src
		${PROJECT_SOURCE_DIR}/include
		${CPR_INCLUDE_DIRS}
)

if(CURL_STATICLIB)
	target_compile_definitions(${CPR_LIBRARIES} PUBLIC CURL_STATICLIB)
endif()
		
target_link_libraries(httprequest04rel ${CPR_LIBRARIES})