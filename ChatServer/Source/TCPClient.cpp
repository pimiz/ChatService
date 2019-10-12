#include "TCPClient.h"
#include <QByteArray>

namespace ChatServer
{
	TCPClient::TCPClient(QTcpSocket* p_socket, QObject* parent) :
		AbstractClient(parent),
		_tcpSocket(p_socket)
	{
		// Initialize inbound data stream
		_inStream.setDevice(_tcpSocket);
		connect(_tcpSocket, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
		connect(_tcpSocket, SIGNAL(disconnected()), this, SIGNAL(disconnected()));
	}

	TCPClient::~TCPClient()
	{
	}

	void TCPClient::writeMessage(const QString& p_message)
	{
		// Write the message to byte array and send it to the client
		QByteArray outArr;
		QDataStream out(&outArr, QIODevice::WriteOnly);
		out << p_message;
		_tcpSocket->write(outArr);
	}

	void TCPClient::onReadyRead()
	{
		// Read the message from client
		_inStream.startTransaction();
		QString message;
		_inStream >> message;
		if (!_inStream.commitTransaction())
		{
			return;
		}
		emit newMessage(message);
	}
}
