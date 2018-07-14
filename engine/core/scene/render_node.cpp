#include "render_node.h"
#include "engine/core/main/Engine.h"

namespace Echo
{
	i32	Render::m_renderTypes = Render::Type_2D;

	void Render::bindMethods()
	{
		CLASS_BIND_METHOD(Render, set2d, DEF_METHOD("set2d"));
		CLASS_BIND_METHOD(Render, is2d, DEF_METHOD("is2d"));

		CLASS_REGISTER_PROPERTY(Render, "2D", Variant::Type::Bool, "is2d", "set2d");
	}

	bool Render::isNeedRender() const
	{
#ifdef ECHO_EDITOR_MODE
		if (!Engine::instance()->getConfig().m_isGame)
		{
			if (m_is2d) return static_cast<bool>(m_renderTypes & Type_2D);
			else		return static_cast<bool>(m_renderTypes & Type_3D);
		}
		else
		{
			return true;
		}
#else
		return true;
#endif
	}

	// update
	void Render::update()
	{
		Camera* camera = is2d() ? NodeTree::instance()->get2dCamera() : NodeTree::instance()->get3dCamera();
		if (camera)
		{
			m_matWVP = getWorldMatrix() * camera->getViewProjMatrix();;
		}
	}

	// get global uniforms
	void* Render::getGlobalUniformValue(const String& name)
	{
		void* value = Node::getGlobalUniformValue(name);
		if (value)
			return value;

		Camera* camera = is2d() ? NodeTree::instance()->get2dCamera() : NodeTree::instance()->get3dCamera();
		if (camera)
		{
			if (name == "u_WorldViewProjMatrix")
				return (void*)(&m_matWVP);
			else if (name == "u_ViewProjMatrix")
				return (void*)(&camera->getViewProjMatrix());
			else if (name == "u_CameraPosition")
				return (void*)(&camera->getPosition());
			else if (name == "u_CameraNear")
				return (void*)(&camera->getNearClip());
			else if (name == "u_CameraFar")
				return (void*)(&camera->getFarClip());
		}

		return nullptr;
	}
}