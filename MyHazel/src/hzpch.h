#pragma once

#include "Hazel/Core/PlatformDetection.h"
#ifdef HZ_PLATFROM_WINDOWS
	#ifdef NOMINMAX
		#define NOMINMAX
	#endif
#endif
#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>
#include <array>

#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Hazel/Core/Log.h"
#include "Hazel/Core/Base.h"
#include "Hazel/Debug/Instrumentor.h"
#ifdef HZ_PLATFORM_WINDOWS
	#include <Windows.h>
#endif