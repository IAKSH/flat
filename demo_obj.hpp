#pragma once
#include "al.h"
#include "core/event_keyboard.hpp"
#include "utils/gameobj.hpp"
#include "utils/vao.hpp"
#include "utils/audio_source.hpp"
#include "utils/animation.hpp"
#include "utils/shader.hpp"
#include "utils/camera.hpp"
#include "utils/audio.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <AL/al.h>
#include <AL/alc.h>

#include <iostream>

namespace demo
{
    // TODO: audio source should remove from here, it should not inherit from MassPoint
    class Bird : public ni::utils::GameObject
    {
    private:
        ni::utils::Animation<3> flyAnimation{ni::utils::MilliSeconds{250},"images/bird0_0.png","images/bird0_1.png","images/bird0_2.png"};
        ni::utils::VertexArrayObj vao;
		ni::utils::AudioSource audioSource;
        const ni::utils::Shader& shader;
        const ni::utils::Camera2D& cam;
		const ni::utils::Audio& testAudio;

    public:
        Bird(const ni::utils::Shader& shader,const ni::utils::Camera2D& cam,const ni::utils::Audio& testAudio)
            : shader(shader),cam(cam),testAudio{testAudio}
        {
        }
        ~Bird() = default;

        virtual void onAttach() override
        {
            std::array<float,36> vertices
            {
				1.0f,  1.0f,  0.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,  // top right
				1.0f,  -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,  // bottom right
				-1.0f, -1.0f, 0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,  // bottom left
				-1.0f, 1.0f,  0.0f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f   // top left
		    };

            std::array<unsigned int, 6> indices
            {
			0, 1, 3,  // first Triangle
			1, 2, 3   // second Triangle
		    };

            vao.create(ni::utils::GLBufferType::Static,vertices,indices);

			// audio
			alSourcei(audioSource.getSourceID(), AL_BUFFER, testAudio.getBufferID());
			alSourcef(audioSource.getSourceID(), AL_GAIN, 0.5f);
			alSourcei(audioSource.getSourceID(), AL_LOOPING, AL_TRUE);
			alSourcePlay(audioSource.getSourceID());
        }

        virtual void onDetach() override
        {

        }

        virtual void onUpdate() override
        {
            setPositionX(getPositionX() + getVelocityX());
            setPositionY(getPositionY() + getVelocityY());
            flyAnimation.tryUpdate();

			alSource3f(audioSource.getSourceID(),AL_POSITION,getPositionX(),getPositionY(),getPositionZ());
			alSource3f(audioSource.getSourceID(),AL_VELOCITY,getVelocityX(),getVelocityY(),getVelocityZ());
        }

        virtual void onRender() override
        {
			glUseProgram(shader.getShaderID());
            glBindTexture(GL_TEXTURE_2D, flyAnimation.getCurrentTexture().getTextureID());

			glm::mat4 trans(1.0f);
			trans *= glm::translate(glm::mat4(1.0f), glm::vec3(getPositionX(),getPositionY(),0.2f));
			trans *= glm::scale(glm::mat4(1.0f), glm::vec3(50.0f, 50.0f, 1.0f));
			trans *= glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f));

			unsigned int transLocation = glGetUniformLocation(shader.getShaderID(), "transform");
			glUniformMatrix4fv(transLocation, 1, GL_FALSE, glm::value_ptr(trans));
			unsigned int camTrans = glGetUniformLocation(shader.getShaderID(), "camTrans");
			glUniformMatrix4fv(camTrans, 1, GL_FALSE, glm::value_ptr(cam.getTranslateMatrix()));

			glBindVertexArray(vao.getVAO());
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArray(0);
        }

        virtual void onEvent(ni::core::Event& e) override
        {
            if(e.getType() == ni::core::EventType::KeyPress)
		    {
			    switch (static_cast<ni::core::KeyPressEvent&>(e).getKeyCode())
			    {
			    	case ni::core::KeyCode::UP:
			    		setVelocityY(0.5f);
			    		break;
			    	case ni::core::KeyCode::DOWN:
			    		setVelocityY(-0.5f);
			    		break;
			    	case ni::core::KeyCode::RIGHT:
			    		setVelocityX(0.5f);
			    		break;
			    	case ni::core::KeyCode::LEFT:
			    		setVelocityX(-0.5f);
			    		break;
                    default:
                        break;
			    }
            }
            else if (e.getType() == ni::core::EventType::KeyRelease)
		    {   
		    	switch (static_cast<ni::core::KeyReleaseEvent&>(e).getKeyCode())
		    	{
		    		case ni::core::KeyCode::LEFT:
		    		case ni::core::KeyCode::RIGHT:
		    			setVelocityX(0.0f);
		    			break;
		    		case ni::core::KeyCode::UP:
		    		case ni::core::KeyCode::DOWN:
		    			setVelocityY(0.0f);
		    			break;
		    		default:
		    			break;
		    	}
            }
        }
    };
}