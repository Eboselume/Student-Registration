// CMSC 341 - Spring 2021 - Project 3
// driver.cpp: sample driver for the RQueue class.


#include "rqueue.h"
#include "time.h"
using namespace std;
// Priority functions compute an integer priority for a student. Internal
// computations may be floating point, but must return an integer.

int priorityFn1(const Student& tudent);
int priorityFn2(const Student& student);
void measureInsertionTime(int numTrials, int N);
void measureRemovalTime(int numTrials, int N);
bool CopyConstructor(RQueue queue);
bool AssignmentOperator(RQueue queue);

int main() {

	RQueue queue1(priorityFn1);
	RQueue queue2(priorityFn1);

	// Create some test students and insert them into the queue
	//Student(string name, int priority, int year, int major, int group)
	{
		Student student1("Sam", 1, 1, 1, 1);
		Student student2("Liz", 5, 1, 2, 0);
		Student student3("Nick", 2, 0, 0, 0);
		Student student4("Eva", 4, 3, 2, 1);

		queue1.insertStudent(student3);
		queue1.insertStudent(student1);
		queue1.insertStudent(student2);
		queue1.insertStudent(student4);

		std::cout << "\nqueue1 dump after inserting 4 students (Nick, Sam, Liz, Eva):" << std::endl;
		queue1.dump();

		Student student5("John", 6, 3, 2, 1);
		Student student6("Mia", 3, 0, 0, 0);

		queue2.insertStudent(student5);
		queue2.insertStudent(student6);

		std::cout << "\nqueue2 dump after inserting 2 students (John, Mia):" << std::endl;
		queue2.dump();

		queue1.mergeWithQueue(queue2);

		// Print the queue, change priority function, print again, change
		// again, print again.  Changing the priority function should cause
		// the heap to be rebuilt.

		std::cout << std::endl << "Contents of queue1 after merging with queue2:\n";
		queue1.printStudentQueue();
		std::cout << "\nDump queue1 after merging with queue2:\n";
		queue1.dump();

		queue1.setPriorityFn(priorityFn2);

		std::cout << std::endl << "Contents of queue1 after changing the priority function to priorityFn2:\n";
		queue1.printStudentQueue();
		std::cout << "\nDump queue1 after changing the priority function to priorityFn2:\n";
		queue1.dump();

		queue1.setPriorityFn(priorityFn1);

		std::cout << std::endl << "Contents of queue1 after changing the priority function back to priorityFn1:\n";
		queue1.printStudentQueue();
		std::cout << "\nDump queue1 after changing the priority function back to priorityFn1:\n";
		queue1.dump();

		//cout << queue1.numStudents() << endl;
		// Remove and print students in priority order

		std::cout << "\nFinal queue1 in priority order:\n";
		while (queue1.numStudents() > 0) {
			Student student = queue1.getNextStudent();
			std::cout << "[" << priorityFn1(student) << "] " << student << std::endl;
		}

	}

//	Test case: Basic correctness
	{
		cout << "\nTest case: Basic Correctness: " << endl;

		RQueue queue3(priorityFn1);  //local queue object

		Student student3("Nick", 2, 0, 0, 0);
		Student student4("Eva", 4, 3, 2, 1);
		Student student5("John", 6, 3, 2, 1);
		Student student6("Mia", 3, 0, 0, 0);


		queue3.insertStudent(student3);
		queue3.insertStudent(student4);
		queue3.insertStudent(student5);
		queue3.insertStudent(student6);

		queue3.printStudentQueue(); // reading them out in priority order functions correctly.
		
	
	}


	//Test case: Normal Insertion

	{
		RQueue queue4(priorityFn1);

		cout << "\nTest case: Normal Insertion: " << endl;

		Student student1("Sam", 1, 1, 1, 1);
		Student student2("Liz", 5, 1, 2, 0);

		queue4.insertStudent(student1);
		queue4.insertStudent(student2);
		
		if (queue4.numStudents() > 0)
		{

			cout << "Test passed! " << endl;
		}

		else
		{

			cout << "Test failed! " << endl;
		}
	}

	//Test case: Insertion of 1 data item
	{
		RQueue queue3(priorityFn2);

		cout << "\nTest case: Insertion of 1 data items: " << endl;

		Student student1("Sam", 1, 1, 1, 1);
		
		queue3.insertStudent(student1);

		if (queue3.numStudents() != 0)
		{
			cout << "Test passed! " << endl;
		}

		else
		{

			cout << "Test failed! " << endl;

		}
	}

	//Test case: Insertion of 0 data items
	{
		RQueue queue3(priorityFn2);

		cout << "\nTest case: Insertion of 0 data items: " << endl;
		Student student1("", 0, 0, 0, 0);
		
		queue1.insertStudent(student1);
		

		if (queue3.numStudents() == 0)
		{

			cout << "Test passed! " << endl;
		}

		else
		{

			cout << "Test failed! " << endl;

		}

	}

	//Test case: Assignment operator: data items in queue
	{
		cout << "\nTest case: Assignment Operator: data items in queue " << endl;

		RQueue queue3(priorityFn1);
		RQueue queue4(priorityFn1);

		Student student1("Sam", 1, 1, 1, 1);
		Student student2("Liz", 5, 1, 2, 0);

		queue3.insertStudent(student1);
		queue3.insertStudent(student2);

		queue3 = queue4;

		if (queue3.numStudents() == queue4.numStudents())
		{
			cout << "Test passed! " << endl;
		}

		else
		{
			cout << "Test failed" << endl;
		}

		
	}
	//Test case: Assignment operator: Empty queue
	{
		cout << "\nTest case: Assignment Operator: Empty queue" << endl;

		RQueue queue3(priorityFn1);

		

		
		if (AssignmentOperator(queue3) == true)
		{
			cout << "Test passed! " << endl;
		}

		else
		{
			cout << "Test failed! " << endl;

		}

	}

	//Test case: Self Assignment Operator 
	//if the program does not crash then it passed the test
	{
		cout << "\nTest case: Self - Assignment Operator: " << endl;

		RQueue queue3(priorityFn1);

		Student student1("Sam", 1, 1, 1, 1);
		Student student2("Liz", 5, 1, 2, 0);

		queue3.insertStudent(student1);
		queue3.insertStudent(student2);

		queue3 = queue3;

		cout << "Test passed! " << endl;

	}

	//Test case: Copy constructor: data items
	{
		cout << "\nTest case: Copy constructor: data items in queue" << endl;
		RQueue queue6(priorityFn1);

		Student student1("Sam", 1, 1, 1, 1);
		Student student2("Liz", 5, 1, 2, 0);

		queue6.insertStudent(student1);
		queue6.insertStudent(student2);

		RQueue copy(queue6);

		if (queue6.numStudents() == copy.numStudents())
		{

			cout << "Test passed! " << endl;
		}

		else
		{
			cout << "Test failed! " << endl;
		}

	}

	//Test case: Copy constructor: Empty queue
	{
	
		cout << "\nTest case: Copy constructor: Empty queue " << endl;

		RQueue queue6(priorityFn1);

		
		if (CopyConstructor(queue6) == true)
		{
			cout << "Test passed! " << endl;
		}

		else
		{
			cout << "Test failed! " << endl;

		}
	
	}

	
	//Test case: Large insertion and extraction

	//{
	//	cout << "\nTest case: Large insertion and Extraction " << endl;

	//	RQueue queue3(priorityFn1);

	//	for (int i = 0; i < 1000; i++)
	//	{
	//		Student student1("Eva ",i % 6 , i % 3, i % 2 , 1);

	//		queue3.insertStudent(student1);

	//	}
	//
	//	queue3.dump();

	//	while (queue3.numStudents() > 0) {
	//		Student student = queue3.getNextStudent();

	//		//std::cout << "[" << priorityFn1(student) << "] " << student << std::endl;
	//	}


	//}

	//Test case: Efficiency for large insertion and Extraction
	{
		cout << "\nTest case: Efficiency of Large insertion and Extraction: " << endl;

		int trials = 5;
		int num = 1000;

		cout << endl;

		measureInsertionTime(trials, num);

		cout << endl;

		measureRemovalTime(trials, num);

	}


	//Test case: exception case :  Merging queues with different priority functions 
 
{
	cout << "\nTest case: Exception case: Merging queues with different priority functions " << endl;

	RQueue queue3(priorityFn2);
	RQueue queue4(priorityFn1);


	Student student1("Sam", 1, 1, 1, 1);
	Student student2("Liz", 5, 1, 2, 0);
		
	queue3.insertStudent(student1);
	queue3.insertStudent(student2);
		
	Student student5("John", 6, 3, 2, 1);
	Student student6("Mia", 3, 0, 0, 0);

	queue4.insertStudent(student5);
	queue4.insertStudent(student6);

	try
	{
		//trying to merge queues with different prority function
		queue3.mergeWithQueue(queue4);
	}

	catch (domain_error& e)
	{
		//the exception that we expect
		cout << "Test passed! " << endl;
	}
	catch (...) {
		//any other exception, this case is not acceptable

		cout << "Test failed!" << endl;
		//return false;
	}
		
}

//Exception case: Dequeue an empty queue
{
	 cout << "\nTest case: Exception case:  Dequeue an empty queue  " << endl;

	RQueue queue3(priorityFn2);
	
	Student student1("", 0, 0, 0, 0);
	
	queue3.insertStudent(student1);

	try
	{
		//trying to dequeue an empty queue
		while (queue3.numStudents() > -1)
		{
			Student student = queue3.getNextStudent();
		}
	}

	catch (domain_error& e)
	{
		//the exception that we expect
		cout << "Test passed! " << endl;
	}
	catch (...) {
		//any other exception, this case is not acceptable

		cout << "Test failed!" << endl;
		//return false;
	}
}

	return 0;
}

