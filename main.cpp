
#include "Aphid.h"
#include "Ant.h"
#include "Ladybug.h"
#include <iostream>
#include <fstream>
#include <list>
#include <map>
#include <array>
#include <string>
#include <sstream>
#include<thread>
using namespace std;

const int DAYS_IN_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const string MONTH[] = {"01","02","03",
                        "04","05","06",
                        "07","08","09",
                        "10","11","12"};
map<string,array<float,3>> load_environment_factors(string);

int main(){

    int aphid_pop, ant_pop, ladybug_pop;
    float temperature, precipitation, UV_index;
    string filename = "weather_data.csv";

    map<string, array<list<int>,3>> populationResults;
    map<string, array<float,3>> environment_factors;
    
    Aphid aphid(8000);
    Ant ant (1900);
    Ladybug ladybug(1125);

    int m = 0;
    for (string month : MONTH) {
        for (int i = 1; i <= DAYS_IN_MONTH[m]; i++){
            string date = month + "-" + to_string(i);
            //cout << date << " - " << m << " - " << i << endl;
            environment_factors = load_environment_factors(filename);

            //cout << date<< "-" << environment_factors[date][0] <<  "," << environment_factors[date][1] << endl;
            
            if (environment_factors.find(date) != environment_factors.end()){
                temperature = environment_factors[date][0];
                precipitation = environment_factors[date][1];
                UV_index = environment_factors[date][2];
                //cout << date << "|" << temperature << endl;
            }
            else{
                cout << "No environmental data for date :" << date << endl;
                continue;
            }

            aphid_pop =  aphid.get_initial_pop();
            ant_pop = ant.get_initial_pop();
            ladybug_pop = ladybug.get_initial_pop();
            //cout << aphid_pop << " - " << ant_pop << " - " << ladybug_pop <<endl;

            aphid.set_current_pop(temperature,UV_index,precipitation,ladybug_pop,ant_pop);
            ant.set_current_pop(temperature,precipitation,aphid_pop);
            ladybug.set_current_pop(temperature,UV_index,aphid_pop);

            populationResults[date][0].push_back(aphid.get_current_pop());
            populationResults[date][1].push_back(ant.get_current_pop());
            populationResults[date][2].push_back(aphid.get_current_pop());

            aphid.set_initial_pop(aphid.get_current_pop());
            aphid.set_initial_pop(aphid.get_current_pop());
            aphid.set_initial_pop(aphid.get_current_pop());

        }
        m++;
    }


    for (const auto& [date,populations] : populationResults) {
        cout << date << " - Aphid Population: " << populations[0].back() << ", Ant Population: " << populations[1].back() << ", Ladybug Population: " << populations[2].back() << std::endl;
        this_thread::sleep_for(chrono::seconds(1));
    }


    return 0;
}

map<string,array<float,3>> load_environment_factors(string filename){

    map<string,array<float,3>> environment_factors;
    string line, month, day, temperature;
    ifstream file (filename);
    float precipitation, UV_index;


    while (getline(file, line)){
        istringstream stream(line);
        getline(stream, month, ',');
        getline(stream, day, ',');
        getline(stream, temperature,',');
        stream >> precipitation >> UV_index;
        //cout << month << day << "-" << temperature << endl;
        string date = month + "-"+ day;

        environment_factors[date] = {stof(temperature),precipitation,UV_index};
        //cout << date<< "-" << environment_factors[date][0] <<  "," << environment_factors[date][1] << endl;

    }
    return environment_factors;

}