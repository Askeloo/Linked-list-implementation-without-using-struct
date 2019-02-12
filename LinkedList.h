#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int uint;

#ifdef __cplusplus
extern "C" {
#endif

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

#ifdef __cplusplus
}
#endif

#endif 