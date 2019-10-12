#pragma once
#include <memory>

class QTcpSocket;

namespace ChatServer
{
	class AbstractClient;
	class DummySocket;

	class ChatClientConnectionFactory
	{
	public:
		// Create a chat client object.
		// This could be overloaded for all supported connection types
		template <typename T>
		static std::shared_ptr<AbstractClient> createClient(T* p_Socket)
		{
			return createClientPrivate(p_Socket);
		}

		// Disable default ctor, copy ctor and assignment operator
		ChatClientConnectionFactory() = delete;
		ChatClientConnectionFactory(const ChatClientConnectionFactory&) = delete;
		ChatClientConnectionFactory operator=(ChatClientConnectionFactory) = delete;

	private:
		static std::shared_ptr<AbstractClient> createClientPrivate(QTcpSocket* p_tcpSocket);
		static std::shared_ptr<AbstractClient> createClientPrivate(DummySocket* p_dummySocket);
	};
}
