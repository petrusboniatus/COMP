//
// Created by someone on 10/6/17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashMap.h"

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


/*
 * next_entry: pointer to the next entry of the linked list. Always 0 if there is no entry
 * key: string that contains the key of the entry.
 * value: pointer to a generic type that contains the content of the entry
 */
typedef struct Entry {
	struct Entry *next_entry;
	char *key;
	EntryValue *value;
} Entry;

/*
 * HashMapData: struck that contains all the attributes of the HashMap object
 * table: List of pointers to the first entry of the box, every position is 0 if now entry is
 * contained in that box
 * number_of_entries: variable that tracks the size of the map
 * equals: function that define weather 2 entries have the same content
 * free_entry: function that liberates the memory of the entries
 */
typedef struct HashMapData {
	Entry **table;
	unsigned long table_size;
	unsigned long number_of_entries;
	equals_function equals;
	free_entry_function free_entry;
} HashMapData;

/*
 * @param table_size - number of boxes that will content the new table
 *
 * @returns new_table - new vector of boxes with memory reserved by malloc
 */
Entry **create_table(unsigned long table_size) {
	Entry **new_table = (Entry **) malloc(sizeof(Entry *) * table_size);
	for (int i = 0; i < table_size; i++) {
		new_table[i] = 0;
	}

	return new_table;
}


/*
 * @param table_size - number of boxes that will content the new table of the new map
 *
 * @returns new_map - map with all it's internal variables initialized
 */
HashMap initialize_map(unsigned long table_size) {
	HashMap new_map = (HashMap) malloc(sizeof(HashMapData));
	new_map->table_size = table_size;
	new_map->number_of_entries = 0;
	new_map->table = create_table(table_size);
	return new_map;
}

/*
 * @param equals - function that define weather 2 entries have the same content
 * @param free_entry - function that liberates the memory of the entries
 *
 * @returns new_map - map with all it's variables initialized.
 */
HashMap create_map(free_entry_function f, equals_function e) {
	HashMap new_map = initialize_map(TABLE_INITIAL_SIZE);
	new_map->free_entry = f;
	new_map->equals = e;
	return new_map;
}

/*
 * @param key - string that will be hashed
 * @param size - maximum number of the resulting hash
 *
 * @returns - hash number corresponding to that string
 *
 * for every char_i in key -> hash_value = sum(char_i*31^i) mod size
 */
unsigned long get_hash_code(char *key, unsigned long size) {
	unsigned long hash_value = 0;
	for (int i = 0; key[i] != 0; i++) {
		hash_value = (hash_value * 31 + key[i]) % size;
	}

	return hash_value;
}

/*
 * @param self - Map object
 *
 * It free all the memory existing in all the entries using the free_entry functions, to do
 * that it has to iterate over all the map, an over every element of the linked list in
 * a box.
 *
 * Lastly it frees the map itself.
 */
void delete_map(HashMap self) {

	for (int i = 0; i < self->table_size; i++) {
		Entry *actual = self->table[i];
		while (actual != 0) {
			Entry *aux = actual;
			actual = actual->next_entry;
			self->free_entry(aux->key, aux->value);
			free(aux);
		}
	}

	free(self->table);
	free(self);
}


/*
 * @param table - pointer array to the first entry of the linked list
 * @param table_size - size of the table array
 * @param entry - entry that will be inserted
 *
 * It insert the entry in the first position of the list, if there is as previous entry
 * it will be pushed to the second position.
 *
 * This functions it's only called to resize table because it not reserve memory to the
 * entry.
 */
void place_entry_in_table(Entry **table, unsigned long table_size, Entry *entry) {
	unsigned long table_position = get_hash_code(entry->key, table_size);
	Entry *previousElement = table[table_position];

	entry->next_entry = previousElement;
	table[table_position] = entry;
}

/*
 * @param self - HashMap object
 * @param new_table_size - size of the new table
 *
 * Create a new table with size passed ass parameter the old elements to new table,
 * then remove the table.
 */
void resize_table(HashMap self, unsigned long new_table_size) {

	Entry **new_table = create_table(new_table_size);

	for (int i = 0; i < self->table_size; i++) {
		Entry *actual = self->table[i];
		while (actual != 0) {
			Entry *aux = actual;
			actual = actual->next_entry;
			place_entry_in_table(new_table, new_table_size, aux);
		}
	}

	free(self->table);

	self->table_size = new_table_size;
	self->table = new_table;
}

/*
 * @param self - HashMap object
 *
 * Check if it's necesary to resize the table up. It will be necesary when the occupation rate
 * exceed the MAX_TABLE_FILL_RATE defined in .h
 */
