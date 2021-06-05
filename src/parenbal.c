#include <stdbool.h>
#include <stdlib.h>
#include "parenbal.h"

#define NUM_PAREN_TYPES 4
#define NUM_PAREN_STATES 2

typedef enum ParenType
{
   PAREN_TYPE_ROUND,
   PAREN_TYPE_SQUARE,
   PAREN_TYPE_CURLY,
   PAREN_TYPE_ANGLED,
   PAREN_TYPE_UNKNOWN
} ParenType_e;

typedef enum ParenState
{
   PAREN_STATE_OPEN,
   PAREN_STATE_CLOSE,
   PAREN_STATE_UNKNOWN
} ParenState_e;

typedef struct Paren
{
   const ParenType_e type;
   const ParenState_e state;
   const char paren;
} Paren_t;

typedef struct ParenSet
{
   const Paren_t parens[NUM_PAREN_STATES];
} ParenSet_t;

static char PARENS[NUM_PAREN_TYPES * NUM_PAREN_STATES];

static const ParenSet_t PAREN_TABLE[NUM_PAREN_TYPES] =
{
   {
      {
         { PAREN_TYPE_ROUND, PAREN_STATE_OPEN,  '(' },
         { PAREN_TYPE_ROUND, PAREN_STATE_CLOSE, ')' }
      }
   },
   {
      {
         { PAREN_TYPE_SQUARE, PAREN_STATE_OPEN,  '[' },
         { PAREN_TYPE_SQUARE, PAREN_STATE_CLOSE, ']' }
      }
   },
   {
      {
         { PAREN_TYPE_CURLY, PAREN_STATE_OPEN,  '{' },
         { PAREN_TYPE_CURLY, PAREN_STATE_CLOSE, '}' }
      }
   },
   {
      {
         { PAREN_TYPE_ANGLED, PAREN_STATE_OPEN,  '<' },
         { PAREN_TYPE_ANGLED, PAREN_STATE_CLOSE, '>' }
      }
   }
};

static bool IsParen(const char c);
static Paren_t* GetParen(const char c);

static bool isInitialised = false;

/*
 * InitParenBal
 */
void InitParenBal(void)
{
   if (!isInitialised)
   {
      for (int i = 0; i < NUM_PAREN_TYPES; i++)
      {
         for (int j = 0; j < NUM_PAREN_STATES; j++)
         {
            PARENS[j + i * NUM_PAREN_STATES] =
               PAREN_TABLE[i].parens[j].paren;
         }
      }
      isInitialised = true;
   }
}

/*
 * IsParenBal
 */
ParenBalResult_e IsParenBal(const char* str, size_t len)
{
   ParenBalResult_e result = PARENBAL_UNKNOWN;
   Paren_t *parenNow = NULL;
   Paren_t **parenPrev = NULL;
   size_t numParens = 0;
   bool newType = false;
   if (str)
   {
      if (len == 0 &&
         !IsParen(str[0]))
      {
         result = PARENBAL_SUCCESS;
      }
      else
      {
         parenPrev = malloc((len / 2) * sizeof(Paren_t*));
         if (parenPrev)
         {
            for (size_t i = 0; i < len && numParens < (len / 2); i++)
            {
               if (IsParen(str[i]))
               {
                  parenNow = GetParen(str[i]);
                  if (parenNow)
                  {
                     switch(parenNow->state)
                     {
                        case PAREN_STATE_OPEN:
                           numParens++;
                           parenPrev[numParens-1] = parenNow;
                           result = PARENBAL_SUCCESS;
                           break;
                        case PAREN_STATE_CLOSE:
                           if (numParens == 0)
                           {
                              result = PARENBAL_MISMATCH;
                              break;
                           }
                           if (parenPrev[numParens-1]->type != parenNow->type)
                           {
                              result = PARENBAL_INTERLOCK;
                              break;
                           }
                           numParens--;
                           result = PARENBAL_SUCCESS;
                           break;
                        default:
                           break;
                     }
                     if (result != PARENBAL_SUCCESS)
                     {
                        break;
                     }
                  }
               }
            }
            if (result == PARENBAL_SUCCESS &&
                  numParens != 0)
            {
               result = PARENBAL_MISMATCH;
            }
            free(parenPrev);
            parenPrev = NULL;
         }
      }
   }
   return result;
}

/*
 * IsParen
 */
bool IsParen(const char c)
{
   bool result = false;
   for (int i = 0; i < NUM_PAREN_TYPES * NUM_PAREN_STATES; i++)
   {
      if (c == PARENS[i])
      {
         result = true;
         break;
      }
   }
   return result;
}

/*
 * GetParen
 */
Paren_t* GetParen(const char c)
{
   Paren_t* result = NULL;
   const ParenSet_t *set = NULL;
   const Paren_t *paren = NULL;
   for (int i = 0; i < NUM_PAREN_TYPES; i++)
   {
      set = &PAREN_TABLE[i];
      for (int j = 0; j < NUM_PAREN_STATES; j++)
      {
         paren = &set->parens[j];
         if (c == paren->paren)
         {
            result = (Paren_t*) paren;
            break;
         }
      }
   }
   return result;
}
