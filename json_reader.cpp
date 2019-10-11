#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <map>
#include <iostream>

namespace pt = boost::property_tree;
using namespace std;

//https://stackoverflow.com/questions/4479017/storing-std-map-in-map
int main() {

    pt::ptree tree;
    pt::read_json("run2_reco.json", tree);

    int j =0;

    map< string, map< string, map< string, map< string, map<string, double> > > > > map_sf;


    for(auto&& v : tree) { // YEAR LOOP
        if (j>=5) { break; } // early stop; for debugging
        const string & k_yr = v.first; 
        const pt::ptree & tree_ID = v.second; 
        cout  << endl<< endl << endl << k_yr; 

        for(auto&& sv : tree_ID) { // ID LOOP
            if (j>=5) { break; }
            const string & k_ID = sv.first; 
            const pt::ptree & tree_pt = sv.second; 
            cout  << endl<< endl << endl << k_ID; 

            for(auto&& ssv : tree_pt) { // PT LOOP
                [[maybe_unused]] const string & k_pt = ssv.first; 
                const pt::ptree & tree_eta = ssv.second; 
                cout << endl << endl << k_pt << ": ";
                cout << tree_eta.data();

                for(auto&& sssv: tree_eta) { // ETA LOOP
                    int i = 0; 
                    [[maybe_unused]] const string & k_eta = sssv.first; 
                    const pt::ptree & tree_val_err = sssv.second; 
                    cout << endl << k_eta  << ": ";
                    j++;
                    if(tree_val_err.empty()) {
                        if (auto tree_val_err_v = tree_val_err.get_value_optional<double>()) {
                            cout << tree_val_err_v.get() << "; ";
                            if (i == 1) { cout << endl << endl; }
                            i++;
                        }
                    }
                    else {
                        cout << tree_eta.data(); 

                        for(auto&& ssssv: tree_val_err) { // (VALUE, ERROR) LOOP
                            int ii = 0; 
                            [[maybe_unused]] const string & k_val_err = ssssv.first; 
                            const pt::ptree & tree_pt_val_err = ssssv.second; 
                            cout << k_val_err  << ": ";
                            j++;
                            if(tree_pt_val_err.empty()) {
                                if (auto tree_pt_val_err_v = tree_pt_val_err.get_value_optional<double>()) {
                                    double data = tree_pt_val_err_v.get();
                                    cout << data << "; ";
                                    map_sf[k_yr][k_ID][k_pt][k_eta][k_val_err] = data;
                                    cout << endl << "lvl4: TEST MAP 4 (double): " << map_sf[k_yr][k_ID][k_pt][k_eta][k_val_err] << endl; 
                                    if (ii == 1) { cout << endl << endl; }
                                    ii++;
                                }
                            }
                            else {
                                cout << tree_val_err.data(); 
                            }
                        }
                    }
                }
            }
        }
    }
    cout << endl << endl << endl;
    return 0;
}
