#include "TCPChatClient.h"
#include <QByteArray>
#include <QApplication>
#include <QHostAddress>
#include <iostream>

#ifdef WITH_GTEST
#include "Mocks/MockQTcpSocket.h"
#include "Mocks/MockQDataStream.h"
#else
#include <QDataStream>
#include <QTcpSocket>
#endif
namespace ChatClient {
	TCPChatClient::TCPChatClient(QObject *parent) : AbstractChatClient(parent)
	{
		_tcpSocket = std::make_shared<TCPSocketType>(this);
		_inStream = std::make_shared<DataStreamType>();
		setSocket(_tcpSocket);
	}

	TCPChatClient::~TCPChatClient()
	{
	}

	bool TCPChatClient::connectToServer(const QString &p_host, int p_port)
	{
		_tcpSocket->connectToHost(p_host, p_port);
		_tcpSocket->waitForConnected(1000);
		return isConnected();
	}

	void TCPChatClient::disconnect()
	{
		_tcpSocket->disconnectFromHost();
	}

	bool TCPChatClient::isConnected() const
	{
		return (_tcpSocket->state() == QAbstractSocket::ConnectedState);
	}

	void TCPChatClient::onDisconnect()
	{
		std::cout << "Connection lost..." << std::endl;
		QApplication::exit();
	}

	void TCPChatClient::onReadyRead()
	{
		// Read data sent from server
		_inStream->startTransaction();
		QString message;
		*_inStream >> message;
		if (!_inStream->commitTransaction())
		{
			return;
		}
		emit newMessage(message);
	}

	void TCPChatClient::sendMessage(QString p_message)
	{
		if (!isConnected())
		{
			std::cerr << "ERROR: Not connected to server" << std::endl;
			return;
		}

		// Read message to byte array for sending to server
		QByteArray outArr;
		QDataStream out(&outArr, QIODevice::WriteOnly);

		out << p_message;
		auto bytesWritten = _tcpSocket->write(outArr);

		if (bytesWritten == -1 || _tcpSocket->waitForBytesWritten(1000) == false)
		{
			std::cerr << "ERROR: Unable to send message" << std::endl;
		}
	}
	
void TCPChatClient::setSocket(std::shared_ptr<TCPSocketType> p_socket)
{
		Q_ASSERT(p_socket->socketType() == QAbstractSocket::TcpSocket);
		
		// Disconnect signals from old socket
		if (_tcpSocket.get())
		{
			QObject::disconnect(_tcpSocket.get());
		}
		_tcpSocket = p_socket;
		QObject::connect(_tcpSocket.get(), SIGNAL(readyRead()), this, SLOT(onReadyRead()));
		QObject::connect(_tcpSocket.get(), SIGNAL(disconnected()), this, SLOT(onDisconnect()));
		_inStream->setDevice(_tcpSocket.get());
	}
}