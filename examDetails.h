#ifndef SORTEDLISTQUIMARCHE_EXAMDETAILS_H
#define SORTEDLISTQUIMARCHE_EXAMDETAILS_H

#ifndef TEMPEXAM_EXAMDETAILS_H
#define TEMPEXAM_EXAMDETAILS_H
#define SPACE " "
#include <iostream>

namespace
{
    using std::string;
    using std::ostream;
}

class ExamDetails {
    int course_number;
    int exam_month;
    int exam_day;
    double exam_hour;
    int exam_time;
    string zoom_link;


public:

    ExamDetails();

    ExamDetails( const int course_number, const int exam_month, const int exam_day, const double exam_hour, const int exam_time, string zoom_link="");

    ~ExamDetails()=default;

    ExamDetails (const ExamDetails& exam_detail_to_copy)=default;

    ExamDetails& operator=(const ExamDetails&)=default;

    string getLink() const;

    void setLink (const string& new_link);

    int operator - (const ExamDetails& exam_to_compare) const;

    bool operator < (const ExamDetails& new_exam) const;

    friend ostream& operator<<(ostream& os, const ExamDetails& exam_detail);

    class InvalidDateException{};

    class InvalidTimeException{};

    class InvalidArgsException{};

    static ExamDetails makeMatamExam()
    {
        ExamDetails matam_exam(234124, 7, 28, 13, 3, "https://tinyurl.com/59hzps6m");
        return matam_exam;
    }


};


#endif //TEMPEXAM_EXAMDETAILS_H
#endif //SORTEDLISTQUIMARCHE_EXAMDETAILS_H