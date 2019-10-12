#pragma once
#include "gtest/gtest.h"
#include "ChatClientTest.h"
#include "ChatClient/Source/TCPChatConnection.h"
#include "Mocks/MockQTcpSocket.h"
#include "Mocks/MockQDataStream.h"
#include "MessageReceiver.h"
#include <random>
#include <chrono>
#include <algorithm>
#include <memory>

namespace ChatServiceUnitTests
{
	class TCPChatConnectionTest : public ChatClientTest
	{
	public:
		TCPChatConnectionTest();
		virtual ~TCPChatConnectionTest() = default;
		QString getHost() const;
		int getPort() const;
		bool connect() override;
		void disconnect() override;
		bool isConnected() const override;
		void sendMessage(const QString& p_message) override;
		// not just a setter
		virtual void replaceDataStream(std::shared_ptr<MockQDataStream> p_dataStream);

	protected:
		void SetUp() override;
		void TearDown() override;
		std::shared_ptr<ChatClient::TCPChatConnection> _TCPChatConnection;
		QString _host;
		int _port;
		std::shared_ptr<MockQTcpSocket> _mockQTcpSocket;
	};
}
