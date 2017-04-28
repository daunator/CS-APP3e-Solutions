#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define BUFSIZE 5

/* Read input line and write it back */
/* Terminate with EOF(^D on linux) on an empty line */
void good_echo(void)
{
  char *text = NULL;
  char buffer[BUFSIZE];
  size_t text_len = 0u;
  while(fgets(buffer, BUFSIZE, stdin)) {
    size_t buf_len = strlen(buffer);
    text = realloc(text, text_len + buf_len + 1u);
    memcpy(text + text_len, buffer, buf_len + 1u);
    text_len += buf_len;
  }
  fputs(text, stdout);
  free(text);
}

