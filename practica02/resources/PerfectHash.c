//
// Created by someone on 10/14/17.
//

#include "PerfectHash.h"

/*
 * Used to calculate the id's of the Lexical ids that are less than 4 characters (separators and
 * punctuation)
 */
unsigned int perfect_hash(char * string){
	unsigned int result = 0;
	for(int i=0;string[i]!=0;i++){
		result = (result << 8) + string[i];
	}
	return result;
}