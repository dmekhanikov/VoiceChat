#ifndef AUDIOHELPER_H
#define	AUDIOHELPER_H

#include "soundio/asoundpp.hpp"
#include "soundio/input_device.hpp"
#include "soundio/output_device.hpp"
#include "soundio/speex_encoder.hpp"
#include "soundio/speex_decoder.hpp"

#include <QByteArray>

class AudioHelper {
	asound::global_config_cleanup cleanup;
	frame_format *format;
	input_device *in;
    output_device *out;
	static const size_t MAX_AUDIO_SIZE = 8192;
	
public:
	AudioHelper();
	~AudioHelper();
	QByteArray read();
	void play(const QByteArray);
};

#endif	/* AUDIOHELPER_H */

