//
// Created by someone on 10/13/17.
//

#ifndef UNTITLED_ERRORLOG_H
#define UNTITLED_ERRORLOG_H

#endif //UNTITLED_ERRORLOG_H

/*This .c/.h encapsulates the error display in this program*/

/*
 * Print the error contained in error_message and displaying string_guilty as the
 * source cause
 */
void print_error_log(char *error_message, char *string_guilty);
/*
 * Print the error contained in error_message and displaying string_guilty as the
 * source cause. Then it execute exit(1)
 */
void print_fatal_error(char *error_message, char *string_guilty);