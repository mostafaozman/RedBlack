//
//  main.cpp
//  SearchTree
//
//  Created by Mostafa Osman on 3/3/20.
//  Copyright © 2020 Mostafa Osman. All rights reserved.

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <iomanip>
#include <fstream>
#include "tree.h"

using namespace std;
void buildTree(int value, tree* current);
void visualPrint(tree* root, int space);
void print(tree* root);
tree* getGrandParent(tree* current);
tree* getUncle(tree* current);
bool parentRed(tree* root, tree* current);
bool rotateParent(tree* root, tree* current);
bool rotateFull(tree* root, tree* current);
void rotateFull2(tree* root, tree* current);
tree* search(tree* current, int value);
tree* findNext(tree* current);
void del(tree* current, int value);
void delMethod(tree* current, int value);
tree* getSibling(tree* current);
void case4(tree* current);
void case6(tree* current);

int heap[100];
int size;
int counter = 0;
int position;
int num;
int ten = 10;
bool yes = true;

tree* head = NULL;
tree* current2 = NULL;

int main()
{
    int type;
    char input[1000];
    char fileName[10];
    cout << "How would you like to input? Direct input (1) or file input (2)" << endl;
    cin >> type;
    cin.clear();
    cin.ignore(10000, '\n');
    
    
    int i = 0;
    if (type == 1) // Compares to see which type of input
    {
        // direct input
        
        cout << "Please input numbers sperated by spaces." << endl;
        cin.get(input, 1000);
        cin.clear();
        cin.ignore(10000, '\n');
        cout << input << endl;
        
    }
    
    if (type == 2)
    {
        // file input, credit to Omar Nassar
        cout << endl << "What is the name of the file?" << endl << ">> ";
        cin.get(fileName, 20);
        cin.clear();
        cin.ignore(1000000, '\n');
        //        ifstream inputFile;
        //        inputFile.open(fileName);
        //        while (inputFile>>input)
        //        {
        //            cout<<input<<" ";
        //        };
        streampos size;
        ifstream file(fileName, ios::in | ios::binary | ios::ate);
        if (file.is_open())
        {
            size = file.tellg();
            file.seekg(0, ios::beg);
            file.read(input, size);
            file.close();
        }
        cout << input;
    }
    
    // parsing algorithim
    char my_number [100];
    while (input[i] != '\0')
    {
        // If the input has a space then do nothing or "skip" it
        if (input[i] == ' ')
        {
            
        }
        else
        {
            int z = 0;
            for (int j = counter; j <= sizeof(input); j++)
            {
                if(input[j] == ' ')
                {
                    // my_number[j]='\0';
                    counter++;
                    z++;
                    break;
                }
                else
                {
                    
                    my_number[z] = input[j];
                    counter++;
                    z++;
                    //heap[i] = atoi(input[j]);
                }
                
            }
            //cout<<"my number is  "<<my_number<<"\n";
            if(atoi(my_number) == 0)
            {
                
            }
            else
            {
                heap[position] = atoi(my_number);
                position++;
                for (int z = 0; z < sizeof(my_number); z++)
                {
                    my_number[z] = '\0';
                }
            }
        }
        i++;
    }
    
    //printheap();
    for (int i = 0; i < position; i++)
    {//iterate through pasred array and add to tree
        buildTree(heap[i], head);
    }
    
    print(head);
    //3 cout << findGreatest(head) -> getData() << "\n";
    // cout << search(head, 4)-> getData();
    
    while (yes == true)
    {
        cout << "\nWhat would you like to  do? Add (1), Print (2), Search (3), Delete (4), or Quit (5)"<< endl;
        cin >> type;
        cin.clear();
        cin.ignore(10000, '\n');
        
        if (type == 1)
        {
            cout << "What number would you like to add?" << endl;
            cin >> num;
            cin.clear();
            cin.ignore(10000, '\n');
            buildTree(num, head);
        }
        
        if (type == 2)
        {
            print(head);
        }
        
        if (type == 3)
        {
            int s;
            cout << "\nWhat number would you like to search for?" << endl;
            cin >> s;
            cin.clear();
            cin.ignore(10000, '\n');
            if(search(head, s) != NULL)
            {
                cout << "\nFound!" << endl;
            }
            else
            {
                cout << "\nNot Found :(" << endl;
            }
        }
        
        if (type == 4)
        {
            int d;
            cout << "\nWhat number would you like to delete?" << endl;
            cin >> d;
            cin.clear();
            cin.ignore(10000, '\n');
            tree* n = search(head, d);
            delMethod(n, d);
            print(head);
        }
        
        if (type == 5)
        {
            break;
        }
        
        else
        {
            
        }
        
    }
    
}


