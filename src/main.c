#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "parenbal.h"

typedef struct TestCase
{
   const char *input;
   const ParenBalResult_e output;
} TestCase_s;

#define TEST_TABLE_LEN 10
static const TestCase_s TEST_TABLE[TEST_TABLE_LEN] =
{
   { "", PARENBAL_SUCCESS },
   { "()" , PARENBAL_SUCCESS },
   { "(())" , PARENBAL_SUCCESS },
   { "()()" , PARENBAL_SUCCESS },
   { "[()]" , PARENBAL_SUCCESS },
   { "<{[()]}>" , PARENBAL_SUCCESS },
   { "(", PARENBAL_MISMATCH },
   { "[(])", PARENBAL_INTERLOCK },
   { ")(", PARENBAL_MISMATCH },
   { "()[[]](<><[()]>)" , PARENBAL_SUCCESS }
};

int main(int argc, char **argv)
{
   ParenBalResult_e result = PARENBAL_UNKNOWN;
   bool pass = false;

   InitParenBal();

   for (int i = 0; i < TEST_TABLE_LEN; i++)
   {
      result = IsParenBal(
            TEST_TABLE[i].input,
            strlen(TEST_TABLE[i].input));
      pass = (result == TEST_TABLE[i].output);
      printf("(%d,%d) %s : %s\n",
            TEST_TABLE[i].output,
            result,
            pass ? "PASS" : "FAIL",
            TEST_TABLE[i].input);
   }

   return 0;
}
