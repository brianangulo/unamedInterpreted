//
// Created by Brian Angulo on 2/22/23.
//

#ifndef INTERPRETER_C_TOKENS_C_H
#define INTERPRETER_C_TOKENS_C_H

#endif //INTERPRETER_C_TOKENS_C_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef enum TT_TYPE {TT_LBRACE, TT_RBRACE, TT_KEY} TT_TYPE;

typedef struct Token
{
    // token type
    TT_TYPE type;
    // start and end location of the token string should be a 2 value int array
    int *position;
    // size of the value
    size_t valueLength;
    // the actual token string
    char *value;
} Token;

// small abstraction for creating token struct.
// creates token stores it in heap memory and returns a pointer to it.
// each token created via this function must be freed
Token createToken(TT_TYPE type, char value[], int posVector[2]);

// frees memory allocated by createToken
void deleteToken(Token token);

typedef struct TokensDynamicArray
{
    // pointer to the array
    Token *array;
    // the next available index
    uint32_t nextIdx;
    // current total amount of memory allocated for this array
    size_t currMaxArrLen;
} TokensDynamicArray;

// it mutates the passed in array directly
// appends a new token at the end of the array and returns the index of such token
// it will increment the array's size if needed using the doubling approach
// max size determined by uint32_t
uint32_t appendToken(TokensDynamicArray *array, Token newToken);

// builds a brand-new array of arrSize with default values
TokensDynamicArray buildNewArray(size_t arrSize);

