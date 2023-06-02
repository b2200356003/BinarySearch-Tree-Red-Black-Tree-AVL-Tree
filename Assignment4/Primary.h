#include <iostream>
#include "Secondary.h"
#include "SecondaryRed.h"
using namespace std;

class Primary {
public:
    string key;
    Primary *left;
    Primary *right;
    Secondary *secondary;
    SecondaryRed *secondaryRed;
    static Primary *newNode(string item);
    static Primary *insert(Primary *node, string key);
    static Primary *minValueNode(Primary *node2);
    static Primary *deleteNode(Primary *root, string key);
    static Primary* find(Primary *primary,string name);
};


