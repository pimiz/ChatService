#pragma once
#include <QObject>
#include <QList>
#include <memory>

namespace ChatServer
{
	class AbstractClient;

	class ChatClientManager : public QObject
	{
	Q_OBJECT

	public:
		ChatClientManager(QObject* parent = nullptr);
		~ChatClientManager();

		// Broadcast a message to all connected clients
		void broadcastMessage(const QString& p_message) const;

	public slots:
		// Adds a new client to be managed. Takes the ownership of client object.
		void addClient(std::shared_ptr<AbstractClient> p_client);

		// Gets called when a message has been received from a client
		void onNewMessage(QString p_message);

		// Gets called when a client disconnects
		void onClientDisconnected();

		// Get number of connected clients
		int clientCount() const;

		// Get a client
		std::shared_ptr<AbstractClient> getClient(int p_index);

	private:
		// Disable copy ctor and assignment operator
		ChatClientManager(const ChatClientManager&) = delete;
		ChatClientManager operator=(const ChatClientManager&) = delete;

		// Container for client objects
		QList<std::shared_ptr<AbstractClient>> _clients;
	};
}
