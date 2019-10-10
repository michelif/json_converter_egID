#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/json_parser.hpp>

//http://techgate.fr/boost-property-tree/


// Short alias for this namespace
//using namespace std;
//namespace pt = boost::property_tree;

int main () {

//Create a root
//pt::ptree root;

//Load the json file in this ptree
//pt::read_json("combined_eleIDSFs_2018.json", root);

////float msg = root.get<float>("cutBasedElectronID-Fall17-94X-V2-veto.pt:[10.0,20.0].eta:[-2.5,-2.0].value");

////std::cout << msg << std::endl;

////A vector to allow storing our animals
//std::vector< std::pair<std::string, std::string> > IDs;

//// Iterator over all animals 
//for (pt::ptree::value_type &ID : root.get_child("cutBasedElectronID-Fall17-94X-V2-veto"))
//{
    //// Animal is a std::pair of a string and a child

    //// Get the label of the node
    //std::string pt = ID.first;
    //std::cout << pt << std::endl;
    //pt::ptree::value_type &PT = ID.get_child("pt:[10.0,20.0]");
    ////auto eta = ID.second.get_value<eta>();
    //// Get the content of the node
    ////auto eta = ID.second.get_value;//.data();
    ////pt::ptree::value_type &eta = ID.get_child("eta:[-2.5,-2.0]");
    ////std::string eee = eta.first;
    ////auto eta = ID.second;
    ////std::string pt_str = "cutBasedElectronID-Fall17-94X-V2-veto." + pt;
    ////std::cout << pt_str << std::endl;
    ////std::string eta = root.get<std::string>(pt_str);
    ////std::string eee = eta.first;
    ////std::cout << eee << std::endl;
    ////std::cout << eta << std::endl;
    ////animals.push_back(std::make_pair(name, color));
//}

boost::property_tree::ptree pt, sub_pt;
std::string json_str, key, sub_key;
boost::property_tree::read_json("combined_eleIDSFs_2018.json", pt);

for (boost::property_tree::ptree::iterator iter = pt.begin(); iter != pt.end(); iter++)
{
    //get data
    key = boost::lexical_cast <std::string>(iter->first.data());
    std::cout << key << std::endl;
    sub_pt = iter->second;

    // iterate over subtree
    for (boost::property_tree::ptree::iterator sub_iter = sub_pt.begin(); sub_iter != sub_pt.end(); sub_iter++)
    {
        // get data
        sub_key = boost::lexical_cast <std::string>(sub_iter->first.data());
        value = boost::lexical_cast <int>(sub_iter->second.data());
    }
}

std::cout << "success" << std::endl;
return 0;
}

//class EleSF_JSONReader {
    //json_format [> define json_format <] 
 
    //public:
        //void set_json 
        //bin_info getBinInfo [> define bin_info <]

//};

//EleSF_JSONReader :: init (string file_name , string sf_name) {
//}
