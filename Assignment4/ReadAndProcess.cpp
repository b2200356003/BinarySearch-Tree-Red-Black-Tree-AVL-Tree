#include <iostream>
#include "fstream"
#include <queue>
#include "ReadAndProcess.h"
using namespace std;

Primary *ReadAndProcess::Action(string filename, Primary *primary,string outputFile,string outputFile2) {
    ofstream writer;
    ofstream writer2;
    writer.open(outputFile);
    writer2.open(outputFile2);
    Primary* tempP;
    Secondary* tempS;
    SecondaryRed* tempRed;
    ifstream inFile(filename);
    string line;
    string temp;
    string lineList[10];


    while (getline(inFile, line)){

        int count = 0;
        line+="\t";
        for (int i = 0; i < line.length(); i++) {
            if (string(1, line[i]) != "\t") {
                temp += line[i];
            }
            else {
                lineList[count]=temp;
                temp="";
                count++;
            }
        }

        //Read the line and run proper function


        if (lineList[0]=="insert"){

            primary= Primary::insert(primary,lineList[1]);
            tempP = primary;
            while (tempP->key!=lineList[1]){
                if (tempP->key.compare(lineList[1]) == -1){
                    tempP = tempP->right;
                }
                else if (tempP->key.compare(lineList[1]) == 1) {
                    tempP = tempP->left;
                }
            }
            tempP->secondary= Secondary::insertNode(tempP->secondary,lineList[2], stoi(lineList[3]));
            tempP->secondaryRed= SecondaryRed::Insert(tempP->secondaryRed,lineList[2],stoi(lineList[3]));
        }

        if (lineList[0]=="updateData"){
            tempP = primary;
            while (tempP->key!=lineList[1]){
                if (tempP->key.compare(lineList[1]) == -1){
                    tempP = tempP->right;
                }
                else if (tempP->key.compare(lineList[1]) == 1) {
                    tempP = tempP->left;
                }
            }

            tempS = tempP->secondary;
            while (tempS->key!=lineList[2]){
                if (tempS->key.compare(lineList[2]) == -1){
                    tempS = tempS->right;
                }
                else if (tempS->key.compare(lineList[2]) == 1) {
                    tempS = tempS->left;
                }
            }

            tempRed = tempP->secondaryRed;
            while (tempRed->data!=lineList[2]){
                if (tempRed->data.compare(lineList[2]) == -1){
                    tempRed = tempRed->right;
                }
                else if (tempRed->data.compare(lineList[2]) == 1) {
                    tempRed = tempRed->left;
                }
            }

            tempS->price= stoi(lineList[3]);
            tempRed->price = stoi(lineList[3]);
        }


        if (lineList[0]=="remove"){
            tempP = primary;
            while (tempP->key!=lineList[1]){
                if (tempP->key.compare(lineList[1]) == -1){
                    tempP = tempP->right;
                }
                else if (tempP->key.compare(lineList[1]) == 1) {
                    tempP = tempP->left;
                }
            }

            tempP->secondary= Secondary::deleteNode(tempP->secondary,lineList[2]);
            tempP->secondaryRed= SecondaryRed::Delete(tempP->secondaryRed,lineList[2]);
        }



        if (lineList[0]=="printAllItemsInCategory"){
            writer << "command:" << lineList[0] << "\t" << lineList[1] << endl;
            writer << "{" << endl;
            writer2 << "command:" << lineList[0] << "\t" << lineList[1] << endl;
            writer2 << "{" << endl;

            tempP = primary;
            while (tempP->key!=lineList[1]){
                if (tempP->key.compare(lineList[1]) == -1){
                    tempP = tempP->right;
                }
                else if (tempP->key.compare(lineList[1]) == 1) {
                    tempP = tempP->left;
                }
            }

            writer << "'" << lineList[1] << "'" << ":" << endl << "\t";
            writer2 << "'" << lineList[1] << "'" << ":" << endl << "\t";

            Secondary::printTree(tempP->secondary,writer);
            SecondaryRed::printTree(tempP->secondaryRed,writer2);

            if (tempP->secondary==NULL){writer << "{}";}
            if (tempP->secondaryRed==NULL){writer2 << "{}";}
            writer << "}";
            writer << endl;
            writer2 << "}";
            writer2 << endl;
        }


        if (lineList[0]=="printAllItems"){
            writer << "command:" << lineList[0] << endl;
            writer << "{" << endl;
            writer2 << "command:" << lineList[0] << endl;
            writer2 << "{" << endl;
            queue<Primary*> PrimaryQueue;

            if (primary!=NULL) {
                PrimaryQueue.push(primary);
            }
            while (PrimaryQueue.size()!=0){
                tempP=PrimaryQueue.front();
                PrimaryQueue.pop();
                if (tempP->left!=NULL) {
                    PrimaryQueue.push(tempP->left);
                }
                if (tempP->right!=NULL) {
                    PrimaryQueue.push(tempP->right);
                }
                writer << "'" << tempP->key << "'" << ":" << endl;
                writer << "\t" ;

                writer2 << "'" << tempP->key << "'" << ":" << endl;
                writer2 << "\t" ;

                Secondary::printTree(tempP->secondary,writer);
                SecondaryRed::printTree(tempP->secondaryRed,writer2);

                if (tempP->secondary==NULL){
                    writer << "{}";
                }

                if (tempP->secondaryRed==NULL){
                    writer2 << "{}";
                }
                writer<< endl;
                writer2<< endl;
            }
            writer << "}";
            writer << endl;
            writer2 << "}";
            writer2 << endl;
        }


        if (lineList[0]=="printItem" || lineList[0]=="find"){
            writer << "command:" << lineList[0] << "\t" << lineList[1] << "\t" << lineList[2] <<endl;
            writer << "{" << endl;
            writer2 << "command:" << lineList[0] << "\t" << lineList[1] << "\t" << lineList[2] <<endl;
            writer2 << "{" << endl;

            tempP = primary;
            while (tempP->key!=lineList[1]){
                if (tempP->key.compare(lineList[1]) == -1){
                    tempP = tempP->right;
                }
                else if (tempP->key.compare(lineList[1]) == 1) {
                    tempP = tempP->left;
                }
                if (tempP==NULL){
                    break;
                }
            }

            if (tempP!=NULL) {
                tempS = tempP->secondary;
                tempRed = tempP->secondaryRed;
                while (tempS->key != lineList[2]) {
                    if (tempS->key.compare(lineList[2]) == -1) {
                        tempS = tempS->right;
                    } else if (tempS->key.compare(lineList[2]) == 1) {
                        tempS = tempS->left;
                    }
                    if (tempS == NULL) {
                        break;
                    }
                }
                while (tempRed->data != lineList[2]) {
                    if (tempRed->data.compare(lineList[2]) == -1) {
                        tempRed = tempRed->right;
                    } else if (tempRed->data.compare(lineList[2]) == 1) {
                        tempRed = tempRed->left;
                    }
                    if (tempRed == NULL) {
                        break;
                    }
                }

                if (tempS != NULL) {
                    writer << "'" << tempP->key << "'" << ":" << endl;
                    writer << "\t";
                    writer << "'" << tempS->key << "'" << ":" << "'" << tempS->price << "'" << endl;
                }

                if (tempRed != NULL) {
                    writer2 << "'" << tempP->key << "'" << ":" << endl;
                    writer2 << "\t";
                    writer2 << "'" << tempRed->data << "'" << ":" << "'" << tempRed->price << "'" << endl;
                }


            }

            writer << "}";
            writer << endl;
            writer2 << "}";
            writer2 << endl;
        }

    }

    inFile.close();
    return primary;
}