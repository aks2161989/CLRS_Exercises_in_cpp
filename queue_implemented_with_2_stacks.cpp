/* 10.1-6
   Show how to implement a queue using two stacks. Analyze the running time of
   the queue operations.
 */

#include <iostream>
#include <string>

using namespace std;

class Queue
{
	private:
		int *mArr = nullptr;
		int mArrLen;
		char mChoice;
		int secondStackStarts;
		int firstStackCount;
		int elementValue;
		int firstStackLength;
		int secondStackLength;
		int *tempCopy = nullptr;
		int copyLength = 0;
		int tempCounter;

	public:

		Queue(int len = 0)
			:mArrLen(len)
		{
			mArr = new int[mArrLen] {0};

			secondStackStarts = (mArrLen - 1) / 2; // Because the last element is a blank (0) element
			firstStackLength = secondStackStarts;
			secondStackLength = firstStackLength; // For even-length queues, both stacks are of equal length
			if(mArrLen % 2 == 0 && mArrLen != 2) // If queue is even (array is odd), secondStackStarts is mArrLen - 1/2. When queue is odd, secondStackStarts is (mArrLen - 1/2) + 1
			{
				secondStackStarts++;
				firstStackLength++;
				secondStackLength--; // For odd-length queues, second stack is one element less than the first stack
			}
			else if(mArrLen == 2)
			{
				firstStackLength++;
				secondStackLength = firstStackLength;
			}
			tempCopy = new int[ firstStackLength ] {0};
			copyLength = firstStackLength;			

			cout << "secondStackStarts is " << secondStackStarts << '\n';	

			firstStackCount = 0;
			elementValue = 1;
		}
		void moveElements()
		{
			int earlierElements = 0;

			for(int index = secondStackStarts; mArr[index] != 0; index++) 
				earlierElements++;
			
			for(int index = mArrLen - 1; index > secondStackStarts + earlierElements; --index) 
			{
				mArr[index - 1] = mArr[index];
				mArr[index] = 0;
			}
		}
		const string fullOrEmpty()
		{
			int stack1Count = 0;
			int stack2Count = 0;

			for(int index = 0; index < secondStackStarts; ++index)
			{
				if(mArr[index] == 0)
					stack1Count++;
			}
			for(int index = secondStackStarts; index < mArrLen - 1; ++index)
			{
				if(mArr[index] == 0)
					stack2Count++;
			}

			if(stack1Count == 0 && stack2Count == 0)
				return "FFSF"; // First Full, Second Full
			else if(stack1Count == 0 && stack2Count != 0)
				return "FFSE"; // First Full, Second Empty
			else if(stack1Count != 0 && stack2Count == 0)
				return "FESF"; // First empty, second full
			else if(stack1Count + stack2Count == (mArrLen - 1))
				return "CompletelyEmpty"; // Both Stacks Completely Empty
			else if(stack1Count != 0 && stack2Count != 0)
				return "FESE"; // First empty, Second empty (but queue not completely empty)
			return "";
		}
		void copyStack()
		{
			if(tempCopy[copyLength - 1] != 0) // The second time copyStack() is called, just copy one element
			{
				int secStackCounter = secondStackStarts;
				while(secStackCounter < mArrLen - 1) // Moving the single element from secondStackStarts to mArrLen - 1 
				{
					mArr[secStackCounter + 1] = mArr[secStackCounter];
					mArr[secStackCounter] = 0;
					secStackCounter++;
				}
				tempCopy[ 0 ] = mArr[mArrLen - 1];
				mArr[ mArrLen - 1 ] = 0;
				
				return ;
			}
			int stackCounter = mArrLen - 1;
			
			if(firstStackLength == secondStackLength)// Start filling the temporary array from the second element in case of odd-length queues
				tempCounter = 0;
			else
				tempCounter = 1;
				
			copyLength = firstStackLength;
			
			while(stackCounter > secondStackStarts) // Pushing the 0 at mArrLen - 1 to secondStackStarts, so that elements can be extracted easily
			{
				mArr[stackCounter] = mArr[stackCounter - 1];
				mArr[stackCounter - 1] = 0;
				stackCounter--;
			}
			
			cout << "second stack is: ";
			for(int i = secondStackStarts ; i < mArrLen; ++i)
				cout << mArr[i] << ' ';
			cout << '\n';
			
			
			tempCopy = new int[copyLength] {0};
			
			while(tempCounter < copyLength) // Copying the second stack into a temporary array
			{
				tempCopy[tempCounter] = mArr[mArrLen - 1];
				tempCounter++;
				
				stackCounter = mArrLen - 1;
				while(stackCounter > secondStackStarts + 1)
				{
					mArr[stackCounter] = mArr[stackCounter - 1];
					mArr[stackCounter - 1] = 0;
					stackCounter--;
				}
			}
			
			cout << "tempCopy is: ";
			for(int i = 0; i < copyLength; ++i)
				cout << tempCopy[i] << ' ';
			cout << '\n';
		}
		void pasteStack() 
		{	
			int stackCounter;		
			tempCounter = 0; // Pasting the temporary array into the first stack
			while(tempCounter < copyLength)
			{
				stackCounter = secondStackStarts - 1;
				mArr[0] = tempCopy[tempCounter];
				
				while(stackCounter > 0 && tempCounter != copyLength - 1)
				{
					mArr[stackCounter] = mArr[stackCounter - 1];
					mArr[stackCounter - 1] = 0;
					stackCounter--;
				}
				tempCounter++;				
			} 
		}
		friend ostream& operator<<(ostream& out, const Queue& q);
		void enqueue()
		{
			if(this->fullOrEmpty() == "FFSE" || this->fullOrEmpty() == "FESE" || this->fullOrEmpty() == "CompletelyEmpty")
			{
				mArr[ mArrLen - 1 ] = elementValue;
				if(mArr[mArrLen - 2] == 0)
					this->moveElements();
				elementValue++;
				cout << *this;
			}
			else if(this->fullOrEmpty() != "FFSF")
			{
				this->copyStack();
				
				if(firstStackLength > secondStackLength)
				{
					this->enqueue();
					this->copyStack();
				}
				this->enqueue();
				this->pasteStack();
				cout << *this;
			}
		}
		void dequeue()
		{
			int elementdequeued = 0;
			while( mArr[ 0 ] != 0 )
			{
				elementdequeued = mArr[ 0 ];
				mArr[ 0 ] = 0;
				
				for(int stackOneIndex = 0; stackOneIndex < secondStackStarts - 1; stackOneIndex++)
				{
					mArr[ stackOneIndex ] = mArr[ stackOneIndex + 1];
					mArr[ stackOneIndex + 1 ] = 0;
				}
				cout << "Element " << elementdequeued << " dequeued from queue.\n";
				cout << *this;
			}
			if( this->fullOrEmpty() == "FESF")
			{
				delete[] tempCopy;
				tempCopy = new int[ copyLength ]{ 0 };
				this->copyStack();
				this->pasteStack();
				if( mArr[ 0 ] == 0 ) // When Array is even and queue is odd, 0 is pasted on index 0 of mArr by pasteStack()
				{
					int counter = 0;
					while( counter < secondStackStarts - 1 ) // Shift 0 from index 0 to index secondStackStarts - 1, in case of even arrays (odd queues)
					{
						mArr[ counter ] = mArr [ counter + 1 ];
						mArr[ counter + 1 ] = 0;
						counter++;
					}
				}
				this->dequeue();
			}
		}

		~Queue()
		{
			delete[] mArr;
			mArr = nullptr;
		}

};

ostream& operator<<(ostream& out, const Queue& q)
{
	out << "ARRAY: ";
	for(int index = 0; index < q.mArrLen; ++index)
	{
		out << q.mArr[index] << " ";
	}
	out << '\n';

	out << "QUEUE:";
	for(int index = 0; index < q.mArrLen; ++index)
	{
		if(q.mArr[index] != 0)
		{
			out << ' ' << q.mArr[index];
		}
	}
	out << '\n';

	return out;
}

int main()
{
	int len;
	cout << "How many elements should the queue have? ";
	cin >> len;

	Queue q(len);

	cout << "\nENQUEUEING...\n";
	while(q.fullOrEmpty() != "FFSF")
		q.enqueue();

	cout << "\nDEQUEUEING...\n";
	if(q.fullOrEmpty() != "CompletelyEmpty")
		q.dequeue();
		
	return 0;
}



