#include "ChatClient.h"

ChatClient::ChatClient() {
	PING = "PING";
	HELLO = "HELLO ";
	BYE = "BYE";
	AUDIO = "AUDIO ";
	connect(&udpSocket, SIGNAL(readyRead()),
			this, SLOT(processPendingDatagrams()));
	connect(&sendTimer, SIGNAL(timeout()), this, SLOT(sendAudio()));
}

void ChatClient::join(const QString &nickname) {
	myNickname = nickname;
	if (udpSocket.state() == QUdpSocket::UnconnectedState) {
		udpSocket.bind(PORT);
	}
	QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
	int addrNo = 0;
	while (!addresses.at(addrNo).toString().startsWith("192.168.")) {
		++addrNo;
	}
	myAddress = QNetworkInterface::allAddresses().at(addrNo);
	QString helloMessage = HELLO + nickname;
	udpSocket.writeDatagram(helloMessage.toAscii(), QHostAddress::Broadcast, PORT);
	udpSocket.writeDatagram(PING.toAscii(), QHostAddress::Broadcast, PORT);
	startSendingAudio();
}

void ChatClient::leave() {
	stopSendingAudio();
	udpSocket.writeDatagram(BYE.toAscii(), QHostAddress::Broadcast, PORT);
	udpSocket.close();
}

void ChatClient::startSendingAudio() {
	audio.startRecording();
	sendTimer.start(SEND_PERIOD);
}

void ChatClient::stopSendingAudio() {
	audio.stopRecording();
	sendTimer.stop();
}

void ChatClient::updateUserList() {
	udpSocket.writeDatagram(PING.toAscii(), QHostAddress::Broadcast, PORT);
}

void ChatClient::processPendingDatagrams() {
	while (udpSocket.hasPendingDatagrams()) {
		QByteArray datagram;
		datagram.resize(udpSocket.pendingDatagramSize());
		QHostAddress sender;
		udpSocket.readDatagram(datagram.data(), datagram.size(), &sender);
		if (datagram == PING) {
			QString response = HELLO + myNickname;
			udpSocket.writeDatagram(response.toAscii(), sender, PORT);
		} else if (datagram.startsWith(HELLO.toAscii())) {
			emit userConnected(sender, datagram.right(datagram.size() - HELLO.size()));
		} else if (datagram == BYE) {
			emit userDisconnected(sender);
		} else if (sender != myAddress && datagram.startsWith(AUDIO.toAscii())) {
			QByteArray audioSource = datagram.right(datagram.size() - AUDIO.size());
			audio.play(audio.decode(audioSource));
		}
	}
}

void ChatClient::sendAudio() {
	QByteArray audioData = audio.read();
	if (!audioData.isEmpty()) {
		QByteArray audioMessage = AUDIO.toAscii();
		audioMessage.append(audio.encode(audioData));
		udpSocket.writeDatagram(audioMessage, QHostAddress::Broadcast, PORT);
	}
}