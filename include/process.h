#ifndef PROCESS_H
#define PROCESS_H

#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
 public:
  Process(int Pid,std::string User,std::string Command,float CpuUtilization,std::string Ram,long int UpTime):Pid_(Pid),User_(User),Command_(Command),CpuUtilization_(CpuUtilization),Ram_(Ram),UpTime_(UpTime){};  
  int Pid();                               // TODO: See src/process.cpp
  std::string User();                      // TODO: See src/process.cpp
  std::string Command();                   // TODO: See src/process.cpp
  float CpuUtilization();                  // TODO: See src/process.cpp
  std::string Ram();                       // TODO: See src/process.cpp
  long int UpTime();                       // TODO: See src/process.cpp
  bool operator<(Process const& a) const;  // TODO: See src/process.cpp

  // TODO: Declare any necessary private members
 private:
  int Pid_;
  std::string User_;
  std::string Command_;
  float CpuUtilization_;
  std::string Ram_;
  long int UpTime_; 
};

#endif