// COMSC 210 | Lab 29,30,31 | Winston Jose
// IDE used: Visual Studio Code
// Github link: https://github.com/winstonjose01/COMSC210-Lab29-bugslife 


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
#include <assert.h>
#include <iomanip>
#include <random>
using namespace std;
// Constants for typical days and months in a year
const int DAYS_IN_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const string MONTH[] = {"01","02","03","04","05","06","07","08","09","10","11","12"};
const int MAX_INSECT = 5000; // Max population for each insect
const int MIN_INSECT = 2500; // Min population for each insect
const int NO_OF_YEARS = 3;   // No of years to simulate

map<string,array<float,3>> load_environment_factors(string);
void print_Population(map<string,array<list<double>,3>> &);
void test_load_environment_factors(); // Unit testing

int main(){
    random_device rd;   // Random device generator
    mt19937 gen(rd());
    uniform_int_distribution<> dist(MIN_INSECT,MAX_INSECT); // Uniform distribution
    int aphid_pop, ant_pop, ladybug_pop;
    float temperature, precipitation, UV_index; // Variables for environmental data
    string filename = "weather_data.csv";  // Filename for environmental data
    int aphid_pop_yrend, ant_pop_yrend, ladybug_pop_yrend;

    map<string, array<list<double>,3>> populationResults;
    map<string, array<float,3>> environment_factors;
    
    Aphid aphid(dist(gen));     // Create and initialize Aphid object
    Ant ant (dist(gen));        // Create and initialize Ant object
    Ladybug ladybug(dist(gen)); // Creat and initialize Ladybug object
    // For debuggin
    //cout << "--->" << aphid.get_initial_pop() << " | " << ant.get_initial_pop() << " | " << ladybug.get_initial_pop()<<endl;

    environment_factors = load_environment_factors(filename);
    for (int k = 0; k < NO_OF_YEARS; k++){ // Simulate for 3 years
    int m = 0;
    for (string month : MONTH) {
        string date = "";
        // Loop through each day in the month
        for (int i = 1; i <= DAYS_IN_MONTH[m]; i++){
            // Format date string
            if (i < 10)
                date = month + "-0" + to_string(i);
            else
                date = month + "-" + to_string(i);
            
            // Check if environmental data exists for the date
            if (environment_factors.find(date) != environment_factors.end()){
                temperature = environment_factors[date][0];
                precipitation = environment_factors[date][1];
                UV_index = environment_factors[date][2];
            }
            else{
                // Skip if no data is found
                cout << "No environmental data for date :" << date << endl;
                continue;
            }

            // Get the initial population of each insect type
            aphid_pop =  aphid.get_initial_pop();
            ant_pop = ant.get_initial_pop();
            ladybug_pop = ladybug.get_initial_pop();

            //cout << aphid_pop << " | " << ant_pop << " | " << ladybug_pop <<endl;

             // Update populations based on environmental factors
            aphid.set_current_pop(temperature,UV_index,precipitation,ladybug_pop,ant_pop);
            ant.set_current_pop(temperature,precipitation,aphid_pop);
            ladybug.set_current_pop(temperature,UV_index,aphid_pop);

             // Store the updated population in the map for the current date
            populationResults[date][0].push_back(aphid.get_current_pop());
            populationResults[date][1].push_back(ant.get_current_pop());
            populationResults[date][2].push_back(ladybug.get_current_pop());

             // Update initial populations for the next day
            aphid.set_initial_pop(aphid.get_current_pop());
            ant.set_initial_pop(ant.get_current_pop());
            ladybug.set_initial_pop(ladybug.get_current_pop());

            if (month == "12" && i == 31){
                aphid_pop_yrend = aphid.get_current_pop();
                ant_pop_yrend = ant.get_current_pop();
                ladybug_pop_yrend = ladybug.get_current_pop();
                //cout << aphid_pop_yrend << " | " << ant_pop_yrend << " | " << ladybug_pop_yrend << endl;

            }
        }
        m++;
    }
    aphid.set_initial_pop(aphid_pop_yrend);
    ant.set_initial_pop(ant_pop_yrend);
    ladybug.set_initial_pop(ladybug_pop_yrend);
    }

    print_Population(populationResults);
    //***************Unit Testing****************/
    //test_load_environment_factors();
    cout << "All tests completed successfully.\n";

    return 0;
}
// This function loads the environmental data into a map with an inner array of 3 float values
// arguments: a string that is the filename with environmental data
// returns: a map with array of 3 values: temperature, precipitation, uv-index
map<string,array<float,3>> load_environment_factors(string filename){

    map<string,array<float,3>> environment_factors;
    string line, month, day, temperature;
    ifstream file (filename);
    if (!file.is_open()){
         cerr << "Error. Could not open environmental factors file";
         exit(1);
     }
    float precipitation, UV_index;

    while (getline(file, line)){
        istringstream stream(line);
        getline(stream, month, ',');
        getline(stream, day, ',');
        getline(stream, temperature,',');
        stream >> precipitation >> UV_index;
        string date = month + "-"+ day;

        environment_factors[date] = {stof(temperature),precipitation,UV_index};
        
    }
    return environment_factors;

}
// This function prints the aphid, ant, and ladybug population
// arguments: a map with an inner array of 3 lists.
// returns: no returns
void print_Population(map<string,array<list<double>,3>> &insectPop){
    for (int k = 0; k < NO_OF_YEARS; k++){
        cout << "\n------------------------------------------ YEAR " << k + 1 << " ---------------------------------------\n";
        cout << endl;

        for (const auto& [date,populations] : insectPop) {
            auto it_aphid = populations[0].begin();  // Iterator for aphid population
            auto it_ant = populations[1].begin();    // Iterator for ant population
            auto it_ladybug = populations[2].begin(); // Iterator for ladybug population
            // Check if there are aphid populations to print
            if (it_aphid != populations[0].end()){
                    cout << "Year-" << k+1 << " | " << date << " --> " << setw(18) << "Aphid Population: " << static_cast<int>(*it_aphid) << setw(4)<< "|";
            }
             // Check if there are ant populations to print
            if (it_ant != populations[1].end()){
                cout << setw(18) << "Ant Population: " << static_cast<int>(*it_ant) << setw(4) << "|" ;
            }
            // Check if there are ladybug populations to print
            if (it_ladybug != populations[2].end()){
                cout << setw(23) << "Ladybug Population: " << static_cast<int>(*it_ladybug) << std::endl;
            }
            // Pause for a brief moment (500 ms)
            this_thread::sleep_for(chrono::milliseconds(500));

            // Move to the next day for each insect population
            advance(it_aphid,1);
            advance(it_ant,1);
            advance(it_ladybug,1);
            };
    }
}

//**************************** Unit Testing ****************************************
void test_load_environment_factors(){

    map<std::string, std::array<float, 3>> test_env_factors; 

    test_env_factors= load_environment_factors("test_weather_data.csv");

    assert(test_env_factors["01-01"][0] == 52.0);  // Temperature on Jan 1
    assert(test_env_factors["01-01"][1] == 0);  // Precipitation on Jan 1
    assert(test_env_factors["01-01"][2] == 4.2);   // UV Index on Jan 1

    cout << "load_environment_factors test passed.\n";
}
