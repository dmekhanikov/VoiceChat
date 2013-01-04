#ifndef _VOICECHATFORM_H
#define	_VOICECHATFORM_H

#include "ui_VoiceChatForm.h"
#include "ChatClient.h"

#include <map>

class VoiceChatForm : public QDialog {
	Q_OBJECT
public:
	VoiceChatForm();
	virtual ~VoiceChatForm();
private:
	QTimer updateTimer;
	static const int UPDATE_PERIOD = 60;
	
	Ui::VoiceChatForm widget;
	ChatClient chat;
	std::map<QString, QString> users;
	void addUserToListWidget(const QString&);
	void deleteUserFromListWidget(const QString&);
private slots:
	void join();
	void leave();
	void userConnected(const QHostAddress&, const QString&);
	void userDisconnected(const QHostAddress&);
	void updateUsers();
	void nicknameEditTextChanged(const QString&);
};

#endif	/* _VOICECHATFORM_H */