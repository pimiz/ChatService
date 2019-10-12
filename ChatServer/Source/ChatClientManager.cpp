#include "ChatClientManager.h"
#include "AbstractClient.h"
#include <iostream>

namespace ChatServer
{
	ChatClientManager::ChatClientManager(QObject* parent) : QObject(parent)
	{
	}


	ChatClientManager::~ChatClientManager()
	{
	}

	void ChatClientManager::addClient(std::shared_ptr<AbstractClient> p_client)
	{
		connect(p_client.get(), SIGNAL(newMessage(QString)), this, SLOT(onNewMessage(QString)));
		connect(p_client.get(), SIGNAL(disconnected()), this, SLOT(onClientDisconnected()));
		_clients.push_back(std::move(p_client));
	}

	void ChatClientManager::broadcastMessage(const QString& p_message) const
	{
		for (auto& client : _clients)
		{
			client->writeMessage(p_message);
		}
	}

	void ChatClientManager::onNewMessage(QString p_message)
	{
		broadcastMessage(p_message);
	}

	void ChatClientManager::onClientDisconnected()
	{
		std::cout << "Client disconnected..." << std::endl;
		for (int i = 0; i < _clients.size(); ++i)
		{
			if (_clients[i].get() == sender())
			{
				_clients.removeAt(i);
				break;
			}
		}
	}

	int ChatClientManager::clientCount() const
	{
		return _clients.size();
	}

	std::shared_ptr<AbstractClient> ChatClientManager::getClient(int p_index)
	{
		if (p_index < 0 || p_index > _clients.size() - 1)
		{
			return std::shared_ptr<AbstractClient>();
		}
		return _clients[p_index];
	}
}
