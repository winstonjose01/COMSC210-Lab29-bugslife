
#ifndef ANT_H
#define ANT_H
#include <iostream>
#include <cmath>
using namespace std;


class Ant
    {
    const double MIN_POPULATION = 5;  // MInimum ants alive
    private:
        /* data */
        double P_ant_t0;    // Initial ant population or previous day population    
        double P_ant_t1;    // Current day ant population

        float ant_GR = 0.10;          // Ants growth rate
        float ant_MR_Temp = .017;     // .03 Ants sensitivity to Temperature
        float ant_MR_Precip = .01;   // .02 Ants sensitivity to Precipitation
        float ant_Topt = 72.0;       // Optimum temperature for Ants to reproduce
        float K_benefit = .15;       // Growth benefit because of positive effects between aphids on ants

    public:
        Ant(int n) {P_ant_t0 = n;}

        void set_initial_pop(int n) {P_ant_t0 = n;}       // Set initial Aphid population
        double get_initial_pop()      {return P_ant_t0;}     // Get initial Aphid population

        // Calculate the current's day population based on the environmental factors
        void set_current_pop (float T_now, float Precip_now, int P_aphid_t0 ){
            P_ant_t1 = P_ant_t0 * (1 + ant_GR - ant_MR_Temp*(abs(T_now - ant_Topt)) -  ant_MR_Precip * Precip_now);
            P_ant_t1 = P_ant_t1*(1 + K_benefit); // Symbiotic impact K
            P_ant_t1 = max(P_ant_t1, MIN_POPULATION); //Make sure minimum population is not less than 5
            }
        double get_current_pop()       {return P_ant_t1;}

    };

#endif

