#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return Pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
  CpuUtilization_ = LinuxParser::ActiveJiffies(Pid_);
  return CpuUtilization_;
}

// TODO: Return the command that generated this process
string Process::Command() { return Command_; }

// TODO: Return this process's memory utilization
string Process::Ram() { 
  Ram_ = LinuxParser::Ram(Pid_);
  return Ram_;
}

// TODO: Return the user (name) that generated this process
string Process::User() { return User_; }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
  UpTime_ = LinuxParser::UpTime(Pid_);
  return UpTime_;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const { 

  if (this->CpuUtilization_ < a.CpuUtilization_){
    return true;
  }
  else {
    return false;
  } 
  
}