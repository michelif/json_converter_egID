#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <map>
#include <iostream>
#include <vector>

namespace pt = boost::property_tree;

pt::ptree tree;

int main() {

    pt::read_json("combined_eleIDSFs_2018.json", tree);
    //pt::read_json("fullrun2.json", tree);

    int j =0;

    std::map<std::string, std::string> test0;
    std::map< std::string, std::map<std::string, std::string> > test1;
    std::map< std::string, std::map< std::string, std::map<std::string, std::string> > > test2;
    std::map< std::string, std::map< std::string, std::map< std::string, std::map<std::string, std::string> > > > test3;
    std::map< std::string, std::map< std::string, std::map< std::string, std::map<std::string, double> > > > test4;


    // DON"T FORGET TO MAKE THE YEAR LOOP!
    for(auto&& v : tree) { // ID LOOP
        if (j>=5) { break; }
        const std::string & key = v.first; 
        const pt::ptree & sub_tree = v.second; 
        std::cout  << std::endl<< std::endl << std::endl << key; 
        // testing lvl 0
        test0[key] = key;
        std::cout << std::endl << "lvl0: TEST MAP 0:" << test0[key] << std::endl; 
        if(sub_tree.empty()) {
            } else {

            for(auto&& sv : sub_tree) { // PT LOOP
                [[maybe_unused]] const std::string & sub_key = sv.first; 
                const pt::ptree & sub_sub_tree = sv.second; 
                std::cout << std::endl << std::endl << sub_key << ": ";
                // testing lvl 1
                test1[key][sub_key] = sub_key;
                std::cout << std::endl << "lvl1: TEST MAP 1: " << test1[key][sub_key] << std::endl; 
                if(sub_sub_tree.empty()) {
                    } else {
                    std::cout << sub_sub_tree.data();

                    for(auto&& ssv: sub_sub_tree) { // ETA LOOP
                        int i = 0; 
                        [[maybe_unused]] const std::string & sub_sub_key = ssv.first; 
                        const pt::ptree & sub_sub_sub_tree = ssv.second; 
                        std::cout << std::endl << sub_sub_key  << ": ";
                        // testing lvl 2
                        test2[key][sub_key][sub_sub_key] = sub_sub_key;
                        std::cout << std::endl << "lvl2: TEST MAP 2: " << test2[key][sub_key][sub_sub_key] << std::endl; 
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
                                // testing lvl 3 : string
                                test3[key][sub_key][sub_sub_key][sub_sub_sub_key] = sub_sub_sub_key;
                                std::cout << std::endl << "lvl2: TEST MAP 3 (string): " << test3[key][sub_key][sub_sub_key][sub_sub_sub_key] << std::endl; 
                                j++;
                                if(sub_sub_sub_sub_tree.empty()) {
                                    if (auto sub_sub_sub_sub_tree_v = sub_sub_sub_sub_tree.get_value_optional<double>()) {
                                        double data = sub_sub_sub_sub_tree_v.get();
                                        std::cout << data << "; ";
                                        //std::cout << sub_sub_sub_sub_tree_v.get() << "; ";
                                        // testing lvl 3 : double 
                                        test4[key][sub_key][sub_sub_key][sub_sub_sub_key] = data;
                                        std::cout << std::endl << "lvl2: TEST MAP 3 (double): " << test4[key][sub_key][sub_sub_key][sub_sub_sub_key] << std::endl; 
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
