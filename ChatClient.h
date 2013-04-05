#ifndef CHATCLIENT_H
#define	CHATCLIENT_H

#include "AudioHelper.h"

#include <QUdpSocket>
#include <QNetworkInterface>
#include <QTimer>

class ChatClient : public QObject {
	Q_OBJECT
	
	QUdpSocket udpSocket;
	QHostAddress myAddress;
	QString myNickname;
	QTimer sendTimer;
	AudioHelper audio;
	
	static const int PORT = 4815;
	QString PING;
	QString HELLO;
	QString BYE;
	QString AUDIO;
	static const int SEND_PERIOD = 100;
	
private slots:
	void processPendingDatagrams();
	void sendAudio();
	
public:
	ChatClient();
	void join(const QString&);
	void leave();
	void startSendingAudio();
	void stopSendingAudio();
	void updateUserList();
	
signals:
	void userConnected(const QHostAddress&, const QString&);
	void userDisconnected(const QHostAddress&);
	void noNetwork();
};

#endif	/* CHATCLIENT_H */