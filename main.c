#include "headers.h"

FILE *readFile(char *filename) {
  char ch;
  FILE *fptr;

  if ((fptr = fopen(filename, "r")) == NULL) {
    printf("Error! opening file");
    exit(1);
  }
  return fptr;
}

int startTest(FILE *fptr) {
  char ch;
  char *originalText = malloc(sizeof(originalText));
  int originalTextLen = 0;
  int inputTextLen = 0;
  int inputTextLenWords = 0;
  int originalTextLenWords = 1;
  int idx = 0;
  int incorrectWords = 0;
  // populate originalText and count wc
  while (!feof(fptr)) {
    ch = fgetc(fptr);
    if (ch != '\0') {
      originalTextLen++;
      originalText = realloc(originalText, originalTextLen);
      originalText[idx] = ch;
      idx++;
    }
    if (ch == ' ') {
      originalTextLenWords++;
    }
  }

  printf(ANSI_COLOR_RED "TEXT: " ANSI_COLOR_RESET);
  printf("%s\n", originalText);
  char *text = malloc(sizeof(text) * originalTextLen);
  printf(ANSI_COLOR_GREEN "TYPE HERE: " ANSI_COLOR_RESET);

  // Calculate the time taken by scanf
  time_t userInputTime, inputStart, inputEnd;
  inputStart = time(NULL);
  scanf(" %[^\n]", text);
  inputEnd = time(NULL);
  userInputTime = inputEnd - inputStart;
  float userInputTimeInMinutes = userInputTime / 60.0;
  
  inputTextLen = strlen(text);
  originalTextLen = strlen(originalText) - 2;

  // go through inputted text and count incorrect entries
  char *token = strtok(text, " ");
  while (token != NULL) {
    inputTextLenWords++;
    if (strstr(originalText, token) == NULL) {
      incorrectWords++;
    }
    token = strtok(NULL, " ");
  }

  // do calculations for WPM here
  int temp = inputTextLen / 5;
  float errorRate = (float)incorrectWords / userInputTimeInMinutes;
  float grossWPM = temp / userInputTimeInMinutes;
  float netWPM = grossWPM - errorRate;
  float accuracy = ((inputTextLen - (float)incorrectWords) / originalTextLen ) * 100;
  printf(ANSI_COLOR_BLUE "GROSS WPM = %.2f\nNET WPM = %.2f\nACCURACY = %.2f%%\n" ANSI_COLOR_RESET, grossWPM, netWPM, accuracy);

  fclose(fptr);
  free(originalText);
  free(text);
  return 0;
}

int main(int argc, char *argv[]) {
  char *option = malloc(sizeof(option) * 1024);
  printf(ANSI_COLOR_BLUE "Enter the name of a text file: " ANSI_COLOR_RESET);
  scanf("%s", option);
  startTest(readFile(option));
}
