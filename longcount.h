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

#define SECS		86400		// Seconds in a day ( 60 secs * 60 mins * 24 hrs)
#define	DAYS		20		// Days in a Score
#define SCORES		18		// Scores in a Solar Cycle

#define GMTCOR		584283		// Default Maya to Gregoerian correlation (GMT)
#define JCCOR		1272022		// UNIX Time correlation
#define TRUE		1
#define FALSE		0

/* TYPEDEF DEFINITIONS */
typedef	short int Flag;
typedef	short int Digit;
typedef	long  int LongNumber;

/* STRUCTURE DEFINITIONS */

struct lc {						
	Digit lc_day;				/* days since beginning of score [0-19] */
	Digit lc_score;				/* score days since beginning of cycle [0-17] (i.e powalli/winal/twenty days) */
	LongNumber lc_cycle;			/* cycles since epoch, (one cycle is eighteen score days or 360 days) */
	Flag  lc_postepoch;			/* Epoch flag, TRUE if date is post-epoch, FALSE if date is pre-epoch */
};
