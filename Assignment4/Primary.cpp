#include "Primary.h"
using namespace std;

Primary *Primary::newNode(std::string item) {
    Primary *temp = new Primary();
    temp->key = item;
    temp->left = NULL;
    temp->right = NULL;
    temp->secondary=NULL;
    return temp;}

Primary *Primary::deleteNode(Primary *root, std::string key) {
    if (root == NULL) {return root;}
    if (key.compare(root->key)==-1){
        root->left = deleteNode(root->left, key);}
    else if (key.compare(root->key)==1){
        root->right = deleteNode(root->right, key);}
    else {

        if (root->left == NULL) {
            Primary *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Primary *temp = root->left;
            free(root);
            return temp;
        }


        Primary *temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

Primary *Primary::find(Primary *primary, std::string name) {
    if (primary!= NULL) {
        if (primary->key.compare(name) == -1) {
            find(primary->right, name);
        } else if (primary->key.compare(name) == 1) {
            find(primary->left, name);
        } else if (primary->key.compare(name) == 0) {
            return primary;
        }
    }
}

Primary *Primary::insert(Primary *node, std::string key) {
    if (node == NULL) {return newNode(key);}
    if (key.compare(node->key)==-1)
        node->left = insert(node->left, key);
    else if(key.compare(node->key)==1)
        node->right = insert(node->right, key);
    return node;
}

Primary *Primary::minValueNode(Primary *node2) {
    Primary *temp = node2;

    while (temp && temp->left != NULL)
        temp = temp->left;

    return temp;
}
