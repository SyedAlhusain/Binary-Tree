/********************************************
** File:    Fleet.cpp
** Project: CMSC 341 Project 3, Spring 2022
** Author:  Syed Husain
** Date:    3/26/22
** E-mail:  ax18210@umbc.edu
** Desc: This file makes the Fleet object to run by mytest.cpp
** Course/Section : CMSC 341 
**/

#include "fleet.h"

Fleet::Fleet(){
    // Preconditions: None
    // Postconditions: Initializes variables
    m_root = nullptr;

}

Fleet::~Fleet(){
    // Preconditions: None
    // Postconditions: The Fleet tree is deallocated by deleting all the nodes and it childrens

    //calls clear to dellocate memory
    clear();
}

void Fleet::insert( const Ship& ship){
    // Preconditions: None
    // Postconditions: Insert the ship in the BST

    //checks if id passed is valid 
    if(ship.m_id > MAXID || ship.m_id < MINID){
        return;
    }

    //checks if its not a duplicate id
    if(findShip(ship.m_id) == true){
        return;
    }

    //calls the helpers function and insert the node at root
    m_root = insertHelp(m_root, ship.m_id, ship.getType());

}

Ship * Fleet::insertHelp(Ship* aShip, int key, SHIPTYPE type){
    // Preconditions: None
    // Postconditions: Insert the ship in the BST

    //if ship point to null creates a new node, set it items and returns it
    if(aShip == nullptr){
        Ship  *aShip = new Ship(key, type, DEFAULT_STATE);
        aShip->m_height = 0;
        aShip->m_left = nullptr;
        aShip->m_right = nullptr;
        return aShip;
    }

    //checks if id passed is valid 
    if(key > MAXID || key < MINID){
        return aShip;
    }

    //checks if its not a duplicate id
    if(findShip(key) == true){
        return aShip;
    }

    //if key passed is lower the current ship traverse through it left child 
    if(key < aShip->m_id)
        aShip->m_left = insertHelp(aShip->m_left, key, type);
    //if key is higher traverses through it right child
    else if(key > aShip->m_id)
        aShip->m_right = insertHelp(aShip->m_right, key, type);
    else //return the ship if there same
        return aShip;

    //call the function to updates the height once node is inserted
    updateHeight(aShip);

    //checks for balance and balances the tree if it unbalanced
    return rebalance(aShip);
    
}

void Fleet::clear(){
    // Preconditions: Require a BST
    // Postconditions: The Fleet tree is deallocated by deleting all the nodes and it childrens

    //calls helper function with m_root to dellocate memory
    clearHelp(m_root);
}

void Fleet::clearHelp(Ship* &aShip){
    // Preconditions: Require a BST
    // Postconditions: The Fleet tree is deallocated by deleting all the nodes and it childrens

    //if BST is empty returns
    if (aShip == nullptr){
        return;
    }

    //else traverse throught BST and delete each iternal node and its child
    clearHelp(aShip->m_left);
    clearHelp(aShip->m_right);
    delete(aShip);

    //set the ship to null after deleting
    aShip = nullptr;

}

void Fleet::remove(int id){
    // Preconditions: Require a BST
    // Postconditions: Traverses the tree to find a node with the id and removes it from the tree.

    //calls the helper function with m_root and id;
    m_root = removeHelp(m_root, id);
}

