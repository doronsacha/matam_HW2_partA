
#include "examDetails.h"

#include <iostream>

#include <string>

#include <cmath>

#define FIRST_MONTH 1
#define LAST_MONTH 12
#define FIRST_DAY_IN_MONTH 1
#define LAST_DAY_IN_MONTH 30

//Helper statics functions
/**
 * function that determines whether a course is validated or not
 * @param course_number: the course number we are checking
 */
static void isAValidCourseNumber (int course_number);

/**
 * function that determines whether a month is validated or not
 * @param month_exam:the month number we are checking
 */
static void isAValidExamMonth (int month_exam);

/**
 * function that determines whether a day is validated or not
 * @param day_exam :the day number we are checking
 */
static void isAValidDayExam ( int day_exam);

/**
 * function that determines whether an hour is validated or not
 * @param exam_hour :the hour we are checking
 */
static void isAValidExamHour (double exam_hour);

/**
 * function that determines whether a duration of an exam is validated or not
 * @param exam_time :the exam duration we are checking
 */
static void isAValidExamTime(int exam_time);

/**
 * function which returns the difference between 2 dates
 * @param first_month: the month of the first date
 * @param first_day: the day of the first date
 * @param second_month: the month of the second date
 * @param second_day: the day of the second date
 * @return the differences of days between the two dates
 */
static int dayDifferences(int first_month,int first_day,int second_month,int second_day);

/**
 * this function return the hour part of an exam time
 * @param exam_hour : the exam time receiveid like 9.5 or 10;
 * @return the hour part of the time received
 */
static int returnExamHour (double exam_hour);

/**
 * this function return the minutes part of an exam time
 * @param exam_hour :  the exam time receiveid like 9.5 or 10;
 * @return the minutes part of the time received
 */
static double returnExamMinutes (double exam_hour);

/**
 * convert the hour time to string of hour for example 9->"9"
 * @param hour the hour that we want to print
 * @return the hour that we want to print but in string
 */
static string forPrintTheHour(double hour);

/**
 * convert the minutes time to string of minutes for example 9.5->"9:30"
 * @param minutes the minutes that we want to convert
 * @return the minutes that we want to print but in string
 */
static string forPrintTheMinutes(double minutes);

/**
 * constructor without parameters
 */
ExamDetails::ExamDetails()
{
    course_number=0;
    exam_month=0;
    exam_day=0;
    exam_hour=0;
    exam_time=0;
    zoom_link=" ";
}

ExamDetails::ExamDetails(const int new_course_number, const int new_exam_month, const int new_exam_day, const double new_exam_hour,
                         const int new_exam_time, string new_zoom_link): course_number(new_course_number), exam_month(new_exam_month),
                                                                         exam_day(new_exam_day), exam_hour(new_exam_hour), exam_time(new_exam_time), zoom_link(new_zoom_link)
{
    isAValidCourseNumber(new_course_number);
    isAValidExamMonth(new_exam_month);
    isAValidDayExam(new_exam_day);
    isAValidExamHour(new_exam_hour);
    isAValidExamTime(new_exam_time);
}

string ExamDetails:: getLink() const
{
    return this->zoom_link;
}

void ExamDetails:: setLink (const string& new_link)
{
    this->zoom_link=new_link;
}

int ExamDetails:: operator -(const ExamDetails &exam_to_compare) const
{
    return dayDifferences(this->exam_month,this->exam_day,exam_to_compare.exam_month,exam_to_compare.exam_day);
}

bool ExamDetails:: operator < (const ExamDetails& new_exam) const
{
    if(this->exam_month<new_exam.exam_month)
    {
        return true;
    }
    if(this->exam_month==new_exam.exam_month && this->exam_day<new_exam.exam_day)
    {
        return true;
    }
    if(this->exam_month==new_exam.exam_month && this->exam_day==new_exam.exam_day && this->exam_hour<new_exam.exam_hour)
    {
        return true;
    }
    return false;
}

std:: ostream& operator<<(std::ostream& os, const ExamDetails& exam_detail)
{
    int exam_hour=returnExamHour(exam_detail.exam_hour);
    int exam_minutes=(int)returnExamMinutes(exam_detail.exam_hour);
    string exam_t=forPrintTheHour(exam_hour);
    string exam_r=forPrintTheMinutes(exam_minutes);
    return os<<"Course Number: " << exam_detail.course_number<<"\nTime: " \
    << exam_detail.exam_day <<"."<<exam_detail.exam_month<<" at "<<exam_t<<":"<<exam_r<<"\nDuration: "<<exam_detail.exam_time<<":00"<<"\nZoom Link:"<<" "<<exam_detail.zoom_link<<std::endl;
}


static void isAValidCourseNumber (int course_number)
{
    if(course_number<0)
    {
        throw ExamDetails::InvalidArgsException();
    }
}

static void isAValidExamMonth (int month_exam)
{
    if(FIRST_MONTH>month_exam || month_exam>LAST_MONTH)
    {
        throw ExamDetails::InvalidDateException();
    }

}

static void isAValidDayExam (int day_exam)
{
    if (FIRST_DAY_IN_MONTH>day_exam || day_exam>LAST_DAY_IN_MONTH)
    {
        throw ExamDetails::InvalidDateException();
    }
}

static void isAValidExamHour (double exam_hour)
{
    double hour_to_test=2*exam_hour;

    if(floor(hour_to_test)!=ceil(hour_to_test))
    {
        throw ExamDetails::InvalidArgsException();
    }
}

static void isAValidExamTime(int exam_time)
{
    if(exam_time<0)
    {
        throw ExamDetails::InvalidTimeException();
    }
}

static int returnExamHour (double exam_hour)
{
    int integer_part=static_cast<int>(exam_hour);
    return integer_part;
}



static double returnExamMinutes (double exam_hour)
{
    double decimal_part=exam_hour-returnExamHour(exam_hour);
    double minutes=decimal_part*60;
    return minutes;
}

static string forPrintTheMinutes(double minutes)
{
    if(minutes==30)
    {
        return "30";
    }
    return "00";
}

static string forPrintTheHour(double hour)
{
    return std::to_string((int)hour);
}

static int dayDifferences(const int first_month,const int first_day,const int second_month,const int second_day)
{
    int month_difference=(first_month-second_month);
    int day_difference=(first_day-second_day);
    return (LAST_DAY_IN_MONTH*month_difference)+ day_difference;
}