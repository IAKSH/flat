#pragma once

#include "OpenAL/openal_buffer.hpp"
#include "OpenAL/openal_source.hpp"
#include "OpenAL/openal_scope.hpp"
#include "OpenAL/openal_listener.hpp"
#include "OpenGL/opengl_texture.hpp"
#include "OpenGL/opengl_camera.hpp"
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
    //template <PhysicsModel Model>
    //class Object
    //{
    //private:
    //    Model model;
    //    inline static unsigned long long object_count = 0;
    //    long long id;
//
    //protected:
    //    void generate_id();
//
    //public:
    //    virtual ~Object() = default;
    //    long long get_id() const;
    //};

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

    //template <Object T>
    //std::array<float,3>&& get_position(const T& t)
    //{
    //    return (t.model.get_position_x(),t.model.get_position_y(),t.model.get_position_z());
    //}
//
    //template <Object T>
    //void set_position(const T& t,const std::array<float,3>& arr)
    //{
    //    t.model.set_position_x(arr[0]);
    //    t.model.set_position_x(arr[1]);
    //    t.model.set_position_x(arr[2]);
    //}
//
    //template <Object T>
    //std::array<float,3>&& get_velocity(const T& t)
    //{
    //    return (t.model.get_velocity_x(),t.model.get_velocity_y(),t.model.get_velocity_z());
    //}
//
    //template <Object T>
    //void set_velocity(const T& t,const std::array<float,3>& arr)
    //{
    //    t.model.set_velocity_x(arr[0]);
    //    t.model.set_velocity_x(arr[1]);
    //    t.model.set_velocity_x(arr[2]);
    //}
//
    //template <Object T>
    //void set_height(const T& t,float h)
    //{
    //    t.model.set_sqaure_height(h);
    //}
//
    //template <Object T>
    //void set_width(const T& t,float w)
    //{
    //    t.model.set_square_width(w);
    //}
//
    //template <Object T>
    //float get_height(const T& t)
    //{
    //    return t.model.get_sqaure_height();
    //}
//
    //template <Object T>
    //float get_width(const T& t)
    //{
    //    return t.model.set_square_width();
    //}

    // audio mixer & renderer's camera, all in one
    class Camera
    {
    private:
        ID id;
        Rotator rotator;
        std::array<float,3> position;
        std::array<float,3> velocity;
        float radius;
    
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
    
        //template <typename T>
        //friend std::array<float,3>&& get_position(const T& t);

        //template <Object T>
        //friend void set_position(const T& t,const std::array<float,3>& arr);

        //template <Object T>
        //friend std::array<float,3>&& get_velocity(const T& t);

        //template <Object T>
        //friend void set_velocity(const T& t,const std::array<float,3>& arr);

        //template <Object T>
        //friend void set_height(const T& t,float h);

        //template <Object T>
        //friend void set_width(const T& t,float w);

        //template <Object T>
        //friend float get_height(const T& t);

        //template <Object T>
        //friend float get_width(const T& t);
    };

    static_assert(Object<Camera>);
    

    //class RenableObject
    //{
    //private:
    //    ID id;
    //    Square model;
    //    opengl::RectangleVertexArray<opengl::BufferType::Dynamic> rect;

    //public:
    //    RenableObject();
    //    ~RenableObject();
    //    void flush_to_screen() const;
    //    virtual void flush_to_screen(const flat::Camera& camera) const = 0;
    //    const opengl::RectangleVertexArray<opengl::BufferType::Dynamic>& get_rect_vao() const;
    //    // TODO: 提供修改vertices data的API（坐标/颜色/纹理坐标）
    //};

    class Sound
    {
    private:
        ID id;
        Ball Ball;
        openal::Buffer<openal::Format::MONO16> buffer;

    public:
        Sound(const unsigned char* const pcm,int sample_rate,int pcm_len);
        ~Sound();
        void play();
        void pause();
        void resume();
        void restart();
    };

    class Music
    {
    private:
        ID id;
        Ball model;
        openal::Buffer<openal::Format::STEREO16> buffer;

    public:
        Music(const unsigned char* const pcm,int sample_rate,int pcm_len);
        ~Music();
        void play();
        void pause();
        void resume();
        void restart();
    };

    class Sample
    {
    private:
        ID id;
        Ball model;
        std::unique_ptr<unsigned char[]> pcm_data;
        size_t pcm_len;
        int channels;
        int sample_rate;
        int byte_rate;
        int bits_per_sample;

    public:
        Sample(std::unique_ptr<unsigned char[]> pcm,size_t pcm_len,int channels,int sample_rate,int byte_rate,int bits_per_sample);
        ~Sample();
        std::unique_ptr<Sound> gen_sound();
        std::unique_ptr<Music> gen_music();
    };

    class Frame : public RenableObject
    {
    private:
        opengl::FrameBuffer fbo;

    public:
        Frame(int w,int h);
        ~Frame();
        const opengl::FrameBuffer& get() const;
        virtual void flush_to_screen(const Camera& camera) const override;
    };

    // Texture --(RenderPipe)--> Frame
    // Frame.get_texture() --(RenderPipe)--> new Frame
    // Frame.flush_to_screen(): display on screen using default shader
    class Texture : public RenableObject
    {
    private:
        std::unique_ptr<opengl::BasicTexture> texture;

    public:
        Texture(const unsigned char* const data,int x,int y,int w,int h,int channels);
        ~Texture();
        const opengl::BasicTexture& get() const;
        virtual void flush_to_screen(const Camera& camera) const override;
        // TODO: 应当提供更多的在GPU中处理图像的API
    };

    class CharTexture : public Texture
    {

    };

    class Image : public Object
    {
    private:
        std::unique_ptr<unsigned char[]> bitmap_data;
        int channels;
        int width;
        int height;

    public:
        Image(std::string_view path);
        Image(std::unique_ptr<unsigned char[]> data,int w,int h,int c);
        ~Image();
        std::unique_ptr<Texture> gen_texture(int x,int y,int w,int h);
        // TODO: 应当提供更多的在CPU中处理图像的API
    };

    class Font : public Object
    {
    private:
        FT_Face face;
        unsigned int font_size;

    public:
        Font(std::string_view path);
        ~Font();
        unsigned int get_font_size() const;
        void set_font_size(unsigned int val);
        std::unique_ptr<Texture> gen_char_texture(char32_t c);
    };

    extern std::unique_ptr<Camera> default_camera;
}