#include "iostream"
#include "fstream"

using namespace std;

class SecondaryRed
{
public:
    SecondaryRed *left, *right;
    string data;
    bool isRed;
    int price;
    static SecondaryRed* createNode(string data, bool color, int price);
    static SecondaryRed* rotateLeft(SecondaryRed* Node);
    static SecondaryRed* rotateRight(SecondaryRed* Node);
    static int isRedF(SecondaryRed *myNode);
    static void swapColors(SecondaryRed *node1, SecondaryRed *node2);
    static void colorChange(SecondaryRed* Node);
    static SecondaryRed* MoveRedtoLeft(SecondaryRed* Node);
    static SecondaryRed* MoveRedtoRight(SecondaryRed* Node);
    static SecondaryRed* FindMin(SecondaryRed* Node);
    static SecondaryRed* CheckAndRotate(SecondaryRed *Node);
    static SecondaryRed *DeleteMin(SecondaryRed *Node);
    static SecondaryRed *Insert(SecondaryRed *myNode, string data,int price);
    static SecondaryRed* DeleteAndRotate(SecondaryRed* Node , string data);
    static SecondaryRed* Delete(SecondaryRed* Node, string key);
    static int max_Height(SecondaryRed *root);
    static void printLevel(SecondaryRed *root, int level_no, ofstream &writer);
    static void printTree(SecondaryRed *root, ofstream &writer);
};

