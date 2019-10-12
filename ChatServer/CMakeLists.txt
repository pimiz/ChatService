project(ChatServer)

set(CHATSERVER_ROOT ${CMAKE_CURRENT_SOURCE_DIR} CACHE INTERNAL "")

set(CHATSERVER_SRCS 
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/ChatClientConnectionFactory.cpp" 	
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/ChatClientManager.cpp" 
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/ServerListenerFactory.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/TCPClient.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/TCPServerListener.cpp"
	CACHE INTERNAL "")
	
set(CHATSERVER_HDRS
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/AbstractClient.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/AbstractServerListener.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/ChatClientConnectionFactory.h" 	
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/ChatClientManager.h" 
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/DummyClient.h" 
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/ServerListenerFactory.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/TCPClient.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/TCPServerListener.h" 	
	CACHE INTERNAL "")
	
set(CMAKE_AUTOMOC ON)
set(CHATSERVER_AUTOGEN_DIR ${AUTOGEN_BUILD_DIR} CACHE INTERNAL "")
add_executable(ChatServer "Source/main.cpp" ${CHATSERVER_HDRS} ${CHATSERVER_SRCS})

#set default command arguments for debugging
set_target_properties(ChatServer PROPERTIES
	VS_DEBUGGER_COMMAND_ARGUMENTS "1337")

target_link_libraries(ChatServer Qt5::Core)
target_link_libraries(ChatServer Qt5::Network)
target_link_libraries(ChatServer Qt5::Gui)
target_link_libraries(ChatServer Qt5::Widgets)