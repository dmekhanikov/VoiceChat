#ifndef AUDIOHELPER_H
#define	AUDIOHELPER_H

#include "soundio/asoundpp.hpp"
#include "soundio/input_device.hpp"
#include "soundio/output_device.hpp"
#include "soundio/speex_encoder.hpp"
#include "soundio/speex_decoder.hpp"

#include <QByteArray>
#include <vector>

class AudioHelper {
	frame_format *format;
	input_device *in;
    output_device *out;
	speex_encoder *enc;
	speex_decoder *dec;
	static const size_t MAX_AUDIO_SIZE = 5120;
	
public:
	AudioHelper();
	~AudioHelper();
	QByteArray encode(const QByteArray&);
	QByteArray decode(const QByteArray&);
	QByteArray read();
	void play(const QByteArray&);
};

#endif	/* AUDIOHELPER_H */