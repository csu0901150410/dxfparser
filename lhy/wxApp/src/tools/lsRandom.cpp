#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* These functions come from Eric Roberts' "The Art and Science of C". */

/*
 * Function: InitRandom
 * --------------------
 * This function seeds the random number generator
 * with the current time.  It should be called once
 * (and only once) prior to calling any other random
 * number function.
 */
void InitRandom(void)
{
  srand((int) time(NULL));
}


/*
 * Constant: RAND_MAX
 * ------------------
 * Unfortunately, several libraries that supposedly conform to
 * the ANSI standard do not define RAND_MAX in <stdlib.h>.  To
 * reduce portability problems, this interface defines RAND_MAX
 * to be the largest positive integer if it is undefined.
 */
#ifndef RAND_MAX
#define RAND_MAX ((int) ((unsigned) ~0 >> 1))
#endif


/*
 * Function: RandomReal
 * --------------------
 * This function returns a random real number between
 * low and high, inclusive.
 */
double RandomReal(double low, double high)
{
  double d;

  d = (double) rand() / ((double) RAND_MAX + 1);
  return (low + d * (high - low));
}


/*
 * Function: RandomInteger
 * -----------------------
 * This function returns a random integer between
 * low and high, inclusive.
 */
int RandomInteger(int low, int high)
{
  int k;
  double d;

  d = (double) rand() / ((double) RAND_MAX + 1);
  k = (int) (d * (high - low + 1));
  return (low + k);
}