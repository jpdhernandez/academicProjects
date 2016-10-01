/* IPC144; Professor Marek Laskowski
 * jphernandez2@myseneca.ca; Julian Philip Hernandez
 * This program processes a large set of weather data
 */

/* V 1.2:
 * Changes:
 * 1) declared i outside of loop, you don't need -std=c99 to compile anymore
 * 2) added a check for existence of historicaldata.csv
 * 3) completed code for all of the functions
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

// an instance of this struct holds the weather data for a single day
struct DailyData
{
	int day;
	int month;
	int year;
	float high;
	float low;
	float precipitation;
	char condition;
};

// an instance of this struct holds summary information for the weather
// for a given month
struct MonthlyStatistic{
	float minTemperature;
	float maxTemperature;
	float averageTemperature;
	float totalPrecipitation;
};

// function declarations
int readDailyData(FILE* fp, struct DailyData allData[]);
int getRelevantRecords(int yearWanted, const struct DailyData allData[], int sz, struct DailyData yearData[]);
void sortYearData(struct DailyData yearData[], int sz);
void getStats(int month, const struct DailyData yearData[],int sz, struct MonthlyStatistic* monthStats);
void printMonthlyStatistic(int month, const struct MonthlyStatistic* monthly);
void graphLine(int month, const struct MonthlyStatistic* monthly);
void printVerbose(const struct DailyData yearData[],int sz);
char symbolToDraw(char condition, float avgTemp);
float average(float first, float second);
void draw(char c, int num);
float roundf(float);

// debug function; used to check if data is sorted or not
void printdata(const struct DailyData d[], int sz)
{
	char* Names[] = {"zero", "January", "February", "March", "April", "May", "June", 
				"July", "August", "September", "October", "November", "December"};
	
	int i;
	for (i = 0; i < sz; i++)
	{
		printf("%s   %d,%d,%d,%f,%f,%f,%c\n", 
		Names[d[i].month], d[i].year, d[i].month, d[i].day,
		d[i].high, d[i].low, d[i].precipitation,
		d[i].condition);
		
		//draw(symbolToDraw(d[i].condition, average(d[i].high, d[i].low)), 20);
		//printf("\n");
	}
}

int main(void)
{
	// open data file
	FILE* fp = fopen("historicaldata.csv","r");
	if(!fp) // file validation
	{
		printf("you need to put historicaldata.csv into this directory\n");
		exit(0);
	}
	
	struct DailyData  allData[3000]; // struct array that will hold the all the data from from file
	struct DailyData yearData[366];  // struct array that will hold the selected year
	int numTotalRecords;
	numTotalRecords = readDailyData(fp, allData); // read all data from file to allData struct
	int year;
	int reportType;
	int i;
	struct MonthlyStatistic monthly[12]; // struct array to store the evaluated weather data
	
	fclose(fp);
	// prompt user for the which year to generate a report for
	printf("Please enter the year for the report: ");
	scanf("%d",&year);

	// prompt user to enter the type of report
	printf("Please enter the type of report you wish to generate:\n");
	printf("1) summary\n"); 
	printf("2) detailed\n");
	scanf("%d",&reportType);

	
	// this store number elemts in yearData and stores entered year to struct yearData
	int numDays = getRelevantRecords(year, allData, numTotalRecords, yearData);
	sortYearData(yearData, numDays); // this sorts the yearData array by month and day
	
	// this loop calculates monthly average and monthly total precipitation 
	// it also searches for the min and max from low and high respectively
	for(i = 0; i < 12; i++)
	{
		getStats(i + 1, yearData, numDays, &monthly[i]);
	}
	
	// this prints out a visual summary based on the weather data
	printf("Weather summary for %d\n",year);
	printf("|   Month   | High  |  Low  |  Avg  | Precip  |\n");
	printf("|-----------|-------|-------|-------|---------|\n");
	for(i = 0; i < 12; i++)
	{
		printMonthlyStatistic(i + 1, &monthly[i]);
	}
	
	// this prints out a bar graph that shows the amount of precipitation
	// for a given month in the selected year
	printf("\n\n");
	printf("Precipitation Graph\n\n");
	for(i = 0; i < 12; i++)
	{
		graphLine(i + 1, &monthly[i]);
	}
	
	// this prints out a detailed report if user selected a detailed report
	if(reportType == 2)
	{
		printf("\n\n");
		printf("Detailed report:\n");
		printVerbose(yearData, numDays);
	}
	
	return 0;
}

/* This function accepts a FILE pointer and a struct array
 * this fuction reads the data from the file pointed to by fp
 * and it copies all the information to the struct array allData
 */
