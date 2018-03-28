// 10.1-5: Write four O(1) time procedures to insert elements into and delete elements from both ends of a deque implemented by an array

#include <iostream>

using namespace std;

class myDeque
{
	private:
		int* mArr;
		int mLen;
		int mStart;
		int mHead;
		int mTail;
		char mChoice;
		int mInput;

	public:
		myDeque(int len = 0)
			: mLen(len), mInput(0)
		{
			mArr = new int[mLen] {0};

			cout << "Where should the deque begin? ";
			cin >> mStart;
			mHead = mTail = mStart;
		}

		void setDefaultPos()
		{
			int countBlankSpaces = 0;
			for(int index = 0; index < mLen; ++index)
			{
				if(mArr[index] == 0)
					countBlankSpaces++;
			}
			if(countBlankSpaces == mLen)
				mHead = mTail = mStart;
		}

		void insertBack()
		{
			cout << '\n';
			
			do
			{
				cout << "Enter a number to insert it at the back of the deque: ";
				cin >> mInput;

				if(mTail >= mHead && (mTail + 1) < mLen && mArr[mTail] == 0 && mArr[mTail + 1] == 0)
				{
					mArr[mTail] = mInput;
					mTail++;
				}
				else if(mTail + 1 < mHead && mArr[mTail] == 0 && mArr[mTail + 1] == 0)
				{
					mArr[mTail] = mInput;
					mTail++;
				}
				else if(mTail == mLen - 1 && mArr[0] == 0 && mArr[mTail] == 0)
				{
					mArr[mTail] = mInput;
					mTail = 0;
				}
				else
				{
					cout << "Error: The deque is full.\n";
				}

				cout << "Press 'y' to insert more numbers at the back: ";
				cin >> mChoice;
			}
			while(mChoice == 'y' || mChoice == 'Y');

			if(mArr[mTail] == 0)
				mTail--;
		}

		void deleteBack()
		{
			cout << '\n';
			
			cout << "Deleting a number from the back...\n";
			do
			{
				if(mTail < mLen && mTail >= mHead && mArr[mTail] != 0)
				{
					mArr[mTail] = 0;
					cout << *this;
					mTail--;
				}
				else if(mTail + 1 < mHead && mArr[mTail] != 0 && mArr[mTail - 1] != 0 && (mTail - 1) >= 0)
				{
					mArr[mTail] = 0;
					cout << *this;
					mTail--;
				}
				else if(mTail == 0 && mArr[mTail] != 0 && mArr[mLen - 1] != 0)
				{
					mArr[mTail] = 0;
					cout << *this;
					mTail = mLen - 1;
				}
				else
				{
					cout << "Error: The deque is empty.\n";
				}

				cout << "Press 'y' to delete more numbers from the back: ";
				cin >> mChoice;
			}
			while(mChoice == 'y' || mChoice == 'Y');

			if(mTail < mHead && mArr[mHead] == 0)
				mTail++;

			this->setDefaultPos();
		}

		void insertFront() 
		{
			cout << '\n';
			
			do
			{
				cout << "Enter a number to insert it at the front of the deque: ";
				cin >> mInput;

				if(mArr[mHead] != 0 && mArr[mHead - 1] == 0 && mHead - 1 != mTail + 1 && mHead - 1 != mTail && mHead - 1 >= 0)
				{
					mHead--;
				}
				else if(mArr[mHead] != 0 && mHead == 0 && mArr[mLen - 1] == 0 && mLen - 1 != mTail + 1 && mLen - 1 != mTail)
				{
					mHead = mLen - 1;
				}
				if(mArr[mHead] == 0)
				{
					mArr[mHead] = mInput;
				}
				else
				{
					cout << "Error: The deque is full.\n";
				}
				cout << *this;

				cout << "Press 'y' to insert more numbers at the front: ";
				cin >> mChoice;
			}
			while(mChoice == 'y' || mChoice == 'Y');

			if(mArr[mHead] == 0)
				mHead++;
			
		}

		void deleteFront() 
		{
			cout << '\n';
			
			do
			{
				if(mArr[mHead] != 0 && mHead >= 0 && mHead <= mTail)
				{
					cout << mArr[mHead] << " at index " << mHead << " deleted from the front.\n";
					mArr[mHead] = 0;
					mHead++;
				}
				else if(mArr[mHead] != 0 && mHead + 1 <= mLen - 1 && mHead > mTail + 1)
				{
					cout << mArr[mHead] << " at index " << mHead << " deleted from the front.\n";
					mArr[mHead] = 0;
					mHead++;
				}
				else if(mArr[mHead] != 0 && mHead == mLen - 1 && mArr[0] != 0 && mTail != mLen - 1)
				{
					cout << mArr[mHead] << " at index " << mHead << " deleted from the front.\n";
					mArr[mHead] = 0;
					mHead = 0;
				}
				else
				{
					cout << "Error: The deque is empty.\n";
				}
				cout << *this;
				
				cout << "mHead is " << mHead << " and mTail is " << mTail << '\n';
				cout << "Press 'y' to delete another number from the front. ";
				cin >> mChoice;
			}
			while(mChoice == 'y' || mChoice == 'Y');

			this->setDefaultPos();
		}

		friend ostream& operator<<(ostream& out, const myDeque& d);

		~myDeque()
		{
			delete[] mArr;
			mArr = nullptr;
		}
};


ostream& operator<<(ostream& out, const myDeque& d)
{
	for(int index = 0; index < d.mLen; index++)
		out << d.mArr[index] << " ";
	out << '\n';

	return out;
}

int main()
{
	int arrLen;
	cout << "How big should the array be? ";
	cin >> arrLen;

	myDeque d(arrLen);

	d.insertBack();
	cout << d;

	d.deleteBack();
	cout << d;

	d.insertFront();
	cout << d;

	d.deleteFront();
	cout << d;

	return 0;
}
