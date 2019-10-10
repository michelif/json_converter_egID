#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <map>
#include <iostream>
#include<list>
#include <vector>
using boost::property_tree::ptree;

struct Config {
    std::string name;
    std::list<std::vector<std::string>> parameters;
};

std::list<std::vector<std::string>> parse_config(std::string const& fname) {

    boost::property_tree::ptree pt;
    std::ifstream file(fname);
    boost::property_tree::read_json(file, pt);
    Config config;

    for (auto& v : pt.get_child("cutBasedElectronID-Fall17-94X-V2-veto"))
    {
        auto& node = v.second;

        config.name = node.get("pt:[10.0,20.0]", "");
        std::cout<<config.name;

        //for( auto &param : node.get_child("pt:[10.0,20.0]") )
        //{  
            //for( const auto& itr : param.second )
            //{
                 //config.parameters.push_back( {config.name,itr.second.get_value("")} );
            //}
        //}  
    }
    return config.parameters;
}


int main() {

    std::list<std::vector<std::string>> vec = parse_config("combined_eleIDSFs_2018.json");

for (auto &v : vec)
{

    for (auto const &i : v)

        std::cout<<i<<std::endl;
}
}


