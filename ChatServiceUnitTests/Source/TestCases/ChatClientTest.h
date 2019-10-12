#pragma once
#include <QString>
using namespace testing;

namespace ChatServiceUnitTests
{
	class ChatClientTest : public Test
	{
	public:
		virtual ~ChatClientTest()
		{
		}

		virtual bool connect() = 0;
		virtual void disconnect() = 0;
		virtual bool isConnected() const = 0;
		virtual void sendMessage(const QString& p_message) = 0;
	};
}
