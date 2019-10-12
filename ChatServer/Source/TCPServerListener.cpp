#include "TCPServerListener.h"
#include "ChatClientConnectionFactory.h"
#include <QTcpSocket>
#include <iostream>

namespace ChatServer
{
	TCPServerListener::TCPServerListener(QObject* parent) : AbstractServerListener(parent)
	{
		connect(&_tcpServer, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
	}


	TCPServerListener::~TCPServerListener()
	{
	}

	bool TCPServerListener::startListening(int p_port)
	{
		return _tcpServer.listen(QHostAddress::Any, p_port);
	}

	void TCPServerListener::stopListening()
	{
		_tcpServer.close();
	}

	bool TCPServerListener::isListening() const
	{
		return _tcpServer.isListening();
	}

	void TCPServerListener::onNewConnection()
	{
		std::cout << "New client connection..." << std::endl;

		std::shared_ptr<AbstractClient> client = {};
		try
		{
			client = ChatClientConnectionFactory::createClient<QTcpSocket>(_tcpServer.nextPendingConnection());
		}
		catch (std::exception& e)
		{
			std::cerr << "ERROR in creating chat client: " << e.what() << std::endl;
			return;
		}
		emit newClientConnection(client);
	}
}
