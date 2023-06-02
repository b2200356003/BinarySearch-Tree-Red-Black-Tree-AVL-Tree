using namespace std;
#include "string"

class Secondary {
public:
    string key;
    Secondary *left;
    Secondary *right;
    int height;
    int price;
    static int Height(Secondary *N);
    static Secondary *newNode(string key,int price);
    static Secondary *rightRotate(Secondary *y);
    static Secondary *leftRotate(Secondary *x);
    static int BalanceFac(Secondary *N);
    static Secondary *insertNode(Secondary *node, string key,int price);
    static Secondary *MinNode(Secondary *node);
    static Secondary *deleteNode(Secondary *root, string key);
    static int max_Height(Secondary* root);
    static void printLevel(Secondary* root, int level_no,ofstream& writer);
    static void printTree(Secondary* root,ofstream& writer);
};