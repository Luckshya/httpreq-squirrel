cmake_minimum_required (VERSION 3.6)

project(httpreq-squirrel)

option(BUILD_64 "" OFF) 

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(ExternalProject)
include(buildtools/cmake/DownloadProject.cmake)

download_project(
	PROJ           cpr
	GIT_REPOSITORY https://github.com/whoshuu/cpr.git
	GIT_TAG        master
	SOURCE_DIR     ${PROJECT_SOURCE_DIR}/cpr
	UPDATE_DISCONNECTED 1
)

#the cmake test has issues on visual studio so disable them
if(NOT DEFINED BUILD_CPR_TESTS)
	set(BUILD_CPR_TESTS OFF CACHE BOOL "")
endif()

set(BUILD_CURL_EXE OFF CACHE BOOL "")
set(CURL_STATICLIB ON CACHE BOOL "")
set(CURL_ZLIB OFF CACHE BOOL "")

#set what ssl library to use for curl based on OS
#this fixes
if(NOT DEFINED CMAKE_USE_OPENSSL)
	if(WIN32)
		set(CMAKE_USE_WINSSL ON CACHE BOOL "")
		set(CMAKE_USE_OPENSSL OFF CACHE BOOL "")
	elseif(UNIX)
		set(CMAKE_USE_OPENSSL OFF CACHE BOOL "")
	endif()
endif()

if(NOT DEFINED USE_SYSTEM_CURL AND ${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	#using cmake to configure curl on linux has issues
	#so use system curl
	set(USE_SYSTEM_CURL ON CACHE BOOL "")
endif()

add_subdirectory(cpr)
add_subdirectory(src)