#pragma once
#include <string>
#include "HandshakeProtocol.h"

using std::string;

class Message
{
public:
	virtual string GetContent() = 0;
	virtual HandshakeProtocol* GetHandshake() = 0;
};