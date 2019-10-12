#include <QtCore/QCoreApplication>
#include "ChatGUI.h"
#include "ChatConnectionFactory.h"
#include <iostream>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	// Read command line arguments
	if (a.arguments().count() != 3)
	{
		std::cout << "USAGE: ChatClient.exe <host> <port>" << std::endl;
		return 0;
	}
	QString host = a.arguments().at(1);
	int port = a.arguments().at(2).toInt();

	// Create UI and connection to chat server
	auto ui = ChatClient::ChatGUI::create();
	auto client = ChatClient::ChatConnectionFactory::createClient<ChatClient::TCPChatConnection>();
	ui->setClientConnection(client.get());

	// Connect to chat server
	if (client->connectToServer(host, port))
	{
		std::cout << "Connected to " << host.toStdString() << ":" << port << std::endl;
	}
	else
	{
		std::cerr << "Unable to connect to " << host.toStdString() << ":" << port << std::endl;
		return 0;
	}

	// Show the UI
	ui->show();
	return a.exec();
}
