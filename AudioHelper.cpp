#include "AudioHelper.h"

AudioHelper::AudioHelper() {
	format = new frame_format(44100, 1, SOUNDIO_SAMPLE_FORMAT_S16);
    in = new input_device(*format);
    out = new output_device(*format);
}

AudioHelper::~AudioHelper() {
	delete format;
	delete in;
	delete out;
}

QByteArray AudioHelper::read() {
	size_t size = in->get_available();
	if (size == 0) {
		size = 1;
	} else if (size > MAX_AUDIO_SIZE) {
		size = MAX_AUDIO_SIZE;
	}
	QByteArray res(size * format->frame_size(), 0);
	in->read(res.begin(), size);
	return res;
}

void AudioHelper::play(const QByteArray &data) {
	out->write(data, data.size() / format->frame_size());
}