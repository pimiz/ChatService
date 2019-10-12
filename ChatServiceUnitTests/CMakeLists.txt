project(ChatServiceUnitTests)

enable_testing()
if(WIN32)
	set(GTEST_BUILD "C:/code/googletest-release-1.8.1/googletest_build")
	set(GTEST_LIBRARY_DEBUG "${GTEST_BUILD}/Debug/gtestd.lib")
	set(GTEST_LIBRARY "${GTEST_BUILD}/Release/gtest.lib")
	set(GTEST_MAIN_LIBRARY_DEBUG "${GTEST_BUILD}/Debug/gtest_maind.lib")
	set(GTEST_MAIN_LIBRARY "${GTEST_BUILD}/Release/gtest_main.lib")
	set(GTEST_INCLUDE_DIR "C:/code/googletest-release-1.8.1/googletest/include")
	set(GMOCK_BUILD "C:/code/googletest-release-1.8.1/googlemock_build")
	set(GMOCK_LIBRARY_DEBUG "${GMOCK_BUILD}/Debug/gmockd.lib")
	set(GMOCK_LIBRARY_RELEASE "${GMOCK_BUILD}/Release/gmock.lib")
	set(GMOCK_MAIN_LIBRARY_DEBUG "${GMOCK_BUILD}/Debug/gmock_maind.lib")
	set(GMOCK_MAIN_LIBRARY_RELEASE "${GMOCK_BUILD}/Release/gmock_main.lib")
	set(GMOCK_INCLUDE_DIR "C:/code/googletest-release-1.8.1/googlemock/include")
elseif(UNIX)	
	set(GMOCK_LIBRARY "/usr/lib/libgmock.a")
	set(GMOCK_MAIN_LIBRARY "/usr/lib/libgmock_main.a")
	set(GMOCK_INCLUDE_DIR "/usr/include/gmock")
endif(WIN32)
find_package(GTest REQUIRED)

set(CHATSERVICEUNITTESTS_SRCS 	
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/TestCases/ChatClientManagerTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/TestCases/TCPChatConnectionTest.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/TestCases/MessageReceiver.cpp")
	
set(CHATSERVICEUNITTESTS_HDRS 
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/TestCases/ChatClientTest.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/TestCases/ChatClientManagerTest.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/TestCases/TCPChatConnectionTest.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/TestCases/MessageReceiver.h")		
	
set(CHATSERVICEUNITTESTS_MOCKS
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/Mocks/MockClient.h"	
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/Mocks/MockQTcpSocket.h"	
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/Mocks/MockQDataStream.h")
	
source_group("ChatClient" FILES  ${CHATCLIENT_HDRS} ${CHATCLIENT_SRCS})
source_group("ChatServer" FILES ${CHATSERVER_HDRS} ${CHATSERVER_SRCS})
source_group("Mocks" FILES ${CHATSERVICEUNITTESTS_MOCKS})
source_group("TestCases" FILES ${CHATSERVICEUNITTESTS_HDRS} ${CHATSERVICEUNITTESTS_SRCS})
	
add_compile_definitions(WITH_GTEST)

add_executable(ChatServiceUnitTests 
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/test.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/pch.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/Source/pch.cpp"
	${CHATSERVICEUNITTESTS_HDRS} 
	${CHATSERVICEUNITTESTS_SRCS}
	${CHATSERVICEUNITTESTS_MOCKS}
	${CHATCLIENT_HDRS}
	${CHATCLIENT_SRCS}
	${CHATSERVER_HDRS}
	${CHATSERVER_SRCS}
	)	
target_include_directories(ChatServiceUnitTests PUBLIC ${CHATSERVICE_ROOT})
target_include_directories(ChatServiceUnitTests PUBLIC "${CHATCLIENT_ROOT}/Source")
target_include_directories(ChatServiceUnitTests PUBLIC ${CHATCLIENT_AUTOGEN_DIR})
target_include_directories(ChatServiceUnitTests PUBLIC "${CHATSERVER_ROOT}/Source")
target_include_directories(ChatServiceUnitTests PUBLIC ${CHATSERVER_AUTOGEN_DIR})
target_include_directories(ChatServiceUnitTests PUBLIC ${GMOCK_INCLUDE_DIR})
#explicitly include own source directory so that the testable units will find mock headers
target_include_directories(ChatServiceUnitTests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Source/")	

set_target_properties(ChatServiceUnitTests PROPERTIES
            CXX_STANDARD 14
            )
			
target_link_libraries(ChatServiceUnitTests Qt5::Core Qt5::Network Qt5::Gui Qt5::Widgets)
target_link_libraries(ChatServiceUnitTests GTest::GTest GTest::Main)
if(WIN32)
target_link_libraries(ChatServiceUnitTests debug ${GMOCK_LIBRARY_DEBUG} ${GMOCK_MAIN_LIBRARY_DEBUG})
target_link_libraries(ChatServiceUnitTests optimized ${GMOCK_LIBRARY_RELEASE} ${GMOCK_MAIN_LIBRARY_RELEASE})
elseif(UNIX)
target_link_libraries(ChatServiceUnitTests ${GMOCK_LIBRARY} ${GMOCK_MAIN_LIBRARY})
endif(WIN32)