#pragma once

// ���������¼���Event��������
// Layer���߼��ϵġ��㡱�����û�������ĵط�
// Applicationֻ��һ��������Ҳֻ��һ�������ǿ����ж��Layer��Application����Events��Ȼ��Ͷ�ݵ�ÿ��Layer��ִ����Ӧ����
// ��������Ǽ�ʱ�ģ�û����Ϣ���С�

#include <string_view>

#include "event.hpp"

namespace flat::core
{
	class Layer
	{
	private:
		std::string layerName;

	public:
		Layer(std::string_view name = "Layer")
			: layerName(name)
		{
		}
		~Layer() = default;

		std::string_view getName() { return layerName; }

		virtual void onAttach() = 0;
		virtual void onDetach() = 0;
		virtual void onUpdate() = 0;
		virtual void onRender() = 0;
		virtual void onEvent(Event& e) = 0;
	};
}