#pragma once
#pragma warning(disable: 4996)
#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

class clsDate
{
private:
	short _Day = 1;
	short  _Month = 1;
	short _Year = 1900;
	vector <string> SplitString(string S1, string delim) {
		string sWorld;
		vector <string> vString;
		short pos = 0;

		while ((pos = S1.find(delim)) != string::npos) {
			sWorld = S1.substr(0, pos);
			if (sWorld != "")
				vString.push_back(sWorld);
			S1.erase(0, pos + delim.length());
		}
		if (S1 != "")
			vString.push_back(S1);
		return vString;
	}

	struct stPeriod {
		string StartDate;
		string EndDate;
	};
public:

	clsDate() {
		time_t t = time(0);
		tm* now = localtime(&t);
		_Year = 1900 + now->tm_year;
		_Month = 1 + now->tm_mon;
		_Day = now->tm_mday;
	}
	clsDate(string Date) {
		vector <string> vDate;
		vDate = SplitString(Date, "/");
		_Day = stoi(vDate[0]);
		_Month = stoi(vDate[1]);
		_Year = stoi(vDate[2]);
	}
	clsDate(short Day, short Month, short Year) {
		_Day = Day;
		_Month = Month;
		_Year = Year;
	}
	clsDate(short Number, short year) {
		clsDate Date = GetDateFromDayOrderInYear(Number, year);
		_Day = Date._Day;
		_Month = Date._Month;
		_Year = Date._Year;
	}
	static bool IsLeapYear(short Year) {
		return ((Year % 4 == 0 && Year % 100 != 0) || (Year % 400 == 0));
	}
	bool IsLeapYear() {
		return IsLeapYear(_Year);
	}
	void SetDay(short Day) {
		_Day = Day;
	}
	short GetDay() {
		return _Day;
	}
	__declspec(property(get = GetDay, put = SetDay)) short Day;
	void SetMonth(short Month) {
		_Month = Month;
	}
	short GetMonth() {
		return _Month;
	}
	__declspec(property(get = GetMonth, put = SetMonth)) short Month;
	void SetYear(short Year) {
		_Year = Year;
	}
	short GetYear() {
		return _Year;
	}
	__declspec(property(get = GetYear, put = SetYear)) short Year;
	static clsDate GetSystemDate() {

		time_t t = time(0);
		tm* now = localtime(&t);
		short Day, Month, Year;
		Year = now->tm_year + 1900;
		Month = now->tm_mon + 1;
		Day = now->tm_mday; return clsDate(Day, Month, Year);
	}
	static string DateToString(clsDate Date) {
		return  to_string(Date.Day) + "/" + to_string(Date.Month) + "/" + to_string(Date.Year);
	}
	string DateToString() {
		return  DateToString(*this);
	}
	static short NumberOfDaysInYear(short Year) {
		return IsLeapYear(Year) ? 366 : 365;
	}
	short NumberOfDaysInYear() {
		return NumberOfDaysInYear(_Year);
	}
	static short NumberOfHoursInYear(short Year) {
		return NumberOfDaysInYear(Year) * 24;
	}
	short NumberOfHoursInYear() {
		return NumberOfHoursInYear(_Year);
	}
	static int NumberOfMinutesInYear(short Year) {
		return NumberOfHoursInYear(Year) * 60;
	}
	int NumberOfMinutesInYear() {
		return NumberOfMinutesInYear(_Year);
	}
	static int NumberOfSecondInYear(short Year) {
		return NumberOfMinutesInYear(Year) * 60;
	}
	int NumberOfSecondInYear() {
		return NumberOfSecondInYear(_Year);
	}
	static short NumberOfHoursInMonth(short Year, short Month) {
		return NumberOfDaysInMonth(Year, Month) * 24;
	}
	short NumberOfHoursInMonth() {
		return NumberOfHoursInMonth(_Year, _Month);
	}
	static int NumberOfMinutesInMoth(short Year, short Month) {
		return NumberOfHoursInMonth(Year, Month) * 60;
	}
	int NumberOfMinutesInMoth() {
		return NumberOfMinutesInMoth(_Year, _Month);
	}
	static int NumberOfSecondsInMoth(short Year, short Month) {
		return NumberOfMinutesInMoth(Year, Month) * 60;
	}
	int NumberOfSecondsInMoth() {
		return NumberOfSecondsInMoth(_Year, _Month);
	}
	static short NumberOfDaysInMonth(short Year, short Month) {
		if (Month < 1 || Month > 12)
			return 0;
		int Numberdays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		return (Month == 2) ? (IsLeapYear(Year) ? 29 : 28) : Numberdays[Month - 1];
	}
	short NumberOfDaysInMonth() {
		return NumberOfDaysInMonth(_Year, _Month);
	}
	static clsDate GetDateFromDayOrderInYear(short DateDateOrderInYear, short Year) {
		clsDate Date;
		short RemainingDays = DateDateOrderInYear; // 354
		short MonthDays = 0;
		short YearDays = 0;
		Date._Year = Year;
		int Month = 1;
		while (true) {
			MonthDays = NumberOfDaysInMonth(Year, Month);
			if (RemainingDays > MonthDays) {
				RemainingDays -= MonthDays;
				Month++;
			}
			else {
				Date._Day = RemainingDays;
				break;
			}
		}
		return Date;
	}
	clsDate GetDateFromDayOrderInYear(short DateDateOrderInYear) {
		return GetDateFromDayOrderInYear(DateDateOrderInYear, _Year);
	}
	static short AddDays() {
		short AddDays = 0;
		cout << "How many add to days? ";
		cin >> AddDays;
		return AddDays;
	}
	static clsDate DateAddDays(short Days, clsDate Date) {
		short RemainingDays = Days + NumberOfDaysFromTheBeginingOfTheYear(Date.Day, Date.Month, Date.Year);
		short MonthDays = 0;
		int Month = 1;
		while (true) {
			MonthDays = NumberOfDaysInMonth(Date.Year, Month);

			if (RemainingDays > MonthDays) {
				RemainingDays -= MonthDays;
				Month++;

				if (Month > 12) {
					Month = 1;
					Date.Year++;
				}
			}
			else {
				Date.Day = RemainingDays;
				break;
			}
		}
		return Date;
	}
	clsDate DateAddDays(short Days) {
		return DateAddDays(Days, *this);
	}
	static bool IsDate1EqualDate2(clsDate Date, clsDate Date2) {
		return (Date._Year == Date2._Year) ? ((Date._Month == Date2._Month) ?
			((Date._Day == Date2._Day) ? true : false) :
			false) : false;
	}
	bool IsDate1EqualDate2(clsDate Date2) {
		return IsDate1EqualDate2(*this, Date2);
	}
	static void Print(clsDate Date) {
		cout << Date._Day << "/" << Date._Month << "/" << Date._Year << endl;
	}
	void Print() {
		cout << _Day << "/" << _Month << "/" << _Year << endl;
	}
	static short DayOfWeekOrder(short Day, short Month, short Year) {
		short a, y, m;
		a = (14 - Month) / 12;
		y = Year - a;
		m = Month + 12 * a - 2;
		Day = (Day + y + (y / 4) - (y / 100) + (y / 400) + ((31 * m) / 12)) % 7;
		return Day;
	}
	static short DayOfWeekOrder(clsDate Date) {
		return DayOfWeekOrder(Date._Day, Date._Month, Date._Year);
	}
	static string MonthShortNumber(short Month) {
		string name[12] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		return name[Month - 1];
	}
	string MonthShortNumber() {
		return MonthShortNumber(_Month);
	}
	static void PrintCalenderMonth(short Month, short Year) {
		int NumberOfDays;
		int current = DayOfWeekOrder(1, Month, Year);
		NumberOfDays = NumberOfDaysInMonth(Year, Month);
		printf("-----------------%s----------------\n\n", MonthShortNumber(Month).c_str());
		printf("  Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
		int i;
		for (i = 0; i < current; i++)
			printf("     ");
		for (int j = 1; j <= NumberOfDays; j++) {
			printf("%5d", j);
			if (++i == 7) {
				i = 0;
				printf("\n");
			}
		}
		printf("\n---------------------------------------\n");
	}
	void PrintCalenderMonth() {
		return PrintCalenderMonth(_Month, _Year);
	}
	static void PrintYearCalendar(short Year) {
		printf("\n-------------------------------------------\n\n");
		printf("         Calendar - %d\n", Year);
		printf("  ----------------------------------------\n");
		for (int i = 1; i <= 12; i++) {
			PrintCalenderMonth(i, Year);
		}
	}
	void PrintYearCalendar() {
		return PrintYearCalendar(_Year);
	}
	static bool IsDate1BeforeDate2(clsDate Date, clsDate Date2) {
		return (Date._Year < Date2._Year) ? true : ((Date._Year == Date2._Year) ? (Date._Month < Date2._Month ? true : (Date._Month == Date2._Month ? Date._Day < Date2._Day : false)) : false);
	}
	bool IsDate1BeforeDate2(clsDate Date2) {

		return IsDate1BeforeDate2(*this, Date2);
	}
	static bool IsLastDayInMonth(clsDate Date) {
		return (Date._Day == NumberOfDaysInMonth(Date._Year, Date._Month));
	}
	static bool IsLastMonthInYear(short Month) {
		return (Month == 12);
	}
	static clsDate IncreaseDateByOneDay(clsDate& Date) {
		if (IsLastDayInMonth(Date)) {
			if (IsLastMonthInYear(Date._Month)) {
				Date._Month = 1;
				Date._Day = 1;
				Date._Year++;
			}
			else {
				Date._Day = 1;
				Date._Month++;
			}
		}
		else {
			Date._Day++;
		}
		return Date;
	}
	void IncreaseDateByOneDay() {
		IncreaseDateByOneDay(*this);
	}
	clsDate IncreaseDateByXDays(clsDate& Date, int Number) {
		for (int i = 0; i < Number; i++) {
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByXDays(int Number) {
		IncreaseDateByXDays(*this, Number);
	}
	clsDate IncreaseDateByOneWeek(clsDate& Date) {
		for (int i = 0; i < 7; i++) {
			Date = IncreaseDateByOneDay(Date);
		}
		return Date;
	}
	void IncreaseDateByOneWeek() {
		IncreaseDateByOneWeek(*this);
	}
	clsDate IncreaseDateByXWeeks(clsDate& Date, int Number) {
		for (int i = 0; i < Number; i++) {
			Date = IncreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void IncreaseDateByXWeeks(int Number) {
		IncreaseDateByXWeeks(*this, Number);
	}
	clsDate IncreaseDateByOneMonth(clsDate& Date) {
		if (IsLastMonthInYear(Date._Month)) {
			Date._Month = 1;
			Date._Year++;
		}
		else
			Date._Month++;
		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date._Year, Date._Month);
		if (Date._Day > NumberOfDaysInCurrentMonth) {
			Date._Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}
	void IncreaseDateByOneMonth() {
		IncreaseDateByOneMonth(*this);
	}
	clsDate IncreaseDateByXMonths(clsDate& Date, int Month) {
		for (int i = 0; i < Month; i++)
			Date = IncreaseDateByOneMonth(Date);

		return Date;
	}
	void IncreaseDateByXMonths(int Month) {
		IncreaseDateByXMonths(*this, Month);
	}
	clsDate IncreaseDateByOneYear(clsDate& Date) {
		Date._Year++;
		return Date;
	}
	void IncreaseDateByOneYear() {
		IncreaseDateByOneYear(*this);
	}
	clsDate IncreaseDateByXYears(clsDate& Date, int Year) {
		for (int i = 0; i < Year; i++)
			Date = IncreaseDateByOneYear(Date);
		return Date;
	}
	void IncreaseDateByXYears(int Year) {
		IncreaseDateByXYears(*this, Year);
	}
	clsDate IncreaseDateByXYearsFaster(clsDate& Date, int Year) {
		Date._Year += Year;
		return Date;
	}
	void IncreaseDateByXYearsFaster(int Year) {
		IncreaseDateByXYearsFaster(*this, Year);
	}
	clsDate IncreaseDateByOneDecade(clsDate& Date) {
		Date._Year += 10;
		return Date;
	}
	void IncreaseDateByOneDecade() {
		IncreaseDateByOneDecade(*this);
	}
	clsDate IncreaseDateByXDecades(clsDate& Date, int Decade) {
		//int Number = NumberOfDaysInYear(Date.Year);
		for (int i = 0; i < Decade * 10; i++)
			Date = IncreaseDateByOneYear(Date);
		return Date;
	}
	void IncreaseDateByXDecades(int Decade) {
		IncreaseDateByXDecades(*this, Decade);
	}
	clsDate IncreaseDateByXDecadesFaster(clsDate& Date, int Decade) {
		Date._Year += Decade * 10;
		return Date;
	}
	void IncreaseDateByXDecadesFaster(int Decade) {
		IncreaseDateByXDecadesFaster(*this, Decade);
	}
	clsDate IncreaseDateByOneCentury(clsDate& Date) {
		Date._Year += 100;
		return Date;
	}
	void IncreaseDateByOneCentury() {
		IncreaseDateByOneCentury(*this);
	}
	clsDate IncreaseDateByOneMillennium(clsDate& Date) {
		Date._Year += 1000;
		return Date;
	}
	void IncreaseDateByOneMillennium() {
		IncreaseDateByOneMillennium(*this);
	}
	clsDate DecreaseDateByOneDay(clsDate& Date) {
		if (Date._Day == 1) {
			if (Date._Month == 1) {
				Date._Month = 12;
				Date._Day = 31;
				Date._Year--;
			}
			else {
				Date._Month--;
				Date._Day = NumberOfDaysInMonth(Date._Year, Date._Month);
			}
		}
		else
			Date._Day--;
		return Date;
	}
	void DecreaseDateByOneDay() {

		DecreaseDateByOneDay(*this);
	}
	clsDate DecreaseDateByXDays(clsDate& Date, int Number) {
		for (int i = 0; i < Number; i++) {
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByXDays(int Number) {
		DecreaseDateByXDays(*this, Number);
	}
	clsDate DecreaseDateByOneWeek(clsDate& Date) {
		for (int i = 0; i < 7; i++) {
			Date = DecreaseDateByOneDay(Date);
		}
		return Date;
	}
	void DecreaseDateByOneWeek() {
		DecreaseDateByOneWeek(*this);
	}
	clsDate DecreaseDateByXWeeks(clsDate& Date, int weeks) {

		for (int i = 0; i < weeks; i++) {
			Date = DecreaseDateByOneWeek(Date);
		}
		return Date;
	}
	void DecreaseDateByXWeeks(int weeks) {
		DecreaseDateByXWeeks(*this, weeks);
	}
	clsDate DecreaseDateByOneMonth(clsDate& Date) {
		if (Date._Month == 1) {
			Date._Month = 12;
			Date._Year--;
		}
		else
			Date._Month--;
		short NumberOfDaysInCurrentMonth = NumberOfDaysInMonth(Date._Year, Date._Month);
		if (Date._Day > NumberOfDaysInCurrentMonth) {
			Date._Day = NumberOfDaysInCurrentMonth;
		}

		return Date;
	}
	void DecreaseDateByOneMonth() {
		DecreaseDateByOneMonth(*this);
	}
	clsDate DecreaseDateByXMonths(clsDate& Date, int Month) {
		for (int i = 0; i < Month; i++)
			Date = DecreaseDateByOneMonth(Date);

		return Date;
	}
	void DecreaseDateByXMonths(int Month) {
		DecreaseDateByXMonths(*this, Month);
	}
	clsDate DecreaseDateByOneYear(clsDate& Date) {
		Date._Year--;
		return Date;
	}
	void DecreaseDateByOneYear() {
		DecreaseDateByOneYear(*this);
	}
	clsDate DecreaseDateByXYears(clsDate& Date, int Year) {
		for (int i = 0; i < Year; i++)
			Date = DecreaseDateByOneYear(Date);
		return Date;
	}
	void DecreaseDateByXYears(int Year) {
		DecreaseDateByXYears(*this, Year);
	}
	clsDate DecreaseDateByXYearsFaster(clsDate& Date, int Year) {
		Date._Year -= Year;
		return Date;
	}
	void DecreaseDateByXYearsFaster(int Year) {
		DecreaseDateByXYearsFaster(Year);
	}
	clsDate DecreaseDateByOneDecade(clsDate& Date) {
		Date._Year -= 10;
		return Date;
	}
	void DecreaseDateByOneDecade() {
		DecreaseDateByOneDecade(*this);
	}
	clsDate DecreaseDateByXDecades(clsDate& Date, int Decade) {
		//int Number = NumberOfDaysInYear(Date.Year);
		for (int i = 0; i < Decade * 10; i++)
			Date = DecreaseDateByOneYear(Date);
		return Date;
	}
	void DecreaseDateByXDecades(int Decade) {
		DecreaseDateByXDecades(*this, Decade);
	}
	clsDate DecreaseDateByXDecadesFaster(clsDate& Date, int Decade) {
		Date._Year -= Decade * 10;
		return Date;
	}
	void DecreaseDateByXDecadesFaster(int Decade) {
		DecreaseDateByXDecadesFaster(*this, Decade);
	}
	clsDate DecreaseDateByOneCentury(clsDate& Date) {
		Date._Year -= 100;
		return Date;
	}
	void DecreaseDateByOneCentury() {
		DecreaseDateByOneCentury(*this);
	}
	clsDate DecreaseDateByOneMillennium(clsDate& Date) {
		Date._Year -= 1000;
		return Date;
	}
	void DecreaseDateByOneMillennium() {
		DecreaseDateByOneMillennium(*this);
	}
	static void SwapDates(clsDate& Date, clsDate& Date2) {
		clsDate temp;
		temp = Date;
		Date = Date2;
		Date2 = temp;
	}
	static int GetDifferenceInDays(clsDate Date, clsDate Date2, bool IncludeEndDay = false) {
		int Days = 0;
		short SwapDate = 1;
		if (!IsDate1BeforeDate2(Date, Date2)) {
			SwapDates(Date, Date2);
			SwapDate = -1;
		}
		while (IsDate1BeforeDate2(Date, Date2)) {
			Days++;
			Date = IncreaseDateByOneDay(Date);
		}
		return IncludeEndDay ? ++Days * SwapDate : Days * SwapDate;
	}
	int GetDifferenceInDays(clsDate Date2, bool IncludeEndDay = false) {
		return GetDifferenceInDays(*this, Date2, IncludeEndDay);
	}
	static short CalculateMyAgeInDays(clsDate DateOfBirth) {
		return GetDifferenceInDays(DateOfBirth, clsDate::GetSystemDate(), true);
	}
	static short IsEndOfWeek(clsDate Date) {
		return DayOfWeekOrder(Date) == 6;
	}
	short IsEndOfWeek() {
		return IsEndOfWeek(*this);
	}
	static bool IsWeekEnd(clsDate Date) {
		short IndexDay = DayOfWeekOrder(Date);
		return (IndexDay == 5 || IndexDay == 6);
	}
	bool IsWeekEnd() {
		return IsWeekEnd(*this);
	}
	static bool IsBusinessDay(clsDate Date) {
		return !IsWeekEnd(Date);
	}
	bool IsBusinessDay() {
		return IsBusinessDay(*this);
	}
	static short DaysUntilTheEndOfWeek(clsDate Date) {
		return 6 - DayOfWeekOrder(Date);
	}
	short DaysUntilTheEndOfWeek() {
		return DaysUntilTheEndOfWeek(*this);
	}
	static short DaysUntilTheEndOfMonth(clsDate Date) {
		clsDate EndOfMonthDate;
		EndOfMonthDate._Day = NumberOfDaysInMonth(Date._Year, Date._Month);
		EndOfMonthDate._Month = Date._Month;
		EndOfMonthDate._Year = Date._Year;
		return GetDifferenceInDays(Date, EndOfMonthDate, true);
	}
	short DaysUntilTheEndOfMonth() {
		return DaysUntilTheEndOfMonth(*this);
	}
	static short DaysUntilTheEndOfYear(clsDate Date) {
		clsDate EndOfYearDate;
		EndOfYearDate._Day = 31;
		EndOfYearDate._Month = 12;
		EndOfYearDate._Year = Date._Year;
		return GetDifferenceInDays(Date, EndOfYearDate, true);
	}
	short DaysUntilTheEndOfYear() {
		return DaysUntilTheEndOfYear(*this);
	}
	static short CalculateBusinessDays(clsDate DateFrom, clsDate DateTo) {
		short Days = 0;
		while (IsDate1BeforeDate2(DateFrom, DateTo)) {
			if (IsBusinessDay(DateFrom))
				Days++;
			DateFrom = IncreaseDateByOneDay(DateFrom);
		}
		return Days;
	}
	static short CalculateVacationDays(clsDate DateFrom, clsDate Date2To) {
		return CalculateBusinessDays(DateFrom, Date2To);
	}
	short CalculateVacationDays(clsDate Date2To) {
		return CalculateVacationDays(*this, Date2To);
	}
	static clsDate CalculateVacationReturnDate(clsDate Date, short VacationDays) {
		while (true) {
			if (IsBusinessDay(Date)) {
				Date = IncreaseDateByOneDay(Date);
				VacationDays--;
			}
			else {
				Date = IncreaseDateByOneDay(Date);
			}
			if (VacationDays == 0)
				break;
		}
		return Date;

	}
	clsDate CalculateVacationReturnDate(short VacationDays) {
		return CalculateVacationReturnDate(*this, VacationDays);
	}
	enum enDateCompare { Before = -1, Equal = 0, After = 1 };
	static enDateCompare CompareDates(clsDate Date1, clsDate Date2) {
		if (IsDate1BeforeDate2(Date1, Date2))
			return enDateCompare::Before;
		if (IsDate1EqualDate2(Date1, Date2))
			return enDateCompare::Equal;
		return enDateCompare::After;
	}
	enDateCompare CompareDates(clsDate Date2) {
		return CompareDates(*this, Date2);
	}
	static bool ValidDate(clsDate Date) {
		int DaysInMonth = NumberOfDaysInMonth(Date._Year, Date._Month);
		if (Date._Month > 12 || Date._Month < 1 || Date._Day < 1 || Date._Day > 31)
			return false;
		if (Date._Day > DaysInMonth)
			return false;
		return true;
	}
	bool ValidDate() {
		return ValidDate(*this);
	}
	static short NumberOfDaysFromTheBeginingOfTheYear(short Day, short Month, short Year) {
		short TotalDays = 0;
		for (int i = 1; i <= (Month - 1); i++) {
			TotalDays += NumberOfDaysInMonth(Day, i);
		}
		TotalDays += Day;
		return TotalDays;
	}
	static short NumberOfDaysFromTheBeginingOfTheYear(clsDate Date) {
		short TotalDays = 0;
		for (int i = 1; i <= (Date._Month - 1); i++) {
			TotalDays += NumberOfDaysInMonth(Date._Day, i);
		}
		TotalDays += Date._Day;
		return TotalDays;
	}
	short NumberOfDaysFromTheBeginingOfTheYear() {
		return NumberOfDaysFromTheBeginingOfTheYear(*this);
	}

};
