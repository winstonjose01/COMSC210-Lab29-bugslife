// Aphid.h

#ifndef APHID_H
#define APHID_H
#include <iostream>
#include <cmath>
using namespace std;

class Aphid
{
    const double MIN_POPULATION = 1;
    private:
        /* data */
        double P_aphid_t0;
        double P_aphid_t1;

        float aphid_GR = 0.08;          // Aphid growth rate
        float aphid_MR_Temp = .01;      // .03 Aphid sensitivity to Temperature
        float aphid_MR_UV = .005;        // .02 Aphid sensitivity to UV
        float aphid_Topt = 72.0;        // Optimum temperature for Aphids to reproduce
        float aphid_Pred_LB = .01;        // .03 Ladybug predation factore on aphids
        float K_benefit = .05;         // Growth benefit because of positive between ants and aphids

    public:
        Aphid(int n) {P_aphid_t0 = n;}

        void set_initial_pop(int n) {P_aphid_t0 = n;}       // Set initial Aphid population
        double get_initial_pop()      {return P_aphid_t0;}     // Get initial Aphid population

        void set_current_pop (float T_now, float UV_now,float Precip_now, int P_ladybug_t0, int P_ant_t0 ){
            P_aphid_t1 = P_aphid_t0 * ((1 + aphid_GR) - aphid_MR_UV*UV_now - aphid_MR_Temp*(abs(T_now - aphid_Topt)) - aphid_Pred_LB * P_ladybug_t0/P_aphid_t0);
            P_aphid_t1 = P_aphid_t1 * (1 + K_benefit);
            P_aphid_t1 = max(P_aphid_t1, MIN_POPULATION);
            

        }
        double get_current_pop()       {return P_aphid_t1;}

    };

#endif
