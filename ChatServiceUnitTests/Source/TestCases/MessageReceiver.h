#pragma once
#include <QString>
#include <QObject>

namespace ChatServiceUnitTests
{
	class MessageReceiver : public QObject
	{
	Q_OBJECT

	public:
		QString _receivedMessage;

	public slots:
		virtual void showMessage(QString p_message);
	};
}
