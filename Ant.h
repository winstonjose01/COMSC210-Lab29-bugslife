
#ifndef ANT_H
#define ANT_H
#include <iostream>
#include <cmath>
using namespace std;


class Ant
{
private:
    /* data */
    int P_ant_t0;
    int P_ant_t1;

    float ant_GR = 0.1;          // Ants growth rate
    float ant_MR_Temp = .03;     // Ants sensitivity to Temperature
    float ant_MR_Precip = .02;   // Ants sensitivity to Precipitation
    float ant_Topt = 25.0;       // Optimum temperature for Ants to reproduce
    float K_benefit = .05;       // Growth benefit because of positive effects between aphids on ants

public:
    Ant(int n) {P_ant_t0 = n;}

    void set_initial_pop(int n) {P_ant_t0 = n;}       // Set initial Aphid population
    int get_initial_pop()      {return P_ant_t0;}     // Get initial Aphid population

    void set_current_pop (float T_now, float Precip_now, int P_aphid_t0 ){
        P_ant_t1 = P_ant_t0 * (1 + ant_GR - ant_MR_Temp*(abs(T_now - ant_Topt)) -  ant_MR_Precip * Precip_now);
        P_ant_t1 = (1 + K_benefit * min(1,P_aphid_t0 / P_ant_t0));
    }
    int get_current_pop()       {return P_ant_t1;}

};

#endif

