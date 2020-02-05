#pragma once
#include <queue>
#include <chrono>
#include <ctime>
#include <ratio>
#include <thread>
#include "Message.h"
#include "Logger.h"
#include "Math.h"
#include "vector3.h"
#include "vector2.h"
#include "matrix4f.h"
#include <GL/glew.h>
extern std::queue <Message> messagequeue;