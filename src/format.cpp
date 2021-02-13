#include <string>
#include <sstream>
#include <iomanip>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function

std::string ZeroPadNumber(int num) //copied from http://www.cplusplus.com/forum/general/15952/
{
    std::ostringstream ss;
    ss << std::setw( 2 ) << std::setfill( '0' ) << num;
    return ss.str();
}

string Format::ElapsedTime(long seconds) { 
  int hours, minutes;
  string time;
  minutes = seconds / 60;
  hours = minutes / 60;
  time = ZeroPadNumber(hours)+":"+ ZeroPadNumber(int(minutes%60))+":"+ ZeroPadNumber(int(seconds%60));
  return time;
}