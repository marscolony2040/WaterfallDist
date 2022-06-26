#include <iostream>
#include <math.h>
#include <vector>


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
    r1 = r0 - fx(cf, r0) / df(cf, r0);
    if(abs(r1 - r0) < pow(10,-3)){
      break;
    }
    r0 = r1;
  }
  return r1;
}



int main()
{
  double irr = IRR({-200.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0});
  std::cout << irr << std::endl;

  return 0;
}
