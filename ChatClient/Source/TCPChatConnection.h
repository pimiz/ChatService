#pragma once
#include "AbstractChatConnection.h"
#include <memory>
// Below has to be done since MockQTcpSocket mocks QTcpSocket methods which are
// non-virtual, and thus MockQTcpSocket methods won't get invoked if called via QTcpSocket*
// (same case with QDataStream).
#ifdef WITH_GTEST
namespace ChatServiceUnitTests
{
	class MockQDataStream;
	class MockQTcpSocket;
}

using TCPSocketType = ChatServiceUnitTests::MockQTcpSocket;
using DataStreamType = ChatServiceUnitTests::MockQDataStream;

namespace ChatServiceUnitTests
{
	class TCPChatConnectionTest;
}
#else
class QDataStream;
class QTcpSocket;
using TCPSocketType = QTcpSocket;
using DataStreamType = QDataStream;
#endif

namespace ChatClient
{
	class TCPChatConnection :
		public AbstractChatConnection
	{
	Q_OBJECT

#ifdef WITH_GTEST
		friend class ChatServiceUnitTests::TCPChatConnectionTest;
#endif
	public:
		TCPChatConnection(QObject* parent = nullptr);
		~TCPChatConnection();

		// Connect to TCP chat host
		bool connectToServer(const QString& p_host, int p_port) override;

		// Set the QTcpSocket (or MockQTcpSocket if testing) and deletes the default one. Takes ownership.
		void setSocket(std::shared_ptr<TCPSocketType> p_socket);

	signals:
		// Emits when a new message has been received from TCP chat server
		void newMessage(QString) override;

	public slots:
		// Send a TCP chat message
		void sendMessage(QString p_message) override;

		// Gets called when TCP socket is ready for reading
		void onReadyRead();

		// Disconnect from TCP chat host
		void disconnect() override;

		// Is the client connected to TCP chat host
		bool isConnected() const override;

		// Gets called when connection is lost
		void onDisconnect() override;

	private:
		// Disable copy ctor and assignment operator
		TCPChatConnection(const TCPChatConnection&) = delete;
		TCPChatConnection operator=(const TCPChatConnection&) = delete;

		// The socket used to connect to chat server
		std::shared_ptr<TCPSocketType> _tcpSocket;

		// Data stream to read from chat server
		std::shared_ptr<DataStreamType> _inStream;
	};
}
