#include "MicroSecondTimer.h"
#include "sort.h"
#include <iostream>
#include <math.h>
#define NUMRECS 10000

using namespace std;

struct SortData
{
   int key;
   char strData[5];
   double numData;
};

bool ReadData(SortData DA[], int count);
void BubbleSort(SortData DA[], int count);
void InsertionSort(SortData DA[], int count);
void QuickSort(SortData DA[], int startIdx, int endIdx);
void MergeSort(SortData DA[], int startIdx, int endIdx);
void Merge(SortData DA[], int start1, int end1, int start2, int end2);
void ProxmapSort(SortData DA[], SortData DA2[], int count);
int Hash(int key, int KeyMax, int KeyMin, int count);
bool Verify(SortData DA[], int count);
bool getNextLine(ifstream *inF, char *line, int lineLen);
void Partition(SortData DA[], int *I, int *J);

int main(void)
{
	int ReadFile;
	double QSaverageTime=0;
	double MSaverageTime = 0;
	double timeInMS;
	int x, y;

	SortData DataArray[10000];
	SortData DataArray2[10000];

	//BUBBLESORT
	ReadFile = ReadData(DataArray, 9999);
	BubbleSort(DataArray, 9999); //Working
	if (Verify(DataArray, 9999))
		cout << "The list is correctly sorted.\n";
	else
		cout << "List is not properly sorted.\n";

	//INSERTIONSORT
	ReadFile = ReadData(DataArray, 9999);
	InsertionSort(DataArray, 9999); //Working
	if (Verify(DataArray, 9999))
		cout << "The list is correctly sorted.\n";
	else
		cout << "List is not properly sorted.\n";

	//QUICKSORT
	ReadFile = ReadData(DataArray, 9999);
	for(x=1; x<6; x++)
	{
		MicroSecondTimer *mst = new MicroSecondTimer();
		mst->Start();
		QuickSort(DataArray,0,9999); 
		mst->Stop();
		timeInMS = mst->getTime();
		QSaverageTime = (QSaverageTime + timeInMS)/x;
	}
	cout<<"QuickSort took " << QSaverageTime << " miscroseconds." << endl;
	if (Verify(DataArray, 9999))
		cout << "The list is correctly sorted.\n";
	else
		cout << "List is not properly sorted.\n";

	//MERGESORT
	ReadFile = ReadData(DataArray, 9999);
	for(x=1; x<6; x++)
	{
		MicroSecondTimer *mst = new MicroSecondTimer();
		mst->Start();
		MergeSort(DataArray,0,9999);  
		mst->Stop();
		timeInMS = mst->getTime();
		MSaverageTime = (MSaverageTime + timeInMS)/x;
	}
	cout<<"MergeSort took " << MSaverageTime << " miscroseconds." << endl;
	if (Verify(DataArray, 9999))
		cout << "The list is correctly sorted.\n";
	else
		cout << "List is not properly sorted.\n";

	//PROXMAPSORT
	ReadFile = ReadData(DataArray, 9999);
	ProxmapSort(DataArray, DataArray2,9999); 
	//for(int x = 0; x < 99;x++)
	//	cout<<DataArray[x].key<<"\n";
	if (Verify(DataArray, 9999))
		cout << "The list is correctly sorted.\n";
	else
		cout << "List is not properly sorted.\n";

	return 0;
}

bool ReadData(SortData DA[], int count)         // Read database from file
{
	ifstream  inF;        // Input file stream
	char      line[64];   // Line read from file

	inF.open("SortData.txt", ifstream::in);
	if(!inF.is_open())
	{
		return false;
	}

	for(int i=0; i<count; i++)
	{
		getNextLine(&inF, line, 64);
		DA[i].key = atoi(strtok(line, " "));
		strcpy(DA[i].strData, strtok(NULL, " "));
		DA[i].numData = atof(strtok(line, " "));
		//cout<< DA[i].key << " " << DA[i].strData << " " <<DA[i].numData << "\n";
	}

	inF.close();
	return true;
}

