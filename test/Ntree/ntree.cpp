#include "ntree.h"
void MTree::init(MNode *root) { this->root = root; }

void MTree::putChild(MNode *node, MNode *parent) {
    parent->children.push_back(node);
    node->Parent = parent;
}

void MTree::putChildren(vector<MNode *> nodes, MNode *parent) {
    for (int i = 0; i < nodes.size(); ++i) {
        putChild(nodes[i], parent);
    }
}

void MTree::tranversal() {
    this->tranversal(this->root);
}

void MTree::tranversal(MNode *root) {
    vector<MNode *> nodes = root->children;
    for (int i = 0; i < nodes.size(); ++i) {
        if (nodes[i]->children.size() > 0)
            tranversal(nodes[i]);
        else
            cout << nodes[i]->element << ",";
    }
    cout << root->element << ",";
}

int MTree::getMaxDepth(MNode *root,vector<MNode*> nodes) {
    auto iResult = 0;

    return iResult;
}