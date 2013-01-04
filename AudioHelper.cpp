#include "AudioHelper.h"

AudioHelper::AudioHelper() {
	format = new frame_format(44100, 1, SOUNDIO_SAMPLE_FORMAT_S16);
    in = new input_device(*format);
    out = new output_device(*format);
	enc = new speex_encoder(wideband_speex_profile, 5);
	dec = new speex_decoder();
}

AudioHelper::~AudioHelper() {
	delete format;
	delete in;
	delete out;
	delete enc;
	delete dec;
}

QByteArray AudioHelper::encode(const QByteArray& source) {
	QByteArray res;
	for (size_t i = 0; source.size() - i >= enc->block_size() * format->frame_size(); 
			i += enc->block_size() * format->frame_size()) {
		enc->encode(source.begin() + i);
		size_t size = enc->get_encoded_size();
		res.append(size);
		res.append(QByteArray((const char*)enc->get_encoded_data(), size));
	}
	return res;
}

QByteArray AudioHelper::decode(const QByteArray& source) {
	QByteArray res;
	std::vector<char> buf(dec->block_size() * format->frame_size());
	for (int i = 0; i < source.size(); ) {
		int enc_size = source.at(i);
		if (enc_size < 0) {
			return res;
		}
		++i;
		dec->decode(source.begin() + i, enc_size, &buf[0]);
		res.append(&buf[0], dec->block_size() * format->frame_size());
		i += enc_size;
	}
	return res;
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
	asound::global_config_cleanup cleanup;
	return res;
	asound::global_config_cleanup cleanup;
}

void AudioHelper::play(const QByteArray &data) {
	out->write(data, data.size() / format->frame_size());
}