Ship * Fleet::removeHelp(Ship* &aShip, int key){
    // Preconditions: Require a BST
    // Postconditions: Traverses the tree to find a node with the id and removes it from the tree.
    
    //if ship is null returns the ship
    if (aShip == nullptr){
        return aShip;

    //if ship doesn't exist in the tree then returns it
    if(findShip(key) == false){
        return aShip;
    }

    //if key passed is lower the current ship traverse through it left child 
    }if (key < aShip->m_id){
        aShip->m_left = removeHelp(aShip->m_left, key);

    //if key is higher traverses through it right child
    }else if (key > aShip->m_id){
        aShip->m_right = removeHelp(aShip->m_right, key);

    //once found performs removal
    }else{
        //if there no child delete the ship and return it
        if (aShip->m_left == nullptr && aShip->m_right== nullptr){
            delete aShip;
            aShip = nullptr;
            return aShip;
            
        //if the left child is null then swaps the ship with it right child and delete the right child
        }else if(aShip->m_left == nullptr){
            Ship* temp = aShip->m_right;

            swap(aShip->m_type, temp->m_type);
            swap(aShip->m_left, temp->m_left);
            swap(aShip->m_right, temp->m_right);
            swap(aShip->m_height, temp->m_height);
            swap(aShip->m_id, temp->m_id);
            swap(aShip->m_state, temp->m_state);

            delete temp;
            temp = nullptr;
            return aShip;

        //if the right child is null then swaps the ship with it left child and delete the left child
        }else if(aShip->m_right == nullptr){
            Ship* temp = aShip->m_left;

            swap(aShip->m_type, temp->m_type);
            swap(aShip->m_left, temp->m_left);
            swap(aShip->m_right, temp->m_right);
            swap(aShip->m_height, temp->m_height);
            swap(aShip->m_id, temp->m_id);
            swap(aShip->m_state, temp->m_state);

            delete temp;
            temp = nullptr;
            return aShip;

        }else{
            //set current to right child
            Ship* current = aShip->m_right;

            //traverse throught the leftmost leaf of the right child
            while (current->m_left != nullptr){
                current = current->m_left;
            }

            //set a temp and swaps items with current and then delete the inorder sucessor
            Ship* temp = current;
            aShip->m_id = temp->m_id;
            aShip->m_state = temp->m_state;
            aShip->m_type = temp->m_type;
            aShip->m_right = removeHelp(aShip->m_right, temp->m_id);

        }
    }

    //updates the height and rebalances the tree after removal
    updateHeight(aShip);
    return rebalance(aShip);

}

void Fleet::updateHeight(Ship* aShip){
    // Preconditions: Require a node
    // Postconditions: Update the height of the internal node after its inserted

    if (aShip != nullptr){
        int left_height ;
        int right_height;

        //check if left or right child is null return -1 else returns it height
        if(aShip->m_left == nullptr){
            left_height = -1;
        }else{
            left_height = aShip->m_left->m_height;

        }

        if(aShip->m_right == nullptr){
            right_height = -1;
        }else{
            right_height = aShip->m_right->m_height;
        }

        //check which childest is longest and increments the hieght by 1 by its child
        if(left_height > right_height )
            aShip->m_height = left_height + 1;
        else
            aShip->m_height = right_height + 1;     

    }

}

int Fleet::checkImbalance(Ship* aShip){
    // Preconditions: Require a node
    // Postconditions: Returns the difference between the childs of the node

    //if ship is null return -1
    if (aShip == nullptr){
        return -1;
    }

    int left_height;
    int right_height;

    //check if left or right child is null return -1 else returns it height
    if(aShip->m_left == nullptr){
        left_height = -1;
    }else{
        left_height = aShip->m_left->m_height;

    }
    if(aShip->m_right == nullptr){
        right_height = -1;
    }else{
        right_height = aShip->m_right->m_height;

    }

    //returns the the difference between the left and right child of the node
    return left_height - right_height;
}


Ship * Fleet::rightRotate(Ship *y){
    // Preconditions: Require a node
    // Postconditions: Right rotates the node's childrens

    //set left and right pointer
    Ship *x = y->m_left;
    Ship *r = x->m_right;

    //rotates the tree in right direction
    x->m_right = y;
    y->m_left = r;
 
    //updates the height of left and right child
    updateHeight(y);
    updateHeight(x);
    
    //return the left child
    return x;
}

