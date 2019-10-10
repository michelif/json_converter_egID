#include <json.hpp>
#include <iostream>

// for convenience
using json = nlohmann::json;

int main() {

 std::ifstream ifs("combined_eleIDSFs_2018.json");
 json j = json::parse(ifs);

 j["cutBasedElectronID-Fall17-94X-V2-veto"]

 return 0;
}


