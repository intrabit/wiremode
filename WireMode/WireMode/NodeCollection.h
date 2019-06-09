#pragma once
#include "Node.h"
#include "Message.h"
#include <string>

using std::string;

class NodeCollection
{
private:
	int size;
	int capacity;
	Node* collection;
	const int RESIZE_AMOUNT = 5;
	void resize(int newSize);
public:
	NodeCollection(string sourceFile);
	NodeCollection() : size(0), capacity(0), collection(nullptr) { }
	void AddNode(Node newNode);
	void RemoveNode(Node* node);
	void BroadcastMessage(Message* message);
	void SendDirectMessage(string nodeIdentifier, Message* message);
};