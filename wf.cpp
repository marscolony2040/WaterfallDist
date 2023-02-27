#include <iostream>
#include <vector>
#include <map>
#include "irr.cpp"

double cash(double inv, std::vector<double> ca, double r)
{
    int T = ca.size();
    double total = 0;
    int i = 1;
    for(auto & v : ca){
        total += v/pow(1 + r, i);
        i += 1;
    }
    return (-inv - total)*pow(1 + r, T+1);
}

std::vector<int> cn(int n)
{
    std::vector<int> x;
    double k = -1;
    for(int i = 0; i < n; ++i){
        x.push_back(k);
        k -= 2;
    }
    return x;
}

std::vector<std::vector<double>> transpose(std::vector<std::vector<double>> x)
{
    std::vector<std::vector<double>> hold;
    std::vector<double> temp;
    for(int i = 0; i < x[0].size(); ++i){
        temp.clear();
        for(int j = 0; j < x.size(); ++j){
            temp.push_back(x[j][i]);
        }
        hold.push_back(temp);
    }
    return hold;
}

std::vector<std::vector<double>> setting(std::vector<double> cs, int herd)
{
    std::vector<std::vector<double>> data;
    std::vector<double> temp;
    int x = herd*2;
    for(int i = 0; i <= x; ++i){
        temp.clear();
        if(i == 0){
            for(auto & t : cs){
                temp.push_back(t);
            }
        } else {
            for(auto & t : cs){
                temp.push_back(0.0);
            }
        }
        data.push_back(temp);
    }
    return data;
}

std::vector<int> find_hurdle(std::vector<double> h, std::vector<double> IR)
{
    std::vector<int> res;
    for(auto & s : h){
        for(int i = 0; i < IR.size(); ++i){
            if(s < IR[i]){
                res.push_back(i+1);
                break;
            }
        }
    }
    return res;
}

double irr(std::vector<double> cf)
{
    return IRR(cf);
}

int main()
{
    std::vector<double> cf = {-150, 20, 30, 80, 40, 50, 60, 70, 80, 90, 100};
    std::vector<double> hurdles = {0.01, 0.05, 0.10, 0.15, 0.24};
    std::vector<double> _IRR;

    std::vector<std::vector<double>> frame = transpose(setting(cf, hurdles.size()));

    for(int i = 2; i <= cf.size(); ++i){
        _IRR.push_back(irr({cf.begin(), cf.begin() + i}));
    }

  
    std::vector<int> hurdle_find = find_hurdle(hurdles, _IRR);
    
    int old_f = -1;
    int hf = 0;
    int hi = 0;

    std::vector<double> cash_flow;

    for(auto & f : hurdle_find){
        //std::cout << cf[f] << "\t" << _IRR[f-1] << std::endl;
        cash_flow.clear();
        for(int g = 1; g < f; ++g){
            //frame[g][hf+1] = frame[g][hf];
            cash_flow.push_back(frame[g][0]);
        }
        if(old_f != f){
            frame[f][hf+1] = cash(frame[0][0], cash_flow, hurdles[hi]);
        } else {
            double totalz = 0;
            for(auto & jj : cn(hi+1)){
                totalz += frame[f][hf+jj];
                //frame[f][hf+1] = cash(frame[0][0], cash_flow, hurdles[hi]) - frame[f][hf-1];
            }
            frame[f][hf+1] = cash(frame[0][0], cash_flow, hurdles[hi]) - totalz;
        }
        for(int q = f; q < frame.size(); ++q){
            frame[q][hf+2] = frame[q][hf] - frame[q][hf+1];
        }
        
        

        hf += 2;    
        hi += 1;
        old_f = f;
    }

    std::cout << std::endl;
    std::cout << "Waterfall Distribution" << std::endl;
    std::cout << std::endl;
    for(auto & t : frame){
        for(auto & u : t){
            std::cout << u << "\t";
        }
        std::cout << std::endl;
    }
    

    return 0;
}