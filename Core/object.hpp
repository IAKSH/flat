#pragma once

#include "OpenAL/openal_buffer.hpp"
#include "OpenAL/openal_source.hpp"
#include "OpenAL/openal_scope.hpp"
#include "OpenAL/openal_listener.hpp"
#include "OpenGL/opengl_texture.hpp"
#include "OpenGL/opengl_fbo.hpp"
#include "OpenGL/opengl_vao.hpp"
#include "../../misc/disable_copy.hpp"
#include "../../misc/abstract_base.hpp"
#include "physics.hpp"
#include <exception>
#include <ft2build.h>
#include <type_traits>
#include FT_FREETYPE_H
#include <string>
#include <memory>

// 该文件需要进行拆分

namespace flat
{
    class ID
    {
    private:
        inline static unsigned long long count {0};
        unsigned long long id;

    public:
        ID() : id(++count) {}
        ~ID() = default;
        auto get() const {return id;}
    };

    // temp code
    template <typename T>
    concept Object = PhysicsModel<T> && requires(T t)
    {
        {t.get_id()} -> std::same_as<unsigned long long>;
    };

    // audio mixer & renderer's camera, all in one
    class Camera
    {
    private:
        ID id;
        Rotator rotator;
        std::array<float,3> position;
        std::array<float,3> velocity;
        float radius;

        float fov,zoom;
        int view_width,view_height;
    
    public:
        Camera(int view_width,int view_height) {}
        ~Camera() = default;

        float get_ball_radius() const {return radius;}
        void set_ball_radius(float val) {radius = val;}
        auto get_id() const {return id.get();}
        const auto& get_position() const {return position;}
        const auto& get_velocity() const {return velocity;}
        const auto& get_orientation_quat() const {return rotator.get_orientation_quat();}
        const auto& get_right_vec() const {return rotator.get_right_vec();}
        const auto& get_up_vec() const {return rotator.get_up_vec();}
        void set_position(const std::array<float,3>& arr) {position = arr;}
        void set_velocity(const std::array<float,3>& arr) {velocity = arr;}
        void set_orientation_quat(const std::array<float,4>& arr) {rotator.set_orientation_quat(arr);}
        void set_right_vec(const std::array<float,3>& arr) {rotator.set_right_vec(arr);}
        void set_up_vec(const std::array<float,3>& arr) {rotator.set_up_vec(arr);}

        float get_zoom() {return zoom;}
        float get_fov() {return fov;}
        void set_zoom(float val);
        void set_fov(float val);
    };

    static_assert(Object<Camera>);

    template <typename T>
    concept AnyCamera = Object<T> && requires(T t,float zoom,float fov)
    {
        {t.get_zoom()} -> std::same_as<float>;
        {t.get_fov()} -> std::same_as<float>;
        {t.set_zoom(zoom)} -> std::same_as<void>;
        {t.set_fov(fov)} -> std::same_as<void>;
    };

    static_assert(AnyCamera<Camera>);

    template <AnyCamera T>
    glm::mat4 get_camera_matrix(const T& cam)
    {
        // TODO: ...
    };

    template <typename T>
    concept Renable = Object<T> && requires(T t,const Camera& cam)
    {
        {t.flush()} -> std::same_as<void>;
        {t.flush(cam)} -> std::same_as<void>;
        // TODO: 提供修改vertices data的API（坐标/颜色/纹理坐标）
    };

    template <typename T>
    concept Audible = Object<T> && requires(T t)
    {
        {t.play_audio()} -> std::same_as<void>;
        {t.pause_audio()} -> std::same_as<void>;
        {t.resume_audio()} -> std::same_as<void>;
        {t.restart_audio()} -> std::same_as<void>;
        // TODO: 提供修改OpenAL Source的API
    };

    class Sound
    {
    private:
        ID id;
        Rotator rotator;
        std::array<float,3> position;
        std::array<float,3> velocity;
        float radius;
        openal::Buffer<openal::Format::MONO16> buffer;

    public:
        Sound(const unsigned char* const pcm,int sample_rate,int pcm_len);
        ~Sound();
        void play_audio();
        void pause_audio();
        void resume_audio();
        void restart_audio();

