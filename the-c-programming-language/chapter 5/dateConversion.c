#include<stdio.h>

/*
	Multi-dimensional arrays

	C provides rectangular multi-dimensional arrays, although in practice they are much
	less used than arrays of pointers.

	Example:

	Consider the proble of date conversion, from day of the month to day of the year
	and vice versa. For example, March 1 is the 60th day of a non-leap year, and the
	61st  day of a leap year. Let us define two functions to do the conversions:

		day_of_year: converts the month and day into the day of the year

		month_day: converts the day of the year into the month and day. Since the
				   latter function computes two values, the month and day arguments
				   	will be pointers:

				   	month_day(1988, 60, &m, &d)

				   	sets m to 2 and d to 29 (February 29th)
*/

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day. */
int day_of_year(int year, int month, int day) {
	int i, leap;

	leap = isleap(year);
	for (i = 1; i < month; i++) {
		day += daytab[leap][i];
	}

	return day;
}

/* month_day: set month, day from day of year. */
void month_day(int year, int yearday, int *pmonth, int *pday) {
	int i, leap;

	leap = isleap(year);
	for (i = 1; yearday > daytab[leap][i]; i++) {
		yearday -= daytab[leap][i];
	}

	*pmonth = i;
	*pday = yearday;
}

/* It calculates if the year is leap or not. Recall that the arithmetic
   value of a logical expression, such as the one for leap, is either
   zero (false) or one (true), so it can be used as subscript of the
   array daytab.   
 */
int isleap(int year) {
	int leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
	return leap;
}

char *month_name(int n) {
	static char *name[] = {
		"Illegal month",
		"January", "February", "March",
		"April", "May", "June",
		"July", "August", "September",
		"October", "November", "December"
	};

	return (n < 1 || n > 12) ? name[0] : name[n];
}

int main() {
	// Calculating the day of the year
	int year = 2013;
	int month = 8;
	int day = 7;

	printf("------------ Calculating the day of the year ------------\n");
	printf("Day of year (%s %d, %d): %d\n", month_name(month), day, year, day_of_year(year, month, day));

	year = 2012;
	month = 2;
	day = 29;
	printf("Day of year (%s %d, %d): %d\n", month_name(month), day, year, day_of_year(year, month, day));


	// Calculating the month and day
	int pmonth;
	int pday;
	char *name_month;
	int yearday = 60;
	
	year = 2013;

	printf("\n\n------------ Calculating month and day ------------\n");	
	month_day(year, yearday, &pmonth, &pday);
	name_month = month_name(pmonth);
	printf("Date (%d, day %d): %s %d\n\n", year, yearday, name_month, pday);
}