bool getNextLine(ifstream *inF, char *line, int lineLen)
{
    bool    done = false;

    while(!done)
    {
        inF->getline(line, lineLen);
        
        if(inF->good())    // If a line was successfully read
        {
           if(strlen(line) == 0)  // Skip any blank lines
                continue;
            else if(line[0] == '#')  // Skip any comment lines
                continue;
            else done = true;  // Got a valid data line so return it
        }
        else
        {
            strcpy(line, "");
            return false;  // Flag end of file
        }
    } // end while
	return true;
}

void BubbleSort(SortData DataArray[], int count) //Uses the Bubble Sort algorithm to sort the 10,000 items.
{
	MicroSecondTimer *mst = new MicroSecondTimer();
	double timeInMS;
	double averageTime = 0;
	int i, j, x;
    SortData temp;
	//SortData DataArray[NUMRECS];

	for(x=1; x<6; x++)
	{
		mst->Start();
		for(i=0; i<count; i++)
		{
			for(j=0; j<(count-i - 1); j++)
			{
				if(DataArray[j].key > DataArray[j+1].key)
				 {
					 temp = DataArray[j];
					 DataArray[j] = DataArray[j+1];
					 DataArray[j+1] = temp;
				 }
			}
		}
		mst->Stop();
		timeInMS = mst->getTime();
		averageTime = (averageTime + timeInMS)/x;
	}
	cout<<"BubbleSort took " << averageTime << " miscroseconds." << endl;
}

void InsertionSort(SortData DataArray[], int count) //Uses the Insertion Sort algorithm to sort the 10,000 items.
{
	MicroSecondTimer *mst = new MicroSecondTimer();
	double timeInMS;
	double averageTime=0;
	int i,j,x;
    SortData temp;
    int NotDone;
    int Key;

	for(x=1; x<6; x++)
	{
		mst->Start();
		for(i=1; i<count; i++)
		{
			Key = DataArray[i].key;
			j = i;
			NotDone = (DataArray[j-1].key > Key);

			temp = DataArray[j]; /* Remove and hold the one to be moved */

			while(NotDone)
			{
				/* Slide all others to the right */
				DataArray[j] = DataArray[j-1];
				j--;
				if(j > 0)
					NotDone = (DataArray[j - 1].key > Key);
				else
					NotDone = FALSE;
			}

			/* Put the removed record into it's correct slot */
			DataArray[j] = temp;
		}
			mst->Stop();
			timeInMS = mst->getTime();
			averageTime = (averageTime + timeInMS)/x;
	}
	cout<<"InsertionSort took " << averageTime << " miscroseconds." << endl;
}

void QuickSort(SortData DataArray[], int startIdx, int endIdx) //Uses the Quick Sort algorithm to sort the 10,000 items.
{
	int i,j;
	//SortData temp;

		if(startIdx < endIdx)
		{
			i=startIdx;
			j = endIdx;
			Partition(DataArray, &i, &j);
			/* On return i will be greater than j */
			QuickSort(DataArray, startIdx, j);
			QuickSort(DataArray, i, endIdx);
		}
}

void Partition(SortData DataArray[], int *I, int *J)
{
    int Pivot;    /* Key data */
    SortData temp;

    Pivot = DataArray[(*I + *J)/2].key; /* Choose an arbidrary pivot point like center of array */
    /* Divide the array into < and > Pivot */
    do
    {
        /* Find leftmost I such that DataArray[I].key > Pivot */
        while(DataArray[*I].key < Pivot) 
			(*I)++;

        /* Find rightmost J such that DataArray[J].key < Pivot */
        while(DataArray[*J].key > Pivot) 
			(*J)--;

        /* If i and J didn't cross over one another, then swap the structs */
        if(*I <= *J)
        {
            temp = DataArray[*I];
            DataArray[*I] = DataArray[*J];
            DataArray[*J] = temp;
            (*I)++;            /* Move i one space to the right */
            (*J)--;            /* Move j one space to the left */
        }
    }while(*I <= *J);
}

