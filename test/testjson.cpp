#include <iostream>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main(){
    json j;
    j["happy"] = true;



    j.emplace("weather", 1); 
    cout << j["weather"]<<endl;
    return 0;
}
