#include "LinkedList.h"



int main()
{
	char* myList;
	StringListInit(&myList);

	StringListAdd(&myList, "abc3");
	StringListAdd(&myList, "abc2");
	StringListAdd(&myList, "abc4");
	StringListAdd(&myList, "abc1");
	StringListAdd(&myList, "abc1");
	StringListAdd(&myList, "abc2");
	StringListAdd(&myList, "abc0");

	
	StringListRemove(&myList, "abc2");
	

	//StringListSort(&myList);
	//StringListReplaceInStrings(&myList, "abc2", "zzz");

	//StringListRemoveDuplicates(&myList);
	
	/*
	StringListDestroy(&myList);
	if(myList)
		PrintList(&myList);
	*/

	//printf("%d\n", StringListIndexOf(&myList, "abc2"));

	//printf("%d\n", StringListSize(&myList));

	PrintList(&myList);

	return 0;
}
