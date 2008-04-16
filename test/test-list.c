 
/*
 
Copyright (c) 2005, Simon Howard
All rights reserved.

Redistribution and use in source and binary forms, with or without 
modification, are permitted provided that the following conditions 
are met:

 * Redistributions of source code must retain the above copyright 
   notice, this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright 
   notice, this list of conditions and the following disclaimer in 
   the documentation and/or other materials provided with the 
   distribution.
 * Neither the name of the C Algorithms project nor the names of its 
   contributors may be used to endorse or promote products derived 
   from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS 
FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE 
COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, 
INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; 
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT 
LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN 
ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
POSSIBILITY OF SUCH DAMAGE.

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "list.h"
#include "compare-int.h"

int variable1 = 50, variable2, variable3, variable4;

/* Returns a list containing four entries */

ListEntry *generate_list(void)
{
	ListEntry *list = NULL;

	list_append(&list, &variable1);
	list_append(&list, &variable2);
	list_append(&list, &variable3);
	list_append(&list, &variable4);

	return list;
}

void check_list_integrity(ListEntry *list)
{
	ListEntry *prev;
	ListEntry *rover;

	prev = NULL;
	rover = list;

	while (rover != NULL) {
		assert(list_prev(rover) == prev);
		prev = rover;
		rover = list_next(rover);
	}
}

void test_list_append(void)
{
	ListEntry *list = NULL;

	list_append(&list, &variable1);
	check_list_integrity(list);
	list_append(&list, &variable2);
	check_list_integrity(list);
	list_append(&list, &variable3);
	check_list_integrity(list);
	list_append(&list, &variable4);
	check_list_integrity(list);

	assert(list_nth_data(list, 0) == &variable1);
	assert(list_nth_data(list, 1) == &variable2);
	assert(list_nth_data(list, 2) == &variable3);
	assert(list_nth_data(list, 3) == &variable4);
}

void test_list_prepend(void)
{
	ListEntry *list = NULL;

	list_prepend(&list, &variable1);
	check_list_integrity(list);
	list_prepend(&list, &variable2);
	check_list_integrity(list);
	list_prepend(&list, &variable3);
	check_list_integrity(list);
	list_prepend(&list, &variable4);
	check_list_integrity(list);

	assert(list_nth_data(list, 0) == &variable4);
	assert(list_nth_data(list, 1) == &variable3);
	assert(list_nth_data(list, 2) == &variable2);
	assert(list_nth_data(list, 3) == &variable1);
}

void test_list_free(void)
{
	ListEntry *list;

	/* Create a list and free it */

	list = generate_list();

	list_free(list);

	/* Check the empty list frees correctly */

	list_free(NULL);
}

void test_list_next(void)
{
	ListEntry *list;
	ListEntry *rover;

	list = generate_list();

	rover = list;
	assert(list_data(rover) == &variable1);
	rover = list_next(rover);
	assert(list_data(rover) == &variable2);
	rover = list_next(rover);
	assert(list_data(rover) == &variable3);
	rover = list_next(rover);
	assert(list_data(rover) == &variable4);
	rover = list_next(rover);
	assert(rover == NULL);
}

void test_list_nth_entry(void)
{
	ListEntry *list;
	ListEntry *entry;

	list = generate_list();

	/* Check all values in the list */

	entry = list_nth_entry(list, 0);
	assert(list_data(entry) == &variable1);
	entry = list_nth_entry(list, 1);
	assert(list_data(entry) == &variable2);
	entry = list_nth_entry(list, 2);
	assert(list_data(entry) == &variable3);
	entry = list_nth_entry(list, 3);
	assert(list_data(entry) == &variable4);

	/* Check negative values */

	entry = list_nth_entry(list, -1);
	assert(entry == NULL);

	/* Check out of range values */

	entry = list_nth_entry(list, 4);
	assert(entry == NULL);
	entry = list_nth_entry(list, 400);
	assert(entry == NULL);
}

void test_list_nth_data(void)
{
	ListEntry *list;

	list = generate_list();

	/* Check all values in the list */

	assert(list_nth_data(list, 0) == &variable1);
	assert(list_nth_data(list, 1) == &variable2);
	assert(list_nth_data(list, 2) == &variable3);
	assert(list_nth_data(list, 3) == &variable4);

	/* Check out of range values */

	assert(list_nth_data(list, -1) == NULL);
	assert(list_nth_data(list, 4) == NULL);
	assert(list_nth_data(list, 400) == NULL);
}

void test_list_length(void)
{
	ListEntry *list;

	/* Generate a list and check that it is four entries long */

	list = generate_list();

	assert(list_length(list) == 4);

	/* Add an entry and check that it still works properly */

	list_prepend(&list, &variable1);

	assert(list_length(list) == 5);

	/* Check the length of the empty list */

	assert(list_length(NULL) == 0);
}

void test_list_remove_entry(void)
{
	ListEntry *empty_list = NULL;
	ListEntry *list;
	ListEntry *entry;

	list = generate_list();

	/* Remove the third entry */

	entry = list_nth_entry(list, 2);
	assert(list_remove_entry(&list, entry) != 0);
	assert(list_length(list) == 3);
	check_list_integrity(list);

	/* Remove the first entry */

	entry = list_nth_entry(list, 0);
	assert(list_remove_entry(&list, entry) != 0);
	assert(list_length(list) == 2);
	check_list_integrity(list);
	
	/* Try some invalid removes */

	/* NULL */

	assert(list_remove_entry(&list, NULL) == 0);

	/* Removing NULL from an empty list */

	assert(list_remove_entry(&empty_list, NULL) == 0);
}

