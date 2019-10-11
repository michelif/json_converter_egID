#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <map>
#include <iostream>

namespace pt = boost::property_tree;
using namespace std;

class SF_Reader {
    map< string, map< string, map< string, map< string, map<string, double> > > > > map_sf;

    public:
    void read_json(string);
    double value (string, string, string, string);
    double error (string, string, string, string);
};

// TESTING
int main () {
    SF_Reader sf;
    sf.read_json("run2_eleIDs.json");

    cout << "2016, cutBasedElectronID-Fall17-94X-V2-loose, pt:[20.0,35.0], eta:[1.444,1.566], error: ";
    cout << sf.error ("2016", "cutBasedElectronID-Fall17-94X-V2-loose", "pt:[20.0,35.0]", "eta:[1.444,1.566]") << endl;

    cout << "2016, cutBasedElectronID-Fall17-94X-V2-loose, pt:[100.0,200.0], eta:[2.0,2.5, value:: "; 
    cout << sf.value ("2016", "cutBasedElectronID-Fall17-94X-V2-loose", "pt:[100.0,200.0]", "eta:[2.0,2.5]")   << endl;
    return 0;
}

double SF_Reader::error(string year, string ID, string pt, string eta) { 
    double error = map_sf[year][ID][pt][eta]["error"];
    return error;
}

double SF_Reader::value(string year, string ID, string pt, string eta) { 
    double value = map_sf[year][ID][pt][eta]["value"];
    return value;
}

void SF_Reader::read_json(string json_file) {

    pt::ptree tree;
    pt::read_json(json_file, tree);

    for(auto&& v : tree) { // YEAR LOOP
        const string & k_yr = v.first; 
        const pt::ptree & tree_ID = v.second; 

        for(auto&& sv : tree_ID) { // ID LOOP
            const string & k_ID = sv.first; 
            const pt::ptree & tree_pt = sv.second; 

            for(auto&& ssv : tree_pt) { // PT LOOP
                [[maybe_unused]] const string & k_pt = ssv.first; 
                const pt::ptree & tree_eta = ssv.second; 

                for(auto&& sssv: tree_eta) { // ETA LOOP
                    [[maybe_unused]] const string & k_eta = sssv.first; 
                    const pt::ptree & tree_val_err = sssv.second; 
                    for(auto&& ssssv: tree_val_err) { // (VALUE, ERROR) LOOP
                        [[maybe_unused]] const string & k_val_err = ssssv.first; 
                        const pt::ptree & tree_pt_val_err = ssssv.second; 
                        if(tree_pt_val_err.empty()) {
                            if (auto tree_pt_val_err_v = tree_pt_val_err.get_value_optional<double>()) {
                                double data = tree_pt_val_err_v.get();
                                map_sf[k_yr][k_ID][k_pt][k_eta][k_val_err] = data;
                            }
                        }
                    }
                }
            }
        }
    }
}
