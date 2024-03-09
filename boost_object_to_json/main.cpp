#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree;

// Define a simple tree node structure
struct TreeNode {
    int value;
    std::vector<TreeNode> children;
};

// Serialize a tree of TreeNode objects into JSON
pt::ptree serializeTree(const TreeNode& node) {
    pt::ptree tree;
    tree.put("value", node.value);

    // Recursively serialize children
    pt::ptree children;
    for (const auto& child : node.children) {
        children.push_back(std::make_pair("", serializeTree(child)));
    }
    tree.add_child("children", children);

    return tree;
}

int main() {
    // Create a sample tree
    TreeNode root{1};
    root.children.push_back(TreeNode{3});
    root.children.push_back(TreeNode{5});
    root.children[1].children.push_back(TreeNode{4});

    // Serialize the tree into JSON
    pt::ptree jsonTree = serializeTree(root);

    // Write JSON to output stream
    pt::write_json(std::cout, jsonTree);

    return 0;
    }
