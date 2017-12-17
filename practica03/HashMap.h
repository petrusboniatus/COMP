//
// Created by someone on 10/6/17.
//

#ifndef UNTITLED_HASHMAP_H
#define UNTITLED_HASHMAP_H

#endif //UNTITLED_HASHMAP_H

/* This is a implementation of a generic HashMap, it can Store All types of variable, the only
 * restriction is that the key must be an string.
 *
 * It consist in a HashMap where every entry is a linked list (LIFO). It has a dynamic
 * Implementation so it will reserve or Memory when it's density is too high or too low.
 *
 * Despite it's generic, it has a custom collision policy made thinking on the symbol table in
 * mind: if an entry with an existing key is inserted it will put that entry at the top of
 * the liked list of his correspondent box. So this implementation allows to insert variables with
 * different scopes but the same key. It will always pop the last entry when delete_entry() is
 * called.
 */


// The initial size of the table
#define TABLE_INITIAL_SIZE 10

// When this ratio is surpassed the HashMap is resized up
#define MAX_TABLE_FILL_RATE  0.7

// When this ratio is less than this the HashMap is resized down
#define MIN_TABLE_FILL_RATE 0.1

// In every resize the map is multiplied for that constant
#define SIZE_MULTIPLIER_WHEN_FILL 2

// Abstract object that content the map
typedef struct HashMapData * HashMap;

// The value that you what to store
typedef void * EntryValue;

// Function to compare values
// most return TRUE if the entries are equal, FALSE if not
typedef int (*equals_function)(EntryValue, EntryValue);

// Function to free space
typedef void (*free_entry_function)(char * key, EntryValue);

/*
 * @param equals - function that define weather 2 entries have the same content
 * @param free_entry - function that liberates the memory of the entries
 *
 * @returns new_map - map with all it's variables initialized.
 */
HashMap create_map(free_entry_function f , equals_function e);

/*
 * @param self - Map object
 *
 * It free all the memory existing in all the entries using the free_entry functions, to do
 * that it has to iterate over all the map, an over every element of the linked list in
 * a box.
 *
 * Lastly it frees the map itself.
 */
void delete_map(HashMap self);

/*
 * @param self - HashMap object
 * @param key - key of the entry that will be inserted
 * @param value - value of the entry that will be inserted
 *
 * Makes the procedure necesary to insert the map:
 * 1. Increment the count of the number of elements
 * 2. Resize the table up if it's necesary
 * 3. Reserve the memory for the new Entry
 * 4. Insert the Entry at the first position
 */
void put(HashMap self, char * key, EntryValue value);

/*
 * @param self - HashMap object
 * @param key - key of the value to recover
 *
 * @returns value - the first value whose key have an exact match
 *
 * It iterate the list corresponding to the hash position finding the exact key,
 * return the first coincidence.
 */
EntryValue get(HashMap self, char * key);

/*
 * @param self - HashMap object
 * @param key - key that could exits
 *
 * @return whether the key exits in the map
 */
int contains(HashMap self, char * key);

/*
 * @param self - HashMap object
 * @param key - key of the object to delete
 *
 * Remove the first coincidence of the exact value of the key if exist
 *
 * It iterate over the linked list of the box given by the hash of the
 * key. If it it's not the first entry the next_entry of the previous
 * entry is redefined as the next entry of the entry to delete. Otherwise
 * the next entry is placed in the box.
 */
void delete_entry(HashMap self, char * key);

/* @param value_to_erase - value equals to all the values that will be erased
 * @param HashMap self - HashMap object
 *
 * Delete values equals to value_value_to_erase
 * equals function determined by the function equals passed on
 * create_map(free_entry_function f, equals_function e)
 *
 * In order to delete all the values that match the coincidence it
 * has to iterate all over the table and all over the linked list
 * of the boxes
 */
void delete_entries(HashMap self, EntryValue value_to_erase);

/*
 * @param the map object
 * @returns the number of entries in the map
 */
unsigned long get_size(HashMap self);

/*
 * Debug function, necesary to the practice.
 */
void print_map(HashMap self);
