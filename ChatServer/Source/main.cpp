#include <QtCore/QCoreApplication>
#include "ServerListenerFactory.h"
#include "ChatClientConnectionFactory.h"
#include "ChatClientManager.h"
#include "AbstractServerListener.h"
#include <iostream>

int main(int argc, char* argv[])
{
	QCoreApplication a(argc, argv);

	// Read command line arguments
	if (a.arguments().count() != 2)
	{
		std::cout << "USAGE: ChatServer.exe <port>" << std::endl;
		return 0;
	}
	int port = a.arguments().at(1).toInt();

	// Create client manager and server listener
	auto manager = std::make_unique<ChatServer::ChatClientManager>();
	auto serverListener = ChatServer::ServerListenerFactory::createDefaultServerListener();

	// Connect server listener to get notified of new connections
	QObject::connect(serverListener.get(), SIGNAL(newClientConnection(std::shared_ptr<AbstractClient>)), manager.get(),
	                 SLOT(addClient(std::shared_ptr<AbstractClient>)));

	// Start listening for new connections
	if (serverListener->startListening(port))
	{
		std::cout << "Listening for connections on port " << port << std::endl;
	}
	else
	{
		std::cerr << "Unable to start listening on port " << port << "!" << std::endl;
		return 0;
	}

	return a.exec();
}