int priorityFn1(const Student& student) {
	//priority value is determined based on some criteria
	//priority value falls in the range [0-6]
	//the smaller value means the higher priority
	int priority = student.getYear() + student.getMajor() + student.getGroup();
	return priority;
}

int priorityFn2(const Student& student) {
	//priority is determined by an officer in registrar office
	//priority value falls in the range [0-6]
	//the smaller value means the higher priority
	return student.getPriority();
}

void measureInsertionTime(int numTrials, int N)
{
	//Measuring the efficiency of insertion algorithm with system clock ticks
	//Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
	//Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.
	const int a = 2;//scaling factor for input size
	double T = 0.0;//to store running times
	clock_t start, stop;//stores the clock ticks while running the program
	for (int k = 0; k < numTrials - 1; k++)
	{

		RQueue p1(priorityFn1);//the algorithm to be analyzed for efficiency

		start = clock(); //starts stop watch
		
		for (int i = 0; i < N; i++)
		{
			Student student1("Eva ", i % 6, i % 3, i % 2, 1);

			p1.insertStudent(student1);

		}

		stop = clock();
		T = stop - start;//number of clock ticks the algorithm took
		cout << "Inserting " << N  << " members took " << T << " clock ticks (" << T / CLOCKS_PER_SEC << " seconds)!" << endl;
		N = N * a;//increase the input size by the scaling factor
	}
}

