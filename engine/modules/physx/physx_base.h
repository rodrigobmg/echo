#pragma once

#include <engine/core/base/echo_def.h>

#if defined(ECHO_PLATFORM_IOS) || defined(ECHO_PLATFORM_MAC)
	#define NDEBUG
#endif

#include <PxPhysicsAPI.h>
#include <vehicle/PxVehicleSDK.h>
