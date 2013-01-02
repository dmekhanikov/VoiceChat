#include "VoiceChatForm.h"

VoiceChatForm::VoiceChatForm() {
	widget.setupUi(this);
	connect(&chat, SIGNAL(userConnected(QHostAddress, QString)),
			this, SLOT(userConnected(QHostAddress, QString)));
	connect(&chat, SIGNAL(userDisconnected(QHostAddress)),
			this, SLOT(userDisconnected(QHostAddress)));
	connect(&updateTimer, SIGNAL(timeout()), this, SLOT(updateUsers()));
	connect(widget.connectButton, SIGNAL(clicked()), this, SLOT(join()));
	connect(widget.disconnecButton, SIGNAL(clicked()), this, SLOT(leave()));
}

VoiceChatForm::~VoiceChatForm() {
	chat.leave();
}

void VoiceChatForm::updateUserListWidget() {
	widget.userList->clear();
	for (std::map<QString, QString>::const_iterator iter = users.begin();
			iter != users.end(); ++iter) {
		widget.userList->addItem(iter->second);
	}
}

void VoiceChatForm::join() {
	chat.join(widget.nicknameEdit->text());
	widget.nicknameEdit->setReadOnly(true);
	widget.connectButton->setEnabled(false);
	widget.disconnecButton->setEnabled(true);
	updateTimer.start(UPDATE_PERIOD * 1000);
}

void VoiceChatForm::leave() {
	chat.leave();
	widget.nicknameEdit->setReadOnly(false);
	widget.connectButton->setEnabled(true);
	widget.disconnecButton->setEnabled(false);
	widget.userList->clear();
	updateTimer.stop();
}

void VoiceChatForm::userConnected(QHostAddress IP, QString nickname) {
	users[IP.toString()] = nickname;
	updateUserListWidget();
}

void VoiceChatForm::userDisconnected(QHostAddress IP) {
	users.erase(IP.toString());
	updateUserListWidget();
}

void VoiceChatForm::updateUsers() {
	users.clear();
	chat.updateUserList();
	updateTimer.start(UPDATE_PERIOD * 1000);
}
