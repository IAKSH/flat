#pragma once

#include "opengl_texture.hpp"
#include "timer.hpp"
#include "../core/template.hpp"
#include <array>
#include <memory>
#include <iterator>

namespace ni::utils
{
    using Texture = ni::utils::opengl::Texture<ni::utils::opengl::ColorChannelType::RGBA,ni::utils::opengl::ColorChannelType::RGBA>;

    template <size_t texturesLen>
    class [[deprecated("abandoned since commit 489d6aa")]] Animation : public core::DisableCopy
    {
    private:
        std::array<std::unique_ptr<ni::utils::Texture>,texturesLen> textures;
        decltype(textures)::iterator ite;
        ni::utils::TimeRecorder recorder;
        ni::utils::MilliSeconds interval;
        
    public:
        // we don't need Concepts for this func,
        // for the compiler will check Args' type and count when compiling
        template <typename... Args>
        Animation(const ni::utils::MilliSeconds& interval,Args&&... args)
            : interval{interval},textures{std::make_unique<ni::utils::Texture>(std::forward<Args>(args))...},ite{std::begin(textures)}
        {
        }
        ~Animation() = default;
        const ni::utils::Texture& getCurrentTexture() const { return **ite; }
        void rewind() {ite = std::begin(textures);}
        void tryUpdate()
        {
            if(recorder.getSpanAsMilliSeconds() >= interval)
            {
                if(++ite;ite == std::end(textures))
                    rewind();
                recorder.update();
            }
        }
    };
}