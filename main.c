#include <stdio.h>
#include <time.h>

/*
 * Bare with the comments, bc they explain (to me) what's going on
 */

int main()
{
 time_t t = time(NULL); // returns current time in sec since the Epoch
 struct tm tm = *localtime(&t); // converts time_t value into broken-down time structure
 char formattedString[20]; // create buffer for the formatted data
 sprintf(formattedString, "%02d-%02d-%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900); // format the string
 printf("Formatted Date: %s", formattedString); // print to make sure
}
