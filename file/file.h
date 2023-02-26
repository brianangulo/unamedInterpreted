#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

size_t getFileSize(const char *fileLocation);

void readFile(const char *fileLocation, char *buffer, size_t bufferSize);
