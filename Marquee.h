#pragma once

/*
 * CHANGELOG:
 * 2023.03.02 Alexi Brooks - Created
 * 2023.03.07 Dylan Rothbauer - Completed implementing required fucntions
 * 2023.03.08 Dylan Rothbauer - updated decomission() to have upcoming = nullptr after deletion (so we dont point to something we dont own)
*/

#include <string>

//Class for holding a single bulletin
//Copied directly from in-class implementation
template <typename T>
class ListNode {
	//fields
private:
	T data;
	ListNode<T>* next;
	//methods
public:
	//constructor
	ListNode(T data) {
		this->data = data;
		next = nullptr;
	}
	ListNode(T data, ListNode<T>* next) {
		this->data = data;
		this->next = next;
	}
	//getters, setters
	T getData() { return data; }
	ListNode<T>* getNext() { return next; }
	void setData(T d) { data = d; }
	void setNext(ListNode<T>* n) { next = n; }
};

//Class for holding a linked list of string bulletins
class Marquee {
//FIELDS
private:
	ListNode<std::string>* upcoming{ nullptr }; //Only maintain the "upcoming" (pre-current) pointer
	int size{ 0 }; // size of list

	//Helper function to help the copy constructor and copy assignment
	void copyHelper(int size, ListNode<std::string>* otherc) {
		if (size > 0) {
			upcoming = new ListNode<std::string>{ otherc->getData() };
			ListNode<std::string>* current = upcoming;
			size--;
			// Does deep copy
			while (size > 0) {
				otherc = otherc->getNext();
				current->setNext(new ListNode<std::string>{ otherc->getData() });
				current = current->getNext();
				size--;
			}
			current->setNext(upcoming);
		}
	}

public:
	//Constructor
	Marquee() {
		// No really, im leaving this empty
	}

	//Copy Constructor
	Marquee(const Marquee& other) {

		copyHelper(other.size, other.upcoming);
		// increase OUR size to other size
		this->size = other.size;
	}

	//Destructor
	~Marquee() {
		// gets memory location that doesnt belong to us. Thank you.
//		ListNode<std::string>* a = upcoming;
//		while (a != nullptr) {
//			ListNode<std::string>* temp = a->getNext();
//			delete a;
//			a = temp;
//		}
		for (int i = 0; i < size; i++) {
			ListNode<std::string>* current = upcoming;
			upcoming = current->getNext();
			delete current;
		}

	}

	//Copy Assignment Operator
	Marquee& operator=(const Marquee& other) {
		// check for self assignment
		if (this == &other) {
			return *this;
		}

		this->~Marquee(); // delete first, then copy
		copyHelper(other.size, other.upcoming);
		// increase OUR size to other size
		this->size = other.size;
		return *this;
	}

	//Return the next string and advance
	std::string rotate() {
		upcoming = upcoming->getNext(); // advance
		return upcoming->getData(); // then return
	}

	//add as next to play
	void playNext(std::string s) {
		if (upcoming == nullptr) {
			ListNode<std::string>* newNode = new ListNode<std::string>{ s };
			upcoming = newNode;
			upcoming->setNext(upcoming);
			upcoming->setData(s);
			size++;
		}
		else {
			ListNode<std::string>* newNode = new ListNode<std::string>(s);
			newNode->setNext(upcoming->getNext());
			upcoming->setNext(newNode);
			size++;
		}
	}

	//remove the next and return it
	std::string decomission() {

		ListNode<std::string>* nodeToDelete = upcoming->getNext();
		std::string result = nodeToDelete->getData();
		upcoming->setNext(nodeToDelete->getNext());
		delete nodeToDelete;
		size--;

		// Make it point to nullptr
		//	that way we dont try to point to a node that doesn't exist
		if (size == 0) {
			upcoming = nullptr;
		}


		return result;
		
	}

	// Return size of list
	int getSize() { 
		return size;
	}
};