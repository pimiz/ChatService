#pragma once
#include "AbstractClient.h"

// These classes really do nothing, they are solely for demonstration purposes

namespace ChatServer
{
	class DummySocket
	{
	public:
		DummySocket() = default;
	};

	class DummyClient : public AbstractClient
	{
	Q_OBJECT

	public:
		DummyClient(DummySocket* p_socket, QObject* parent = nullptr): AbstractClient(parent)
		{
			Q_UNUSED(p_socket);
		}

		~DummyClient() = default;

		// Disable copy ctor and assignment operator
		DummyClient(const DummyClient&) = delete;
		DummyClient operator=(const DummyClient&) = delete;

		void writeMessage(const QString& p_message) override
		{
		}

	signals:
		void newMessage(QString) override;
		void disconnected() override;
	};
}