void measureRemovalTime(int numTrials, int N)
{
	//Measuring the efficiency of insertion algorithm with system clock ticks
	//Clock ticks are units of time of a constant but system-specific length, as those returned by function clock().
	//Dividing a count of clock ticks by CLOCKS_PER_SEC yields the number of seconds.
	const int a = 2;//scaling factor for input size
	double T = 0.0;//to store running times
	clock_t start, stop;//stores the clock ticks while running the program
	for (int k = 0; k < numTrials - 1; k++)
	{

		RQueue p1(priorityFn1);//the algorithm to be analyzed for efficiency


		for (int i = 0; i < N; i++)
		{
			Student student1("Eva ", i % 6, i % 3, i % 2, 1);

			p1.insertStudent(student1);

		}
		start = clock(); //starts stop watch

		while (p1.numStudents() > 0) {
			Student student = p1.getNextStudent();
		}

		stop = clock();
		T = stop - start;//number of clock ticks the algorithm took

		cout << "Extracting " << N << " members took " << T << " clock ticks (" << T / CLOCKS_PER_SEC << " seconds)!" << endl;
		N = N * a;//increase the input size by the scaling factor
	}
}

bool CopyConstructor(RQueue queue)
{
	RQueue copy(queue);
	
	while (copy.numStudents() > 0 && queue.numStudents() > 0 )
	{

		if (queue.getNextStudent().getName() != copy.getNextStudent().getName())
		{
		
			return false;
		}
	}

	return true;


}

bool AssignmentOperator(RQueue queue)
{
	RQueue queue5(priorityFn1);

	
	queue5 = queue;

	while (queue5.numStudents() > 0)
	{

		if (queue.getNextStudent().getName() != queue5.getNextStudent().getName())
		{
			

			return false;
		}
	}

	

	return true;
}