void visualPrint(tree* root, int space)
{
    // If the tree is empty
    if(root == NULL)
    {
        return;
    }
    // increase distance
    space += ten;
    
    // Process right child
    visualPrint(root->getRight(), space);
    
    // Print current node
    cout << endl;
    for (int i = ten; i < space; i++)
    {
        cout << " ";
    }
    // If head exists make it black
    if(head != NULL)
    {
        head ->  setColor(false);
    }
    if(root -> getColor() == true && root -> getData() != 0)
    {
        cout << root -> getData() << " RED" << "\n";
    }
    else if(root -> getColor() == false && root -> getData() != 0)
    {
        cout << root -> getData() << " BLACK" << "\n";
    }
    
    // Process Left Child
    visualPrint(root->getLeft(), space);
}

void print(tree* root)
{
    
    visualPrint(root, 0);
}

void buildTree(int value, tree* current)
{
    // If the tree does not exist yet, insert node and make it black
    if(head == NULL)
    {
        tree* t = new tree(value);
        head = t;
        head ->  setColor(false);
        
        /* tree* five = new tree(5);
         five -> setColor(false);
         tree* thirty = new tree(30);
         thirty -> setColor(false);
         tree* fourty = new tree(40);
         fourty -> setColor(true);
         tree* twentyfive = new tree(25);
         twentyfive -> setColor(true);
         
         thirty -> setLeft(twentyfive);
         twentyfive -> setParent(thirty);
         thirty -> setRight(fourty);
         fourty -> setParent(thirty);
         head -> setRight(thirty);
         thirty -> setParent(head);
         head -> setLeft(five);
         five -> setParent(head);*/
    }
    
    
    else // if the tree exists
    {
        // If the value is larger than the previous node
        if(value > current -> getData())
        {
            if(current -> getRight() == NULL || current -> getRight() -> getData() == 0)
            {
                tree* right = new tree(value);
                current -> setRight(right);
                right -> setParent(current);
                current2 = right;
                
                while (rotateParent(head, current2) == true || rotateFull(head, current2) == true || parentRed(head, current2) == true)
                {
                    print(head);
                }
                print(head);
            }
            else
            {
                buildTree(value, current-> getRight());
            }
        }
        // If the value is less than, set as left
        else if(value < current -> getData())
        {
            if(current -> getLeft() == NULL || current -> getLeft() -> getData() == 0)
            {
                tree* left = new tree(value);
                current -> setLeft(left);
                left -> setParent(current);
                current2 = left;
                
                while (rotateParent(head, current2) == true || rotateFull(head, current2) == true || parentRed(head, current2) == true)
                {
                    print(head);
                }
                print(head);
                
            }
            else
            {
                buildTree(value, current-> getLeft());
            }
        }
        else // the value is duplicate
        {
            
        }
    }
}

tree* getGrandParent(tree* current)
{
    if(current->getParent()->getParent() != NULL)
    {
        return current->getParent()->getParent();
    }
    else
    {
        return NULL;
    }
}

tree* getUncle(tree* current)
{
    if(current == head || current -> getParent() -> getParent() ==NULL)
    {
        return NULL;
    }
    if(getGrandParent(current)->getLeft() == current -> getParent())
    {
        return current->getParent()-> getParent() ->getRight();
    }
    if(getGrandParent(current)->getRight() == current -> getParent())
    {
        return current->getParent()-> getParent() -> getLeft();
    }
    else
    {
        return NULL;
    }
}

bool parentRed(tree* root, tree* current)
{
    if (current -> getParent() != NULL)
    {
        if(current-> getParent()->getColor() == true)
        {
            current->getParent()->toggle();
            if(getUncle(current) != NULL)
            {
                getUncle(current) -> toggle();
            }
            getGrandParent(current) -> toggle();
            
            if (getGrandParent(current) !=  NULL)
            {
                parentRed(getGrandParent(current), root);
                current2 = getGrandParent(current);
            }
            return true;
        }
    }
    
    else
    {
        
    }
    return false;
}

