#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <map>
#include <iostream>
#include <vector>

namespace pt = boost::property_tree;

pt::ptree tree;

int main() {

    //pt::read_json("combined_eleIDSFs_2018.json", tree);
    pt::read_json("run2_reco.json", tree);

    int j =0;

    std::map<std::string, std::string> test0;
    std::map< std::string, std::map<std::string, std::string> > test1;
    std::map< std::string, std::map< std::string, std::map<std::string, std::string> > > test2;
    std::map< std::string, std::map< std::string, std::map< std::string, std::map<std::string, std::string> > > > test3;
    //std::map< std::string, std::map< std::string, std::map< std::string, std::map<std::string, double> > > > test4;
    std::map< std::string, std::map< std::string, std::map< std::string, std::map< std::string, std::map<std::string, std::string> > > > > test4;
    std::map< std::string, std::map< std::string, std::map< std::string, std::map< std::string, std::map<std::string, double> > > > > test5;


    for(auto&& v : tree) { // YEAR LOOP
        if (j>=5) { break; }
        const std::string & k_yr = v.first; 
        const pt::ptree & tree_ID = v.second; 
        std::cout  << std::endl<< std::endl << std::endl << k_yr; 
        // testing lvl 0
        test0[k_yr] = k_yr;
        std::cout << std::endl << "lvl0: TEST MAP 0:" << test0[k_yr] << std::endl; 
        if(tree_ID.empty()) {
            } else {

            for(auto&& sv : tree_ID) { // ID LOOP
                if (j>=5) { break; }
                const std::string & k_ID = sv.first; 
                const pt::ptree & tree_pt = sv.second; 
                std::cout  << std::endl<< std::endl << std::endl << k_ID; 
                // testing lvl 1
                test1[k_yr][k_ID] = k_ID;
                std::cout << std::endl << "lvl1: TEST MAP 1:" << test1[k_yr][k_ID] << std::endl; 
                if(tree_pt.empty()) {
                    } else {

                    for(auto&& ssv : tree_pt) { // PT LOOP
                        [[maybe_unused]] const std::string & k_pt = ssv.first; 
                        const pt::ptree & tree_eta = ssv.second; 
                        std::cout << std::endl << std::endl << k_pt << ": ";
                        // testing lvl 2
                        test2[k_yr][k_ID][k_pt] = k_pt;
                        std::cout << std::endl << "lvl2: TEST MAP 2: " << test2[k_yr][k_ID][k_pt] << std::endl; 
                        if(tree_eta.empty()) {
                            } else {
                            std::cout << tree_eta.data();

                            for(auto&& sssv: tree_eta) { // ETA LOOP
                                int i = 0; 
                                [[maybe_unused]] const std::string & k_eta = sssv.first; 
                                const pt::ptree & tree_val_err = sssv.second; 
                                std::cout << std::endl << k_eta  << ": ";
                                // testing lvl 3
                                test3[k_yr][k_ID][k_pt][k_eta] = k_eta;
                                std::cout << std::endl << "lvl3: TEST MAP 3: " << test3[k_yr][k_ID][k_pt][k_eta] << std::endl; 
                                j++;
                                if(tree_val_err.empty()) {
                                    if (auto tree_val_err_v = tree_val_err.get_value_optional<double>()) {
                                        std::cout << tree_val_err_v.get() << "; ";
                                        if (i == 1) { std::cout << std::endl << std::endl; }
                                        i++;
                                    }
                                }
                                else {
                                    std::cout << tree_eta.data(); 
                                    for(auto&& ssssv: tree_val_err) { // (VALUE, ERROR) LOOP
                                        int ii = 0; 
                                        [[maybe_unused]] const std::string & k_val_err = ssssv.first; 
                                        const pt::ptree & tree_pt_val_err = ssssv.second; 
                                        std::cout << k_val_err  << ": ";
                                        // testing lvl 4 : string
                                        test4[k_yr][k_ID][k_pt][k_eta][k_val_err] = k_val_err;
                                        std::cout << std::endl << "lvl4: TEST MAP 4 (string): " << test4[k_yr][k_ID][k_pt][k_eta][k_val_err] << std::endl; 
                                        j++;
                                        if(tree_pt_val_err.empty()) {
                                            if (auto tree_pt_val_err_v = tree_pt_val_err.get_value_optional<double>()) {
                                                double data = tree_pt_val_err_v.get();
                                                std::cout << data << "; ";
                                                //std::cout << tree_pt_val_err_sv.get() << "; ";
                                                // testing lvl 4 : double 
                                                test5[k_yr][k_ID][k_pt][k_eta][k_val_err] = data;
                                                std::cout << std::endl << "lvl4: TEST MAP 4 (double): " << test5[k_yr][k_ID][k_pt][k_eta][k_val_err] << std::endl; 
                                                if (ii == 1) { std::cout << std::endl << std::endl; }
                                                ii++;
                                            }
                                        }
                                        else {
                                            std::cout << tree_val_err.data(); 
                                        }
                                    }
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
