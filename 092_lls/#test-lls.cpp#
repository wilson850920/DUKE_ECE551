#include <assert.h>

#include <cstdlib>
#include <iostream>

#include "ll.hpp"

typedef LinkedList<int> IntList;

class Tester {
 public:
  // testing for default constructor is done for you
  void testDefCtor() {
    IntList l1;
    assert(l1.head == NULL);
    assert(l1.tail == NULL);
    assert(l1.getSize() == 0);
  }
  // example of another method you might want to write
  void testAddFront() {
    // WRITE ME	

	  IntList l1;
	  l1.addFront(4);
	  assert(l1[0] == 4 && l1.getSize() == 1 && l1.head->next == NULL && l1.head->prev == NULL && l1.tail != NULL && l1.tail == l1.head);

	  assert(l1.head == l1.tail);
	  assert(l1.head != NULL);
	  assert(l1[0] == 4);
	  assert(l1.getSize() == 1);

	  l1.addFront(2);
	  assert(l1.head->next->prev == l1.head);
	  assert(l1.head->next = l1.tail);
	  assert(l1.head->next->next == NULL);
	  assert(l1.head->prev == NULL);
	  assert(l1.tail->prev == l1.head);
	  assert(l1[0] == 2);
	  assert(l1[1] == 4);
	  assert(l1.getSize() == 2);

	  IntList l2 = l1;
	  assert(l1.head != l2.head);
	  assert(l1.tail != l2.tail);
	  assert(l2.tail->prev == l2.head);
	  assert(l2.head->next->prev == l2.head);
	  assert(l2.head->next = l2.tail); 
	  assert(l1.head->next->next == NULL);
	  assert(l2.head->prev == NULL);
	  assert(l2[0] == 2);
	  assert(l2[1] == 4);
	  assert(l2.getSize() == 2);

	  IntList l3;
	  l3.addFront(1000);
	  l3.remove(1000);
	  assert(l3.head == NULL);
      	  assert(l3.tail == NULL);
      	  assert(l3.getSize() == 0);
	
  }

  void testAddBack() {
	  IntList l1;
	  l1.addBack(8);
	  assert(l1.head == l1.tail);
	  assert(l1.head->prev == NULL);
	  assert(l1.head->next == NULL);
	  assert(l1.head != NULL);
	  assert(l1[0] == 8);
	  assert(l1.getSize() == 1);

	  l1.addBack(2);
	  assert(l1.head->next->prev == l1.head);
	  assert(l1.head->next->next == NULL);
	  assert(l1.head->prev == NULL);
	  assert(l1.head->next == l1.tail);
	  assert(l1[0] == 8);
	  assert(l1[1] == 2);
	  assert(l1.getSize() == 2);

	  IntList l2;
	  l2.addBack(1);
	  l2.addBack(2);
	  l2.addBack(3);
	  l2 = l1;
	  assert(l1.head != l2.head);
	  assert(l2.tail->prev == l2.head);
	  assert(l2[0] == 8 && l2[1] == 2);
	  assert(l2.getSize() == 2);

	  IntList l3(l1);
	  l3.addBack(3);
	  assert(l3.getSize() == 3);
	  assert(l3[2] == 3);
	  assert(l3.find(3) == 2);
	  assert(l3.find(11) == -1);
	  assert(l3.head != l1.head);
  }

  void remove() {
	IntList l1;
	l1.addFront(3);
	l1.addFront(2);
	l1.addFront(1);
	
	l1.remove(3);
	assert(l1.head->next->next == NULL);
	assert(l1.head == l1.tail->prev);
	assert(l1.head->next == l1.tail);
	assert(l1.getSize() == 2);
	assert(l1[0] == 1 && l1[1] == 2);
	
	l1.addBack(3);
	l1.remove(2);
	assert(l1.getSize() == 2);
	assert(l1[1] == 3);
	assert(l1.head->next == l1.tail);
	assert(l1.head == l1.tail->prev);
	assert(l1[0] == 1 && l1[1] == 3);
	
	l1.addFront(0);
	l1.remove(0);
	assert(l1.head == l1.tail->prev);
	assert(l1[0] == 1 && l1[1] == 3);
	assert(l1.head->next->next == NULL);
	assert(l1.head->prev == NULL);
	assert(l1.head->next == l1.tail);
	assert(l1.getSize() == 2);
	
	l1.remove(1);
	assert(l1.remove(1) == false);
	assert(l1.head->next == NULL);
	assert(l1.head->prev == NULL);
	assert(l1.head == l1.tail);
	assert(l1[0] == 3);
  }
  // many more tester methods
};

int main(void) {
  Tester t;
  t.remove();
  t.testDefCtor();
  t.testAddFront();
  t.testAddBack();
  // write calls to your other test methods here
  return EXIT_SUCCESS;
}
