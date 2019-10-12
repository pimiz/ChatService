#pragma once
#include "gmock/gmock.h"
#include <QDataStream>

namespace ChatServiceUnitTests
{
	class MockQDataStream : public QDataStream
	{
	public:

		// originally non-virtual methods
		MOCK_METHOD0(startTransaction, void());
		MOCK_METHOD0(commitTransaction, bool());

		void operator>>(QString& str)
		{
			str.append(_message);
		}

		void setMessage(const QString& p_message)
		{
			_message = p_message;
		}

		MockQDataStream() : QDataStream()
		{
		}

		virtual ~MockQDataStream()
		{
		}

	private:
		QString _message;
	};
}
