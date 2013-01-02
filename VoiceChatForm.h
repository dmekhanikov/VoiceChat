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
	Ui::VoiceChatForm widget;
	ChatClient chat;
	std::map<QString, QString> users;
	void updateUserList();
private slots:
	void join();
	void leave();
	void userConnected(QHostAddress, QString);
	void userDisconnected(QHostAddress);
};

#endif	/* _VOICECHATFORM_H */
