#include "Node.h"

bool Node::operator==(const Node& node) {
	return (this->ipV4Address == node.ipV4Address) &&
		(this->ipV6Address == node.ipV6Address) &&
		(this->nodeIdentifier == node.nodeIdentifier);
}

void Node::SendMessage(Message* message) {
	string content = message->GetContent();
	NodeConnection connection = InitiateHandshake(message->GetHandshake());
	
}