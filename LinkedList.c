#include "LinkedList.h"

#define PTR_SIZE sizeof(void*)
enum indexes { NEXT, CURR };


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

		while (node[NEXT] != NULL) 
			node = (uint*)node[NEXT];

		uint* newNode = (uint*)malloc(PTR_SIZE * 2);
		if (newNode)
		{
			if (newNode[CURR] = (uint)malloc(strlen(str) + 1))
			{
				strcpy((char*)newNode[CURR], str);
				newNode[NEXT] = NULL;
				node[NEXT] = (uint)newNode;
			}
		}
	}
	else
	{
		uint* newNode = (uint*)malloc(PTR_SIZE * 2);
		if (newNode)
		{
			if (newNode[CURR] = (uint)malloc(strlen(str) + 1))
			{
				strcpy((char*)newNode[CURR], str);
				newNode[NEXT] = NULL;
			}
		}
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
	for (uint* node = (uint*)*list; node != NULL; node = (uint*)node[NEXT])
	{
		if (!strcmp((char*)node[CURR], before))
		{
			if (node[CURR] = (uint)realloc((void*)node[CURR], strlen(after) + 1))
				strcpy((char*)node[CURR], after);
		}
	}
}


void StringListRemoveDuplicates(char** list)		// remove after sorting, so that after calling this function we will have sorted list
{
	StringListSort(list);

	for (uint* node = (uint*)*list; node[NEXT] != NULL; )
	{
		if (!strcmp((char*)node[CURR], (char*)(((uint*)node[NEXT])[CURR])))  // deleting next node if curr == next
		{
			free((void*)((uint*)node[NEXT])[CURR]);

			void* node_to_free = (void*)node[NEXT];
			node[NEXT] = ((uint*)node[NEXT])[NEXT];
			free(node_to_free);
		}
		else
		{
			node = (uint*)node[NEXT];
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


