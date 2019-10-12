#pragma once
#include <QTcpServer>
#include "AbstractServerListener.h"

namespace ChatServer
{
	class TCPServerListener :
		public AbstractServerListener
	{
	Q_OBJECT

	public:
		TCPServerListener(QObject* parent = nullptr);
		~TCPServerListener();

		// Start listening for incoming TCP connections on given port
		bool startListening(int p_port) override;

		// Stop listening for incoming TCP connections
		void stopListening() override;

		// Is the server currently listening for TCP connections
		bool isListening() const override;

	signals:
		// Emits when a new client connection has been received
		void newClientConnection(std::shared_ptr<AbstractClient> p_client) override;

	public slots:
		// Gets called when the QTcpServer has received a new connection 
		void onNewConnection();

	private:
		// Disable copy ctor and assignment operator
		TCPServerListener(const TCPServerListener&) = delete;
		TCPServerListener operator=(const TCPServerListener&) = delete;

		QTcpServer _tcpServer;
	};
}
