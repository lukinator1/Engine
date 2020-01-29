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
#include <GL/glew.h>
extern std::queue <Message> messagequeue;