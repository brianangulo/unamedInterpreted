#include "file.h"

size_t getFileSize(const char *fileLocation)
{
    struct stat buffer;
    int status;

    status = stat(fileLocation, &buffer);
    if (status == 1)
    {
        printf("Error getting file size\n");
        exit(EXIT_FAILURE);
    }
    if (status == 0)
    {
        return (size_t) buffer.st_size;
    }
    printf("Error: unable to get file size\n");
    exit(EXIT_FAILURE);
}

void readFile(const char *fileLocation, char *buffer, size_t bufferSize)
{
    FILE *pOpenFile = fopen(fileLocation, "r");
    // check if error
    if (pOpenFile == NULL)
    {
        printf("Error opening file\n");
        exit(EXIT_FAILURE);
    }
    // reading char stream into buffer
    int character;
    size_t bufferPos = 0;
    while (character != EOF && bufferPos < bufferSize)
    {
        character = fgetc(pOpenFile);
        buffer[bufferPos] = character;
        bufferPos++;
    }
    if (ferror(pOpenFile)) {
        printf("I/O error reading file\n");
        exit(EXIT_FAILURE);
    }
    int closeStatus = fclose(pOpenFile);
    if (closeStatus == EOF) {
        printf("I/O error closing file\n");
        exit(EXIT_FAILURE);
    }
}
