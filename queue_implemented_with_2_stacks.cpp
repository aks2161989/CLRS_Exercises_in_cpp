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
		int mQLen;
		char mChoice;
		int secondStackStarts;
		int firstStackCount;
		int elementValue;

	public:

		Queue(int len = 0)
			:mArrLen(len)
		{
			mQLen = mArrLen - 1;
			
			mArr = new int[mArrLen] {0};

			secondStackStarts = mQLen / 2;
			if(mQLen % 2 != 0) // If mQLen is even, secondStackStarts is mQLen/2. When mQLen is odd, secondStackStarts is (mQLen/2) + 1
				secondStackStarts++;

			cout << "secondStackStarts is " << secondStackStarts << '\n';	

			firstStackCount = 0;
			elementValue = 1;
		}
		void moveElements()
		{
			int mark = 0;
			int tempLen = 0;
			int *tempArr = nullptr;
			int earlierElements = 0;

			for(int index = secondStackStarts; mArr[index] != 0; index++)
				earlierElements++;
			
			for(int index = secondStackStarts + earlierElements; index < mArrLen; ++index)
			{
				if(mArr[index] != 0)
				{
					if(mark == 0)
						mark = index;
					tempLen++;
				}
			}

			tempArr = new int[tempLen] {0};
			int tempCount = 0;
			for(int index = mark; index < (mark + tempLen); ++index)
			{
				tempArr[tempCount] = mArr[index];
				tempCount++;
			}

			tempCount = 0;
			mark = secondStackStarts + earlierElements;
			for(int index = mark ; index < (mark + tempLen); ++index)
			{
				mArr[index] = tempArr[tempCount];
				tempCount++;
			}

			mArr[mArrLen - 1] = 0;

			delete[] tempArr;
			tempArr = nullptr;
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
			else if(stack1Count + stack2Count == mArrLen - 1)
				return "CompletelyEmpty"; // Both Stacks Completely Empty
			else if(stack1Count != 0 && stack2Count != 0)
				return "FESE"; // First empty, Second empty (but queue not completely empty)
			return "";
		}
		void shiftStack()
		{
			int stackCounter = mArrLen - 1;
			int tempCounter = 0;
			int tempLen = 0;
			
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
			
			
			for(int index = secondStackStarts + 1; index < mArrLen ; ++index)
				tempLen++;

			static int* tempArr = new int[tempLen] {0};
			
			while(tempCounter < tempLen) // Copying the second stack into a temporary array
			{
				tempArr[tempCounter] = mArr[mArrLen - 1];
				tempCounter++;
				
				stackCounter = mArrLen - 1;
				while(stackCounter > secondStackStarts + 1)
				{
					mArr[stackCounter] = mArr[stackCounter - 1];
					mArr[stackCounter - 1] = 0;
					stackCounter--;
				}
			}
			
			cout << "tempArr is: ";
			for(int i = 0; i < tempLen; ++i)
				cout << tempArr[i] << ' ';
			cout << '\n';
			
			tempCounter = 0; // Pasting the temporary array into the first stack
			while(tempCounter < tempLen)
			{
				stackCounter = secondStackStarts - 1;
				mArr[0] = tempArr[tempCounter];
				
				while(stackCounter > 0 && tempCounter != tempLen - 1)
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
				this->moveElements();
				elementValue++;
				cout << *this;
			}
			else if(this->fullOrEmpty() != "FFSF")
			{
				this->shiftStack();
				this->enqueue();
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

	while(q.fullOrEmpty() != "FFSF")
		q.enqueue();

	return 0;
}



