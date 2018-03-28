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
		int mLen;
		char mChoice;
		int secondStackStarts;
		int firstStackCount;
		int secondStackCount;
		int elementValue;

	public:

		Queue(int len = 0)
			:mLen(len)
		{
			mArr = new int[mLen] {0};

			secondStackStarts = mLen / 2;
			cout << "secondStackStarts is " << secondStackStarts << '\n';	

			firstStackCount = 0;
			secondStackCount = mLen - 1;
			elementValue = 1;
		}
		void moveElements(int startPoint, int endPoint)
		{
			int mark = 0;
			int tempLen = 0;
			int *tempArr = nullptr;

			for(int index = startPoint; index < endPoint; ++index)
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
			for(int index = mark - 1; index < (mark + tempLen) - 1; ++index)
			{
				mArr[index] = tempArr[tempCount];
				tempCount++;
			}

			if(startPoint == secondStackStarts)
				mArr[mLen - 1] = 0;
			else
				mArr[0] = 0;

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
			for(int index = secondStackStarts; index < mLen; ++index)
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
			else if(stack1Count + stack2Count == mLen)
				return "CompletelyEmpty"; // Both Stacks Completely Empty
			else if(stack1Count != 0 && stack2Count != 0)
				return "FESE"; // First empty, Second empty (but queue not completely empty)
			return "";
		}
		void shiftStack()
		{
			int stackCounter = mLen - 1;
			int tempCounter = 0;
			int tempLen = 0;
			
			for(int index = secondStackStarts; index < mLen ; ++index)
				tempLen++;

			int* tempArr = new int[tempLen] {0};
			
			while(tempCounter < tempLen) // Copying the second stack into a temporary array
			{
				tempArr[tempCounter] = mArr[mLen - 1];
				tempCounter++;
				
				while(stackCounter > secondStackStarts)
				{
					mArr[stackCounter] = mArr[stackCounter - 1];
					mArr[stackCounter - 1] = 0;
					stackCounter--;
				}
				if(mArr[mLen - 1] == 0)
					break;
			}
			
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
				mArr[ mLen - 1 ] = elementValue;
				cout << *this;

				if(secondStackCount - 1 >= secondStackStarts)
				{
					this->moveElements(secondStackStarts, mLen);
					secondStackCount--;
					elementValue++;
				}
				else
				{
					elementValue++;
					this->enqueue();
				}
			}
			else if(this->fullOrEmpty() != "FFSF")
			{
				this->shiftStack();
				secondStackCount = mLen - 1;
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
	for(int index = 0; index < q.mLen; ++index)
	{
		out << q.mArr[index] << " ";
	}
	out << '\n';

	out << "QUEUE:";
	for(int index = 0; index < q.mLen; ++index)
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



