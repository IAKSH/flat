#pragma once

#include <vector>
#include <memory>

#include "../utils/texture.hpp"
#include "../utils/time.hpp"

namespace flat::ni
{
	class Animator
	{
	private:
		std::vector<std::unique_ptr<flat::utils::Texture>> textures;
		flat::utils::TimeRecorder recorder;
		flat::utils::MilliSeconds interval;
		unsigned int index;

	public:
		Animator();
		~Animator();

		flat::utils::Texture& getCurrentTexture();
		const flat::utils::MilliSeconds& getInterval();
		void addTexture(std::unique_ptr<flat::utils::Texture> texture);
		void rewind();
		void tryUpdateIndex();
		void setInterval(const flat::utils::MilliSeconds& interval);
	};
}