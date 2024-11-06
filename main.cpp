
#include "Aphid.h"
#include "Ant.h"
#include "Ladybug.h"
#include <iostream>
#include <list>
#include <map>
#include <array>
using namespace std;

const int DAYS_IN_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const string MONTH[] = {"Jan","Feb","march",
                        "Apr","May","Jun",
                        "Jul","Aug","Sep",
                        "Oct","Nov","Dec"};
map<string,array<float,3>> load_environment_factors();



int main(){

    int aphid_pop, ant_pop, ladybug_pop;

    map<string, array<list<int>,3>> population_results;
    map<string, array<float,3>> environment_factors;
    
    Aphid aphid(1000);
    Ant ant (600);
    Ladybug ladybug(125);

    return 0;

for (const auto& [date,populations] : populationResults) {
    std::cout << date << " - Aphid Population: " << populations[0]
              << ", Ant Population: " << populations[1]
              << ", Ladybug Population: " << populations[2] << std::endl;
}


}
