#pragma once

#include <memory>
#include <cstdint>
#include <string_view>

namespace quick3d::al
{
	struct PCMcodec
	{
		virtual unsigned char* get_sample_pcm() const noexcept = 0;
		virtual uint16_t get_sample_channels() const noexcept = 0;
		virtual uint16_t get_sample_bps() const noexcept = 0;
		virtual uint32_t get_sample_size() const noexcept = 0;
		virtual uint32_t get_sample_freq() const noexcept = 0;
	};

	class Wavcodec : public PCMcodec
	{
	private:
		std::unique_ptr<unsigned char[]> pcm;
		int16_t channels;
		int16_t bps;
		uint32_t size;
		uint32_t freq;

		void load_from_ifs(std::ifstream& ifs) noexcept(false);

	public:
		Wavcodec(std::ifstream& ifs) noexcept(false);
		Wavcodec(Wavcodec&) = delete;
		~Wavcodec() = default;

		unsigned char* get_sample_pcm() const noexcept;
		uint16_t get_sample_channels() const noexcept;
		uint16_t get_sample_bps() const noexcept;
		uint32_t get_sample_size() const noexcept;
		uint32_t get_sample_freq() const noexcept;
	};

	class Sample
	{
	private:
		PCMcodec* codec;
		bool is_wav_audio(std::istream& ifs) noexcept;

	public:
		// 根据文件头判断文件类型，从而调用对应codec
		// 若无法打开，无法识别或暂不支持该文件类型，则抛出异常
		Sample(std::string_view path) noexcept(false);
		Sample(Sample&) = delete;
		~Sample() noexcept;

		const PCMcodec& get_codec() const noexcept;
	};
}