int readDailyData(FILE* fp, struct DailyData allData[])
{
	int i = 0;
	while(fscanf(fp,"%d,%d,%d,%f,%f,%f,%c\n",
		&allData[i].year, &allData[i].month, &allData[i].day,
		&allData[i].high, &allData[i].low, &allData[i].precipitation,
		&allData[i].condition) == 7)
	{
		i++;
	}
	return i;
}

/* This function accepts the yearWanted, allData (contains all the record in the file)
 * it also accepts the size of array (sz) and another array called yearData
 * This function copies all the records from allData to yearData that matches yearwWanted
 * and it returns the number of records copied or read
 */
int getRelevantRecords(int yearWanted, const struct DailyData allData[], int sz,  struct DailyData yearData[])
{
	int j;
	int i = 0;
	for (j = 0; j < sz; j++)
	{
		if (allData[j].year == yearWanted)
		{
			yearData[i] = allData[j];
			i++;
		}
	}
	return i;
}

/* This function accepts the sz of the struct array yearData
 * This function sorts the records in yearData by month and day
 * This function uses selection sort from the IPC144 Chapter on Algorithms
 * this function returns nothing but overwrites yearData struct array
 */
void sortYearData(struct DailyData yearData[], int sz)
{
	int i, j, m;
	struct DailyData temp[sz]; // temporary array for swapping
	
	// this loops sorts yearData by month
	for (i = 0; i < sz; i++)
	{
		m = i;
		for (j = i + 1; j < sz; j++)
		{
			if (yearData[j].month < yearData[m].month)
			{
				m = j;
			}
		}
		if (m != i)
		{
			temp[i] = yearData[i];
			yearData[i] = yearData[m];
			yearData[m] = temp[i];
		}
	}
	// this loop sorts yearData by day
	int x, y, z;
	for (x = 0; x < sz; x++)
	{
		z = x;
		for (y = x + 1; y < sz; y++)
		{
			if (yearData[y].day < yearData[z].day && yearData[y].month == yearData[z].month)
			{
				z = y;
			}
		}
		if (z != x)
		{
			temp[x] = yearData[x];
			yearData[x] = yearData[z];
			yearData[z] = temp[x];
		}
	}
}


/* This function accepts the month, yearData, size of yearData and a pointer to monthlyStatistic struct
 * this function find the min and the max of high and low respectively of the matching month
 * it also gets the monthly average and monthly total precipitation of the matching month
 * the results are stored in the appropriate data members of monthStats monthly
 */
void getStats(int month, const struct DailyData yearData[], int sz, struct MonthlyStatistic* monthly)
{
	int i, j = 0; 
	float average = 0.0;
	monthly->maxTemperature = 0.0;
	monthly->minTemperature = 0.0;
	monthly->totalPrecipitation = 0.0;
	monthly->averageTemperature = 0.0;
	for (i = 0; i < sz; i++)
	{
		if (yearData[i].month == month)
		{
			if (yearData[i].high > monthly->maxTemperature) 
			{
				monthly->maxTemperature = yearData[i].high; // stores the max temp
			}
			if (yearData[i].low < monthly->minTemperature)
			{
				monthly->minTemperature = yearData[i].low; // stores the min temp
			}
			monthly->totalPrecipitation += yearData[i].precipitation; // sums all precipitation data
			average += (yearData[i].high + yearData[i].low) / 2; // sums the average of all high and low
			j++;
		}
	}
	monthly->averageTemperature = average / j; // evaluates the monthly average temperature
}


