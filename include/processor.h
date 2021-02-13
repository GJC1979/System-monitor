#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    float prevuser = 0, prevnice = 0, prevsystem = 0, previrq = 0, prevsoftirq = 0, prevsteal = 0, previdle = 0, previowait = 0;
};

#endif