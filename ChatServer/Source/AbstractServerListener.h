#pragma once
#include <qobject.h> // QObject
#include <memory> // shared_ptr

namespace ChatServer
{
	class AbstractClient;

	class AbstractServerListener : public QObject
	{
	public:
		AbstractServerListener(QObject* parent = nullptr) : QObject(parent)
		{
		}

		virtual ~AbstractServerListener()
		{
		};

		// Start listening for incoming connections
		virtual bool startListening(int p_port) = 0;

		// Stop listening for incoming connections
		virtual void stopListening() = 0;

		// Is the server currently listening
		virtual bool isListening() const = 0;

	signals:
		// Emit this signal when a new connection has been received
		virtual void newClientConnection(std::shared_ptr<AbstractClient> p_client) = 0;
	};
}
