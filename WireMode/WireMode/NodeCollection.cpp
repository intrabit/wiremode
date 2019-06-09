#include "NodeCollection.h"

NodeCollection::NodeCollection(string fileName) {
	/*
		Needs to take the file (probably xml) and process the data, adding each node
		stored in the file to the collection.
	*/
}

void NodeCollection::AddNode(Node newNode) {
	if (size == capacity) {
		resize(capacity + RESIZE_AMOUNT);
	}
	collection[size] = newNode;
	size++;
}

void NodeCollection::RemoveNode(Node* node) {
	if (collection != nullptr) {
		for (Node* nodeItr = collection; nodeItr != collection + size; nodeItr++) {
			if (*nodeItr == *node) {
				/*Shift array elements*/
				for (int i = (nodeItr - collection); i < size - 1; ++i) {
					collection[i] = collection[i + 1];
				}
				size--;
				/*Resize array*/
				if (size + RESIZE_AMOUNT <= capacity) {
					resize(capacity - RESIZE_AMOUNT);
				}
			}
		}
	}
}

void NodeCollection::BroadcastMessage(Message* message) {
	for (Node* nodeItr = collection; nodeItr != collection + size; nodeItr++) {
		nodeItr->SendMessage(message);
	}
}

void NodeCollection::SendDirectMessage(string nodeIdentifier, Message* message) {
	for (Node* nodeItr = collection; nodeItr != collection + size; nodeItr++) {
		if (nodeItr->nodeIdentifier == nodeIdentifier) {
			message->GetContent();
		}
	}
}

void NodeCollection::resize(int newSize) {
	Node* temp = new Node[newSize];
	memcpy(temp, collection, size);
	delete[] collection;
	collection = temp;
	capacity = newSize;
}