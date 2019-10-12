#include "TCPChatConnectionTest.h"
#include "ChatClient/Source/ChatConnectionFactory.h"
#include <QApplication>

using namespace ::testing;	

namespace ChatServiceUnitTests
{
	TCPChatConnectionTest::TCPChatConnectionTest():
		_host(QString()),
		_port(-1)
	{
		// Create "fake" command line arguments
		int argc = 3;
		char* argv[3] = { "ChatClient.exe", "localhost", "1337" };
		
		// Construct a QApplication
		QApplication app(argc, &argv[0]);

		// Store given host and port values
		_host = argv[1];
		_port = atoi(argv[2]);
	}
		
	void TCPChatConnectionTest::SetUp()
	{
		// Construct an instance of Chat TCP Client and cast it to its native interface.
		auto baseClient = ChatClient::ChatConnectionFactory::createClient<ChatClient::TCPChatConnection>();
		if (!baseClient)
		{
			// ERROR
		}
		_TCPChatConnection = std::dynamic_pointer_cast<ChatClient::TCPChatConnection, ChatClient::AbstractChatConnection>(baseClient);
		_mockQTcpSocket = std::make_shared<MockQTcpSocket>();
		_TCPChatConnection->setSocket(_mockQTcpSocket);
	}

	void TCPChatConnectionTest::TearDown()
	{
		_TCPChatConnection.reset();
	}
	
	QString TCPChatConnectionTest::getHost() const
	{
		return _host;
	}

	int TCPChatConnectionTest::getPort() const
	{
		return _port;
	}

	bool TCPChatConnectionTest::connect() 
	{
		return _TCPChatConnection->connectToServer(getHost(), getPort());
	}

	void TCPChatConnectionTest::disconnect() 
	{
		_TCPChatConnection->disconnect();
	}

	bool TCPChatConnectionTest::isConnected() const
	{
		return _TCPChatConnection->isConnected();
	}

	void TCPChatConnectionTest::sendMessage(const QString &p_message)
	{
		_TCPChatConnection->sendMessage(p_message);
	}

	void TCPChatConnectionTest::replaceDataStream(std::shared_ptr<MockQDataStream> p_dataStream)
	{
		p_dataStream->setDevice(_mockQTcpSocket.get());
		_TCPChatConnection->_inStream = p_dataStream;
	}


	TEST_F(TCPChatConnectionTest, CreateConnection)
	{
		// Try to connect when server is not running
		EXPECT_CALL(*_mockQTcpSocket.get(), connectToHost(getHost(), getPort()));
		EXPECT_CALL(*_mockQTcpSocket.get(), waitForConnected(_))
			.WillOnce(Return(false));
		EXPECT_CALL(*_mockQTcpSocket.get(), state())
			.Times(Exactly(2))
			.WillRepeatedly(Return(QAbstractSocket::UnconnectedState));

		EXPECT_FALSE(isConnected());
		EXPECT_FALSE(connect());

		// "Start" the server and try to reconnect
		EXPECT_CALL(*_mockQTcpSocket.get(), connectToHost(getHost(), getPort()));
		EXPECT_CALL(*_mockQTcpSocket.get(), waitForConnected(_))
			.WillOnce(Return(true));
		EXPECT_CALL(*_mockQTcpSocket.get(), state())
			.Times(Exactly(2))
			.WillRepeatedly(Return(QAbstractSocket::ConnectedState));

		EXPECT_TRUE(connect());
		EXPECT_TRUE(isConnected());
	}

	TEST_F(TCPChatConnectionTest, CloseConnection)
	{
		EXPECT_CALL(*_mockQTcpSocket.get(), state())
			.WillOnce(Return(QAbstractSocket::ConnectedState));
		EXPECT_CALL(*_mockQTcpSocket.get(), disconnectFromHost());

		EXPECT_TRUE(isConnected());
		disconnect();

		EXPECT_CALL(*_mockQTcpSocket.get(), state())
			.WillOnce(Return(QAbstractSocket::UnconnectedState));

		EXPECT_FALSE(isConnected());
	}

	TEST_F(TCPChatConnectionTest, SendSingleMessage)
	{
		QString messageToSend("TestMessage");

		// sendMessage writes to cerr on error, so we want to monitor it.	
		internal::CaptureStderr();

		EXPECT_CALL(*_mockQTcpSocket.get(), state())
			.WillOnce(Return(QAbstractSocket::ConnectedState));
		EXPECT_CALL(*_mockQTcpSocket.get(), write(_))
			.WillOnce(Return(QByteArray(messageToSend.toUtf8()).size()));
		EXPECT_CALL(*_mockQTcpSocket.get(), waitForBytesWritten(1000))
			.WillOnce(Return(true));

		sendMessage(messageToSend);

		EXPECT_EQ(internal::GetCapturedStderr().size(), 0);
	}

	TEST_F(TCPChatConnectionTest, SendManyRandomMessages)
	{
		constexpr int amountOfMessages = 100;

		EXPECT_CALL(*_mockQTcpSocket.get(), state())
			.Times(Exactly(amountOfMessages))
			.WillRepeatedly(Return(QAbstractSocket::ConnectedState));
		EXPECT_CALL(*_mockQTcpSocket.get(), waitForBytesWritten(1000))
			.Times(Exactly(amountOfMessages))
			.WillRepeatedly(Return(true));

		std::mt19937 mt_rand;
		auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
		mt_rand.seed(static_cast<unsigned>(seed));

		auto genRandom = [](std::mt19937 & mt, int ls, int rs)
		{
			std::uniform_int_distribution<int> distribution(ls, rs);
			return distribution(mt);
		};

		// sendMessage writes to cerr on error, so we want to monitor it.	
		internal::CaptureStderr();

		for (int i = 0; i < amountOfMessages; ++i)
		{
			std::string randomString(genRandom(mt_rand, 0, 100), ' ');
			std::generate(std::begin(randomString), 
				std::end(randomString),
				[&]() { return '0' + (genRandom(mt_rand, 0, 126)); });
			EXPECT_CALL(*_mockQTcpSocket.get(), write(_))
				.WillOnce(Return(QByteArray(randomString.c_str()).size()));

			sendMessage(QString::fromStdString(randomString));
		}

		EXPECT_EQ(internal::GetCapturedStderr().size(), 0);
	}

	TEST_F(TCPChatConnectionTest, ReceiveMessage)
	{
		auto dataStream = std::make_shared<MockQDataStream>();
		QString message("ShouldReceiveThisMessage");
		dataStream->setMessage(message);
		replaceDataStream(dataStream);
		MessageReceiver msgRcvr;
		QObject::connect(_TCPChatConnection.get(), SIGNAL(newMessage(QString)), &msgRcvr, SLOT(showMessage(QString)));
		EXPECT_CALL(*dataStream, startTransaction());
		EXPECT_CALL(*dataStream, commitTransaction())
			.WillOnce(Return(true));
			
		emit _mockQTcpSocket->readyRead();
		QApplication::processEvents();
		EXPECT_STREQ(message.toStdString().c_str(), msgRcvr._receivedMessage.toStdString().c_str());
	}
}