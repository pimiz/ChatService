project(ChatClient)

set(CHATCLIENT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(CHATCLIENT_SRCS 
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/ChatGUI.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/TCPChatConnection.cpp" 
	CACHE INTERNAL "")

set(CHATCLIENT_HDRS 
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/AbstractChatConnection.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/ChatConnectionFactory.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/ChatGUI.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/TCPChatConnection.h"
	CACHE INTERNAL "")	
	
set(CHATCLIENT_UI "ChatGUI.ui")

add_executable(ChatClient "Source/main.cpp" ${CHATCLIENT_HDRS} ${CHATCLIENT_SRCS})

qt5_wrap_ui(${CHATCLIENT_UI})
if (UNIX)
	target_include_directories(ChatClient PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/ChatClient_autogen/include")
endif(UNIX)

set(CHATCLIENT_AUTOGEN_DIR ${AUTOGEN_BUILD_DIR} CACHE INTERNAL "")

#set default command arguments for debugging
set_target_properties(ChatClient PROPERTIES
	VS_DEBUGGER_COMMAND_ARGUMENTS "localhost 1337")

target_link_libraries(ChatClient Qt5::Core)
target_link_libraries(ChatClient Qt5::Network)
target_link_libraries(ChatClient Qt5::Gui)
target_link_libraries(ChatClient Qt5::Widgets)
