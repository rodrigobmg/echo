#include "physx_shape.h"
#include "../physx_world.h"
#include "../physx_body.h"
#include <engine/core/main/Engine.h>

namespace Echo
{
	PhysxShape::PhysxShape()
	{
		m_pxMaterial = PhysxWorld::instance()->getPxPhysics()->createMaterial(0.5f, 0.5f, 0.5f);
	}

	PhysxShape::~PhysxShape()
	{
		if (m_pxShape)
		{
			PhysxBody* body = ECHO_DOWN_CAST<PhysxBody*>(getParent());
			if (body && body->getPxBody())
			{
				body->getPxBody()->detachShape(*m_pxShape);
				m_pxShape->release();
				m_pxShape = nullptr;
			}
		}
	}

	void PhysxShape::bindMethods()
	{

	}

	void PhysxShape::update_self()
	{
		if (m_isEnable && !m_pxShape)
		{
			PhysxBody* body = ECHO_DOWN_CAST<PhysxBody*>(getParent());
			if (body && body->getPxBody())
			{
				m_pxShape = createPxShape();
				if (m_pxShape)
				{
					physx::PxTransform localTransform((physx::PxVec3&)getLocalPosition(), (physx::PxQuat&)getLocalOrientation());
					m_pxShape->setLocalPose(localTransform);

					body->getPxBody()->attachShape(*m_pxShape);
				}
			}
		}

		if (m_pxShape)
		{
			if (!Engine::instance()->getConfig().m_isGame)
			{
				physx::PxTransform pxTransform((physx::PxVec3&)getLocalPosition(), (physx::PxQuat&)getLocalOrientation());
				m_pxShape->setLocalPose(pxTransform);
			}
		}
	}
}