cmake_minimum_required (VERSION 3.6)
project(httpreq-squirrel)

# Several plugin options
option(FORCE_32BIT_BIN "Create a 32-bit executable binary if the compiler defaults to 64-bit." OFF)
option(FORCE_DEBUG_BIN "Create debug binary." OFF)

if(FORCE_DEBUG_BIN)
	set(CMAKE_BUILD_TYPE Debug)
	message("Configuring Debug builds.")
else()
	set(CMAKE_BUILD_TYPE Release)
	message("Configuring Release builds.")
endif()

# Enable position independent code
if (UNIX)
	set(CMAKE_POSITION_INDEPENDENT_CODE ON)
	set(USE_SYSTEM_CURL OFF)
	set(CMAKE_USE_OPENSSL ON)
endif()

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