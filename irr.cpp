#include <iostream>
#include <math.h>
#include <vector>
#include <map>


double IRR(std::vector<double> cf)
{
  double r0 = 0.01;
  double r1 = 0.11;

  auto fx = [](std::vector<double> cf, double r) {
    int dt = 0;
    double npv = 0;
    for(auto & t : cf) {
      npv += t / pow(1 + r, dt);
      dt += 1;
    }
    return npv;
  };

  auto df = [](std::vector<double> cf, double r) {
    int dt = 0;
    double npv = 0;
    for(auto & t : cf){
      npv += -dt * t / pow(1 + r, dt+1);
      dt += 1;
    }
    return npv;
  };

  while(true){
    r1 = r0 - 0.1*fx(cf, r0) / df(cf, r0);
    if(abs(r1 - r0) < pow(10,-3)){
      break;
    }
    r0 = r1;
  }
  return r1;
}