Ship *Fleet::leftRotate(Ship *x){
    // Preconditions: Require a node
    // Postconditions: Left rotates the node's childrens

    //set left and right pointer
    Ship *y = x->m_right;
    Ship *r = y->m_left;

    //rotates the tree in left direction
    y->m_left = x;
    x->m_right = r;

    //updates the height of left and right child
    updateHeight(x);
    updateHeight(y);

    //return the right child
    return y;
}


Ship* Fleet::rebalance(Ship * aShip){
    // Preconditions: Require a BST
    // Postconditions: Balances the BST by rotating it

    int balance = checkImbalance(aShip);

    //If positive imbalance accours on left child then performs a right rotation
    if (balance > 1 && checkImbalance(aShip->m_left) >= 0 )
        return rightRotate(aShip);
 
    //If negative imbalance accours on right child then performs a left rotation
    if (balance < -1 && checkImbalance(aShip->m_right) <= 0)
        return leftRotate(aShip);
 
    //If positive imbalance accours on left child then performs a left rotation on left
    if (balance > 1 && checkImbalance(aShip->m_left) <= 0){
        aShip->m_left = leftRotate(aShip->m_left);
        return rightRotate(aShip); //return the right rotation
    }
 
    //If positive imbalance accours on left child then performs a right rotation on right 
    if (balance < - 1 && checkImbalance(aShip->m_right) >= 0){
        aShip->m_right = rightRotate(aShip->m_right);
        return leftRotate(aShip); //return the left rotation
    }

    //return the ship if there's no imbalance
    return aShip;

}

void Fleet::dumpTree() const {
    // Preconditions: Requires a BST
    // Postconditions: Displays each ship and its children in orderly
    
    dump(m_root);
    cout << endl;
}

void Fleet::dump(Ship* aShip) const{
    // Preconditions: Requires a BST
    // Postconditions: Displays each ship and its children in orderly

    //Traverse the binary tree recursively and displays each ship and its children
    if (aShip != nullptr){
        cout << "(";
        dump(aShip->m_left);//first visit the left child
        cout << aShip->m_id << ":" << aShip->m_height; //second visit the node itself
        dump(aShip->m_right);//third visit the right child
        cout << ")";
    }
}

void Fleet::listShips() const{
    // Preconditions: Require a BST
    // Postconditions: Prints a list of all ships in the tree to the standard output in the ascending order of IDs.

    //calls the helper function with m_root to print all the ships
    listHelp(m_root);

}

void Fleet::listHelp(Ship* aShip) const {
    // Preconditions: Require a BST
    // Postconditions: Prints a list of all ships in the tree to the standard output in the ascending order of IDs.

    //Traverse the binary tree recursively and displays each ship and its children along with it state and type
    if (aShip != nullptr){
        listHelp(aShip->m_left);//first visit the left child
        cout << aShip->m_id << ":" << aShip->getStateStr() << ":" << aShip->getTypeStr() << endl;//second visit the node itself
        listHelp(aShip->m_right);//third visit the right child
    }
}

bool Fleet::setState(int id, STATE state){
    // Preconditions: Require a BST
    // Postconditions: Sets its m_state to state passed once the operation is successful else returns false
    return setStateHelp(m_root, id, state);
}

bool Fleet::setStateHelp(Ship* aShip, int id, STATE state){
    // Preconditions: Require a BST
    // Postconditions: Sets its m_state to state passed once the operation is successful else returns false

    //return false once reaches the end without finding the state
    if(aShip == nullptr){
        return false;

    //Sets its m_state to state once it find the id and return true
    }else if(aShip->m_id == id){
        aShip->m_state = state;
        return true;

    //if key passed is lower the current ship traverse through it left child 
    }else if(aShip->m_id > id){
        bool id_val = setStateHelp(aShip->m_left, id, state);
        return id_val;

    //if key is higher traverses through it right child
    }else{
        bool id_val = setStateHelp(aShip->m_right, id, state);
        return id_val;
    }

}


