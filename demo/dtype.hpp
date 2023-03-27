#pragma once

#include <array>
#include <chrono>
#include <iostream>
#include <stdexcept>

namespace flat::dtype
{
    using Millisecond = unsigned int;
    using TimePoint = std::chrono::steady_clock::time_point;

	template<int N>
	class Vec
	{
	private:
		std::array<float, N> data{ 0.0f };

	public:
		Vec() {}
		Vec(std::initializer_list<float> vals)
		{
			try
			{
				int i = 0;
				for (const auto& val : vals) {
					if (i >= N) break;
					data[i] = val;
					i++;
				}
			}
			catch (std::exception& e)
			{
				std::cerr << e.what() << std::endl;
				abort();
			}
		}

		float& operator[](int i)
		{
			if (i >= 0 && i < N)
				return data[i];
			else
			{
				std::cerr << "vec out of range" << std::endl;
				abort();
			}
		}

		int getLength()
		{
			return N;
		}
	};
}