/* This function accepts a month as an integer - 1 is Jan, 2 is Feb
 * it also accepts a pointer to MonthlyStatistic struct
 * This function will print out a formatted output in a form of a summary table
 * each row of the table will consists of text and values stored in monthly struct
 */
void printMonthlyStatistic(int month, const struct MonthlyStatistic* monthly)
{
	// this is a parallel array stores the matching month in string format, 1 - Jan, 2 - Feb, and so on
	char* Names[] = {"zero", "January", "February", "March", "April", "May", "June", 
				"July", "August", "September", "October", "November", "December"};
	
	printf("|%10s | %-5.1f | %-5.1f | %-5.1f |  %-6.1f |\n", 
		Names[month], monthly->maxTemperature, monthly->minTemperature,
		monthly->averageTemperature, monthly->totalPrecipitation);
}


/* This function accepts a month as an int and a pointer to MonthlyStatistic
 * This function will print out one single row of the precipitation bar graph of the matching month
 */
void graphLine(int month,const struct MonthlyStatistic* monthly)
{
	// this parallel array stores the matching month in string format; 1 - Jan, 2 - Feb, and so on
	char* Names[] = {"zero", "January", "February", "March", "April", "May", "June", 
				"July", "August", "September", "October", "November", "December"};
	int j;
	int size = roundf(monthly->totalPrecipitation / 10); // rounds up the value after division
	printf("%12s |", Names[month]);
	for(j = 0; j < size; j++)
	{
		printf("*");
		if(j == size - 1)
		{
			printf("\n");
		}
	}
}


/* This function accpets and prints out the details of the weather data for each of the records in yearData
 * The number of lines printed will be based on the int sz passed, and each line shows the
 * deatiled weather information for a specific date; the info includes the specific date, the
 * average temp and 20 symbols based on the condition of the day; 
 */
void printVerbose(const struct DailyData yearData[],int sz)
{
	// this parallel array stores the matching month in string format; 1 - Jan, 2 - Feb, and so on
	char* Names[] = {"zero", "January", "February", "March", "April", "May", "June", 
				"July", "August", "September", "October", "November", "December"};
	int i;
	for (i = 0; i < sz; i++)
	{
		printf("%9s %2d %-1d: %5.1f ", 
		Names[yearData[i].month], yearData[i].day, yearData[i].year,
		average(yearData[i].high, yearData[i].low));
		draw(symbolToDraw(yearData[i].condition, average(yearData[i].high, yearData[i].low)), 20);
	}
}


/* This function returns the correct character (@, ~, *, ;) given the current
 * condition and the average temperature.
 * NOTE: Precipitation character (* or ;) will change depending on the average
 * temperature.
 * char condition represents the current conditions
 * float averwageTemperature represents the average daily temperature
 */
char symbolToDraw(char condition, float avgTemp)
{
	if (condition == 'c')
	{
		char symbol = '~'; // cloudy
		return symbol;
	}
	else if (condition == 's')
	{
		char symbol = '@'; // sunny
		return symbol;
	}
	else if (condition == 'p')
	{
		if (avgTemp < 1)
		{
			char symbol = '*'; // snowy
			return symbol;
		}
		else if (avgTemp > 0)
		{
			char symbol = ';'; // rainy
			return symbol;
		}
	}
}


// This function returns the average of two floating point values
float average(float first, float second)
{
	float result = (first + second) / 2.0;
	return result;
}


/* This function draws a row of characters (such as @@@@@@@ ).
 * char c holds the character that will be repeated
 * int num holds the number of times that the character will be repeated
 * The number of characters is controlled by the value of "num".
 */
void draw(char c, int num)
{
	int i;
	for(i = 0; i < num; i++)
	{
		printf("%c", c);
		if(i == num -1)
		{
			printf("\n");
		}
	}
}
