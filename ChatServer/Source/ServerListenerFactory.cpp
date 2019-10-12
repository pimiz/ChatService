#include "ServerListenerFactory.h"
#include "TCPServerListener.h"

namespace ChatServer
{
	std::unique_ptr<AbstractServerListener> ServerListenerFactory::createDefaultServerListener()
	{
		// In this implementation the default server listener type is TCP
		return std::make_unique<TCPServerListener>();
	}
}