void test_list_remove_data(void)
{
	int entries[] = { 89, 4, 23, 42, 4, 16, 15, 4, 8, 99, 50, 30, 4 };
	int num_entries = sizeof(entries) / sizeof(int);
	int val;
	ListEntry *list;
	int i;

	/* Generate a list containing all the entries in the array */

	list = NULL;

	for (i=0; i<num_entries; ++i) {
		list_prepend(&list, &entries[i]);
	}

	/* Test removing invalid data */

	val = 0;
	assert(list_remove_data(&list, int_equal, &val) == 0);
	val = 56;
	assert(list_remove_data(&list, int_equal, &val) == 0);
	check_list_integrity(list);
	
	/* Remove the number 8 from the list */

	val = 8;
	assert(list_remove_data(&list, int_equal, &val) == 1);
	assert(list_length(list) == num_entries - 1);
	check_list_integrity(list);

	/* Remove the number 4 from the list (occurs multiple times) */

	val = 4;
	assert(list_remove_data(&list, int_equal, &val) == 4);
	assert(list_length(list) == num_entries - 5);
	check_list_integrity(list);

	/* Remove the number 89 from the list (first entry) */

	val = 89;
	assert(list_remove_data(&list, int_equal, &val) == 1);
	assert(list_length(list) == num_entries - 6);
	check_list_integrity(list);
}

void test_list_sort(void)
{
	ListEntry *list;
	int entries[] = { 89, 4, 23, 42, 4, 16, 15, 4, 8, 99, 50, 30, 4 };
	int sorted[]  = { 4, 4, 4, 4, 8, 15, 16, 23, 30, 42, 50, 89, 99 };
	int num_entries = sizeof(entries) / sizeof(int);
	int i;

	list = NULL;

	for (i=0; i<num_entries; ++i) {
		list_prepend(&list, &entries[i]);
	}

	list_sort(&list, int_compare);

	/* List length is unchanged */

	assert(list_length(list) == num_entries);

	/* Check the list is sorted */

	for (i=0; i<num_entries; ++i) {
		int *value;

		value = (int *) list_nth_data(list, i);
		assert(*value == sorted[i]);
	}

	/* Check sorting an empty list */

	list = NULL;

	list_sort(&list, int_compare);

	assert(list == NULL);
}

void test_list_find_data(void)
{
	int entries[] = { 89, 23, 42, 16, 15, 4, 8, 99, 50, 30 };
	int num_entries = sizeof(entries) / sizeof(int);
	ListEntry *list;
	ListEntry *result;
	int i;
	int val;
	int *data;

	/* Generate a list containing the entries */

	list = NULL;
	for (i=0; i<num_entries; ++i) {
		list_append(&list, &entries[i]);
	}

	/* Check that each value can be searched for correctly */

	for (i=0; i<num_entries; ++i) {

		val = entries[i];
		
		result = list_find_data(list, int_equal, &val);
		
		assert(result != NULL);

		data = (int *) list_data(result);
		assert(*data == val);
	}
	
	/* Check some invalid values return NULL */

	val = 0;
	assert(list_find_data(list, int_equal, &val) == NULL);
	val = 56;
	assert(list_find_data(list, int_equal, &val) == NULL);
}

void test_list_to_array(void)
{
	ListEntry *list;
	void **array;
	
	list = generate_list();
	
	array = list_to_array(list);

	assert(array[0] == &variable1);
	assert(array[1] == &variable2);
	assert(array[2] == &variable3);
	assert(array[3] == &variable4);
}

void test_list_iterate(void)
{
	ListEntry *list;
	ListIterator iter;
	int i;
	int a;
	int counter;
	int *data;

	/* Create a list with 50 entries */

	list = NULL;

	for (i=0; i<50; ++i) {
		list_prepend(&list, &a);
	}

	/* Iterate over the list and count the number of entries visited */

	counter = 0;

	list_iterate(&list, &iter);

	/* Test remove before list_iter_next has been called */

	list_iter_remove(&iter);

	/* Iterate over the list */

	while (list_iter_has_more(&iter)) {
		data = (int *) list_iter_next(&iter);
		++counter;

		if ((counter % 2) == 0) {
			/* Delete half the entries in the list.  */

			list_iter_remove(&iter);

			/* Test double remove */

			list_iter_remove(&iter);
		}
	}

	/* Test remove at the end of a list */

	list_iter_remove(&iter);

	assert(counter == 50);
	assert(list_length(list) == 25);

	/* Test iterating over an empty list */

	list = NULL;
	counter = 0;

	list_iterate(&list, &iter);

	while (list_iter_has_more(&iter)) {
		data = (int *) list_iter_next(&iter);
		++counter;
	}

	assert(counter == 0);
}

int main(int argc, char *argv[])
{
	test_list_append();
	test_list_prepend();
	test_list_free();
	test_list_next();
	test_list_nth_entry();
	test_list_nth_data();
	test_list_length();
	test_list_remove_entry();
	test_list_remove_data();
	test_list_sort();
	test_list_find_data();
	test_list_to_array();
	test_list_iterate();

	return 0;
}

