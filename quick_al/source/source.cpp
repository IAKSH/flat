#include <stdexcept>
#include <quick_al/source.hpp>

quick3d::al::Source::Source() noexcept
    : binding_buffer(nullptr)
{
    create_source();
}

quick3d::al::Source::Source(Buffer& buffer) noexcept
    : binding_buffer(&buffer)
{
    create_source();
    bind_buffer(buffer);
}

quick3d::al::Source::~Source() noexcept
{
    delete_source();
}

void quick3d::al::Source::create_source() noexcept
{
    alGenSources(1, &source_id);
}

void quick3d::al::Source::delete_source() noexcept
{
    alDeleteSources(1, &source_id);
}

ALuint quick3d::al::Source::get_source_id() noexcept
{
    return source_id;
}

void quick3d::al::Source::set_source_position(const Vec3& vec) noexcept
{
    alSourcefv(source_id, AL_POSITION, vec.data());
}

void quick3d::al::Source::set_source_position(ALfloat x, ALfloat y, ALfloat z) noexcept
{
    set_source_position(Vec3{ x, y, z });
}

void quick3d::al::Source::set_source_velocity(const Vec3& vec) noexcept
{
    alSourcefv(source_id, AL_VELOCITY, vec.data());
}

void quick3d::al::Source::set_source_velocity(ALfloat x, ALfloat y, ALfloat z) noexcept
{
    set_source_velocity(Vec3{ x, y, z });
}

void quick3d::al::Source::set_source_orientation(const Vec3& front, const Vec3& up) noexcept
{
    ALfloat orientation[] = { front[0], front[1], front[2], up[0], up[1], up[2] };
    alSourcefv(source_id, AL_ORIENTATION, orientation);
}

void quick3d::al::Source::set_source_orientation(ALfloat front_x, ALfloat front_y, ALfloat front_z, ALfloat up_x, ALfloat up_y, ALfloat up_z)
{
    set_source_orientation(Vec3{ front_x, front_y, front_z }, Vec3{ up_x, up_y, up_z });
}

void quick3d::al::Source::set_source_direction(const Vec3& vec)
{
    alSourcefv(source_id, AL_DIRECTION, vec.data());
}

void quick3d::al::Source::set_source_direction(ALfloat x, ALfloat y, ALfloat z)
{
    set_source_direction(Vec3{ x, y, z });
}

void quick3d::al::Source::set_source_gain(ALfloat gain) noexcept
{
    alSourcef(source_id, AL_GAIN, gain);
}

void quick3d::al::Source::set_source_pitch(ALfloat pitch) noexcept
{
    alSourcef(source_id, AL_PITCH, pitch);
}

void quick3d::al::Source::set_source_looping(ALboolean looping) noexcept
{
    alSourcei(source_id, AL_LOOPING, looping);
}

void quick3d::al::Source::set_source_relative(ALboolean relative) noexcept
{
    alSourcei(source_id, AL_SOURCE_RELATIVE, relative);
}

void quick3d::al::Source::set_source_reference_distance(ALfloat distance) noexcept
{
    alSourcef(source_id, AL_REFERENCE_DISTANCE, distance);
}

void quick3d::al::Source::set_source_max_distance(ALfloat distance) noexcept
{
    alSourcef(source_id, AL_MAX_DISTANCE, distance);
}

void quick3d::al::Source::set_rolloff_factor(ALfloat factor) noexcept
{
    alSourcef(source_id, AL_ROLLOFF_FACTOR, factor);
}

void quick3d::al::Source::set_cone_inner_angle(ALfloat angle) noexcept
{
    alSourcef(source_id, AL_CONE_INNER_ANGLE, angle);
}

void quick3d::al::Source::set_cone_outer_angle(ALfloat angle) noexcept
{
    alSourcef(source_id, AL_CONE_OUTER_ANGLE, angle);
}

void quick3d::al::Source::set_cone_outer_gain(ALfloat gain) noexcept
{
    alSourcef(source_id, AL_CONE_OUTER_GAIN, gain);
}

