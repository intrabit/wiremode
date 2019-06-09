#pragma once
#include "Message.h"
#include "Node.h"

class UpdateControllerMessage : public Message {
public:
	string GetContent();
	UpdateControllerMessage(Node newController);
};


