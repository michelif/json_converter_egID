#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/foreach.hpp>
#include <map>
#include <iostream>
#include<list>
#include <vector>

namespace pt = boost::property_tree;

pt::ptree tree;

int main() {

pt::read_json("combined_eleIDSFs_2018.json", tree);

for(auto&& v : tree.get_child("cutBasedElectronID-Fall17-94X-V2-veto")) {
    const std::string & key = v.first; 
    const pt::ptree & subtree = v.second; 
    std::cout << std::endl << std::endl << key; 
    if(subtree.empty()) {
        } else {

        for(auto&& sv : subtree) {
            [[maybe_unused]] const std::string & skey = sv.first; 
            const pt::ptree & subsubtree = sv.second; 
            std::cout << std::endl << skey << ": ";
            if(subsubtree.empty()) {
                } else {
                std::cout << subsubtree.data();

                for(auto&& ssv: subsubtree) {
                    int i = 0; 
                    [[maybe_unused]] const std::string & subsubkey = ssv.first; 
                    const pt::ptree & subsubsubtree = ssv.second; 
                    std::cout << subsubkey  << ": ";
                    if(subsubsubtree.empty()) {
                        if (auto subsubsubtree_v = subsubsubtree.get_value_optional<double>()) {
                            std::cout << subsubsubtree_v.get() << "; ";
                            if (i == 1) { std::cout << std::endl << std::endl; }
                            i++;
                        }
                    }
                    else {
                        std::cout << subsubtree.data(); 
                    }
                }
            }
        }
    }
}
std::cout << std::endl << std::endl << std::endl;
return 0;

}
