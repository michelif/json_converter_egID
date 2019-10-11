#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <map>
#include <iostream>

namespace pt = boost::property_tree;
using namespace std;

class SF_Reader {
    map< string, map< string, map< string, map< string, map<string, double> > > > > MAP_SF;

    public:
    void test ();
    void read_json(string);
    double value (string, string, string, string);
    double error (string, string, string, string);
    //double get_SF(string, string, string, string); //make pair out of this? (value, error) ?
};

int main () {
    SF_Reader sf;
    sf.read_json("run2_reco.json");
    //sf.test ();
    sf.error ("2016", "reco_sf", "pt:[20.0,45.0]", "eta:[1.444,1.566]");
    sf.value ("2016", "reco_sf", "pt:[20.0,45.0]", "eta:[1.444,1.566]");
    return 0;
}

void SF_Reader::test () {
    cout << "test main:" << MAP_SF["2016"]["reco_sf"]["pt:[20.0,45.0]"]["eta:[1.444,1.566]"]["value"] << endl;
}

double SF_Reader::error(int year, string ID, string eta, string pt) { 
    cout << "test main: error:" << year, ID, eta, pt << MAP_SF[year][ID][eta][pt]["error"] << endl;
    return 0.0;
}

double SF_Reader::value(int year, string ID, string eta, string pt) { 
    cout << "test main: value: " << year, ID, eta, pt << MAP_SF[year][ID][eta][pt]["value"] << endl;
    return 0.0;
}

void SF_Reader::read_json(string json_file) {

    pt::ptree tree;
    pt::read_json(json_file, tree);

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
    MAP_SF = map_sf; 
}
