#pragma once

#include <string_view>
#include <AL/al.h>
#include <AL/alc.h>

namespace quick3d::al
{
    class Device
	{
	private:
		ALCdevice* device;
		void open_device(const ALCchar* device_name) noexcept(false);
		void close_device() noexcept;

	public:
		Device() noexcept;
		Device(const ALCchar* device_name) noexcept(false);
		Device(Device&) = delete;
		~Device() noexcept;

		bool is_loaded() noexcept;
		bool check_al_extension(std::string_view extension_name) noexcept;
		void list_al_devices() noexcept;
        ALCdevice* get_device() noexcept;
	};
}