#pragma once
#include "gmock/gmock.h"
#include "AbstractClient.h"

namespace ChatServiceUnitTests
{
	class MockClient : public ChatServer::AbstractClient
	{
	Q_OBJECT

	public:
		MockClient(QObject* parent = nullptr): AbstractClient(parent)
		{
		}

		virtual ~MockClient()
		{
		}

		MOCK_METHOD1(writeMessage, void(const QString& p_message));

	signals:
		void newMessage(QString) override;
		void disconnected() override;
	};
}