// Do when the uncle is black and the parent is to the left and the child is to the right or
// parent to the right and child is to the left
bool rotateParent(tree* root, tree* current)
{
    if(getUncle(current) != NULL)
    {
        if(getUncle(current) -> getData() != 0)
        {
            //cout << getUncle(current) -> getData();
            // If the uncle is black and the parent is red and the grandparent exists
            if(getUncle(current) -> getColor() == false && current -> getParent() -> getColor() == true
               && getGrandParent(current))
            {
                // if the node is to the right of the parent and the parent is to the left of the grandparent
                if(current -> getParent() -> getRight() == current && getGrandParent(current) -> getLeft() == current -> getParent())
                {
                    tree* temp = new tree(current->getParent()->getData());
                    temp ->setLeft(current->getParent()->getLeft());
                    temp -> setRight(current->getLeft());
                    
                    current ->setParent(getGrandParent(current));
                    current -> getParent() -> setLeft(current);
                    temp -> setParent(current);
                    current -> setLeft(temp);
                    current2 = current -> getLeft();
                    return true;
                }
                // If the node is to the left of that parent and the parent is to the right of the grandparent
                if(current -> getParent() -> getLeft() == current && getGrandParent(current) -> getRight() == current -> getParent())
                {
                    tree* temp = new tree(current->getParent()->getData());
                    temp ->setRight(current->getParent()->getRight());
                    temp -> setLeft(current->getRight());
                    
                    current ->setParent(getGrandParent(current));
                    current -> getParent() -> setRight(current);
                    temp -> setParent(current);
                    current -> setRight(temp);
                    current2 = current -> getRight();
                    return true;
                }
            }
            else
            {
                
            }
        }
    }
    
    else if(getUncle(current) == NULL && current -> getParent() != NULL)
    {
        if(current -> getParent() -> getColor() == true && getGrandParent(current))
        {
            // if the node is to the right of the parent and the parent is to the left of the grandparent
            if(current -> getParent() -> getRight() == current && getGrandParent(current) -> getLeft() == current -> getParent())
            {
                tree* temp = new tree(current->getParent()->getData());
                temp ->setLeft(current->getParent()->getLeft());
                temp -> setRight(current->getLeft());
                
                current ->setParent(getGrandParent(current));
                current -> getParent() -> setLeft(current);
                temp -> setParent(current);
                current -> setLeft(temp);
                current2 = current -> getLeft();
                return true;
            }
            // If the node so to the left of that parent and the parent is to the right of the grandparent
            if(current -> getParent() -> getLeft() == current && getGrandParent(current) -> getRight() == current -> getParent())
            {
                tree* temp = new tree(current->getParent()->getData());
                temp ->setRight(current->getParent()->getRight());
                temp -> setLeft(current->getRight());
                
                current ->setParent(getGrandParent(current));
                current -> getParent() -> setRight(current);
                temp -> setParent(current);
                current -> setRight(temp);
                current2 = current -> getRight();
                return true;
            }
        }
    }
    
    return false;
}

bool rotateFull(tree* root, tree* current)
{
    if (current -> getParent() != NULL)
    {
        if(getUncle(current) == NULL)
        {
            if(current -> getParent() -> getColor() == true && getGrandParent(current))
            {
                rotateFull2(root, current);
                return true;
            }
        }
        else
        {
            // If the uncle is black and the parent is red and the grandparent exists
            if(getUncle(current) -> getColor() == false && current -> getParent() -> getColor() == true
               && getGrandParent(current))
            {
                rotateFull2(root, current);
                return true;
            }
        }
    }
    return false;
}