void MergeSort(SortData DataArray[], int startIdx, int endIdx) //Uses the Merge Sort algorithm to sort the 10,000 items.
{
	int start, end;

		if(startIdx < endIdx)    // If there is more than one item to sort 
		{
			start = startIdx;
			end = startIdx + ((endIdx - startIdx) / 2);
			MergeSort(DataArray, start, end);
			start = end + 1;
			end = endIdx;
			MergeSort(DataArray, start, end);
			Merge(DataArray, startIdx, start - 1, start, end);
		}
}

void Merge(SortData DataArray[], int start1, int end1, int start2, int end2) //supplementary function for the Merge Sort algorithm
{
	 int i, j;
     SortData temp;
     int NotDone;
     int Key;

	 for(i=start2; i<=end2; i++)
     {
          Key = DataArray[i].key;
          j = i;
          NotDone = (DataArray[j-1].key > Key);
          temp = DataArray[j]; 
		  while(NotDone)
          {
               // Slide all others to the right 
               DataArray[j] = DataArray[j-1];
               j--;
               if(j > start1)
                    NotDone = (DataArray[j - 1].key > Key);
               else
                    NotDone = FALSE;
          }
          // Put removed record into correct slot
          DataArray[j] = temp;
	 }
}

void ProxmapSort(SortData DataArray[], SortData DataArray2[], int count) //Uses the Proxmap Sort algorithm to sort the 10,000 items.
{
	MicroSecondTimer *mst = new MicroSecondTimer();
	double timeInMS;
	double averageTime=0;
	int i,x;
    int HitList[NUMRECS];
    int Hidx;                  /* Hashed index */
    int ProxMap[NUMRECS];
    int RunningTotal;          /* Number of hits */
    int Location[NUMRECS];
    int KeyMax, KeyMin;        /* Used in Hash() */

	for(x=1; x<6; x++)
	{
		mst->Start();
		/* Initialize hit list and proxmap */
		for(i=0; i<count; i++)
		{
			HitList[i] = 0;           /* Init to all 0 hits */
			ProxMap[i] = -1;          /* Init to all unused */
			DataArray2[i].key = -1;   /* Init to all empty */
		}

		/* Find the largest key for use in computing the hash */
		KeyMax = 0;        /* Guaranteed to be less than the smallest key */
		KeyMin = 32767;    /* Guaranteed to be more than the largest key */
		for(i=0; i<count; i++)
		{
			if(DataArray[i].key > KeyMax) KeyMax = DataArray[i].key;
			if(DataArray[i].key < KeyMin) KeyMin = DataArray[i].key;
		}

		/* Compute the hit count list (note this is not a collision count, but
			a collision count+1 */
		for(i=0; i<count; i++)
		{
			Hidx = Hash(DataArray[i].key, KeyMax, KeyMin, count);    /* Calculate hash index */
			Location[i] = Hidx;                                      /* Save this for later. (Step 1) */
			HitList[Hidx]++;                                         /* Update the hit count (Step 2) */
		}

		/* Create the proxmap from the hit list. (Step 3) */
		RunningTotal = 0;        /* Init counter */
		for(i=0; i<count; i++)
		{
			if(HitList[i] > 0)    /* There were hits at this address */
			{
				ProxMap[i] = RunningTotal;    /* Set start index for this set */
				RunningTotal += HitList[i];
			}
		}
		mst->Stop();
		timeInMS = mst->getTime();
		averageTime = (averageTime + timeInMS)/x;
	}
	cout<<"ProxmapSort took " << averageTime << " miscroseconds." << endl;
}

int Hash(int key, int KeyMax, int KeyMin, int count)
{
    float keyFloat;

    /* Map integer key to float in the range 0 <= key < 1 */
    keyFloat = (float)(key - KeyMin) / (float)(1 + KeyMax - KeyMin);

    /* Map float key to indices in range 0 <= index < count */
    return((int)floor(count * keyFloat));
}


bool Verify(SortData DataArray[], int count) //checks to see if the list is sorted correctly
{
	int i;

	for(i=0; i<count; i++)
	{
		if (DataArray[i].key > DataArray[i+1].key)
			return false;
		else
			return true;
	}
}