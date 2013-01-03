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

std::vector<char> AudioHelper::read() {
	size_t size = in->get_available();
	if (size == 0) {
		size = 1;
	} else if (size > 8192) {
		size = 8192;
	}
	std::vector<char> res(size * in->get_format().frame_size());
	in->read(&res[0], size);
	return res;
}

void AudioHelper::play(const char *data, size_t size) {
	out->write(data, size / in->get_format().frame_size());
}