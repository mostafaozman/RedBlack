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
void parentRed(tree* root, tree* current);
void rotateParent(tree* root, tree* current);
void rotateFull(tree* root, tree* current);
void rotateFull2(tree* root, tree* current);

int heap[100];
int size;
int counter = 0;
int position;
int num;
int ten = 10;
bool yes = true;

tree* head = NULL;

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
        cout << "\nWhat would you like to  do? Add (1) or  Print (2)"<< endl;
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
        
        if (type == 4)
        {
            print(head);
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
                // Case 5
                rotateFull(head, right);
                // Case 4
                rotateParent(head, right);
                // Case 3
                parentRed(head, right);
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
                // Case 5
                rotateFull(head, left);
                // Case 4
                rotateParent(head, left);
                // Case 3
                parentRed(head, left);
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
    if(current == head)
    {
        return NULL;
    }
    if(current->getParent()->getRight() == current && current -> getParent() -> getParent() !=NULL)
    {
        return current->getParent()-> getParent() ->getLeft();
    }
    if(current->getParent()->getLeft() == current && current -> getParent() -> getParent() !=NULL)
    {
        return current->getParent()-> getParent() -> getRight();
    }
    else
    {
        return NULL;
    }
}

void parentRed(tree* root, tree* current)
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
            }
        }
    }
    
    else
    {
        
    }
}

// Do when the uncle is black and the parent is to the left and the child is to the right or
// parent to the right and child is to the left
void rotateParent(tree* root, tree* current)
{
    if(getUncle(current) != NULL)
    {
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
                getGrandParent(current) -> setLeft(current);
                temp -> setParent(current);
                current -> setLeft(temp);
            }
            // If the node so to the left of that parent and the parent is to the right of the grandparent
            if(current -> getParent() -> getLeft() == current && getGrandParent(current) -> getRight() == current -> getParent())
            {
                tree* temp = new tree(current->getParent()->getData());
                temp ->setRight(current->getParent()->getRight());
                temp -> setLeft(current->getRight());
                
                current ->setParent(getGrandParent(current));
                getGrandParent(current) -> setRight(current);
                temp -> setParent(current);
                current -> setRight(temp);
            }
        }
        else
        {
            
        }
    }
}

void rotateFull(tree* root, tree* current)
{
    if(getUncle(current) == NULL)
    {
        if(current -> getParent() -> getColor() == true && getGrandParent(current))
        {
            rotateFull2(root, current);
        }
    }
    else
    {
        // If the uncle is black and the parent is red and the grandparent exists
        if(getUncle(current) -> getColor() == false && current -> getParent() -> getColor() == true
           && getGrandParent(current))
        {
            rotateFull2(root, current);
        }
    }
}

void rotateFull2(tree* root, tree* current)
{
    tree* temp = new tree(NULL);
    tree* temp2 = new tree(NULL);
    
    // if the parent is to the right of the granparent and the node is to the right of the parent
    if(current -> getParent() -> getRight() == current && getGrandParent(current) -> getRight() == current -> getParent())
    {
        temp -> setColor(getGrandParent(current) -> getColor());
        temp->setData(getGrandParent(current) -> getData());
        temp -> setRight(current -> getParent() -> getLeft());
        temp -> setLeft(NULL);
        
        if(getUncle(current) != NULL)
        {
            temp2 -> setColor(getUncle(current) -> getColor());
            temp2->setData(getUncle(current) -> getData());
            temp2 -> setRight(getUncle(current) -> getRight());
            temp2 -> setLeft(getUncle(current) -> getLeft());
        }
        
        else if(getUncle(current) == NULL)
        {
            temp2->setData(NULL);
            temp2 -> setRight(NULL);
            temp2 -> setLeft(NULL);
        }
        
        if(getGrandParent(current) -> getParent() == NULL)
        {
            head = current->getParent();
            temp -> setParent(current->getParent());
            current -> getParent() -> setLeft(temp);
            temp2 -> setParent(temp);
            current -> getParent() -> getLeft() -> setLeft(temp2);
            current -> getParent() -> toggle();
            current -> getParent() -> getLeft() -> toggle();
            return;
        }
        
        if(getGrandParent(current) -> getParent() -> getLeft() == getGrandParent(current))
        {
            current -> getParent() -> setParent(getGrandParent(current) -> getParent());
            getGrandParent(current) -> getParent() -> setLeft(current->getParent());
            temp -> setParent(current->getParent());
            current -> getParent() -> setLeft(temp);
            temp2 -> setParent(temp);
            current -> getParent() -> getLeft() -> setLeft(temp2);
            current -> getParent() -> toggle();
            current -> getParent() -> getLeft() -> toggle();
            return;
        }
        
        if(getGrandParent(current) -> getParent() -> getRight() == getGrandParent(current))
        {
            current -> getParent() -> setParent(getGrandParent(current) -> getParent());
            getGrandParent(current) -> getParent() -> setRight(current->getParent());
            temp -> setParent(current->getParent());
            current -> getParent() -> setLeft(temp);
            temp2 -> setParent(temp);
            current -> getParent() -> getLeft() -> setLeft(temp2);
            current -> getParent() -> toggle();
            current -> getParent() -> getLeft() -> toggle();
            return;
        }
        
    }
    // If the node is to the left of that parent and the parent is to the left of the grandparent
    if(current -> getParent() -> getLeft() == current && getGrandParent(current) -> getLeft() == current -> getParent())
    {
        temp -> setColor(getGrandParent(current) -> getColor());
        temp-> setData(getGrandParent(current) -> getData());
        temp -> setLeft(current -> getParent() -> getRight());
        temp -> setRight(NULL);
        
        if(getUncle(current) != NULL)
        {
            temp2 ->setColor(getUncle(current) -> getColor());
            temp2 -> setData(getUncle(current) -> getData());
            temp2 -> setRight(getUncle(current) -> getRight());
            temp2 -> setLeft(getUncle(current) -> getLeft());
        }
        
        else if(getUncle(current) == NULL)
        {
            temp2 -> setData(NULL);
            temp2 -> setRight(NULL);
            temp2 -> setLeft(NULL);
        }
        
        if(getGrandParent(current) -> getParent() == NULL)
        {
            head = current->getParent();
            temp -> setParent(current->getParent());
            current -> getParent() -> setRight(temp);
            temp2 -> setParent(temp);
            current -> getParent() -> getRight() -> setRight(temp2);
            current -> getParent() -> toggle();
            current -> getParent() -> getRight() -> toggle();
            return;
        }
        
        if(getGrandParent(current) -> getParent() -> getLeft() == getGrandParent(current))
        {
            current -> getParent() -> setParent(getGrandParent(current) -> getParent());
            getGrandParent(current) -> getParent() -> setLeft(current->getParent());
            temp -> setParent(current->getParent());
            current -> getParent() -> setRight(temp);
            temp2 -> setParent(temp);
            current -> getParent() -> getRight() -> setRight(temp2);
            current -> getParent() -> toggle();
            current -> getParent() -> getLeft() -> toggle();
            return;
        }
        
        if(getGrandParent(current) -> getParent() -> getRight() == getGrandParent(current))
        {
            current -> getParent() -> setParent(getGrandParent(current) -> getParent());
            getGrandParent(current) -> getParent() -> setRight(current->getParent());
            temp -> setParent(current->getParent());
            current -> getParent() -> setRight(temp);
            temp2 -> setParent(temp);
            current -> getParent() -> getRight() -> setRight(temp2);
            current -> getParent() -> toggle();
            current -> getParent() -> getLeft() -> toggle();
            return;
        }
    }
}
