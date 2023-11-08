#include <quick_core/com_renderer.hpp>

// 该文件被放弃，需要删除

namespace quick3d::core
{
	class ShadowRenderer : virtual public Renderer
	{
	private:
		void setup_shadow_shader() noexcept;

	public:
		ShadowRenderer() noexcept;
		ShadowRenderer(ShadowRenderer&) = delete;
		~ShadowRenderer() = default;
		virtual void on_tick(float delta_ms) noexcept(false) override = 0;
	};

	class ModelShadowRenderer 
		: virtual public ModelRenderer, virtual public ShadowRenderer
	{
	public:
		ModelShadowRenderer() noexcept;
		ModelShadowRenderer(ModelShadowRenderer&) = delete;
		~ModelShadowRenderer() = default;
		virtual void on_tick(float delta_ms) noexcept(false) override;
	};

	class CubeMapShadowVAORenderer
		: public CubeMapVAORenderer, virtual public ShadowRenderer
	{
	public:
		CubeMapShadowVAORenderer() noexcept;
		CubeMapShadowVAORenderer(CubeMapShadowVAORenderer&) = delete;
		~CubeMapShadowVAORenderer() = default;
		virtual void on_tick(float delta_ms) noexcept(false) override;
	};

	class VAOShadowRenderer
		: public VAORenderer, virtual public ShadowRenderer
	{
	public:
		VAOShadowRenderer() noexcept;
		VAOShadowRenderer(VAOShadowRenderer&) = delete;
		~VAOShadowRenderer() = default;
		virtual void on_tick(float delta_ms) noexcept(false) override;
	};

	class InstanceModelShadowRenderer
		: public InstanceModelRenderer, virtual public ShadowRenderer
	{
	public:
		InstanceModelShadowRenderer() noexcept;
		InstanceModelShadowRenderer(InstanceModelShadowRenderer&) = delete;
		~InstanceModelShadowRenderer() = default;
		virtual void on_tick(float delta_ms) noexcept(false) override;
	};

	class InstanceCubeMapVAOShadowRenderer
		: public InstanceCubeMapVAORenderer, virtual public ShadowRenderer
	{
	public:
		InstanceCubeMapVAOShadowRenderer() noexcept;
		InstanceCubeMapVAOShadowRenderer(InstanceCubeMapVAOShadowRenderer&) = delete;
		~InstanceCubeMapVAOShadowRenderer() = default;
		virtual void on_tick(float delta_ms) noexcept(false) override;
	};

	class InstanceVAOShadowRenderer
		: public InstanceVAORenderer, virtual public ShadowRenderer
	{
	public:
		InstanceVAOShadowRenderer() noexcept;
		InstanceVAOShadowRenderer(InstanceVAOShadowRenderer&) = delete;
		~InstanceVAOShadowRenderer() = default;
		virtual void on_tick(float delta_ms) noexcept(false) override;
	};
}