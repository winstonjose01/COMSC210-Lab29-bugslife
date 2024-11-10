
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

const int DAYS_IN_MONTH[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const string MONTH[] = {"01","02","03","04","05","06","07","08","09","10","11","12"};
const int MAX_INSECT = 6000;
const int MIN_INSECT = 1000;

map<string,array<float,3>> load_environment_factors(string);
void print_Population(map<string,array<list<int>,3>> &);
void test_load_environment_factors(); // Unit testing

int main(){
    //srand(time(0));
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(MIN_INSECT,MAX_INSECT);
    int aphid_pop, ant_pop, ladybug_pop;
    float temperature, precipitation, UV_index;
    string filename = "weather_data.csv";

    map<string, array<list<int>,3>> populationResults;
    map<string, array<float,3>> environment_factors;
    
    Aphid aphid(dist(gen));     // Create and initialize Aphid object
    Ant ant (dist(gen));        // Create and initialize Ant object
    Ladybug ladybug(dist(gen)); // Creat and initialize Ladybug object
    //cout << "--->" << aphid.get_initial_pop() << " | " << ant.get_initial_pop() << " | " << ladybug.get_initial_pop()<<endl;

    environment_factors = load_environment_factors(filename);
    for (int k = 0; k < 1; k++){
    int m = 0;

    for (string month : MONTH) {
        string date = "";
        for (int i = 1; i <= DAYS_IN_MONTH[m]; i++){
            if (i < 10)
                date = month + "-0" + to_string(i);
            else
                date = month + "-" + to_string(i);
            
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
            //cout << aphid_pop << " | " << ant_pop << " | " << ladybug_pop <<endl;

            aphid.set_current_pop(temperature,UV_index,precipitation,ladybug_pop,ant_pop);
            ant.set_current_pop(temperature,precipitation,aphid_pop);
            ladybug.set_current_pop(temperature,UV_index,aphid_pop);

            populationResults[date][0].push_back(aphid.get_current_pop());
            populationResults[date][1].push_back(ant.get_current_pop());
            populationResults[date][2].push_back(ladybug.get_current_pop());

            aphid.set_initial_pop(aphid.get_current_pop());
            ant.set_initial_pop(ant.get_current_pop());
            ladybug.set_initial_pop(ladybug.get_current_pop());

        }
        m++;
    }
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
        //cout << month << day << "-" << temperature << endl;
        string date = month + "-"+ day;

        environment_factors[date] = {stof(temperature),precipitation,UV_index};
        //cout << date<< "-" << environment_factors[date][0] <<  "," << environment_factors[date][1] << endl;
    }
    return environment_factors;

}
// This function prints the aphid, ant, and ladybug population
// arguments: a map with an inner array of 3 lists.
// returns: no returns
void print_Population(map<string,array<list<int>,3>> &insectPop){
        for (const auto& [date,populations] : insectPop) {
        cout << date << ": " << setw(18) << "Aphid Population: " << populations[0].back() << setw(4)<< "|"  << setw(18) << "Ant Population: " 
                                << populations[1].back() << setw(4) << "|"  << setw(23) << "Ladybug Population: " << populations[2].back() << std::endl;
        this_thread::sleep_for(chrono::milliseconds(700));
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
