#include "MessageReceiver.h"

namespace ChatServiceUnitTests
{
	void MessageReceiver::showMessage(QString p_message)
	{
		_receivedMessage = p_message;
	}
};
