#include <iostream>
#include <chrono> //Library with functions for obtaining current date. Only available with C++11
#include <iomanip> //Library with function for converting time_t to various other var types
#include <string>
#include <math.h>

//Function for storing date in a character array
//Array must be 9 bytes long because there must be an extra byte at end to store null terminator
//Delivered char array is in the following format: ddmmyyyy
void deliverDate(char*);

void deliverWeekday(char*);

int charArrayToInt(char*,int);

void intToCharArray(int,int,char*);

int main(){
	
	const int DAYS_IN_WEEK = 7,
			DAYS_IN_YEAR = 365,
					 YEARS = 3,
		   WEEKS_PER_YEAR = 52;
					
	const int DATE_REP_LENGTH = 8; //Indicates size of each char array that together represents a specific date (ddmmyyyy)
	
	//A 3D array of three years of weeks is created where each day in a week 
	//holds an 8-byte character array that indicates the date
	char arrayOfWeeks[YEARS*WEEKS_PER_YEAR][DAYS_IN_WEEK][DATE_REP_LENGTH];
					
	//Store current date from system in char array
	char currentDate[9]; //Needs extra byte at end to store null terminator
	deliverDate(currentDate);
	
	//Convert char array of current date into separate ints
	int currentYearInt = charArrayToInt(currentDate+4,4);	
	int currentDayInt = charArrayToInt(currentDate,2);	
	int currentMonthInt = charArrayToInt(currentDate+2,2);	
	
	std::cout<<"Today's date: "<<currentMonthInt<<'/'<<currentDayInt<<'/'<<currentYearInt<<std::endl;
	
	char wdChar;
	char* wdPtr = &wdChar;
	deliverWeekday(wdPtr);
	int wdInt = static_cast<int>(wdChar) - 48;

	bool leapYearFlag;
	int daysInThisMonth;
	
	//Char arrays for converting year, month, and day ints
	char currentYearChars[4],
		 currentMonthChars[2],
		   currentDayChars[2];
	
	int y = currentYearInt;
	int m = currentMonthInt;
	int d = currentDayInt;
	
	int weekNumber = 0;
	
	intToCharArray(y,4,currentYearChars);
	std::cout << std::endl;
	std::cout.put(currentYearChars[3]);
	std::cout << std::endl;
	
	for(;y <= (currentYearInt + YEARS);y++){

		//Checking if year is a leap year
		(y%4) ? (leapYearFlag = 0) : (leapYearFlag = 1);
		
		//Reset the month counter
		if(m==13)
			m=1;

		while(m<=12){

			//Number of days in month varies
			if(m<7){
				//Odd-numbered months before July have 31 days

				//Special case for February with leap year
				if(m==2)
					(leapYearFlag) ? (daysInThisMonth = 29) : (daysInThisMonth = 28);

				if(m%2)
					daysInThisMonth = 31;
				else
					daysInThisMonth = 30;

			}
			else{
				//Odd-numbered months after June have 30 days
				if(m%2)
					daysInThisMonth = 30;
				else
					daysInThisMonth = 31;
			}

			for(;d<=daysInThisMonth;d++){


				intToCharArray(d,2,&arrayOfWeeks[weekNumber][wdInt][0]);
				intToCharArray(m,2,&arrayOfWeeks[weekNumber][wdInt][2]);
				intToCharArray(y,4,&arrayOfWeeks[weekNumber][wdInt][4]);

				wdInt++;
				
				//Reset after Sunday (wdInt=6)
				if(wdInt==7)
				{
					weekNumber++;
					wdInt=0;
				}

			}
			
			//Reset day counter after exiting loop
			d=1;
			m++;

		}

	}

	// for(int n = 0;n<8;n++){
	// 	std::cout << std::endl;
	// 	std::cout.put(arrayOfWeeks[6][4][n]);
	// }
	
	return 0;
}

//Function for storing date in a character array
//Array must be 9 bytes long because there must be an extra byte at end to store null terminator
//Delivered char array is in the following format: mmddyyyy
void deliverDate(char* target){
	
	//Creating time_point type and converting to a time_t type
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	std::strftime(target,static_cast<size_t>(8),"%e%m%Y",std::localtime(&now_c));
	
}

void deliverWeekday(char* target){
	
	//Creating time_point type and converting to a time_t type
	std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
	std::time_t now_c = std::chrono::system_clock::to_time_t(now);

	std::strftime(target,static_cast<size_t>(1),"%w",std::localtime(&now_c));
	
}

//Function for converting an array of characters stored in standard decimal form
//to the equivalent int value.
//
//charArry must be the address of the leftmost digit and size is the number
// of digits
int charArrayToInt(char* charArray,int size){
	
	int convertedInt = 0; //V
	int magnitude = 1;
	
	for(int n = (size-1);n>=0;n--){
		
		convertedInt += (static_cast<int>(charArray[n])-48)*magnitude;
		magnitude*=10;
		
	}

	return convertedInt;
	
}

void intToCharArray(int myInt, int digits, char* target){
	
	//Placeholder for int while being convereted
	int myIntConverted;
	//Placeholder for single integer digit as char
	char intAsChar;
	
	int magnitude;
	
	for(int n=0;n<digits;n++){
		
		//Reset original int
		myIntConverted = myInt;
		
		//Adjust magnitude
		magnitude = pow(10,(digits-n-1));
		
		//Isolate each digit by magnitude
		myIntConverted = (myIntConverted/magnitude)%10;	
		
		//Convert digit to ASCII value then char
		myIntConverted+=48;
		intAsChar = static_cast<char>(myIntConverted);
		
		//Store char at current decimal place of target
		target[n] = intAsChar;
		
	}
	
}
