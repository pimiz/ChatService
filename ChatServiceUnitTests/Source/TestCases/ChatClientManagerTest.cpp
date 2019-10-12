#include "ChatClientManagerTest.h"
#include "ChatClientManager.h"
#include "Mocks/MockClient.h"

namespace ChatServiceUnitTests
{
	void ChatClientManagerTest::addClients(const int p_numOfClientsToAdd)
	{
		for (int i = 0; i < p_numOfClientsToAdd; ++i)
		{
			std::shared_ptr<ChatServer::AbstractClient> mockedClient = std::make_shared<MockClient>();
			_chatClientManager->addClient(mockedClient);
		}
	}

	void ChatClientManagerTest::SetUp()
	{
		_chatClientManager = std::make_unique<ChatServer::ChatClientManager>();
	}

	void ChatClientManagerTest::TearDown()
	{
		_chatClientManager.reset();
	}

	TEST_F(ChatClientManagerTest, AddSingleClient)
	{
		addClients(1);
		EXPECT_EQ(_chatClientManager->clientCount(), 1);
	}

	TEST_F(ChatClientManagerTest, AddRandomAmountOfClients)
	{
		qsrand(time(nullptr));
		auto numOfClients = qrand() % 64;
		addClients(numOfClients);
		EXPECT_EQ(_chatClientManager->clientCount(), numOfClients);
	}

	TEST_F(ChatClientManagerTest, EnsureMessageIsBroadcasted)
	{
		const QString messageToBroadcast("This is a message");

		// Create 10 mock clients and check that each of them gets the same msg
		const int numOfClients = 10;
		addClients(numOfClients);
		EXPECT_EQ(_chatClientManager->clientCount(), numOfClients);
		for (int i = 0; i < numOfClients; ++i)
		{
			std::shared_ptr<ChatServer::AbstractClient> client = _chatClientManager->getClient(i);
			std::shared_ptr<MockClient> mockedClient = std::dynamic_pointer_cast<MockClient>(client);
			EXPECT_CALL(*mockedClient.get(), writeMessage(messageToBroadcast))
				.Times(Exactly(1));
		}

		// Make the first client send the message to be broadcasted
		emit _chatClientManager->getClient(0)->newMessage(messageToBroadcast);
	}

	TEST_F(ChatClientManagerTest, DisconnectClient)
	{
		// Create 3 mock clients
		addClients(3);
		EXPECT_EQ(_chatClientManager->clientCount(), 3);

		// Disconnect the middle one
		emit _chatClientManager->getClient(1)->disconnected();
		EXPECT_EQ(_chatClientManager->clientCount(), 2);
	}
}