void rotateFull2(tree* root, tree* current)
{
    tree* temp = new tree(NULL);
    
    // if the parent is to the right of the granparent and the node is to the right of the parent
    if(current -> getParent() -> getRight() == current && getGrandParent(current) -> getRight() == current -> getParent())
    {
        temp -> setColor(getGrandParent(current) -> getColor());
        temp->setData(getGrandParent(current) -> getData());
        current -> getParent() -> getLeft() -> setParent(temp);
        temp -> setRight(current -> getParent() -> getLeft());
        temp -> setLeft(getUncle(current));
        getUncle(current) -> setParent(temp);
        
        
        if(getGrandParent(current) -> getParent() == NULL)
        {
            head = current->getParent();
            if (head -> getParent() != NULL)
            {
                head -> setParent(NULL);
            }
            
            temp -> setParent(current->getParent());
            current -> getParent() -> setLeft(temp);
            current -> getParent() -> toggle();
            current -> getParent() -> getLeft() -> toggle();
            print(head);
            return;
        }
        
        if(getGrandParent(current) -> getParent() -> getLeft() == getGrandParent(current))
        {
            current -> getParent() -> setParent(getGrandParent(current) -> getParent());
            getGrandParent(current) -> setLeft(current->getParent());
            temp -> setParent(current->getParent());
            current -> getParent() -> setLeft(temp);
            current -> getParent() -> toggle();
            current -> getParent() -> getLeft() -> toggle();
            print(head);
            return;
        }
        
        if(getGrandParent(current) -> getParent() -> getRight() == getGrandParent(current))
        {
            current -> getParent() -> setParent(getGrandParent(current) -> getParent());
            getGrandParent(current) -> setRight(current->getParent());
            temp -> setParent(current->getParent());
            current -> getParent() -> setLeft(temp);
            current -> getParent() -> toggle();
            current -> getParent() -> getLeft() -> toggle();
            print(head);
            return;
        }
        
    }
    // If the node is to the left of that parent and the parent is to the left of the grandparent
    if(current -> getParent() -> getLeft() == current && getGrandParent(current) -> getLeft() == current -> getParent())
    {
        temp -> setColor(getGrandParent(current) -> getColor());
        temp-> setData(getGrandParent(current) -> getData());
        temp -> setLeft(current -> getParent() -> getRight());
        temp -> setRight(getUncle(current));
        getUncle(current) -> setParent(temp);
        
        if(getGrandParent(current) -> getParent() == NULL)
        {
            head = current->getParent();
            if(head -> getParent() != NULL)
            {
                head -> setParent(NULL);
            }
            temp -> setParent(current->getParent());
            current -> getParent() -> setRight(temp);
            current -> getParent() -> toggle();
            current -> getParent() -> getRight() -> toggle();
            print(head);
            return;
        }
        
        if(getGrandParent(current) -> getParent() -> getLeft() == getGrandParent(current))
        {
            current -> getParent() -> setParent(getGrandParent(current) -> getParent());
            getGrandParent(current) -> setLeft(current->getParent());
            temp -> setParent(current->getParent());
            current -> getParent() -> setRight(temp);
            current -> getParent() -> toggle();
            current -> getParent() -> getRight() -> toggle();
            print(head);
            return;
        }
        
        if(getGrandParent(current) -> getParent() -> getRight() == getGrandParent(current))
        {
            current -> getParent() -> setParent(getGrandParent(current) -> getParent());
            getGrandParent(current) -> setRight(current->getParent());
            temp -> setParent(current->getParent());
            current -> getParent() -> setRight(temp);
            current -> getParent() -> toggle();
            current -> getParent() -> getRight() -> toggle();
            print(head);
            return;
        }
    }
}

tree* search (tree* current, int value)
{
    if (value == current->getData())
    {
        return current;
    }
    
    if (current -> getLeft()== NULL && current -> getRight() == NULL)
    {
        return NULL;
    }
    
    else if (value > current->getData())
    {
        if(current->getRight() == NULL)
        {
            return NULL;
        }
        else
        {
            if( current -> getRight() != NULL)
            {
                return search(current->getRight(), value);
            }
        }
    }
    else if (value < current -> getData())
    {
        if (current-> getLeft() == NULL)
        {
            return NULL;
        }
        else
        {
            if(current ->getLeft() != NULL)
            {
                return search(current->getLeft(), value);
            }
        }
    }
    
    
    return NULL;
}

tree* findNext(tree* current)
{
    // go right once then left all the way
    if(current == NULL || current->getRight() == NULL)
    {
        
    }
    else
    {
        current = current -> getRight();
        
        while(current->getLeft() != NULL)
        {
            current = current->getLeft();
        }
    }
    return current;
}

