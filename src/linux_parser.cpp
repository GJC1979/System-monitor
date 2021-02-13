#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <iomanip>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >>kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string memTotal, memFree,t;
  string line;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> t >> memTotal;
    std::getline(stream, line);
    std::istringstream linestream1(line);
    linestream1 >> t >> memFree; 
  }
  return (stof(memTotal)-stof(memFree))/stof(memTotal); 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string  total, idle;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> total >> idle;
  }
  return stol(total); 
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) { 
  string line;  
  string value;
  long utime, stime, cutime, cstime, starttime;
  long total_time, seconds, cpu_usage;
  long Hertz;
  std::ifstream filestream(kProcDirectory + to_string(pid) +kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    std::vector<std::string> values(std::istream_iterator<std::string>{linestream}, std::istream_iterator<std::string>{});
    utime = stol(values[13]); 
    stime = stol(values[14]); 
    cutime = stol(values[15]);
    cstime = stol(values[16]);
    starttime = stol(values[21]);
    Hertz = sysconf(_SC_CLK_TCK);
    total_time = utime + stime;
    total_time = total_time + cutime + cstime;
    seconds = (starttime-utime) / Hertz;
    cpu_usage = 100 * ((total_time / Hertz) / seconds);
    return cpu_usage;
  }  
  return 0; 
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
  string cpu,user,nice,system,idle, iowait, irq, softirq, steal;
  string line,t;
  vector<string> aux{};
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> t >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal;
    aux.push_back(cpu);    
    aux.push_back(user);
    aux.push_back(nice);
    aux.push_back(system);
    aux.push_back(idle);
    aux.push_back(iowait);
    aux.push_back(irq);
    aux.push_back(softirq);
    aux.push_back(steal);
  }   
  return aux; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {          
          return stoi(value);
        }
      }
    }
  } 
  return 0; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {          
          return stoi(value);
        }
      }
    }
  } 
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string line;  
  string value;
  std::ifstream filestream(kProcDirectory + to_string(pid)+kCmdlineFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    linestream >> value; 
    return (value);
  }
  return string();   
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + to_string(pid) + kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") { 
          std::stringstream stream;
          stream << std::fixed << std::setprecision(2) << stof(value)/1024;
          std::string s = stream.str();     
          return s;
        }
      }
    }
  }
  
  
  return string();
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory +to_string(pid) +kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {          
          return value;
        }
      }
    }
  }
  return string(); 
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(string Uid) { 
  string line;
  string name,pass,uid;
  std::ifstream filestream(kPasswordPath) ;
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> name >> pass >> uid) {
        if (uid == Uid) {
          return name;
        }
      }
    }
  }  
  return string();
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string line;  
  string value;
  std::ifstream filestream(kProcDirectory + to_string(pid) +kStatFilename);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::istringstream linestream(line);
    std::vector<std::string> values(std::istream_iterator<std::string>{linestream}, std::istream_iterator<std::string>{});
    return stol(values[21]);
  }
  return 0;
}