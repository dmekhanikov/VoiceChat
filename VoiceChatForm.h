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
	static const int UPDATE_PERIOD = 10;
	
	Ui::VoiceChatForm widget;
	ChatClient chat;
	std::map<QString, QString> users;
	void updateUserListWidget();
private slots:
	void join();
	void leave();
	void userConnected(QHostAddress, QString);
	void userDisconnected(QHostAddress);
	void updateUsers();
};

#endif	/* _VOICECHATFORM_H */
