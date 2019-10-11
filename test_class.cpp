#include <json_wrapper.h>

using namespace std;

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
