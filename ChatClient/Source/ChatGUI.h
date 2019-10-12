#pragma once

#include <QWidget>
#include <memory>
#include "GeneratedFiles/ui_ChatGUI.h"

namespace ChatClient
{
	class AbstractChatConnection;

	class ChatGUI : public QWidget
	{
	Q_OBJECT

	public:
		virtual ~ChatGUI() = default;
		ChatGUI(QWidget* parent = Q_NULLPTR);
		ChatGUI(AbstractChatConnection const* p_client, QWidget* parent = Q_NULLPTR);

		// TODO uniqptr ei "saa" laittaa referenssin‰, onks t‰‰ parempi sit?
		virtual void setClientConnection(AbstractChatConnection const* p_client);

		// Static factory method for convenience
		static std::unique_ptr<ChatGUI> create(QWidget* parent = Q_NULLPTR,
		                                       AbstractChatConnection const* p_client = Q_NULLPTR);

	protected:
		bool eventFilter(QObject* obj, QEvent* event) override;

	signals:
		// Emits when a new chat message is about to be sent to server
		void submitMessage(QString);

	public slots:
		// Show a message on UI
		virtual void showMessage(QString p_message);

		// Gets called when send button has been clicked
		void onSendClicked();

	private:
		Ui::ChatGUI ui;

		//Q_DISABLE_COPY_MOVE(ChatClient::ChatGUI)
	};
}
