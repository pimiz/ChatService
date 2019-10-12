#pragma once
#include "gmock/gmock.h"
#include <QTcpSocket>

namespace ChatServiceUnitTests
{
	class MockQTcpSocket : public QTcpSocket
	{
	public:
		MOCK_METHOD2(connectToHost, void(const QString &hostName, quint16 port));
		MOCK_METHOD1(waitForConnected, bool(int msecs));
		MOCK_METHOD0(disconnectFromHost, void());
		MOCK_METHOD1(waitForBytesWritten, bool(int msecs));

		// originally non-virtual methods
		MOCK_CONST_METHOD0(state, QAbstractSocket::SocketState());
		MOCK_METHOD1(write, qint64(const QByteArray &byteArray));

		MockQTcpSocket(QObject* parent = nullptr) : QTcpSocket(parent)
		{
		}

		virtual ~MockQTcpSocket()
		{
		}
	};
}
