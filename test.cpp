#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

boost::property_tree::ptree pt, sub_pt;
std::string json_str, key, sub_key;
std::stringstream ss;
int value = 0, bus_num = 0;

json_str = "{\"arduino_1\": {\"bus_1\": 17425,\"bus_2\": 1025,\"bus_3\": 0,\"bus_4\": 0,\"bus_5\": 0,\"bus_6\": 0,\"bus_7\": 0,\"bus_8\": 0}}";


ss << json_str; // put string into stringstream
boost::property_tree::read_json(ss, pt);    // put stringstream into property tree
for (boost::property_tree::ptree::iterator iter = pt.begin(); iter != pt.end(); iter++)
{
    //get data
    key = boost::lexical_cast <std::string>(iter->first.data());
    sub_pt = iter->second;
    
    // iterate over subtree
    for (boost::property_tree::ptree::iterator sub_iter = sub_pt.begin(); sub_iter != sub_pt.end(); sub_iter++)
    {
        // get data
        sub_key = boost::lexical_cast <std::string>(sub_iter->first.data());
        value = boost::lexical_cast <int>(sub_iter->second.data());
    }
}
