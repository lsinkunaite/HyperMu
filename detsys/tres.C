// I/O
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <fstream>
#include <numeric>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;


void tres(double pxx, double pex){

   double p_signal = 0.00016;
   double p_diff = 0.0014;
   double p_decay = 0.008;
   double r_mu = 500;
   double r_event = 100;
   double r_bg_bgo = 7000;
   double uptime = 0.7;
   double t_window = 0.0000002;
   double tsec = 3600;
   double sigmas = 4;
 
   double r_signal; // Signal rate
   double r_bg_diff; // Background rate :: diffusion
   double r_bg_decay; // Background rate :: decay
   double r_bg_unco; // Background rate :: uncorrelated
   double r_bg_tot; // Background rate :: total
   double res_time; // Resonance time needed for 4 sigmas
 
   
   r_signal = p_signal * r_mu * pxx * uptime * tsec;
   r_bg_diff = p_diff * r_mu * pxx * uptime * tsec;
   r_bg_decay = p_decay * r_mu * pex * uptime * tsec;
   r_bg_unco = r_bg_bgo * t_window * r_event * uptime * tsec;
   r_bg_tot = r_bg_diff + r_bg_diff + r_bg_unco;
   res_time = sigmas * sigmas * r_bg_tot / r_signal / r_signal;
 
   std::cout << "t_res = " << res_time << ", t_total = " << res_time/0.6 << std::endl;
}

int main() {
   double par1 = 0.7;
   double par2 = 0.11;
   tres(par1, par2);
   return 0;
}
