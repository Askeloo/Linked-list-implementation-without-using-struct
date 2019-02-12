#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PTR_SIZE sizeof(void*)
typedef unsigned int uint;

enum indexes{NEXT, CURR};

void StringListInit(char** list);  /* Initializes list */
void StringListDestroy(char** list); /* Destroy list and set pointer to NULL. */

void StringListAdd(char** list, const char* str); /* Inserts value at the end of the list. */
void StringListRemove(char** list, const char* str);  /* Removes all occurrences of str in the list. */

uint StringListSize(char** list);  /* Returns the number of items in the list. */
uint StringListIndexOf(char** list, const char* str); /* Returns the index position of the first occurrence of str in the list. */

void StringListRemoveDuplicates(char** list); /* Removes duplicate entries from the list. */
void StringListReplaceInStrings(char** list, const char* before, const char* after); /* Replaces every occurrence of the before, in each of
																			the string lists's strings, with after. */
void StringListSort(char** list); /* Sorts the list of strings in ascending order */

void PrintList(char** list);


int main()
{
	char* myList;
	StringListInit(&myList);

	StringListAdd(&myList, "abc3");
	StringListAdd(&myList, "abc4");
	StringListAdd(&myList, "abc1");
	StringListAdd(&myList, "abc2");
	StringListAdd(&myList, "abc2");

	//StringListSort(&myList);
	//StringListReplaceInStrings(&myList, "abc2", "zzz");
	
	//StringListRemoveDuplicates(&myList);    //error

	StringListDestroy(&myList);
	if(myList)
		PrintList(&myList);

	//printf("%d\n", StringListIndexOf(&myList, "abc2"));

	/*
	printf("%d\n", StringListSize(&myList));
	PrintList(&myList);

	StringListRemove(&myList, "abc2");

	printf("%d\n", StringListSize(&myList));
	PrintList(&myList);*/



	return 0;
}


void PrintList(char** list)
{
	printf("----------------\n");
	uint* node = (uint*)(*list);

	while (node != NULL)
	{
		char* str = (char*)(node[CURR]);
		printf("%s\n", str);
		printf("----------------\n");
		node = (uint*)node[NEXT];
	}
	printf("\n");
}


void StringListInit(char** list)
{
	*list = NULL;
}


void StringListAdd(char** list, const char* str)
{
	if (*list)	// adding not first element
	{
		uint* node = (uint*)*list;

		while (node[NEXT] != NULL) node = (uint*)node[NEXT];

		uint* newNode = (uint*)malloc(PTR_SIZE * 2);
		newNode[CURR] = (uint)malloc(strlen(str) + 1);            //should check if not NULL
		strcpy((char*)newNode[CURR], str);
		newNode[NEXT] = NULL;

		node[NEXT] = (uint)newNode;
	}
	else 
	{
		uint* newNode = (uint*)malloc(PTR_SIZE * 2);
		newNode[CURR] = (uint)malloc(strlen(str) + 1);            //should check if not NULL
		strcpy((char*)newNode[CURR], str);
		newNode[NEXT] = NULL;

		*list = (char*)newNode;
	}
}


void StringListRemove(char** list, const char* str)
{
	uint* node = (uint*)*list;
	uint* prev_node = NULL;

	while (node != NULL)
	{
		if (!strcmp((char*)node[CURR], str))
		{
			free((void*)node[CURR]);

			if (prev_node)						//deleting not first element
				prev_node[NEXT] = node[NEXT]; 
			else   
				*list = (char*)node[NEXT];

			void* node_to_free = (void*)node;
			node = (uint*)node[NEXT];
			free(node_to_free);
		}
		else
		{
			prev_node = node;
			node = (uint*)node[NEXT];
		}		
	}
}


uint StringListSize(char** list)
{
	uint* node = (uint*)(*list);
	uint amount = 0;

	while (node != NULL)
	{
		amount++;
		node = (uint*)node[NEXT];
	}
	return amount;
}


uint StringListIndexOf(char** list, const char* str)
{
	uint* node = (uint*)*list;
	uint amount = 0;

	while (node != NULL)
	{
		if (!strcmp((char*)node[CURR], str))
			break;
		else
			amount++;

		node = (uint*)node[NEXT];
	}
	return (amount == StringListSize(list)) ? -1 : amount;
}


void StringListSort(char** list)		//	Selection sort
{
	uint tmp = 0;
	for (uint* node = (uint*)*list; node[NEXT] != NULL; node = (uint*)node[NEXT]) 
	{
		uint* node_min_element = node;
		for (uint* iter_node = (uint*)node[NEXT]; iter_node != NULL; iter_node = (uint*)iter_node[NEXT])
		{
			if (strcmp((char*)iter_node[CURR], (char*)node_min_element[CURR]) < 0)
				node_min_element = iter_node;
		}
		tmp = node[CURR];
		node[CURR] = node_min_element[CURR];
		node_min_element[CURR] = tmp;
	}
}


void StringListReplaceInStrings(char** list, const char* before, const char* after)
{
	for(uint* node = (uint*)*list; node != NULL; node = (uint*)node[NEXT])
	{
		if (!strcmp((char*)node[CURR], before))
		{
			node[CURR] = (uint)realloc((void*)node[CURR], strlen(after) + 1);
			strcpy((char*)node[CURR], after);
		}
	}
}


void StringListRemoveDuplicates(char** list)		// remove after sorting
{
	StringListSort(list);

	for (uint* node = (uint*)*list; node[NEXT] != NULL; node = (uint*)node[NEXT])
	{
		auto s1 = (char*)node[CURR];						//error
		auto s2 = (char*)(((uint*)node[NEXT])[CURR]);

		if (!strcmp((char*)node[CURR], (char*)(((uint*)node[NEXT])[CURR])))
		{
			node[NEXT] = ((uint*)node[NEXT])[NEXT];

			free((void*)((uint*)node[NEXT])[CURR]);
			void* node_to_free = (void*)node[NEXT];
			free(node_to_free);
		}
	}
}


void StringListDestroy(char** list)
{
	for (uint* node = (uint*)*list; node != NULL; node = (uint*)*list)
	{
		*list = (char*)node[NEXT];

		free((void*)node[CURR]);
		free((void*)node);
	}

}