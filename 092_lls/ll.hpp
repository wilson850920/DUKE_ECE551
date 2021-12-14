#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdlib>
#include <exception>


template<typename T>
class LinkedList {
	private:
		class Node {
			public:
				T data;
				Node * next;
				Node * prev;
				// Initialize
				Node() : next(NULL), prev(NULL){};
				Node(const T & data, Node * next, Node * prev) : data(data), next(next), prev(prev) {}
				Node(const T & data) : data(data), next(NULL), prev(NULL){}
			};
		Node * head;
		Node * tail;
		int size;

	public:
		LinkedList<T>() : head(NULL), tail(NULL), size(0) {}

		LinkedList<T>(const LinkedList & rhs){
			head = NULL;
			tail = NULL;
			//size = rhs.size;
			size = 0;

			Node * s = rhs.head;
			while(s != NULL) {
				addBack(s->data);
				s = s->next;
			}
		}

		LinkedList<T> & operator=(const LinkedList & rhs){
			if (this != &rhs) {
				LinkedList<T> temp(rhs);
				Node * old_head = head;
				head = temp.head;
				temp.head = old_head;
				Node * old_tail = tail;
				tail = temp.tail;
				temp.tail = old_tail;
				size = temp.size;
			}
			return *this;
		}
		
		~LinkedList<T>() {
			while(head != NULL){
				Node * temp = head->next;
				delete head;
				head = temp; 
			}
			head = NULL;
			tail = NULL;
			size = 0;
		}	

		void addFront(const T & item) {
			head = new Node(item, head, NULL);
			if(tail == NULL) {
				tail = head;
			}
			else {
				head->next->prev = head;
			}
			size ++;
		}
		
		void addBack(const T & item) {
			tail = new Node(item, NULL, tail);
			if(head == NULL) {
				head = tail;
			}
			else {
				tail->prev->next = tail;
			}
			size ++;
		}
		
		bool remove(const T & item) {	
			int index = find(item);
			if (index == -1) {
				return false;
			}
			else { 
				Node * temp = head;
				while(temp != NULL) {
					if (temp->data != item) {
						temp = temp->next;
					}
					else {
						if (head == tail && temp == tail){
						       head = tail = NULL;
						}
						else if (head == temp) {
							head = temp->next;
							head->prev = NULL;
						}
						else if (tail == temp) {
							tail = temp->prev;
							tail->next = NULL;
						}
						else {	
							temp->prev->next = temp->next;
							temp->next->prev = temp->prev;
						}
						delete temp;
						--size;
						return true;
					}
				}
				delete temp;
				return false;
			}
		}

		T & operator[](int index) {
			if (index >= 0 && index <= size) {
				Node * temp = head;
				for (int i = 0; i < index; i ++) {
					temp = temp->next;
				}
			       return temp->data;	
			}
			else{
				throw std::out_of_range("Out of Bounds");;
			}
		}

		const T & operator[](int index) const {
			if (index >= 0 && index <= size) {
				Node * temp = head;
				for (int i = 0; i < index; i ++) {
					temp = temp->next;
				}
			       return temp->data;	
			}
			else{
				throw std::out_of_range("Out of Bounds");;
			}
		}

		int find(const T & item){
			for (int i = 0; i < size; i ++) {
				if ((*this)[i] == item) {
					return i;
				}	
			}
			return -1;
		}

		int getSize() const{
			return size;
		}
	friend class Tester;

};



//YOUR CODE GOES HERE

#endif