void Fleet::removeLost(){
    // Preconditions: Require a BST
    // Postconditions: Traverses the tree, finds a ship with LOST state returns it ID

    //array containing all the lost id to be removed
    int remove_id[100000];
    int count = 0;

    //Iterates over all the possible id for the AVL tree
    for(int i = MINID; i < MAXID + 1; i++ ){
        //calls the helper function and check if ship is LOST
        if(removeLostHelp(m_root, i) == true){
            //if ship is lost add its id to the array
            remove_id[count] = i;
            count++;
        }
    }
    
    //iterates over all the lost ships and removes them
    for(int i = 0; i < count; i++ ){
        remove(remove_id[i]);
    }

}


bool Fleet::removeLostHelp(Ship* aShip, int id){
    // Preconditions: Require a BST
    // Postconditions: Traverses the tree, if the ship is found with it state at Lost return true else returns false

    //return false once reaches the end without finding the state
    if(aShip == nullptr){
        return false;

    //once it find the id return true if it state is LOST else returns false
    }else if(aShip->m_id == id){
        if(aShip->m_state == LOST)
            return true;
        else 
            return false;

    //if key passed is lower the current ship traverse through it left child 
    }else if(aShip->m_id > id){
        bool id_val = removeLostHelp(aShip->m_left, id);
        return id_val;

    //if key is higher traverses through it right child
    }else{
        bool id_val = removeLostHelp(aShip->m_right, id);
        return id_val;
    }

}

bool Fleet::findShip(int id) const{
    // Preconditions: Require a BST
    // Postconditions: Returns true if it finds the node with id in the tree, otherwise it returns false.

    //calls the helper function with m_root and id;
    return searchHelp(m_root, id);
}

bool Fleet::searchHelp(Ship * aShip, int id) const{
    // Preconditions: Require a BST
    // Postconditions: Returns true if it finds the node with id in the tree, otherwise it returns false.

    //return false once reaches the end without finding the id 
    if(aShip == nullptr){
        return false;

    //return true once it find the id
    }else if(aShip->m_id == id){
        return true;

    //if key passed is lower the current ship traverse through it left child 
    }else if(aShip->m_id > id){
        bool id_val = searchHelp(aShip->m_left, id);
        return id_val;

    //if key is higher traverses through it right child
    }else{
        bool id_val = searchHelp(aShip->m_right, id);
        return id_val;
    }
    
}


bool Fleet::isBST(Ship* root, Ship* &prev){
    // Preconditions: Require a BST
    // Postconditions: Checks if Tree has BST property that is the value of the key of the left child
    // is less than the value of its parent(root) node's key. Return true if it satifies, else return false

    // Base condition
    if (root == nullptr){
        //set root to left child by calling the function and return false if the function return false
        if (!isBST(root->m_left, prev))
          return false;
    
        //if left child key is less than root return false
        if (prev != nullptr && root->m_id <= prev->m_id)
          return false;

        //set previous to parent root
        prev = root;

        //checks the right child 
        return isBST(root->m_right, prev);
    }

    //return true if no left child key was then it root
    return true;
}

bool Fleet::BSTcheck(){
    // Preconditions: Require a BST
    // Postconditions: Checks if Tree has BST property return true if it satifies, else return false

    //set prev and call the helper function with m_root and prev
    Ship * prev = nullptr;
    return isBST(m_root, prev);
}


bool Fleet::isBalance(Ship* aShip){
    // Preconditions: Require a BST
    // Postconditions: Checks if there imbalance and return false else return true

    //if tree is empty and return true
    if (aShip == nullptr){
        return true;
    }

    //traverse each node and checks if both it child differ by no more than 1 return true if it does else return false
    if (abs(checkImbalance(aShip)) <= 1 && isBalance(aShip->m_left) && isBalance(aShip->m_right))
        return true;

    return false;

}

bool Fleet::testBalanceOfTree(){
    // Preconditions: Require a BST
    // Postconditions: Checks if there imbalance and return false else return true

    //calls the helper function with m_root
    return isBalance(m_root);
}
