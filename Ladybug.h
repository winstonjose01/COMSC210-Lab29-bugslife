
#ifndef LADYBUG_H
#define LADYBUG_H
#include <iostream>
#include <cmath>
using namespace std;

class Ladybug
{
    const double MIN_POPULATION = 5;
    private:
        /* data */
        double P_ladybug_t0;
        double P_ladybug_t1;

        float ladybug_GR = 0.05;          // Ants growth rate
        float ladybug_MR_Temp = .01;     // Ants sensitivity to Temperature
        float ladybug_MR_UV = .01;   // Ants sensitivity to Precipitation
        float ladybug_Topt = 75.0;       // Optimum temperature for Ants to reproduce
        float ladybug_Pred_aphid = .01;       // Ladybug predation by on aphids

    public:
        Ladybug(int n) {P_ladybug_t0 = n;}

        void set_initial_pop(int n) {P_ladybug_t0 = n;}       // Set initial Aphid population
        double get_initial_pop()      {return P_ladybug_t0;}     // Get initial Aphid population

                // Calculate the current's day population based on the environmental factors
        void set_current_pop (float T_now, float UV_now, int P_aphid_t0 ){

            P_ladybug_t1 = P_ladybug_t0 * (1 + ladybug_GR + ladybug_Pred_aphid * P_aphid_t0 / P_ladybug_t0 - ladybug_MR_UV * UV_now - ladybug_MR_Temp * (abs(T_now - ladybug_Topt)));
            P_ladybug_t1 = max(P_ladybug_t1, MIN_POPULATION); //Make sure minimum population is not less than 5
        }
        double get_current_pop()       {return P_ladybug_t1;}

};

#endif