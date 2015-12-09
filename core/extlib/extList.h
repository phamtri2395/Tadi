/** extList.h

    A set of Data Structure based on Doubly Linked List & Iterator

	@docdate 11/14/2015
    @author phamtri2395@gmail.com
*/
#pragma once

/* Node class using template */
template <class T>
class Node {
public:
	T val;
	Node<T>* prev;
	Node<T>* next;

	/* Constructor */
	Node(const T& _value, Node<T>* _prev = nullptr, Node<T>* _next = nullptr) {
		val = _value;
		prev = _prev;
		next = _next;
	}
};

/* Abstract List class */
template <class T>
class List {
private:
	Node<T>* head;
	Node<T>* tail;
public:
	/* Constructors & Destructors */
	List(void) { head = tail = nullptr; }
	void Dispose(void) {
		Node<T>* current = head;
		head = tail = nullptr;
		while (current != nullptr) {
			Node<T>* next = current->next;
			delete current;
			current = next;
		}
	}

	/* Base Functions */
	bool isEmpty(void);
	bool virtual insertHead(const T&);
	bool virtual insertTail(const T&);
	bool virtual deleteHead(void);
	bool virtual deleteTail(void);
	T peekHead(void);
	T peekTail(void);
};

template <class T>
bool List<T>::isEmpty(void) {
	return (head == nullptr);
}

template <class T>
bool List<T>::insertHead(const T& value) {
	if (isEmpty()) head = tail = new Node<T>(value);
	else {
		head = new Node<T>(value, nullptr, head);
		head->next->prev = head;
	}

	return true;
}

template <class T>
bool List<T>::insertTail(const T& value) {
	if (isEmpty()) head = tail = new Node<T>(value);
	else {
		tail = new Node<T>(value, tail, nullptr);
		tail->prev->next = tail;
	}

	return true;
}

template <class T>
bool List<T>::deleteHead() {
	if (isEmpty()) return false;

	if (head == tail) {
		delete head;
		head = tail = nullptr;
		return true;
	}

	head = head->next;
	delete head->prev;
	head->prev = nullptr;

	return true;
}

template <class T>
bool List<T>::deleteTail() {
	if (isEmpty()) return false;

	if (head == tail) {
		delete head;
		head = tail = nullptr;
		return true;
	}

	tail = tail->prev;
	delete tail->next;
	tail->next = nullptr;

	return true;
}

template <class T>
T List<T>::peekHead() {
	return head->val;
}

template <class T>
T List<T>::peekTail() {
	return tail->val;
}





/* Stack class derived from List */
template <class T>
class Stack : private List<T> {
public:
	bool push(const T&);
	T pop(void);
	T peek(void);
	bool isEmpty();
};

template <class T>
bool Stack<T>::push(const T& value) {
	return insertTail(value);
}

template <class T>
T Stack<T>::pop() {
	T temp = peekTail();
	deleteTail();

	return temp;
}

template <class T>
T Stack<T>::peek() {
	return peekTail();
}

template <class T>
bool Stack<T>::isEmpty() {
	return List::isEmpty();
}





/* Queue class derived from List */
template <class T>
class Queue : private List<T> {
public:
	bool enqueue(const T&);
	T dequeue(void);
	T peek(void);
	bool isEmpty();
};

template <class T>
bool Queue<T>::enqueue(const T& value) {
	return insertTail(value);
}

template <class T>
T Queue<T>::dequeue() {
	T temp = peekHead();
	deleteHead();

	return temp;
}

template <class T>
T Queue<T>::peek() {
	return peekHead();
}

template <class T>
bool Queue<T>::isEmpty() {
	return List::isEmpty();
}