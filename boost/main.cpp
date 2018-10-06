#include <iostream>
#include <property_tree/ptree.hpp>
#include <property_tree/json_parser.hpp>

int main(){
    boost::property_tree::ptree tree;

    tree.put("test_name","test_value");
    boost::property_tree::write_json("./output.json", tree);

    return 0;
}