void resize_up_table_if_necesary(HashMap self) {
	if (self->number_of_entries > MAX_TABLE_FILL_RATE * self->table_size) {
		resize_table(self, SIZE_MULTIPLIER_WHEN_FILL * self->table_size);
	}
}

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
void put(HashMap self, char *key, EntryValue value) {
	self->number_of_entries++;
	resize_up_table_if_necesary(self);

	Entry *new_entry = (Entry *) malloc(sizeof(Entry));
	new_entry->key = key;
	new_entry->value = value;

	unsigned long table_position = get_hash_code(key, self->table_size);
	Entry *previousElement = self->table[table_position];

	new_entry->next_entry = previousElement;

	self->table[table_position] = new_entry;
}

/*
 * @param self - HashMap object
 * @param key - key of the value to recover
 *
 * @returns value - the first value whose key have an exact match
 *
 * It iterate the list corresponding to the hash position finding the exact key,
 * return the first coincidence.
 */
EntryValue get(HashMap self, char *key) {
	unsigned long table_position = get_hash_code(key, self->table_size);
	if (!self->table[table_position]) return 0;

	Entry *actual = self->table[table_position];
	while (actual != 0 && strcmp(actual->key, key) != 0) {
		actual = actual->next_entry;
	}

	if (actual) return actual->value; else return 0;
}

/*
 * @param self - HashMap object
 * @param key - key that could exits
 *
 * @return whether the key exits in the map
 */
int contains(HashMap self, char *key) {
	return get(self, key) != 0;
}

/*
 * @param self - HashMap object
 *
 * Check if it's necesary to resize the table down. It will be necesary when the occupation rate
 * is lower than the MIN_TABLE_FILL_RATE defined in .h
 */
void resize_down_table_if_necesary(HashMap self) {
	if (self->number_of_entries < self->table_size * MIN_TABLE_FILL_RATE &&
		self->table_size * MIN_TABLE_FILL_RATE > TABLE_INITIAL_SIZE) {
		unsigned long new_size;
		new_size = self->table_size / SIZE_MULTIPLIER_WHEN_FILL;
		resize_table(self, new_size);
	}
}

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
void delete_entry(HashMap self, char *key) {
	unsigned long table_position = get_hash_code(key, self->table_size);
	if (self->table[table_position] == 0) return;

	Entry *previous_entry = 0;
	Entry *old_entry = self->table[table_position];
	while (old_entry && strcmp(old_entry->key, key) != 0) {
		previous_entry = old_entry;
		old_entry = old_entry->next_entry;
	}

	if (old_entry && previous_entry) {	//It's not the first entry
		self->number_of_entries--;
		previous_entry->next_entry = old_entry->next_entry;
		self->free_entry(old_entry->key, old_entry->value);
		free(old_entry);
	} else if (old_entry) {	//It's the first entry
		self->number_of_entries--;
		self->table[table_position] = old_entry->next_entry;
		self->free_entry(old_entry->key, old_entry->value);
		free(old_entry);
	}

	resize_down_table_if_necesary(self);
}

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
void delete_entries(HashMap self, EntryValue value_to_erase) {

	for (int i = 0; i < self->table_size; i++) {

		Entry *previous_to_delete = 0;
		Entry *value_to_delete = 0;
		Entry *next_to_delete = self->table[i];

		while (next_to_delete != 0) {

			previous_to_delete = value_to_delete;
			value_to_delete = next_to_delete;
			next_to_delete = next_to_delete->next_entry;

			if (self->equals(value_to_delete->value, value_to_erase)) {

				if (previous_to_delete) {
					previous_to_delete->next_entry = next_to_delete;
					free(value_to_delete);
					self->free_entry(value_to_delete->key, value_to_delete->value);
					value_to_delete = previous_to_delete;
				} else {
					self->table[i] = value_to_delete->next_entry;
					self->free_entry(value_to_delete->key,
									 value_to_delete->value);
					value_to_delete = previous_to_delete;
				}
				self->number_of_entries--;
			}
		}
	}
	resize_down_table_if_necesary(self);
}

/*
 * @param the map object
 * @returns the number of entries in the map
 */
unsigned long get_size(HashMap self) {
	return self->number_of_entries;
}

/*
 * Debug function, necesary to the practice.
 */
void print_map(HashMap self){

	printf("---- Welcome to the Map ----\n");
	for (int i = 0; i < self->table_size; i++) {
		Entry *actual = self->table[i];
		while (actual != 0) {
			printf("%u -> %s \n",i, actual->key);
			actual = actual->next_entry;
		}
	}

}


