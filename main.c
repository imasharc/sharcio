#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

/*
 * Bare with the comments, bc they explain (to me) what's going on
 */

int main(int argc, char *argv[])
{
 char *title = NULL;

 int opt;
 while ((opt = getopt(argc, argv, "t:")) != -1)
 {
  switch (opt)
  {
   case 't':
    title = optarg;
    break;
   default:
    fprintf(stderr, "Usage: %s -t title\n", argv[0]);
    exit(EXIT_FAILURE);
  }
 }

 if (title == NULL)
 {
  fprintf(stderr, "You must provide a title using the -t option.\n");
  exit(EXIT_FAILURE);
 }

 time_t t = time(NULL); // returns current time in sec since the Epoch
 struct tm tm = *localtime(&t); // converts time_t value into broken-down time structure
 char formattedString[20]; // create buffer for the formatted data
 sprintf(formattedString, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900); // format the string
 
 char filename[256]; // Adjust the buffer size as needed
 snprintf(filename, sizeof(filename), "%s_%s.txt", formattedString, title);

 FILE *file = fopen(filename, "w");
 if (file == NULL)
 {
  perror("Error opening file");
  exit(EXIT_FAILURE);
 }

 printf("Formatted Date: %s\n", formattedString);
 printf("Title: %s\n", title);
 printf("File name: %s\n", filename);

 // You can write content to the file if needed
 // fprintf(file, "Content goes here\n");

 fclose(file);

 return 0;
}
