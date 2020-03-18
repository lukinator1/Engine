#pragma once
#include "Messaging/Message.h"
#include <queue>
extern std::queue <Message> messagequeue;
extern int messagequeuecapacity;
extern float deltatime;