quick3d::al::Vec3 quick3d::al::Source::get_source_position() const noexcept
{
    Vec3 vec;
    alGetSourcefv(source_id, AL_POSITION, vec.data());
    return vec;
}

quick3d::al::Vec3 quick3d::al::Source::get_source_velocity() const noexcept
{
    Vec3 vec;
    alGetSourcefv(source_id, AL_VELOCITY, vec.data());
    return vec;
}

std::array<quick3d::al::Vec3,2> quick3d::al::Source::get_source_orientation() const noexcept
{
    Vec3 front, up;
    ALfloat orientation[6];
    alGetSourcefv(source_id, AL_ORIENTATION, orientation);
    front[0] = orientation[0];
    front[1] = orientation[1];
    front[2] = orientation[2];
    up[0] = orientation[3];
    up[1] = orientation[4];
    up[2] = orientation[5];
    return std::array<Vec3, 2>{front, up};
}

quick3d::al::Vec3 quick3d::al::Source::get_source_direction() const noexcept
{
    Vec3 vec;
    alGetSourcefv(source_id, AL_DIRECTION, vec.data());
    return vec;
}

ALfloat quick3d::al::Source::get_source_gain() const noexcept
{
    ALfloat gain;
    alGetSourcef(source_id, AL_GAIN, &gain);
    return gain;
}

ALfloat quick3d::al::Source::get_source_pitch() const noexcept
{
    ALfloat pitch;
    alGetSourcef(source_id, AL_PITCH, &pitch);
    return pitch;
}

ALboolean quick3d::al::Source::get_source_looping() const noexcept
{
    ALint looping;
    alGetSourcei(source_id, AL_LOOPING, &looping);
    return static_cast<ALboolean>(looping);
}

ALboolean quick3d::al::Source::get_source_relative() const noexcept
{
    ALint relative;
    alGetSourcei(source_id, AL_SOURCE_RELATIVE, &relative);
    return static_cast<ALboolean>(relative);
}

ALfloat quick3d::al::Source::get_source_reference_distance() const noexcept
{
    ALfloat distance;
    alGetSourcef(source_id, AL_REFERENCE_DISTANCE, &distance);
    return distance;
}

ALfloat quick3d::al::Source::get_source_max_distance() const noexcept
{
    ALfloat distance;
    alGetSourcef(source_id, AL_MAX_DISTANCE, &distance);
    return distance;
}

ALfloat quick3d::al::Source::get_rolloff_factor() const noexcept
{
    ALfloat factor;
    alGetSourcef(source_id, AL_ROLLOFF_FACTOR, &factor);
    return factor;
}

ALfloat quick3d::al::Source::get_cone_inner_angle() const noexcept
{
    ALfloat angle;
    alGetSourcef(source_id, AL_CONE_INNER_ANGLE, &angle);
    return angle;
}

ALfloat quick3d::al::Source::get_cone_outer_angle() const noexcept
{
    ALfloat angle;
    alGetSourcef(source_id, AL_CONE_OUTER_ANGLE, &angle);
    return angle;
}

ALfloat quick3d::al::Source::get_cone_outer_gain() const noexcept
{
    ALfloat gain;
    alGetSourcef(source_id, AL_CONE_OUTER_GAIN, &gain);
    return gain;
}

ALboolean quick3d::al::Source::is_playing() const noexcept
{
    ALint state;
    alGetSourcei(source_id, AL_SOURCE_STATE, &state);
    return state == AL_PLAYING;
}

quick3d::al::Buffer* quick3d::al::Source::get_binding_buffer() noexcept
{
    return binding_buffer;
}

void quick3d::al::Source::bind_buffer(Buffer& buffer) noexcept
{
    binding_buffer = &buffer;
    alSourcei(source_id, AL_BUFFER, buffer.get_buffer_id());
}

void quick3d::al::Source::play_sound(Buffer& buffer) noexcept
{
    bind_buffer(buffer);
    alSourcePlay(source_id);
}

void quick3d::al::Source::play_sound() noexcept(false)
{
    if (!binding_buffer)
        throw std::runtime_error("trying to play an al source without buffer binding");
    alSourcePlay(source_id);
}
