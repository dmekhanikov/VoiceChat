#ifndef AUDIOHELPER_H
#define	AUDIOHELPER_H

#include "soundio/asoundpp.hpp"
#include "soundio/input_device.hpp"
#include "soundio/output_device.hpp"
#include "soundio/speex_encoder.hpp"
#include "soundio/speex_decoder.hpp"

#include <QByteArray>
#include <QHostAddress>

#include <map>

class AudioHelper : public QObject {
	Q_OBJECT

	frame_format *format;
	input_device *in;
	speex_encoder *enc;
	speex_decoder *dec;
	asound::global_config_cleanup cleanup;
	static const size_t MAX_AUDIO_SIZE = 5120;
	std::map<QString, output_device*> users;
	
public:
	AudioHelper();
	~AudioHelper();
	void startRecording();
	void stopRecording();
	QByteArray encode(const QByteArray&);
	QByteArray decode(const QByteArray&);
	QByteArray read();
	void play(const QByteArray&, const QString&);
	
public slots:
	void userConnected(const QHostAddress&);
	void userDisconnected(const QHostAddress&);
};

#endif	/* AUDIOHELPER_H */