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

int j =0;

//for(auto&& v : tree.get_child("cutBasedElectronID-Fall17-94X-V2-veto")) {
for(auto&& v : tree) { // ID LOOP
    //if (j>=50) { break; }
    const std::string & key = v.first; 
    const pt::ptree & sub_tree = v.second; 
    std::cout  << std::endl<< std::endl << std::endl << key; 
    if(sub_tree.empty()) {
        } else {

        for(auto&& sv : sub_tree) { // PT LOOP
            [[maybe_unused]] const std::string & skey = sv.first; 
            const pt::ptree & sub_sub_tree = sv.second; 
            std::cout << std::endl << std::endl << skey << ": ";
            if(sub_sub_tree.empty()) {
                } else {
                std::cout << sub_sub_tree.data();

                for(auto&& ssv: sub_sub_tree) { // ETA LOOP
                    int i = 0; 
                    [[maybe_unused]] const std::string & sub_sub_key = ssv.first; 
                    const pt::ptree & sub_sub_sub_tree = ssv.second; 
                    std::cout << std::endl << sub_sub_key  << ": ";
                    j++;
                    if(sub_sub_sub_tree.empty()) {
                        if (auto sub_sub_sub_tree_v = sub_sub_sub_tree.get_value_optional<double>()) {
                            std::cout << sub_sub_sub_tree_v.get() << "; ";
                            if (i == 1) { std::cout << std::endl << std::endl; }
                            i++;
                        }
                    }
                    else {
                        std::cout << sub_sub_tree.data(); 
                        for(auto&& sssv: sub_sub_sub_tree) { // (VALUE, ERROR) LOOP
                            int ii = 0; 
                            [[maybe_unused]] const std::string & sub_sub_sub_key = sssv.first; 
                            const pt::ptree & sub_sub_sub_sub_tree = sssv.second; 
                            std::cout << sub_sub_sub_key  << ": ";
                            j++;
                            if(sub_sub_sub_sub_tree.empty()) {
                                if (auto sub_sub_sub_sub_tree_v = sub_sub_sub_sub_tree.get_value_optional<double>()) {
                                    std::cout << sub_sub_sub_sub_tree_v.get() << "; ";
                                    if (ii == 1) { std::cout << std::endl << std::endl; }
                                    ii++;
                                }
                            }
                            else {
                                std::cout << sub_sub_sub_tree.data(); 
                            }
                        }
                    }
                }
            }
        }
    }
}
std::cout << std::endl << std::endl << std::endl;
return 0;

}
