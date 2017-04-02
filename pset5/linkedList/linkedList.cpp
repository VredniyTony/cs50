#include <iostream>
#include <windows.h>
#include <stdio.h>

using namespace std;

class LinkedList {
	struct Node {
		Node* next;
		int data = 0;
		int index = 0;
	};

public:
	int length = 0, index = 1;
	Node* head = NULL;

	void add(int data) {
		Node* node = new Node();
		node->data = data;
		node->next = this->head;
		this->head = node;
		this->length++;
		node->index = index++;

	}
	void remove(int checkIndex) {
		Node* previousHead = NULL;
		Node* deleteHead = NULL;
		Node* node = head;
		while (1 == 1) {
			if (node->index == checkIndex) {
				node = previousHead;
				deleteHead = node ->next;
				node -> next = deleteHead->next;
				this->length--;
				return;
			}else{
				previousHead = node;
				node = node->next;
			}
		}
	}

	void print() {
		Node* head = this->head;
		while (head) {
			std::cout << head->data << " ";
			head = head->next;
		}
		std::cout << std::endl;
	}
};

int main() {
	LinkedList* list = new LinkedList();
	for (int count = 1; count <= 10; count++) {
		list->add(count);
	}
	list->remove(4);
	list->print();
	std::cout <<endl;
	delete list;
	system("pause");
	return 0;
}