#include "Secondary.h"

#include <iostream>
#include <fstream>

using namespace std;

Secondary *Secondary::newNode(std::string key, int price) {
    Secondary *node = new Secondary();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    node->price = price;
    return (node);
}

int Secondary::Height(Secondary *N) {
        if (N == NULL)
            return 0;
        return N->height;
}

Secondary *Secondary::rightRotate(Secondary *y) {
    Secondary *x = y->left;
    Secondary *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(Secondary::Height(y->left),
                    Secondary::Height(y->right)) +
                1;
    x->height = max(Secondary::Height(x->left),
                    Secondary::Height(x->right)) +
                1;
    return x;
}

Secondary *Secondary::leftRotate(Secondary *x) {
    Secondary *y = x->right;
    Secondary *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(Secondary::Height(x->left),
                    Secondary::Height(x->right)) +
                1;
    y->height = max(Secondary::Height(y->left),
                    Secondary::Height(y->right)) +
                1;
    return y;
}


int Secondary::BalanceFac(Secondary *N) {
    if (N == NULL)
        return 0;
    return Secondary::Height(N->left) -
            Secondary::Height(N->right);
}

static int max(int a, int b) {
    if (a>b){
        return a;
    }
    else {
        return b;
    }
}

Secondary *Secondary::insertNode(Secondary *node, std::string key, int price) {
    if (node == NULL)
        return (Secondary::newNode(key,price));
    if (key.compare(node->key)==-1)
        node->left = insertNode(node->left, key,price);
    else if (key.compare(node->key)==1)
        node->right = insertNode(node->right, key,price);
    else
        return node;

    node->height = 1 + max(Secondary::Height(node->left),
                           Secondary::Height(node->right));
    int balanceFactor = BalanceFac(node);
    if (balanceFactor > 1) {
        if (key.compare(node->left->key)==-1) {
            return rightRotate(node);
        } else if (key.compare(node->left->key)==1) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    if (balanceFactor < -1) {
        if (key.compare(node->right->key)==1) {
            return leftRotate(node);
        } else if (key.compare(node->right->key)==-1) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

Secondary *Secondary::MinNode(Secondary *node) {
    Secondary *temp = node;
    while (temp->left != NULL)
        temp = temp->left;
    return temp;
}



Secondary *Secondary::deleteNode(Secondary *root, std::string key) {
    if (root == NULL)
        return root;
    if (key.compare(root->key)==-1)
        root->left = deleteNode(root->left, key);
    else if (key.compare(root->key)==1)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == NULL) ||
            (root->right == NULL)) {
            Secondary *temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;
            free(temp);
        } else {
            Secondary *temp = MinNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right,
                                     temp->key);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + max(Secondary::Height(root->left),
                           Secondary::Height(root->right));
    int balanceFactor = BalanceFac(root);
    if (balanceFactor > 1) {
        if (BalanceFac(root->left) >= 0) {
            return rightRotate(root);
        } else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (balanceFactor < -1) {
        if (BalanceFac(root->right) <= 0) {
            return leftRotate(root);
        } else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

int Secondary::max_Height(Secondary *root) {
    if (!root)
        return 0;
    else {
        int left_height = max_Height(root->left);
        int right_height = max_Height(root->right);
        if (left_height >= right_height)
            return left_height + 1;
        else
            return right_height + 1;
    }
}

void Secondary::printLevel(Secondary *root, int level_no, ofstream &writer) {
    if (!root)
        return;
    if (level_no == 0) {
        writer << "'" << root->key << "'" << ":" << "'" <<root->price << "'" << ",";
    }
    else {
        printLevel(root->left, level_no - 1,writer);
        printLevel(root->right, level_no - 1,writer);
    }

}

void Secondary::printTree(Secondary *root, ofstream &writer) {
    if (!root)
        return;
    int height = max_Height(root);
    for (int i=0; i<height; i++) {
        printLevel(root, i, writer);
        writer<< "\n" ;
        writer<< "\t" ;
    }
    writer<< "\n" ;
}