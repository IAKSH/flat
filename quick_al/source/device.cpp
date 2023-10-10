#include <format>
#include <iostream>
#include <stdexcept>
#include <quick_al/device.hpp>

quick3d::al::Device::Device() noexcept
    : device(nullptr)
{
}

quick3d::al::Device::Device(const ALCchar* device_name) noexcept(false)
    : device(nullptr)
{
    open_device(device_name);
}

quick3d::al::Device::~Device() noexcept
{
    if(device)
        close_device();
}

void quick3d::al::Device::open_device(const ALCchar* device_name) noexcept(false)
{
    device = alcOpenDevice(device_name);
    if(!device)
        throw std::runtime_error(std::format("can't open audio device naming {}",device_name));
}

void quick3d::al::Device::close_device() noexcept
{
    alcCloseDevice(device);
}

bool quick3d::al::Device::is_loaded() noexcept
{
    return static_cast<bool>(device);
}

bool quick3d::al::Device::check_al_extension(std::string_view extension_name) noexcept
{
    ALboolean enumeration;
    enumeration = alcIsExtensionPresent(nullptr, extension_name.data());
    return enumeration == AL_TRUE;
}

void quick3d::al::Device::list_al_devices() noexcept
{
    const ALCchar* devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
    const ALCchar *device = devices, *next = devices + 1;
    size_t len = 0;
    std::cout << "Devices list:\n";
    while (device && *device != '\0' && next && *next != '\0') {
            std::cout << device << '\n';
            len = strlen(device);
            device += (len + 1);
            next += (len + 2);
    }
    std::cout << std::endl;
}

ALCdevice* quick3d::al::Device::get_device() noexcept
{
    return device;
}