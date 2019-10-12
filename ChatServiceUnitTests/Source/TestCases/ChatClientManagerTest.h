#pragma once
#include "gtest/gtest.h"
#include <memory>
using namespace testing;

namespace ChatServer
{
	class ChatClientManager;
}

namespace ChatServiceUnitTests
{
	class ChatClientManagerTest : public Test
	{
	public:
		ChatClientManagerTest() = default;
		virtual ~ChatClientManagerTest() = default;
		virtual void addClients(int p_numOfClientsToAdd);

	protected:
		void SetUp() override;
		void TearDown() override;

		std::unique_ptr<ChatServer::ChatClientManager> _chatClientManager;
	};
}
