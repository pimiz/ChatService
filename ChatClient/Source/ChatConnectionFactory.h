#pragma once
#include "TCPChatConnection.h"
#include <QApplication>

// This is a templated factory class to create
// chat clients. When adding new types of chat clients, 
// just #include it above

namespace ChatClient
{
	class ChatConnectionFactory
	{
	public:

		// Create a chat client with base interface
		template <typename T>
		static std::shared_ptr<AbstractChatConnection> createClient()
		{
			return std::make_shared<T>(QApplication::instance());
		}

	private:

		//Q_DISABLE_COPY_MOVE(ChatConnectionFactory)
		ChatConnectionFactory() = delete;
	};
}
