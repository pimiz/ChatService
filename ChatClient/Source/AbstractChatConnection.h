#pragma once
#include <QObject>
#include <QString>


namespace ChatClient
{
	// Derive this to create any type of abstracted connection to chat server
	class AbstractChatConnection : public QObject
	{
	public:
		AbstractChatConnection(QObject* parent = nullptr) : QObject(parent)
		{
		}

		virtual ~AbstractChatConnection()
		{
		}

		// Connect to chat host
		virtual bool connectToServer(const QString& p_host, int p_port) = 0;

		// Disconnect from chat host
		virtual void disconnect() = 0;

		// Is the client connected
		virtual bool isConnected() const = 0;

	signals:
		// Emits when a new message has been received from chat server
		virtual void newMessage(QString) = 0;

	public slots:
		// Send a chat message
		virtual void sendMessage(QString p_message) = 0;

		// Gets called when connection is lost
		virtual void onDisconnect() = 0;
	};
}