tree* getSibling(tree* current)
{
    // If then node is on the right side
    if(current -> getParent() -> getRight() == current)
    {
        return current -> getParent() -> getLeft();
    }
    // If then node is on the left side
    if(current -> getParent() -> getLeft() == current)
    {
        return current -> getParent() -> getRight();
    }
    return NULL;
}

void del(tree* current, int value)
{
    tree* node = search(current, value);
    tree* next = findNext(current);
    // If the node is the only one in the tree
    if(node == head && node -> getRight() == NULL && node -> getLeft() == NULL)
    {
        delete node;
    }
    
    // If the node is the root and has one left child
    if(node == head && node -> getLeft() != NULL && node -> getRight() == NULL)
    {
        tree* t = head -> getLeft();
        head = t;
        t -> setColor(false);
        delete node;
        return;
    }
    // If the successor has a singluar red child on the right
    if (next -> getRight() != NULL && next -> getRight() -> getColor() == true && next -> getLeft() == NULL)
    {
        node -> setData(next->getData());
        next -> getRight() -> setColor(false);
        // If next is on the left side of parent
        if (next -> getParent() -> getLeft() == next)
        {
            next -> getRight() -> setParent(next->getParent());
            next -> getParent() -> setLeft(next -> getRight());
            delete next;
            return;
        }
        // If next is on the right side of parent
        if (next -> getParent() -> getRight() == next)
        {
            next -> getRight() -> setParent(next->getParent());
            next -> getParent() -> setRight(next -> getRight());
            delete next;
            return;
        }
    }
    // If the successor has a singluar red child on the left
    if (next -> getRight() == NULL && next -> getLeft() != NULL && next -> getLeft() -> getColor() == true)
    {
        node -> setData(next->getData());
        next -> getLeft() -> setColor(false);
        // If next is on the left side of parent
        if (next -> getParent() -> getLeft() == next)
        {
            next -> getRight() -> setParent(next->getParent());
            next -> getParent() -> setLeft(next -> getRight());
            delete next;
            return;
        }
        // If next is on the right side of parent
        if (next -> getParent() -> getRight() == next)
        {
            next -> getRight() -> setParent(next->getParent());
            next -> getParent() -> setRight(next -> getRight());
            delete next;
            return;
        }
    }
    
    // It is a node with no children and no siblings
    if (next -> getLeft() == NULL && next -> getRight() == NULL && getSibling(next) == NULL)
    {
        // node -> setData(next -> getData());
        
        // If the node is on the right side
        if (node -> getParent() -> getRight() == node)
        {
            node -> getRight() -> setParent(node->getParent());
            node -> getParent() -> setRight(node->getRight());
            node -> setParent(NULL);
            node -> setRight(NULL);
            delete node;
            current2 = next;
            return;
        }
        // If the node is on the left side
        if (node -> getParent() -> getLeft() == node)
        {
            node -> getRight() -> setParent(node->getParent());
            node -> getParent() -> setLeft(node->getRight());
            node -> setParent(NULL);
            node -> setRight(NULL);
            delete node;
            current2 = next;
            return;
        }
    }
    if (next -> getColor() == false && next -> getRight() -> getColor() == false)
    {
        node -> setData(next->getData());
        next -> getRight() -> setColor(false);
        // If next is on the left side of parent
        if (next -> getParent() -> getLeft() == next)
        {
            next -> getRight() -> setParent(next->getParent());
            next -> getParent() -> setLeft(next -> getRight());
            node -> setParent(NULL);
            node -> setRight(NULL);
            delete node;
            current2 = next;
            return;
        }
        // If next is on the right side of parent
        if (next -> getParent() -> getRight() == next)
        {
            next -> getRight() -> setParent(next->getParent());
            next -> getParent() -> setRight(next -> getRight());
            node -> setParent(NULL);
            node -> setRight(NULL);
            delete node;
            current2 = next;
            return;
        }
    }
}