        float get_ball_radius() const {return radius;}
        void set_ball_radius(float val) {radius = val;}
        auto get_id() const {return id.get();}
        const auto& get_position() const {return position;}
        const auto& get_velocity() const {return velocity;}
        const auto& get_orientation_quat() const {return rotator.get_orientation_quat();}
        const auto& get_right_vec() const {return rotator.get_right_vec();}
        const auto& get_up_vec() const {return rotator.get_up_vec();}
        void set_position(const std::array<float,3>& arr) {position = arr;}
        void set_velocity(const std::array<float,3>& arr) {velocity = arr;}
        void set_orientation_quat(const std::array<float,4>& arr) {rotator.set_orientation_quat(arr);}
        void set_right_vec(const std::array<float,3>& arr) {rotator.set_right_vec(arr);}
        void set_up_vec(const std::array<float,3>& arr) {rotator.set_up_vec(arr);}
    };

    static_assert(Audible<Sound>);

    class Music
    {
    private:
        ID id;
        Rotator rotator;
        std::array<float,3> position;
        std::array<float,3> velocity;
        float radius;
        openal::Buffer<openal::Format::STEREO16> buffer;

    public:
        Music(const unsigned char* const pcm,int sample_rate,int pcm_len);
        ~Music();
        void play_audio();
        void pause_audio();
        void resume_audio();
        void restart_audio();

        float get_ball_radius() const {return radius;}
        void set_ball_radius(float val) {radius = val;}
        auto get_id() const {return id.get();}
        const auto& get_position() const {return position;}
        const auto& get_velocity() const {return velocity;}
        const auto& get_orientation_quat() const {return rotator.get_orientation_quat();}
        const auto& get_right_vec() const {return rotator.get_right_vec();}
        const auto& get_up_vec() const {return rotator.get_up_vec();}
        void set_position(const std::array<float,3>& arr) {position = arr;}
        void set_velocity(const std::array<float,3>& arr) {velocity = arr;}
        void set_orientation_quat(const std::array<float,4>& arr) {rotator.set_orientation_quat(arr);}
        void set_right_vec(const std::array<float,3>& arr) {rotator.set_right_vec(arr);}
        void set_up_vec(const std::array<float,3>& arr) {rotator.set_up_vec(arr);}
    };

    static_assert(Audible<Music>);

    template <typename T>
    concept AudioDataSouce = Object<T> && requires(T t)
    {
        {t.get_pcm_data()} -> std::same_as<const unsigned char*>;
        {t.get_pcm_len()} -> std::same_as<size_t>;
        {t.get_channels()} -> std::same_as<int>;
        {t.get_byte_rate()} -> std::same_as<int>;
        {t.get_bits_per_sample()} -> std::same_as<int>;
    };

    class Sample
    {
    private:
        ID id;
        Rotator rotator;
        std::array<float,3> position;
        std::array<float,3> velocity;
        float radius;

        std::unique_ptr<unsigned char[]> pcm_data;
        size_t pcm_len;
        int channels;
        int sample_rate;
        int byte_rate;
        int bits_per_sample;

    public:
        Sample(std::unique_ptr<unsigned char[]> pcm,size_t pcm_len,int channels,int sample_rate,int byte_rate,int bits_per_sample);
        ~Sample();
        const unsigned char* get_pcm_data() const {return pcm_data.get();}
        size_t get_pcm_len() const {return pcm_len;}
        int get_channels() const {return channels;}
        int get_byte_rate() const {return byte_rate;}
        int get_bits_per_sample() const {return bits_per_sample;}

        float get_ball_radius() const {return radius;}
        void set_ball_radius(float val) {radius = val;}
        auto get_id() const {return id.get();}
        const auto& get_position() const {return position;}
        const auto& get_velocity() const {return velocity;}
        const auto& get_orientation_quat() const {return rotator.get_orientation_quat();}
        const auto& get_right_vec() const {return rotator.get_right_vec();}
        const auto& get_up_vec() const {return rotator.get_up_vec();}
        void set_position(const std::array<float,3>& arr) {position = arr;}
        void set_velocity(const std::array<float,3>& arr) {velocity = arr;}
        void set_orientation_quat(const std::array<float,4>& arr) {rotator.set_orientation_quat(arr);}
        void set_right_vec(const std::array<float,3>& arr) {rotator.set_right_vec(arr);}
        void set_up_vec(const std::array<float,3>& arr) {rotator.set_up_vec(arr);}
    };

