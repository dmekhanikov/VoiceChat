#ifndef AUDIOHELPER_H
#define	AUDIOHELPER_H

#include "soundio/asoundpp.hpp"
#include "soundio/input_device.hpp"
#include "soundio/output_device.hpp"
#include "soundio/speex_encoder.hpp"
#include "soundio/speex_decoder.hpp"
#include <speex/speex.h>

#include <vector>

class AudioHelper {
	asound::global_config_cleanup cleanup;
	frame_format *format;
	input_device *in;
    output_device *out;
	speex_encoder encoder;
	speex_decoder decoder;
	
public:
	AudioHelper();
	~AudioHelper();
	std::vector<char> read();
	void play(const char*, size_t size);
};

#endif	/* AUDIOHELPER_H */