void delMethod(tree* current, int value)
{
    // The node that is being deleted
    tree* node = search(current, value);
    // The node that will take its place
    tree* next = findNext(current);
    
    // If the node that is replacing is red and has no children
    if(next->getColor() == true && next->getLeft() == NULL && next -> getRight() == NULL)
    {
        del(current, value);
        return;
    }
    if (next -> getRight() != NULL || next -> getLeft() != NULL)
    {
        // If the left child of the node that is replacing is red and has no children
        if(next -> getColor() == false && next -> getLeft() -> getColor() == true && next -> getLeft() -> getLeft() == NULL && next -> getLeft() -> getRight() == NULL)
        {
            del(current, value);
            return;
        }
        
        // If the right child of the node that is replacing is red and has no children
        if(next -> getColor() == false && next -> getRight() -> getColor() == true && next -> getRight() -> getLeft() == NULL && next -> getRight() -> getRight() == NULL)
        {
            del(current, value);
            return;
        }
    }
    else
    {
        // This will be the double black node
        tree* doubleBlack = new tree(0);
        doubleBlack -> setColor(false);
        doubleBlack -> setParent(next);
        next -> setRight(doubleBlack);
        del(current, value);
        // Cases 1-6
        case4(current2);
        case6(current2);
        
    }
}

void case4(tree* current)
{
    if (current -> getParent()->getColor() == true)
    {
        
        int color = 0;
        // color checks
        if(getSibling(current) != NULL)
        {
            if(getSibling(current) -> getColor() == false)
            {
                color++;
            }
        }
        else if(getSibling(current) == NULL)
        {
            color++;
        }
        if(getSibling(current) -> getLeft() != NULL)
        {
            if(getSibling(current) -> getLeft() -> getColor() == false)
            {
                color++;
            }
        }
        else if(getSibling(current) -> getLeft() == NULL)
        {
            color++;
        }
        
        if(getSibling(current) -> getRight() != NULL)
        {
            if(getSibling(current) -> getRight() -> getColor() == false)
            {
                color++;
            }
        }
        else if(getSibling(current) -> getRight() == NULL)
        {
            color++;
        }
        
        
        // If the parent is black and the sibling and all if its childeren are black
        if (color == 3)
        {
            // Switch the color of the parent and the sibling
            current -> getParent() -> toggle();
            getSibling(current) -> toggle();
            
            // Case 4 is also terminating case so lets clean up the double black node
            // If its on left side
            if(current -> getParent() -> getLeft() == current)
            {
                current -> getParent() -> setLeft(NULL);
                delete current;
            }
            // If its on  right side
            if(current -> getParent() -> getRight() == current)
            {
                current -> getParent() -> setRight(NULL);
                delete current;
            }
        }
    }
    print(head);
}

void case6(tree* current)
{
    int color = 0;
    // check if node is on right and S is black and SL is red or node is left S is black and SR is right
    // Left side
    if(current -> getParent() -> getRight() == current)
    {
        if (getSibling(current) != NULL)
        {
            if(getSibling(current) -> getColor() == false)
            {
                color++;
            }
        }
        if(getSibling(current) -> getLeft() != NULL)
        {
            if(getSibling(current) -> getLeft() -> getColor() == true)
            {
                color++;
            }
        }
    }
    // right side
    if(current -> getParent() -> getLeft() == current)
    {
        if (getSibling(current) != NULL)
        {
            if(getSibling(current) -> getColor() == false)
            {
                color++;
            }
        }
        if(getSibling(current) -> getRight() != NULL)
        {
            if(getSibling(current) -> getRight() -> getColor() == true)
            {
                color++;
            }
        }
    }
    // Color count will be two if conditions are satisfied
    
    if (color == 2)
    {
        // right side
        if(current -> getParent() -> getRight() == current)
        {
            rotateFull2(head, getSibling(current) -> getLeft());
            current -> getParent() -> setColor(false);
            getGrandParent(current) -> setColor(false);
            getUncle(current) -> setColor(false);
            // Terminating, Remove double black
            current -> getParent() -> setRight(NULL);
            current -> setParent(NULL);
            print(head);
        }
        // left side
        if(current -> getParent() -> getLeft() == current)
        {
            rotateFull2(head, getSibling(current) -> getRight());
            current -> getParent() -> toggle();
            getGrandParent(current) -> setColor(current->getParent()->getColor());
            current -> getParent() -> setColor(false);
            getUncle(current) -> setColor(false);
            // Terminating, Remove double black
            current -> getParent() -> setLeft(NULL);
            current -> setParent(NULL);
            print(head);
        }
    }
}
