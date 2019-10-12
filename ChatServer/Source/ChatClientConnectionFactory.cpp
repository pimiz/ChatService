#include "ChatClientConnectionFactory.h"
#include "TCPClient.h"
#include "DummyClient.h"


#include <iostream>


namespace ChatServer
{
	std::shared_ptr<AbstractClient> ChatClientConnectionFactory::createClientPrivate(QTcpSocket* p_tcpSocket)
	{
		if (!p_tcpSocket)
		{
			throw std::runtime_error("Unable to get socket for client!");
		}

		std::shared_ptr<AbstractClient> client;
		try
		{
			client = std::make_shared<TCPClient>(p_tcpSocket);
		}
		catch (std::exception& e)
		{
			throw std::runtime_error(std::string("Unable to create client object: ") + e.what());
		}
		return client;
	}

	std::shared_ptr<AbstractClient> ChatClientConnectionFactory::createClientPrivate(DummySocket* p_dummySocket)
	{
		std::cout << __FUNCTION__ << std::endl;
		return std::make_shared<DummyClient>(p_dummySocket);
	}
}
