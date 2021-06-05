#ifndef _PARENBAL_H_
#define _PARENBAL_H_

#include <stddef.h>

typedef enum ParenBalResult
{
   PARENBAL_SUCCESS,
   PARENBAL_MISMATCH,
   PARENBAL_INTERLOCK,
   PARENBAL_UNKNOWN
} ParenBalResult_e;

/*
 * Initialises library
 */
void InitParenBal(void);

/*
 * Checks a string for matching pairs of parentheses.
 * @param str Input string.
 * @param len Length of input string.
 * @return 0 on success, error code otherwise
 */
ParenBalResult_e IsParenBal(const char* str, size_t len);

#endif /* _PARENBAL_H_ */
