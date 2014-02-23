/*	
	Copyright 2008, 5195 LC, Chema Hernandez G.
	This file is part of LongCount.

	LongCount is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    LongCount is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with LongCount.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "longcount.h"

#define MINPLACE	5			/* Minimum amount of places */
#define SPACERS		"."
#define PREEPOCH	"-"

/* FUNCTIONS */
// Convert raw days to lc date
struct lc *lcdate(const long int *);

int orderMagnitude ( const long int *);

int digitSize ( const struct lc *);


/* MAIN */
int main (int argc, const char *argv[]) 
{ 
	long int rawDays;
	struct lc *datePtr = malloc (sizeof (struct lc));  // Is malloc necessary, or can I just use a simple pointer??
	
	if (argc==0) { /* use system time for calculations */
		long int unixTimeDays = time(NULL)/SECS;					/* Number of days since Unix Time Epoch, remainder truncated */
		// int gregorianCorrelation = GMTCOR;						// TODO, TURN INTO ARG
		rawDays = unixTimeDays + (GMTCOR + JCCOR);					/* Number of days since Long Count Epoch */
	}
	else {
		rawDays = atol(argv[1]);									// Turn first arg into long int
	}
	
	
	/* Make structure */	
	datePtr = lcdate (&rawDays);
	printf ("Epoch: %d Days: %d Scores: %d Cycles: %d\n", datePtr->lc_postepoch, datePtr->lc_day, datePtr->lc_score, datePtr->lc_cycle);

	/* Calculate size of array */
	int datePlaces = digitSize (datePtr);
	if ( datePlaces < MINPLACE ) datePlaces = MINPLACE;
	// printf("Digits: %d\n",datePlaces);

	/* Create array */
	Digit master[datePlaces];
	int counter=0;
	ldiv_t ldivresult;

	if ( datePlaces >= 1) master[counter++]=datePtr->lc_day;
	if ( datePlaces >  2) master[counter++]=datePtr->lc_score;
	if ( datePlaces >  3) {
		ldivresult.quot = datePtr->lc_cycle;						/* cycles */
		while (counter<datePlaces) {
			ldivresult = ldiv (ldivresult.quot, 20);			// Calculate lc_score and lc_cycle
			master[counter++]=ldivresult.rem;
		}
	}

	/* Transform array to string */
	char oneDigit [3];
	char *dateString = malloc(3 * datePlaces *sizeof (char) + 3);
	
	counter = datePlaces;
	if (datePtr->lc_postepoch==FALSE) strcat (dateString, PREEPOCH);
	while (counter>0) {
		sprintf (oneDigit,"%02d",master[counter-1]);
		strcat (dateString,oneDigit);
		counter--;
		if (counter != 0) strcat (dateString, SPACERS);
//		printf ("d: %d %s\n",strlen(dateString),dateString);
	}
	
	/* Print array*/
	printf ("%s\n", dateString);
//	printf ("%d|%02d|%02d\n", datePtr->lc_cycle, datePtr->lc_score, datePtr->lc_day);

	return 0;
} 





/* Calculate the date TURN TO POINTER FUNCTION!!! */
struct lc *lcdate(const long int *rawDays) {
	struct lc *result = malloc (sizeof (struct lc));  // DOES MALLOC CREATE THE STRUCTURE TOO??
	// (*result)-> = { TRUE, 0, 0, 0 };				// Init HOW TO DO IT???
	
	long int absdays = labs(*rawDays);				// Abs rawdays
	ldiv_t ldivresult;
	
	if (*rawDays < 0) result->lc_postepoch=FALSE;	// Calculate lc_postepoch: set to FALSE if < 0, else TRUE
	else result->lc_postepoch=TRUE;
	
	ldivresult = ldiv (absdays, DAYS);				// Calculate lc_day: LDIV absdays by DAYS (20) & add to structure
	result->lc_day = ldivresult.rem;
	
	ldivresult = ldiv (ldivresult.quot, SCORES);	// Calculate lc_score and lc_cycle
	result->lc_score = ldivresult.rem;
	result->lc_cycle = ldivresult.quot;
	
	// printf ("Epoch: %d Days: %d Scores: %d Cycles: %d\n", result->lc_postepoch, result->lc_day, result->lc_score, result->lc_cycle);	
	return result;
}


/* Calculate the number of digits */
int digitSize ( const struct lc * date) {
	if ( date->lc_cycle > 0 ) return (3 + orderMagnitude ( &(date->lc_cycle)) ); /* Order of magnitude in b20 for cycles + 3 */
	if ( date->lc_score > 0 ) return 2;
	if ( date->lc_day  >= 0 ) return 1;
	return 0;
}


/* Calculate cycle order of magnitude in base 20 */
int orderMagnitude ( const long int * cycle ) {
	if ( *cycle == 0 ) {
		return 0;
	} else {
		double mag = (double) *cycle;
		mag = floor ( log( mag ) / log(20) );
		return (int) mag;
	}
}
