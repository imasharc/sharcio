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
 char *paragraphs[100];
 int paragraph_count = 0;

 int opt;

 while ((opt = getopt(argc, argv, "t:p:")) != -1)
 {
  switch (opt)
  {
   case 't':
    title = optarg;
    break;
   case 'p':
    if (paragraph_count < 100)
     {
      paragraphs[paragraph_count] = optarg;
      paragraph_count++;
     }
    else
     {
      fprintf(stderr, "Too many paragraphs. Limit reached.\n");
      exit(EXIT_FAILURE);
     }
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

 if (paragraph_count == 0)
 {
  fprintf(stderr, "You must provide at least one -p option for a paragraph.\n");
  exit(EXIT_FAILURE);
 }

 time_t t = time(NULL); // returns current time in sec since the Epoch
 struct tm tm = *localtime(&t); // converts time_t value into broken-down time structure
 char formattedString[20]; // create buffer for the formatted data
 sprintf(formattedString, "%02d-%02d-%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900); // format the string
 
 char filename[256]; // Adjust the buffer size as needed
 snprintf(filename, sizeof(filename), "%s_%s.txt", formattedString, title);

 FILE *file = fopen(filename, "a"); // use "a" mode to append to the file
 if (file == NULL)
 {
  perror("Error opening file");
  exit(EXIT_FAILURE);
 }
 
 if (ftell(file) == 0)
 {
  // If the file is empty, write the title
  fprintf(file, "Title: %s\n", title);
 }
 else
 {
  // If the file is not empty, add a newline before appending paragraphs
  fprintf(file, "\n");
 }

 for (int i = 0; i < paragraph_count; i++)
 {
  fprintf(file, "%s\n", paragraphs[i]);
 }

 fclose(file);

 printf("File \"%s\" has been created with the provided title and paragraphs.\n", filename);

 return 0;
}
