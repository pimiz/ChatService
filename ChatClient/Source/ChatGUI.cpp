#include "ChatGUI.h"
#include "AbstractChatConnection.h"
#include <QKeyEvent>

namespace ChatClient
{
	ChatGUI::ChatGUI(QWidget* parent)
		: QWidget(parent)
	{
		ui.setupUi(this);
		connect(ui.sendButton, SIGNAL(clicked()), this, SLOT(onSendClicked()));
		this->setStyleSheet("font-size: 20px;");
		this->installEventFilter(this);
	}

	ChatGUI::ChatGUI(AbstractChatConnection const* p_client, QWidget* parent) : ChatGUI(parent)
	{
		setClientConnection(p_client);
	}

	std::unique_ptr<ChatGUI> ChatGUI::create(QWidget* parent, AbstractChatConnection const* p_client)
	{
		return p_client ? std::make_unique<ChatGUI>(p_client, parent) : std::make_unique<ChatGUI>(parent);
	}

	void ChatGUI::setClientConnection(AbstractChatConnection const* p_client)
	{
		disconnect(this);
		if (p_client)
		{
			connect(this, SIGNAL(submitMessage(QString)), p_client, SLOT(sendMessage(QString)));
			connect(p_client, SIGNAL(newMessage(QString)), this, SLOT(showMessage(QString)));
			connect(this, SIGNAL(destroyed()), p_client, SLOT(disconnect()));
		}
	}

	void ChatGUI::onSendClicked()
	{
		// Read the written message and emit it for sending
		auto message = ui.chatLine->text();
		if (message.length() > 0)
		{
			emit submitMessage(message);
			ui.chatLine->clear();
		}
	}

	void ChatGUI::showMessage(QString p_message)
	{
		// Show message on UI
		ui.chatBrowser->append(p_message);
	}

	// Catch enter keypress to send the message
	bool ChatGUI::eventFilter(QObject* obj, QEvent* event)
	{
		if (event->type() == QEvent::KeyPress)
		{
			QKeyEvent* key = static_cast<QKeyEvent*>(event);
			if ((key->key() == Qt::Key_Enter) || (key->key() == Qt::Key_Return))
			{
				ui.sendButton->click();
				return true;
			}
		}

		return QObject::eventFilter(obj, event);
	}
}
