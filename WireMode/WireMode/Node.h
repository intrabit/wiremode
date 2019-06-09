#pragma once
#include <string>
#include "Message.h"
#include "NodeConnection.h"

using std::string;

class Node
{
private:
	string nodeIdentifier;
	string ipV4Address;
	string ipV6Address;
	NodeConnection InitiateHandshake(HandshakeProtocol* handshake);
public:
	bool operator ==(const Node& node);
	void SendMessage(Message* message);
};

// Add a copy constructor.
// Represents a single node with all the information and methods for interacting with it.