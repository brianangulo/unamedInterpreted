#include "file/file.h"
#include "errors/errors.h"
#include "lexer/tokens.h"

int main(int argc, char const *argv[])
{   
    size_t fileSize;
    char *readBuffer;
    const char fileLocation[] = "/Users/brianangulo/Main/Projects/interpreter_c/index.html";
    // get size stat in bytes
    fileSize = getFileSize(fileLocation);
    // allocate memory
    readBuffer = malloc(sizeof(char) * fileSize);
    // read entire file into buffer
    readFile(fileLocation, readBuffer, fileSize);
    // free buffer
    free(readBuffer);
    // init array
    TokensDynamicArray tokensArr = buildNewArray(sizeof (Token) * 2);
    int vector[] = {0, 3};
    int otherVector[] = {0, 11};
    Token testToken = createToken(TT_KEY, "fool", vector);
    Token fooToken = createToken(TT_KEY, "foolishOfYou", otherVector);
    uint32_t idx = appendToken(&tokensArr, testToken);
    uint32_t index = appendToken(&tokensArr, fooToken);
    printf("{idx: %d index: %d}\n", idx, index);
    // print statements
    puts(tokensArr.array[0].value);
    puts(tokensArr.array[1].value);
    deleteToken(testToken);
    deleteToken(fooToken);
    return 0;
}
