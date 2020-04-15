//
//  tree.h
//  SearchTree
//
//  Created by Mostafa Osman on 3/3/20.
//  Copyright © 2020 Mostafa Osman. All rights reserved.
//

#ifndef TREE_H
#define TREE_H

using namespace std;

class tree
{
public:
    tree(int);
    // setters
    void setRight(tree* inRight);
    void setLeft(tree* inLeft);
    void setParent(tree* inParent);
    void setRoot(tree* inRoot);
    void setData(int inData);
    void setColor(bool color); // True is red and false is black
    void toggle();
    
    //getters
    tree* getRight();
    tree* getLeft();
    tree* getParent();
    tree* getRoot();
    int getData();
    bool getColor();
    // all tree pointers
    tree* parent;
    tree* left;
    tree* right;
    tree* root;
    int data;
    bool color;
};
#endif
