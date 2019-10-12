#pragma once
#include "AbstractClient.h"
#include <QTcpSocket>
#include <QDataStream>
#include <memory> // unique_ptr

namespace ChatServer
{
	class TCPClient :
		public AbstractClient
	{
	Q_OBJECT

	public:
		TCPClient(QTcpSocket* p_socket, QObject* parent = nullptr);
		~TCPClient();

		// Disable copy ctor and assignment operator
		TCPClient(const TCPClient&) = delete;
		TCPClient operator=(const TCPClient&) = delete;

		// Write and send a message to TCP client
		void writeMessage(const QString& p_message) override;

	signals:
		// Emitted when a new message has been received from the client
		void newMessage(QString) override;

		// Emitted when the client disconnects
		void disconnected() override;

	public slots:
		// Gets called when the TCP socket is ready for reading
		void onReadyRead();

	private:
		QTcpSocket* _tcpSocket; // Cannot wrap this to smart pointer since it is managed by Qt
		QDataStream _inStream;
	};
}
