#include "SecondaryRed.h"

SecondaryRed *SecondaryRed::createNode(std::string data, bool color,int price)
{
    SecondaryRed *myNode = new SecondaryRed();
    myNode -> left = NULL;
    myNode -> right = NULL;
    myNode -> data = data;
    myNode -> isRed = true;
    myNode->price = price;
    return myNode;
}

SecondaryRed *SecondaryRed::rotateLeft(SecondaryRed *Node)
{
    SecondaryRed *temp = Node -> right;
    SecondaryRed *tempLeft = temp -> left;
    Node -> right = tempLeft;
    temp -> left = Node;


    return temp;
}

SecondaryRed* SecondaryRed::rotateRight(SecondaryRed* Node)
{
    SecondaryRed *temp = Node -> left;
    SecondaryRed *tempRight =  temp -> right;
    Node -> left = tempRight;
    temp -> right = Node;


    return temp;
}

int SecondaryRed::isRedF(SecondaryRed *myNode)
{
    if (myNode == NULL)
        return 0;

    return (myNode -> isRed == true);
}

void SecondaryRed::swapColors(SecondaryRed *node1, SecondaryRed *node2)
{
    bool temp = node1 -> isRed;
    node1 -> isRed = node2 -> isRed;
    node2 -> isRed = temp;
}

void SecondaryRed::colorChange(SecondaryRed* Node){

    Node->isRed = !Node->isRed;

    if ( Node->left != NULL ) {
        Node->left->isRed = !Node->left->isRed;
    }
    if (Node->right != NULL) {
        Node->right->isRed = !Node->right->isRed;
    }

}

SecondaryRed* SecondaryRed::MoveRedtoLeft(SecondaryRed* Node){
    SecondaryRed::colorChange(Node);
    if ( (Node->right!= NULL) && SecondaryRed::isRedF(Node->right->left))
    {
        Node->right = SecondaryRed::rotateRight(Node->right);
        Node = SecondaryRed::rotateLeft(Node);
        colorChange(Node);
    }
    return Node;

}

SecondaryRed* SecondaryRed::MoveRedtoRight(SecondaryRed* Node){
    SecondaryRed::colorChange(Node);
    if ( (Node->left!= NULL) && SecondaryRed::isRedF(Node->left->left))
    {
        Node = SecondaryRed::rotateRight(Node);
        SecondaryRed::colorChange(Node);
    }
    return Node;
}


 SecondaryRed* SecondaryRed::FindMin(SecondaryRed* Node){
    while (Node->left != NULL) {
        Node = Node->left;
    }
    return Node;
}

 SecondaryRed* SecondaryRed::CheckAndRotate(SecondaryRed *Node) {
    if (SecondaryRed::isRedF(Node->right)) {
        Node = SecondaryRed::rotateLeft(Node);
    }
    if (SecondaryRed::isRedF(Node->left) && SecondaryRed::isRedF(Node->left->left)) {
        Node = SecondaryRed::rotateRight(Node);
    }

    if (SecondaryRed::isRedF(Node->left) && SecondaryRed::isRedF(Node->right)) {
        SecondaryRed::colorChange(Node);
    }

    return Node;
}

 SecondaryRed *SecondaryRed::DeleteMin(SecondaryRed *Node) {
    if (NULL == Node->left) {
        free(Node);
        return NULL;
    }
    if ((false == SecondaryRed::isRedF(Node->left)) && (false == SecondaryRed::isRedF(Node->left->left))) {
        Node = SecondaryRed::MoveRedtoLeft(Node);
    }
    Node->left = DeleteMin(Node->left);

    return CheckAndRotate(Node);
}

SecondaryRed *SecondaryRed::Insert(SecondaryRed *myNode, string data,int price) {
    if (myNode == NULL)
        return SecondaryRed::createNode(data, false,price);

    if (data.compare(myNode->data)==-1)
        myNode->left = Insert(myNode->left, data,price);

    else if (data.compare(myNode->data)==1)
        myNode->right = Insert(myNode->right, data,price);

    else
        return myNode;

    if (SecondaryRed::isRedF(myNode->right) && !SecondaryRed::isRedF(myNode->left)) {

        myNode = SecondaryRed::rotateLeft(myNode);

        SecondaryRed::swapColors(myNode, myNode->left);
    }

    if (SecondaryRed::isRedF(myNode->left) &&
            SecondaryRed::isRedF(myNode->left->left)) {

        myNode = SecondaryRed::rotateRight(myNode);
        SecondaryRed::swapColors(myNode, myNode->right);
    }

    if (SecondaryRed::isRedF(myNode->left) && SecondaryRed::isRedF(myNode->right)) {

        myNode->isRed = !myNode->isRed;

        myNode->left->isRed = false;
        myNode->right->isRed = false;
    }
    return myNode;
}

SecondaryRed* SecondaryRed::DeleteAndRotate(SecondaryRed* Node , string data){
    if (data.compare(Node->data)==-1) {
        if (NULL != Node->left) {
            if ((false == SecondaryRed::isRedF(Node->left)) && (false == SecondaryRed::isRedF(Node->left->left)))
            {
                Node = SecondaryRed::MoveRedtoLeft(Node);
            }
            Node->left = DeleteAndRotate(Node->left, data);
        }
    }
    else{
        if (SecondaryRed::isRedF(Node->left)) {
            Node = SecondaryRed::rotateRight(Node);
        }

        if ((data == Node->data) && (NULL == Node->right))
        {
            free(Node);
            return NULL;
        }

        if (NULL != Node->right) {
            if ((false == SecondaryRed::isRedF(Node->right)) && (false == SecondaryRed::isRedF(Node->right->left)))
            {
                Node = MoveRedtoRight(Node);
            }
            if (data == Node->data) {
                Node->data = FindMin(Node->right)->data;
                Node->right = DeleteMin(Node->right);
            }
            else {
                Node->right = DeleteAndRotate(Node->right, data);
            }
        }
    }

    return CheckAndRotate(Node);
}


SecondaryRed* SecondaryRed::Delete(SecondaryRed* Node,string key)
{
    if (NULL != Node) {

        Node = SecondaryRed::DeleteAndRotate(Node, key);

        if (NULL != Node) {
            Node->isRed = false;
        }
    }
    return Node;
}

int SecondaryRed::max_Height(SecondaryRed *root) {
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

void SecondaryRed::printLevel(SecondaryRed *root, int level_no, ofstream &writer) {
    if (!root)
        return;
    if (level_no == 0) {
        writer << "'" << root->data << "'" << ":" << "'" << root->price << "'" << ",";
    }
    else {
        printLevel(root->left, level_no - 1,writer);
        printLevel(root->right, level_no - 1,writer);
    }

}

void SecondaryRed::printTree(SecondaryRed *root, ofstream &writer) {
    if (!root)
        return;
    int height = max_Height(root);
    for (int i=0; i<height; i++) {
        printLevel(root, i, writer);
        writer << "\n" ;
        writer << "\t" ;
    }
    writer << "\n" ;
}
