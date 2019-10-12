#pragma once
#include <memory>

namespace ChatServer
{
	class AbstractServerListener;

	class ServerListenerFactory
	{
	public:
		// Create a server listener of default type.
		static std::unique_ptr<AbstractServerListener> createDefaultServerListener();

		// Create a server listener of given type.
		template <typename T>
		static std::unique_ptr<AbstractServerListener> createServerListener()
		{
			return std::make_unique<T>();
		}

		// Disable default ctor, copy ctor and assignment operator
		ServerListenerFactory() = delete;
		ServerListenerFactory(const ServerListenerFactory&) = delete;
		ServerListenerFactory operator=(const ServerListenerFactory&) = delete;
	};
}
