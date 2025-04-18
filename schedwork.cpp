#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


bool scheduleHelper(
    AvailabilityMatrix& avail,
    const size_t dailyNeed,
    vector<size_t>& currShifts,
    const size_t maxShifts,
    DailySchedule& sched,
    int start
);


bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();

    vector<unsigned int> currRow;
    sched.push_back(currRow);
    vector<size_t> currShifts;
    for (size_t i = 0; i < avail[0].size(); i++)
    {
        currShifts.push_back(0);
    }
    AvailabilityMatrix availEditable = avail;
    return scheduleHelper(availEditable, dailyNeed, currShifts, maxShifts, sched, 0);
}

bool scheduleHelper(
    AvailabilityMatrix& avail,
    const size_t dailyNeed,
    vector<size_t>& currShifts,
    const size_t maxShifts,
    DailySchedule& sched,
    int start
)
{
    if (sched.back().size() == dailyNeed)
    {
        if (sched.size() == avail.size())
            return true;
        vector<unsigned int> currRow;
        sched.push_back(currRow);
        start = 0;
    }

    for (size_t i = start; i < avail[0].size(); i++)
    {
        if (avail[sched.size()-1][i] == false || currShifts[i] == maxShifts)
            continue;

        sched[sched.size()-1].push_back(i);
        avail[sched.size()-1][i] = false;
        currShifts[i]++;
        if (scheduleHelper(avail, dailyNeed, currShifts, maxShifts, sched, i+1))
        {
            return true;
        }
        else
        {
            sched[sched.size()-1].pop_back();
            avail[sched.size()-1][i] = true;
            currShifts[i]--;
        }
    }
    if (sched[sched.size()-1].size() == 0)
        sched.pop_back();
    return false;
}

