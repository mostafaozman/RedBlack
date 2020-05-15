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
bool case4(tree* current);
bool case6(tree* current);
bool case3(tree* current);
bool case1(tree* current);
bool case5(tree* current);
bool case6(tree* current);
bool case2(tree* current);

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
        
        // left sub tree
        /*   tree* five = new tree(5);
         five -> setColor(false);
         tree* three = new tree(3);
         three -> setColor(false);
         tree* two = new tree(2);
         two -> setColor(false);
         
         five -> setRight(three);
         three -> setParent(five);
         five -> setLeft(two);
         two -> setParent(five);
         
         // right sub tree
         tree* fifty = new tree(50);
         fifty -> setColor(false);
         tree* eighty = new tree(80);
         eighty -> setColor(false);
         tree* sixty = new tree(60);
         sixty -> setColor(true);
         tree* twenty = new tree(20);
         twenty -> setColor(false);
         tree* fourty = new tree(40);
         fourty -> setColor(false);
         
         sixty -> setRight(eighty);
         eighty -> setParent(sixty);
         sixty ->setLeft(fifty);
         fifty -> setParent(sixty);
         
         fourty -> setRight(sixty);
         sixty -> setParent(fourty);
         fourty -> setLeft(twenty);
         twenty -> setParent(fourty);
         
         // full tree
         head -> setLeft(five);
         five -> setParent(head);
         head -> setRight(fourty);
         fourty -> setParent(head);*/
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
        temp -> setRight(current -> getParent() -> getLeft());
        if ( current -> getParent() -> getLeft() != NULL)
        {
            current -> getParent() -> getLeft() -> setParent(temp);
        }
        current  -> getParent() -> setLeft(temp);
        current -> getParent() -> getLeft() -> setParent(current);
        temp -> setLeft(getUncle(current));
        if (getUncle(current) != NULL)
        {
            getUncle(current) -> setParent(temp);
        }
        
        
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
        if (current -> getParent() -> getRight() != NULL)
        {
            current -> getParent() -> getRight() -> setParent(temp);
        }
        temp -> setRight(getUncle(current));
        if (getUncle(current) != NULL)
        {
            getUncle(current) -> setParent(temp);
        }
        
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
    // go left
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
        next = node -> getRight();
        node -> setData(next->getData());
        // If node is on the right side of parent
        if (node -> getParent() -> getRight() == node)
        {
            node -> getRight() -> setParent(node->getParent());
            node -> getParent() -> setRight(node -> getRight());
            delete next;
            return;
        }
    }
    // If the successor has a singluar red child on the left
    if (next -> getRight() == NULL && next -> getLeft() != NULL && next -> getLeft() -> getColor() == true)
    {
        next = node -> getLeft();
        node -> setData(next->getData());
        // If node is on the left side of parent
        if (node -> getParent() -> getLeft() == next)
        {
            node -> getRight() -> setParent(node->getParent());
            node -> getParent() -> setLeft(node -> getLeft());
            delete next;
            return;
        }
    }
    
    // It is a node with no children and no siblings
    if (next -> getLeft() == NULL && next -> getRight() == NULL)
    {
        // node -> setData(next -> getData());
        
        // If the node is on the right side
        if (node -> getParent() -> getRight() == node)
        {
            node -> getParent() -> setRight(node -> getRight());
            if(node -> getRight() != NULL)
            {
                node -> getRight() -> setParent(node->getParent());
            }
            // deleting tree with a root and one child
            if (node -> getParent() == head && getSibling(node) == NULL)
            {
                current2 = head;
            }
            node -> setParent(NULL);
            node -> setRight(NULL);
            return;
        }
        // If the node is on the left side
        if (node -> getParent() -> getLeft() == node)
        {
            node -> getParent() -> setLeft(node -> getRight());
            if(node -> getRight() != NULL)
            {
                node -> getRight() -> setParent(node->getParent());
            }
            node -> setParent(NULL);
            node -> setRight(NULL);
            current2 = next -> getRight();
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
            current2 = next -> getRight();
            next -> setParent(NULL);
            next -> setRight(NULL);
            delete node;
            return;
        }
        // If next is on the right side of parent
        if (next -> getParent() -> getRight() == next)
        {
            next -> getRight() -> setParent(next->getParent());
            next -> getParent() -> setRight(next -> getRight());
            current2 = next -> getRight();
            next -> setParent(NULL);
            next -> setRight(NULL);
            delete node;
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
    
    // If the node is the only one in the tree
    if(node == head && node -> getLeft() == NULL)
    {
        if (node -> getRight() != NULL)
        {
            if (node -> getRight() -> getData() == 0)
            {
                head -> setLeft(NULL);
                head -> getRight() -> setParent(NULL);
                head -> setRight(NULL);
                head = NULL;
                delete node;
            }
        }
        
        if (node -> getRight() == NULL)
        {
            head = NULL;
            return;
        }
        
    }
    
    // If the node that is replacing is red and has no children
    if(next->getColor() == true && next->getLeft() == NULL && next -> getRight() == NULL)
    {
        del(current, value);
        return;
    }
    if (next -> getLeft() != NULL)
    {
        // If the left child of the node that is replacing is red and has no children
        if(next -> getColor() == false && next -> getLeft() -> getColor() == true && next -> getLeft() -> getLeft() == NULL && next -> getLeft() -> getRight() == NULL)
        {
            del(current, value);
            return;
        }
    }
    if(next -> getRight() != NULL)
    {
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
        while (case1(current2) || case2(current2) || case3(current2) || case4(current2) || case5(current2) || case6(current2) == true)
        {
            print(head);
        }
        
        current2 = search(head, 0);
        // getting rid of double black
        if(current2 == NULL)
        {
            // do nothibng
        }
        if (current2 != NULL)
        {
            //Remove double black
            // Left side
            if (current2 -> getParent() -> getLeft() == current2 && current2 -> getData() == 0)
            {
                current2 -> getParent() -> setLeft(NULL);
                current2 -> setParent(NULL);
            }
            // Right Side
            else if (current2 -> getData() == 0)
            {
                current2 -> getParent() -> setRight(NULL);
                current2 -> setParent(NULL);
            }
        }
        
    }
}

bool case4(tree* current)
{
    if (current -> getParent() != NULL)
    {
        if (current -> getParent()->getColor() == true)
        {
            
            int color = 0;
            // color checks
            if (current -> getRight() != NULL)
            {
                if (current -> getRight() -> getColor() == true)
                {
                    return false;
                }
            }
            if (current -> getLeft() != NULL)
            {
                if (current -> getLeft() -> getColor() == true)
                {
                    return false;
                }
            }
            if (current -> getColor() == false)
            {
                color ++;
            }
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
            
            
            // If the parent is red and the sibling and all if its childeren are black
            if (color == 4)
            {
                // Switch the color of the parent and the sibling
                current -> getParent() -> toggle();
                getSibling(current) -> toggle();
                
                // Case 4 is also terminating case so lets clean up the double black node
                // If its on left side
                if(current -> getParent() -> getLeft() == current)
                {
                    current2 = current -> getParent();
                    current -> getParent() -> setLeft(NULL);
                    current -> setParent(NULL);
                    delete current;
                    return true;
                }
                // If its on  right side
                if(current -> getParent() -> getRight() == current)
                {
                    current2 = current -> getParent();
                    current -> getParent() -> setRight(NULL);
                    current -> setParent(NULL);
                    delete current;
                    return true;
                }
                return true;
            }
        }
    }
    return false;
}

bool case6(tree* current)
{
    int color = 0;
    // check if node is on right and S is black and SL is red or node is left S is black and SR is red
    // Left side
    /* if (current -> getRight() != NULL)
     {
     if (current -> getRight() -> getColor() == true)
     {
     return false;
     }
     }
     if (current -> getLeft() != NULL)
     {
     if (current -> getLeft() -> getColor() == true)
     {
     return false;
     }
     }*/
    if (current -> getColor() == false)
    {
        color ++;
    }
    if (current -> getParent() != NULL)
    {
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
    }
    // Color count will be two if conditions are satisfied
    
    if (color == 3)
    {
        // right side
        if(current -> getParent() -> getRight() == current)
        {
            rotateFull2(head, getSibling(current) -> getLeft());
            current -> getParent() -> setColor(false);
            getGrandParent(current) -> setColor(false);
            getUncle(current) -> setColor(false);
            // Terminating, Remove double black
            if (current -> getData() == 0)
            {
                current -> getParent() -> setRight(NULL);
                current -> setParent(NULL);
            }
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
            if (current -> getData() == 0)
            {
                current -> getParent() -> setLeft(NULL);
                current -> setParent(NULL);
            }
            print(head);
            
        }
        return true;
    }
    return false;
}

bool case3(tree* current)
{
    int color = 0;
    // Check if parent is black, sibling is black, and sibling children are black
    // Sibling has to exist
    if (current -> getParent() != NULL)
    {
        if (current -> getColor() == false)
        {
            color ++;
        }
        if (current -> getRight() != NULL)
        {
            if (current -> getRight() -> getColor() == true)
            {
                return false;
            }
        }
        if (current -> getLeft() != NULL)
        {
            if (current -> getLeft() -> getColor() == true)
            {
                return false;
            }
        }
        if (current -> getParent() -> getColor() == false)
        {
            color++;
        }
        if (getSibling(current) != NULL)
        {
            if(getSibling(current) -> getColor() == false)
            {
                color++;
            }
            if(getSibling(current) -> getLeft() == NULL)
            {
                color++;
            }
            if(getSibling(current) -> getRight() == NULL)
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
            if(getSibling(current) -> getLeft() != NULL)
            {
                if(getSibling(current) -> getLeft() -> getColor() == false)
                {
                    color++;
                }
            }
        }
    }
    // Color count should be 5 to proceed
    if (color == 5)
    {
        getSibling(current) -> toggle();
        current2 = current -> getParent();
        
        //Remove double black
        // Left side
        if (current -> getParent() -> getLeft() == current && current -> getData() == 0)
        {
            current -> getParent() -> setLeft(NULL);
            current -> setParent(NULL);
        }
        // Right Side
        else if (current -> getData() == 0)
        {
            current -> getParent() -> setRight(NULL);
            current -> setParent(NULL);
        }
        
        return true;
    }
    return false;
}

bool case5(tree* current)
{
    // Check if parent is black, sibling is black. Then if doubleblack is right to parent, check if SR is red. If doubleblack is left, check if SL is red
    int color = 0;
    // color count should be 4
    if (current  -> getParent() != NULL)
    {
        if (current -> getRight() != NULL)
        {
            if (current -> getRight() -> getColor() == true)
            {
                return false;
            }
        }
        if (current -> getLeft() != NULL)
        {
            if (current -> getLeft() -> getColor() == true)
            {
                return false;
            }
        }
        if (current -> getColor() == false)
        {
            color ++;
        }
        if (current -> getParent()-> getColor() == false)
        {
            color++;
        }
        if (getSibling(current)-> getColor() == false)
        {
            color++;
        }
        // Node is on right of parent, check if SR is red
        if (current-> getParent() -> getRight() == current)
        {
            if (getSibling(current) -> getRight() != NULL)
            {
                if(getSibling(current) -> getRight() -> getColor() == true)
                {
                    color++;
                }
            }
        }
        // Node is on left of parent, check if SL is red
        if (current-> getParent() -> getLeft() == current)
        {
            if (getSibling(current) -> getLeft() != NULL)
            {
                if(getSibling(current) -> getLeft() -> getColor() == true)
                {
                    color++;
                }
            }
        }
    }
    
    if (color == 4)
    {
        // If conditions are satisfied we will do a tree rotation with respect to the siblings child
        if (current -> getParent() -> getLeft() == current)
        {
            current2 = getSibling(current) -> getLeft();
            current2 -> getParent() -> toggle();
            rotateParent(head, current2);
            current2 -> getParent() -> toggle();
            print(head);
        }
        if (current -> getParent() -> getRight() == current)
        {
            current2 = getSibling(current) -> getRight();
            current2 -> getParent() -> toggle();
            rotateParent(head, current2);
            current2 -> getParent() -> toggle();
            print(head);
        }
        return true;
    }
    return false;
}

bool case2(tree* current)
{
    // Check if parent is black, sibling is red, and both of siblings children are black
    int color = 0;
    // color count will be 5 if satisfied
    if (current -> getRight() != NULL)
    {
        if (current -> getRight() -> getColor() == true)
        {
            return false;
        }
    }
    if (current -> getLeft() != NULL)
    {
        if (current -> getLeft() -> getColor() == true)
        {
            return false;
        }
    }
    if (current -> getColor() == false)
    {
        color ++;
    }
    if (current -> getParent() -> getColor() == false)
    {
        color++;
    }
    if (getSibling(current) != NULL)
    {
        if (getSibling(current) -> getColor() == true)
        {
            color++;
        }
    }
    
    if (getSibling(current)-> getRight() != NULL)
    {
        if (getSibling(current) -> getRight() -> getColor() == false)
        {
            color++;
        }
    }
    else if(getSibling(current) -> getRight() == NULL)
    {
        color++;
    }
    
    if (getSibling(current)-> getLeft() != NULL)
    {
        if (getSibling(current) -> getLeft() -> getColor() == false)
        {
            color++;
        }
    }
    else if(getSibling(current) -> getLeft() == NULL)
    {
        color++;
    }
    
    if(color == 5)
    {
        // If everything is good we will do a full tree rotation with respect to SR if node is on left and with respect to SL if node is on right
        // if doubleblack is on left
        if  (current -> getParent() -> getLeft() == current)
        {
            rotateFull2(head, getSibling(current) -> getRight());
            print(head);
        }
        // if doubleblack is on right
        if  (current -> getParent() -> getRight() == current)
        {
            rotateFull2(head, getSibling(current) -> getLeft());
            print(head);
        }
        return true;
    }
    return false;
}

bool case1(tree* current)
{
    if (current -> getColor() == true)
    {
        return false;
    }
    if (current == head && current -> getColor() == false)
    {
        // do nothing
        return false;
    }
    if (current == head && current -> getColor() == true)
    {
        // make black
        current -> toggle();
        return true;
    }
    return false;
}
