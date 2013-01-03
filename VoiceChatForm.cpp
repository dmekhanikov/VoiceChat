#include "VoiceChatForm.h"

VoiceChatForm::VoiceChatForm() {
	widget.setupUi(this);
	connect(&chat, SIGNAL(userConnected(const QHostAddress&, const QString&)),
			this, SLOT(userConnected(const QHostAddress&, const QString&)));
	connect(&chat, SIGNAL(userDisconnected(const QHostAddress&)),
			this, SLOT(userDisconnected(const QHostAddress&)));
	connect(&updateTimer, SIGNAL(timeout()), this, SLOT(updateUsers()));
	connect(widget.connectButton, SIGNAL(clicked()), this, SLOT(join()));
	connect(widget.disconnecButton, SIGNAL(clicked()), this, SLOT(leave()));
	connect (widget.nicknameEdit, SIGNAL(textChanged(const QString&)), 
			this, SLOT(nicknameEditTextChanged(const QString&)));
}

VoiceChatForm::~VoiceChatForm() {
	chat.leave();
}

void VoiceChatForm::addUserToListWidget(const QString &nickname) {
	int l = -1, r = widget.userList->count(), mid;
	while (r - l > 1) {
		mid = l + (r - l) / 2;
		if (widget.userList->item(mid)->text() <= nickname) {
			l = mid;
		} else {
			r = mid;
		}
	}
	widget.userList->insertItem(r, nickname);
}

void VoiceChatForm::deleteUserFromListWidget(const QString &nickname) {
	int l = -1, r = widget.userList->count(), mid;
	while (r - l > 1) {
		mid = l + (r - l) / 2;
		if (widget.userList->item(mid)->text() <= nickname) {
			l = mid;
		} else {
			r = mid;
		}
	}
	if (l < widget.userList->count()) {
		delete widget.userList->takeItem(l);
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
	users.clear();
	updateTimer.stop();
}

void VoiceChatForm::userConnected(const QHostAddress &IP, const QString &nickname) {
	if (users.count(IP.toString())) {
		deleteUserFromListWidget(nickname);
	}
	users[IP.toString()] = nickname;
	addUserToListWidget(nickname);
}

void VoiceChatForm::userDisconnected(const QHostAddress &IP) {
	std::map<QString, QString>::iterator iter = users.find(IP.toString());
	if (iter != users.end()) {
		deleteUserFromListWidget(iter->second);
		users.erase(iter);
	}
}

void VoiceChatForm::updateUsers() {
	users.clear();
	widget.userList->clear();
	chat.updateUserList();
	updateTimer.start(UPDATE_PERIOD * 1000);
}

void VoiceChatForm::nicknameEditTextChanged(const QString& text) {
	if (text.isEmpty()) {
		widget.connectButton->setEnabled(false);
	} else {
		widget.connectButton->setEnabled(true);
	}
} 