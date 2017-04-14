#ifndef DAILYREPORT_H
#define DAILYREPORT_H

#include "member.h"
#include "inventory.h"

//A sales report for any given day.
//include:
//a list of items and quantities sold on that day
//names of the members who shopped that day.
//Report the total revenue for the given day.
//number of preferred members and basic members who shopped during the given day.

class dailyReport
{
public:
    dailyReport(memberList totalMember, string date);
    string getReportForAllMem(memberList* allMember);
    string getReportForBasic(memberList* allMember);
    string getReportForPreferred(memberList* allMember);
    //string getReportForInv(memberList* allMember);
    int getTotalRevenue() const;
    int getPreferredMembers() const;
    int getBasicMembers() const;
private:
     List<string> dailyMembersID;
     inventory dailyInventory;
     int totalRevenue=0;
     int preferredMembers=0;
     int basicMembers=0;
};

#endif // DAILYREPORT_H
