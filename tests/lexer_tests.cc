//
// Created by Brian Angulo on 3/4/23.
//
#include <gtest/gtest.h>

extern "C" {
#include "../lexer/tokens.h"
};

TEST(Lexer, TokenArrBuilderReturnsDefault) {
    size_t testSize = sizeof (Token) * 2;
    TokensDynamicArray testArr = buildNewArray(testSize);

    TokensDynamicArray defaultArr;
    defaultArr.array = static_cast<Token *>(malloc(testSize));
    defaultArr.nextIdx = 0;
    defaultArr.currMaxArrLen = testSize;

    // we check for equalities across default and test
    ASSERT_EQ(sizeof (&defaultArr.array), sizeof (&testArr.array));
    ASSERT_EQ(defaultArr.nextIdx, testArr.nextIdx);
    ASSERT_EQ(defaultArr.currMaxArrLen, testArr.currMaxArrLen);

    // freeing resources
    deleteTokenArray(testArr);
    deleteTokenArray(defaultArr);
}
