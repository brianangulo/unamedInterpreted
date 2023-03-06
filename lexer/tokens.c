#include <memory.h>
#include "tokens.h"
#include "../errors/errors.h"

Token createToken(TT_TYPE type, char value[], int posVector[2])
{
    // literal sizes
    int valueLength = (posVector[1] - posVector[0]) + 1;
    size_t valueSize = sizeof(char) * valueLength;
    size_t vectorSize = sizeof(int) * 2;
    // checking for invalid size
    if (valueLength < 0)
    {
        printf("Error: token size must be greater than zero\n");
        exit(EXIT_FAILURE);
    }
    // memory allocations
    Token tmpToken;
    tmpToken.position = malloc(vectorSize);
    tmpToken.value = malloc(valueSize);
    // setting values
    tmpToken.type = type;
    tmpToken.valueLength = valueLength;
    memcpy(tmpToken.position, posVector, vectorSize);
    strncpy(tmpToken.value, value, valueSize);
    return tmpToken;
}

void deleteToken(Token token)
{
    free(token.position);
    free(token.value);
}

TokensDynamicArray buildNewArray(size_t arrSize)
{
    TokensDynamicArray tmpArr;
    tmpArr.array = malloc(arrSize);
    tmpArr.nextIdx = 0;
    tmpArr.currMaxArrLen = arrSize;
    return tmpArr;
}

void deleteTokenArray(TokensDynamicArray array)
{
    free(array.array);
}

uint32_t appendToken(TokensDynamicArray *array, Token newToken)
{
    uint32_t nextIdx = array->nextIdx;
    // throw if we will be hitting max size
    if (nextIdx >= (UINT32_MAX - 1))
    {
        // TODO: should probably create a throw function
        printf("Out of bounds. Array reached max size: Code: %d\n", ARRAY_OUT_OF_BOUNDS);
        exit(ARRAY_OUT_OF_BOUNDS);
    }

    // checking if we have space for one more token
    size_t arrSize = sizeof (Token) * nextIdx;
    size_t maxSize = array->currMaxArrLen;
    size_t sizeDiff = maxSize - arrSize;

    if (sizeof (Token) <= sizeDiff)
    {
        // we double the space if not enough left
        size_t newSize = sizeof (Token) * (maxSize * 2);
        Token *tmpArr = realloc(array->array, newSize);
        if (tmpArr == NULL) {
            printf("Unable to allocate new array size\n");
            exit(MEM_ALLOC_ERR);
        }
        // explicit assign just in case a new ptr is created and returned
        array->array = tmpArr;
        array->currMaxArrLen = newSize;
    }
    // appending token and updating lastTokenIndex
    printf("%d\n", nextIdx);
    array->array[nextIdx] = newToken;
    array->nextIdx++;
    return nextIdx;
}
