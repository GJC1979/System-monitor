#include <string>
#include <vector>
#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() {
    float user, nice, system, idle, iowait, irq, softirq, steal;
    float PrevIdle, Idle, PrevNonIdle, NonIdle, PrevTotal, Total, totald, idled, CPU_Percentage;
    std::vector<std::string> cpu_values{};
    cpu_values = LinuxParser::CpuUtilization();
    user = stof(cpu_values[0]);
    nice = stof(cpu_values[1]);
    system = stof(cpu_values[2]);
    idle = stof(cpu_values[3]);
    iowait = stof(cpu_values[4]);
    irq = stof(cpu_values[5]);
    softirq = stof(cpu_values[6]);
    steal = stof(cpu_values[7]); 
        
    PrevIdle = previdle + previowait;
    Idle = idle + iowait;

    PrevNonIdle = prevuser + prevnice + prevsystem + previrq + prevsoftirq + prevsteal;
    NonIdle = user + nice + system + irq + softirq + steal;

    PrevTotal = PrevIdle + PrevNonIdle;
    Total = Idle + NonIdle;

    //differentiate: actual value minus the previous one
    totald = Total - PrevTotal;
    idled = Idle - PrevIdle;

    CPU_Percentage = (totald - idled)/totald;
    prevuser = user;
    prevnice = nice;
    prevsystem = system;
    previdle = idle;    
    previowait = iowait;
    previrq = irq;
    prevsoftirq = softirq;
    prevsteal = steal;
return CPU_Percentage; }