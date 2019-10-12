#pragma once
#include <QObject>

namespace ChatServer
{
	class AbstractClient : public QObject
	{
	public:
		AbstractClient(QObject* parent = nullptr) : QObject(parent)
		{
		}

		virtual ~AbstractClient()
		{
		};

		// Write and send a message to the client
		virtual void writeMessage(const QString& p_message) = 0;

	signals:
		// Emitted when a new message has been received from the client
		virtual void newMessage(QString) = 0;

		// Emitted when the client disconnects
		virtual void disconnected() = 0;
	};
}