    static_assert(AudioDataSouce<Sample>);

    template <AudioDataSouce T,Audible U>
    std::unique_ptr<U> gen_audible(const T& t)
    {
        // TODO: ...
    };

    class Frame
    {
    private:
        ID id;
        Rotator rotator;
        std::array<float,3> position;
        std::array<float,3> velocity;
        float width;
        float height;
        opengl::FrameBuffer fbo;

    public:
        Frame(int w,int h);
        ~Frame();
        void flush() const;
        void flush(const Camera& cam) const;

        float get_square_width() const {return width;}
        float get_square_height() const {return height;}
        auto get_id() const {return id.get();}
        const auto& get_position() const {return position;}
        const auto& get_velocity() const {return velocity;}
        const auto& get_orientation_quat() const {return rotator.get_orientation_quat();}
        const auto& get_right_vec() const {return rotator.get_right_vec();}
        const auto& get_up_vec() const {return rotator.get_up_vec();}
        void set_position(const std::array<float,3>& arr) {position = arr;}
        void set_velocity(const std::array<float,3>& arr) {velocity = arr;}
        void set_orientation_quat(const std::array<float,4>& arr) {rotator.set_orientation_quat(arr);}
        void set_right_vec(const std::array<float,3>& arr) {rotator.set_right_vec(arr);}
        void set_up_vec(const std::array<float,3>& arr) {rotator.set_up_vec(arr);}
        void set_square_width(float val) {width = val;}
        void set_square_height(float val) {height = val;}
    };

    static_assert(Renable<Frame>);

    // Texture --(RenderPipe)--> Frame
    // Frame.get_texture() --(RenderPipe)--> new Frame
    // Frame.flush_to_screen(): display on screen using default shader
    class Texture
    {
    private:
        ID id;
        Rotator rotator;
        std::array<float,3> position;
        std::array<float,3> velocity;
        float width;
        float height;
        std::unique_ptr<opengl::BasicTexture> texture;

    public:
        Texture(const unsigned char* const data,int x,int y,int w,int h,int channels);
        ~Texture();
        void flush() const;
        void flush(const Camera& cam) const;

        float get_square_width() const {return width;}
        float get_square_height() const {return height;}
        auto get_id() const {return id.get();}
        const auto& get_position() const {return position;}
        const auto& get_velocity() const {return velocity;}
        const auto& get_orientation_quat() const {return rotator.get_orientation_quat();}
        const auto& get_right_vec() const {return rotator.get_right_vec();}
        const auto& get_up_vec() const {return rotator.get_up_vec();}
        void set_position(const std::array<float,3>& arr) {position = arr;}
        void set_velocity(const std::array<float,3>& arr) {velocity = arr;}
        void set_orientation_quat(const std::array<float,4>& arr) {rotator.set_orientation_quat(arr);}
        void set_right_vec(const std::array<float,3>& arr) {rotator.set_right_vec(arr);}
        void set_up_vec(const std::array<float,3>& arr) {rotator.set_up_vec(arr);}
        void set_square_width(float val) {width = val;}
        void set_square_height(float val) {height = val;}
    };

    static_assert(Renable<Texture>);

    class CharTexture
    {
        // TODO: ...
    };

    //static_assert(Renable<CharTexture>);

    // TODO: 应当提供更多的在GPU中处理图像的API

    template <typename T>
    concept ImageDataSource = Object<T> && requires(T t)
    {
        {t.get_bitmap_data()} -> std::same_as<const unsigned char*>;
        {t.get_bitmap_channels()} -> std::same_as<int>;
        {t.get_bitmap_width()} -> std::same_as<int>;
        {t.get_bitmap_height()} -> std::same_as<int>;
    };

