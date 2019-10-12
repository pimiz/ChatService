cmake_minimum_required(VERSION 3.12.4)
project(ChatService)

#find Qt5 and related packages
if (WIN32)
	set(Qt5_DIR "C:/Qt/5.13/5.13.1/msvc2017_64/lib/cmake/Qt5")
elseif (UNIX)
	set(CMAKE_CXX_STANDARD 17 CACHE INTERNAL "")
	set(CMAKE_CXX_STANDARD_REQUIRED ON CACHE INTERNAL "")
	set(CMAKE_CXX_EXTENSIONS OFF CACHE INTERNAL "")
endif (WIN32)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Network REQUIRED)
find_package(Qt5 COMPONENTS Gui REQUIRED)
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CHATSERVICE_ROOT ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")
add_subdirectory(ChatClient)
add_subdirectory(ChatServer)
add_subdirectory(ChatServiceUnitTests)

