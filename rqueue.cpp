// CMSC 341 - Spring 2021 - Project 3
// RQueue: 

#include "rqueue.h"
using namespace std;
using std::cout;
using std::endl;
using std::domain_error;

RQueue::RQueue(prifn_t priFn)
{
	_heap = nullptr;
	_size = 0;
	priority = priFn;

}

RQueue::~RQueue()
{
	clear();
	priority = nullptr;  //Not to sure

}

RQueue::RQueue(const RQueue& rhs)
{
	
	priority = rhs.priority;

	if (rhs._heap == nullptr)
	{
		_heap = nullptr;

		_size = 0;
	}

	else
	{
		
		_heap = copy(_heap,rhs._heap); //	set to _heap because the copy function returns the copy heap

		_size = rhs._size;

	}
}


RQueue& RQueue::operator=(const RQueue& rhs)
{
	clear();

	//self-assignment
	if (this != &rhs)
	{
		   // we clear in order to remove any data from previous queue

		priority = rhs.priority;
	}

	if (rhs._heap == nullptr)
	{
		_heap = nullptr;
	}

	else 
	{
		_heap = copy(_heap,rhs._heap); //set to _heap because we return the copy heap
	}

	return *this;
}

void RQueue::insertStudent(const Student& input) {

	Node* newStudent = new Node(input);
	RQueue newStudentHeap(priority);  // new heap
	newStudentHeap._heap = newStudent;// sets new heap to the new
	newStudentHeap._size = 1;
	 mergeWithQueue(newStudentHeap);
	//_size++;
	
}

Student RQueue::getNextStudent() {
	
	if(_heap == nullptr)
	{
		throw domain_error("heap is empty! ");
	}

	
		Node* nextStudentNode = _heap;
		Student nextStudent = _heap->getStudent();
		_heap = merge(_heap->_left, _heap->_right);
		_size--;// problem with size

		delete nextStudentNode;
		return nextStudent;
	

	//return the student of the root node
	//remove the root node
	//get the next root node from the left and right chikdren

	//make a pointer to copy the student, then delete the pointer
	
	//then delete the root student
	// merge the left heap and heap right
	// return the student of the old root

	//make a node pointer to the root of student
	//local studnet object that makes a copy of the student root
	//merge left heap and right heap
	//delete root

	//return a local student copy
}


void RQueue::mergeWithQueue(RQueue& rhs) {

	if (this == &rhs)
	{

		return;
	}

	if (priority != rhs.priority) 
	{
		throw domain_error("priority function is not the same");
	}

	_heap = merge(_heap, rhs._heap);
	_size += rhs._size;

	rhs._heap = nullptr;
	rhs._size = 0;
}

void RQueue::clear() {

	clearHeap(_heap);
	_heap = nullptr;
}

int RQueue::numStudents() const
{
	return _size;
}

void RQueue::printStudentQueue() const {
	
	preOrder(_heap);
}

prifn_t RQueue::getPriorityFn() const {
	return priority;
}

void RQueue::setPriorityFn(prifn_t priFn) {
	
	RQueue tempQueue(priFn); // queue object

	while (_heap != nullptr)			//inserts all node in old nodes to new heap
	{
		tempQueue.insertStudent(this->getNextStudent());
	}

	priority = priFn;

	_size = tempQueue._size; //Updating size of the current queue
	_heap = tempQueue._heap; 
	tempQueue._heap = nullptr;// empties out old heap
	
}

// for debugging
void RQueue::dump() const
{
	if (_size == 0) {
		cout << "Empty skew heap.\n";
	}
	else {
		dump(_heap);
		cout << endl;
	}
}

// for debugging
void RQueue::dump(Node* pos) const {
	if (pos != nullptr) {
		cout << "(";
		dump(pos->_left);
		cout << priority(pos->_student) << ":" << pos->_student.getName();
		dump(pos->_right);
		cout << ")";
	}
}

// overloaded insertion operator for Student class
ostream& operator<<(ostream& sout, const Student& student) {
	sout << "Student: " << student.getName() << ", priority: " << student.getPriority()
		<< ", year: " << student.getYear() << ", major: " << student.getMajorStr()
		<< ", group: " << student.getGroupStr();
	return sout;
}

// overloaded insertion operator for Node class
ostream& operator<<(ostream& sout, const Node& node) {
	sout << node.getStudent();
	return sout;
}

Node* RQueue:: copy(Node* heap, Node* rhs)
{
	if (heap == nullptr)
	{
		return nullptr;
	}


	//heap for the right hand side
	heap = new Node(rhs->_student);

	//we assign them to interconnect the lhs and rhs
	heap->_right = copy(heap->_right, rhs->_right);
	heap->_left = copy(heap->_left, rhs->_left);

	return heap;

}

void RQueue:: clearHeap(Node* heap)
{
	if (heap == nullptr)
	{
		return;
	}

	clearHeap(heap->_left);
	clearHeap(heap->_right);
	delete heap;
	//heap = nullptr;
	_size = 0;// _size--
}

Node* RQueue::merge(Node* p1, Node* p2)
{
	if (p1 == NULL) {
		return p2;
	}
	if (p2 == NULL) {
		return p1;
	}

	if (priority(p1->_student) > priority(p2->_student)) {
		swap(p1, p2);
	}


	swap(p1->_left, p1->_right);

	p1->_left = merge(p2, p1->_left);

	return p1;

}

void RQueue::preOrder(Node* heap) const
{
	if (heap == nullptr)
	{
		return;
	}


	cout << "[" << priority(heap->getStudent()) << "]" << heap->getStudent() << endl;
	preOrder(heap->_left);
	preOrder(heap->_right);
}



//n.b: comment shortcut: ctrl + k + c