//
// Created by Brian Angulo on 3/4/23.
//
#include <gtest/gtest.h>

extern "C" {
#include "../lexer/tokens.h"
}

#define TokenPosArrSize 2

TEST(Tokens, TokenArrBuilderReturnsDefault) {
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

TEST(Tokens, CreateTokenBuildsExpected) {
    Token expectedToken;
    expectedToken.type = TT_LBRACE;
    int test[TokenPosArrSize] = {0, 2};
    char foo[] = "foo";
    expectedToken.position = test;
    expectedToken.value = foo;
    expectedToken.valueLength = 3;
    Token testToken = createToken(expectedToken.type, expectedToken.value, expectedToken.position);

    ASSERT_EQ(expectedToken.valueLength, testToken.valueLength);
    EXPECT_STREQ(testToken.value, expectedToken.value);
    ASSERT_EQ(expectedToken.type, testToken.type);
    // asserting Token::position equality
    for (int i = 0; i < TokenPosArrSize ; ++i) {
        ASSERT_EQ(expectedToken.position[i], testToken.position[i]);
    }
}

TEST(Tokens, TokenAppendingAsExp) {
    size_t size = sizeof (Token) * 2;
    TokensDynamicArray testArr = buildNewArray(size);
    int testPos[TokenPosArrSize] = {0, 2};
    char value[] = "foo";
    Token testToken = createToken(TT_LBRACE, value, testPos);
    uint32_t appendedIdx = appendToken(&testArr, testToken);

    // index should be zero since array was empty to begin with
    ASSERT_EQ(appendedIdx, 0);
    // token equality check now
    Token tokenInArr = testArr.array[0];
    ASSERT_EQ(tokenInArr.type, testToken.type);
    ASSERT_EQ(tokenInArr.valueLength, testToken.valueLength);
    EXPECT_STREQ(tokenInArr.value, testToken.value);
    // asserting Token::position equality
    for (int i = 0; i < TokenPosArrSize ; ++i) {
        ASSERT_EQ(tokenInArr.position[i], testToken.position[i]);
    }
}