    class Image
    {
    private:
        ID id;
        Rotator rotator;
        std::array<float,3> position;
        std::array<float,3> velocity;
        float square_width;
        float square_height;

        std::unique_ptr<unsigned char[]> bitmap_data;
        int bitmap_channels;
        int bitmap_width;
        int bitmap_height;
        
    public:
        Image(std::string_view path);
        Image(std::unique_ptr<unsigned char[]> data,int w,int h,int c);
        ~Image();
        const unsigned char* get_bitmap_data() const {return bitmap_data.get();}
        int get_bitmap_channels() const {return bitmap_channels;}
        int get_bitmap_width() const {return bitmap_width;}
        int get_bitmap_height() const {return bitmap_height;}
        
        float get_square_width() const {return square_width;}
        float get_square_height() const {return square_height;}
        auto get_id() const {return id.get();}
        const auto& get_position() const {return position;}
        const auto& get_velocity() const {return velocity;}
        const auto& get_orientation_quat() const {return rotator.get_orientation_quat();}
        const auto& get_right_vec() const {return rotator.get_right_vec();}
        const auto& get_up_vec() const {return rotator.get_up_vec();}
        void set_position(const std::array<float,3>& arr) {position = arr;}
        void set_velocity(const std::array<float,3>& arr) {velocity = arr;}
        void set_orientation_quat(const std::array<float,4>& arr) {rotator.set_orientation_quat(arr);}
        void set_right_vec(const std::array<float,3>& arr) {rotator.set_right_vec(arr);}
        void set_up_vec(const std::array<float,3>& arr) {rotator.set_up_vec(arr);}
        void set_square_width(float val) {square_width = val;}
        void set_square_height(float val) {square_height = val;}
    };

    static_assert(ImageDataSource<Image>);

    // TODO: 应当提供更多的在CPU中处理图像的API

    template <typename T>
    concept Font = Object<T> && requires(T t,char c,unsigned int font_scale)
    {
        {t.get_char_data(c)} -> std::same_as<const unsigned char*>;
        {t.get_char_channels(c)} -> std::same_as<int>;
        {t.get_char_width(c)} -> std::same_as<int>;
        {t.get_char_height(c)} -> std::same_as<int>;
        {t.get_char_bearing(c)} -> std::same_as<std::array<int,2>&&>;
        {t.get_char_advance(c)} -> std::same_as<int>;
        {t.get_font_scale()} -> std::same_as<unsigned int>;
        {t.set_font_scale(font_scale)} -> std::same_as<void>; 
    };

    class TTFont
    {
    private:
        ID id;
        Rotator rotator;
        std::array<float,3> position;
        std::array<float,3> velocity;
        float radius;

        FT_Face face;
        unsigned int font_scale;

    public:
        TTFont(std::string_view path);
        ~TTFont();
        const unsigned char* get_char_data(char c) const;
        int get_char_channels(char c) const;
        int get_char_width(char c) const;
        int get_char_height(char c) const;
        std::array<int,2>&& get_char_bearing(char c) const;
        int get_char_advance(char c) const;
        unsigned int get_font_scale() const {return font_scale;}
        void set_font_scale(unsigned int font_scale);

        float get_ball_radius() const {return radius;}
        void set_ball_radius(float val) {radius = val;}
        auto get_id() const {return id.get();}
        const auto& get_position() const {return position;}
        const auto& get_velocity() const {return velocity;}
        const auto& get_orientation_quat() const {return rotator.get_orientation_quat();}
        const auto& get_right_vec() const {return rotator.get_right_vec();}
        const auto& get_up_vec() const {return rotator.get_up_vec();}
        void set_position(const std::array<float,3>& arr) {position = arr;}
        void set_velocity(const std::array<float,3>& arr) {velocity = arr;}
        void set_orientation_quat(const std::array<float,4>& arr) {rotator.set_orientation_quat(arr);}
        void set_right_vec(const std::array<float,3>& arr) {rotator.set_right_vec(arr);}
        void set_up_vec(const std::array<float,3>& arr) {rotator.set_up_vec(arr);}
    };

    static_assert(Font<TTFont>);

    extern std::unique_ptr<Camera> default_camera;
}