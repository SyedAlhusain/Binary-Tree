/********************************************
** File:    mytest.cpp
** Project: CMSC 341 Project 3, Spring 2022
** Author:  Syed Husain
** Date:    3/26/22
** E-mail:  ax18210@umbc.edu
** Desc:  This file test the Fleet object made in fleet.cpp
** Course/Section : CMSC 341 
**/

#include "fleet.h"
#include <random>

enum RANDOM {UNIFORMINT, UNIFORMREAL, NORMAL};
class Random {
public:
    Random(int min, int max, RANDOM type=UNIFORMINT, int mean=50, int stdev=20) : m_min(min), m_max(max), m_type(type)
    {
        if (type == NORMAL){
            //the case of NORMAL to generate integer numbers with normal distribution
            m_generator = std::mt19937(m_device());
            //the data set will have the mean of 50 (default) and standard deviation of 20 (default)
            //the mean and standard deviation can change by passing new values to constructor 
            m_normdist = std::normal_distribution<>(mean,stdev);
        }
        else if (type == UNIFORMINT) {
            //the case of UNIFORMINT to generate integer numbers
            // Using a fixed seed value generates always the same sequence
            // of pseudorandom numbers, e.g. reproducing scientific experiments
            // here it helps us with testing since the same sequence repeats
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_unidist = std::uniform_int_distribution<>(min,max);
        }
        else{ //the case of UNIFORMREAL to generate real numbers
            m_generator = std::mt19937(10);// 10 is the fixed seed value
            m_uniReal = std::uniform_real_distribution<double>((double)min,(double)max);
        }
    }

    int getRandNum(){
        // this function returns integer numbers
        // the object must have been initialized to generate integers
        int result = 0;
        if(m_type == NORMAL){
            //returns a random number in a set with normal distribution
            //we limit random numbers by the min and max values
            result = m_min - 1;
            while(result < m_min || result > m_max)
                result = m_normdist(m_generator);
        }
        else if (m_type == UNIFORMINT){
            //this will generate a random number between min and max values
            result = m_unidist(m_generator);
        }
        return result;
    }

    double getRealRandNum(){
        // this function returns real numbers
        // the object must have been initialized to generate real numbers
        double result = m_uniReal(m_generator);
        // a trick to return numbers only with two deciaml points
        // for example if result is 15.0378, function returns 15.03
        // to round up we can use ceil function instead of floor
        result = std::floor(result*100.0)/100.0;
        return result;
    }
    
    private:
    int m_min;
    int m_max;
    RANDOM m_type;
    std::random_device m_device;
    std::mt19937 m_generator;
    std::normal_distribution<> m_normdist;//normal distribution
    std::uniform_int_distribution<> m_unidist;//integer uniform distribution
    std::uniform_real_distribution<double> m_uniReal;//real uniform distribution

};
class Tester{
    public:
    /******************************************
    * Test function declarations go here! *
    ******************************************/

    bool FleetAllTest();

    bool testInsertNormalCase(); 
    bool testInsertErrorCase();
    bool testInsertEdgeCase();
    
    bool testRemoveNormalCase(); 
    bool testRemoveErrorCase();
    bool testRemoveEdgeCase();

    bool testInsertBalance();
    bool testRemoveBalance();

    bool testBstPropertyInsert();
    bool testBstPropertyRemove();

    bool testRemoveLost();
    bool testRemoveLostEdgeCase();

    bool testInsertTime();
    bool testRemoveTime();
    bool testFindTime();

    bool testSetState();
    bool testFindShip();

};


int main(){
    Tester tester;

    if(tester.FleetAllTest() == true)
        cout << "\nThe Program worked successfully :) All the tests were passed!!" << endl;
    else
        cout << "\nThe Program failed :( All the tests did not passed succesfully !!" << endl;

}

bool Tester::FleetAllTest(){
    // Preconditions: None
    // Postconditions: Tests all the function to see if the program runs succesfully

    Tester tester;

    cout << "\nTesting insert()(...), Normal Case:\n\n";
    if (tester.testInsertNormalCase() == true){
        cout << "\tNormal Case of insert() passed!\n";
    }else{
        cout << "\tNormal Case of insert() failed!\n";
        return false;
    }

    cout << "\nTesting insert()(...), Edge Case:\n\n";
    if (tester.testInsertEdgeCase() == true){
        cout << "\tEdge Case of insert() passed!\n";
    }else{
        cout << "\tEdge Case of insert() failed!\n";
        return false;
    }

    cout << "\nTesting insert()(...), Error Case:\n\n";
    if (tester.testInsertErrorCase() == true){
        cout << "\tError Case of insert() passed!\n";
    }else{
        cout << "\tError Case of insert() failed!\n";
        return false;
    }
    

    cout << "\nTesting remove()(...), Normal Case:\n\n";
    if (tester.testRemoveNormalCase() == true){
        cout << "\tNormal Case of remove() passed!\n";
    }else{
        cout << "\tNormal Case of remove() failed!\n";
        return false;
    }

    cout << "\nTesting remove()(...), Edge Case:\n\n";
    if (tester.testRemoveEdgeCase() == true){
        cout << "\tEdge Case of remove() passed!\n";
    }else{
        cout << "\tEdge Case of remove() failed!\n";
        return false;
    }

    cout << "\nTesting remove()(...), Error Case:\n\n";
    if (tester.testRemoveErrorCase() == true){
        cout << "\tError Case of remove() passed!\n";
    }else{
        cout << "\tError Case of remove() failed!\n";
        return false;
    }

    cout << "\nTesting insert()(...), Balance:\n\n";
    if (tester.testInsertBalance() == true){
        cout << "\tBalance of insert() passed!\n";
    }else{
        cout << "\tBalance of insert() failed!\n";
        return false;
    }

    cout << "\nTesting remove()(...), Balance:\n\n";
    if (tester.testRemoveBalance() == true){
        cout << "\tBalance of remove() passed!\n";
    }else{
        cout << "\tBalance of remove() failed!\n";
        return false;
    }


    cout << "\nTesting insert()(...), BST Property:\n\n";
    if (tester.testBstPropertyInsert() == true){
        cout << "\tBST Property of insert() passed!\n";
    }else{
        cout << "\tBST Property of insert() failed!\n";
        return false;
    }

    cout << "\nTesting remove()(...), BST Property:\n\n";
    if (tester.testBstPropertyRemove() == true){
        cout << "\tBST Property of remove() passed!\n";
    }else{
        cout << "\tBST Property of remove() failed!\n";
        return false;
    }

    cout << "\nTesting removeLost()(...), Normal Case:\n\n";
    if (tester.testRemoveLost() == true){
        cout << "\tNormal Case of removeLost() passed!\n";
    }else{
        cout << "\tNormal Case of removeLost() failed!\n";
        return false;
    }

    cout << "\nTesting removeLost()(...), Edge Case:\n\n";
    if (tester.testRemoveLostEdgeCase() == true){
        cout << "\tEdge Case of removeLost() passed!\n";
    }else{
        cout << "\tEdge Case of removeLost() failed!\n";
        return false;
    }

    cout << "\nTesting insert()(...), Time complexity:\n\n";
    if (tester.testInsertTime() == true){
        cout << "\tTime complexity of insert() passed!\n";
    }else{
        cout << "\tTime complexity of insert() failed!\n";
        return false;
    }

    cout << "\nTesting remove()(...), Time complexity:\n\n";
    if (tester.testRemoveTime() == true){
        cout << "\tTime complexity of remove() passed!\n";
    }else{
        cout << "\tTime complexity of remove() failed!\n";
        return false;
    }

    cout << "\nTesting findship()(...), Time complexity:\n\n";
    if (tester.testFindTime() == true){
        cout << "\tTime complexity of findship() passed!\n";
    }else{
        cout << "\tTime complexity of findship() failed!\n";
        return false;
    }

    cout << "\nTesting setState()(...) \n\n";
        if (tester.testSetState() == true){
        cout << "\tsetState() passed!\n";
    }else{
        cout << "\tsetState() failed!\n";
        return false;
    }

    cout << "\nTesting findShip()(...) \n\n";
        if (tester.testFindShip() == true){
        cout << "\tfindShip() passed!\n";
    }else{
        cout << "\tfindShip() failed!\n";
        return false;
    }

    return true;
}

bool Tester::testInsertNormalCase(){
    // Preconditions: None
    // Postconditions: Return true if all the nodes are inserted correctly else returns false

    Random idGen(MINID,MAXID);
    Random typeGen(0,4);{
        Fleet fleet;
        int fleetSize = 100;
        int ID = 0;
        int find_id[1000];
        int counter = 0;

        //Loops over the size and insert random number to fleet 
        for(int i=0;i<fleetSize;i++){
            ID = idGen.getRandNum();
            //add ids to array for future test
            find_id[counter] = ID;
            counter++;
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        //checks if all the ids are found else return false
        for(int i=0;i<counter;i++){
            if(fleet.findShip(find_id[i]) == false)
                return false;
        }

        //checks if tree is balanced else return false
        if(fleet.testBalanceOfTree() == false){
            return false;
        }

    }

    //return true if all conditions are met
    return true;

}


bool Tester::testInsertEdgeCase(){
    // Preconditions: None
    // Postconditions: Return true if all the nodes are inserted and correctly and tree is balanced else return false


    Fleet fleet;
    int ID = 10000;
    int fleetSize = 10;

    //iterates over the loop and increment id so that ship is always inserted at right causing imbalance to occur for rebalance to take care of
    for(int i=0;i<fleetSize;i++){
        Ship ship(ID,static_cast<SHIPTYPE>(1));
        fleet.insert(ship);
        ID += 1000;
    }

    //check if imbalanced tree is balanced by rebalance  after insertion
    if(fleet.testBalanceOfTree() == false){
        //return true if its balanced else return false
        return false;
    }

    Fleet fleet2;
    //insert just one ship at root
    Ship ship(10000,static_cast<SHIPTYPE>(1));
    fleet2.insert(ship);

    if(fleet2.testBalanceOfTree() == false){
        //return true if its balanced else return false
        return false;
    }

    if(fleet2.BSTcheck() == false){
        //return if tree is BST else return false;
        return false;
    }

    return true;

}


bool Tester::testInsertErrorCase(){
    // Preconditions: None
    // Postconditions: Return true if the error ship is not inserted else returns false

    Random idGen(MINID,MAXID);
    Random typeGen(0,4);  {
        Fleet fleet;
        int fleetSize = 10;
        int ID = 0;

        for(int i=0;i<fleetSize;i++){
            ID = idGen.getRandNum();
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        //ship case with id less than MINID value
        int ID1 = 5000;
        Ship ship(ID1,static_cast<SHIPTYPE>(1));
        fleet.insert(ship);

        //ship case with id more than MAXID value
        int ID2 = 100000;
        Ship ship2(ID2,static_cast<SHIPTYPE>(1));
        fleet.insert(ship2);

        //if any of the cases return true, return false 
        if(fleet.findShip(ID1) == true){
            return false;
        }
        if(fleet.findShip(ID2) == true){
            return false;
        }

    }

    //return true when no error ids are inserted
    return true;

}

bool Tester::testBstPropertyInsert(){
    // Preconditions: None
    // Postconditions: Return true if Tree has BST property preserved else returns false

    Random idGen(MINID,MAXID);
    Random typeGen(0,4);  {
        Fleet fleet;
        int fleetSize = 10;
        int ID = 0;

        //insert ships
        for(int i=0;i<fleetSize;i++){
            ID = idGen.getRandNum();
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        //calls helper function and return true if BST property is preserved else return false
        if(fleet.BSTcheck() == true){
            return true;
        }

    }
    return false;
}


bool Tester::testInsertBalance() {
    // Preconditions: None
    // Postconditions:  Return true if tree is balanced after large insertion(300 ships) else returns false

    Random idGen(MINID,MAXID);
    Random typeGen(0,4);
    {
        Fleet fleet;
        int fleetSize = 300;
        int ID = 0;

        //inserts 300 ships
        for(int i=0;i<fleetSize;i++){
            ID = idGen.getRandNum();
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        //checks if tree is balanced return true if it is, else return false
        if(fleet.testBalanceOfTree() == false)
            return false;

    }

    return true;
}

bool Tester::testRemoveNormalCase(){
    // Preconditions: None
    // Postconditions: Return true if node is removed else return false

    Random idGen(MINID,MAXID);
    Random typeGen(0,4);{
        Fleet fleet;
        int fleetSize = 300;
        int ID = 0;
        int tempID = 0; //tempID to be removed

        for(int i=0;i<fleetSize;i++){
            ID = idGen.getRandNum();
            if (i == fleetSize / 2) 
                tempID = ID; //store a random id for temp
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        //removes the tempId
        fleet.remove(tempID);

        //checks if tempId still exist return false else return true
        if(fleet.findShip(tempID) == true){
            return false;

        }
    }

    return true;

}

bool Tester::testRemoveErrorCase(){
    // Preconditions: None
    // Postconditions: Return true if error node is not removed else return false

    Random idGen(MINID,MAXID);
    Random typeGen(0,4);{
        Fleet fleet;
        int fleetSize = 300;
        int ID = 0;
        int tempID;

        for(int i=0;i<fleetSize;i++){
            ID = idGen.getRandNum();
            if (i == fleetSize / 2) 
                tempID = ID; //store a random id for temp
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        //removes the last ID
        fleet.remove(ID);

        //checks if removed Id still exist return false else return true
        if(fleet.findShip(ID) == true){
            return false;
        }

        //checks if unremoved tempId still exist return true else return false
        if(fleet.findShip(tempID) == false){
            return false;
        }
    }

    return true;

}

//before test on test.cpp on pro2_b
bool Tester::testRemoveEdgeCase(){
    // Preconditions: None
    // Postconditions: Return true if a balanced tree is still balanced after removal else return false

    Fleet fleet;

    //insert node orderly that is each node is decreased/for left child and then increased for right after the parent root
    Ship ship1(11000,static_cast<SHIPTYPE>(1));
    Ship ship2(10050,static_cast<SHIPTYPE>(1));
    Ship ship3(14000,static_cast<SHIPTYPE>(1));
    Ship ship4(13000,static_cast<SHIPTYPE>(1));
    Ship ship5(16000,static_cast<SHIPTYPE>(1));
    Ship ship6(15000,static_cast<SHIPTYPE>(1));
    Ship ship7(18000,static_cast<SHIPTYPE>(1));
    Ship ship8(10040,static_cast<SHIPTYPE>(1));
    Ship ship9(10060,static_cast<SHIPTYPE>(1));

    //insert ships
    fleet.insert(ship1);
    fleet.insert(ship2);
    fleet.insert(ship3);
    fleet.insert(ship4);
    fleet.insert(ship5);
    fleet.insert(ship6);
    fleet.insert(ship7);
    fleet.insert(ship8);
    fleet.insert(ship9);

    //remove the right childs on he left side of tree making it imbalance
    fleet.remove(10060);
    fleet.remove(13000);

    //check if imbalanced tree is balanced by rebalance after removal
    if(fleet.testBalanceOfTree() == true){
        //return true if its balance else return false
        return true;
    }

    return false;

}

bool Tester::testRemoveBalance(){
    // Preconditions: None
    // Postconditions: Return true if tree is balanced after multiple removals else return false

    Random idGen(MINID,MAXID);
    Random typeGen(0,4);{

        Fleet fleet;
        int fleetSize = 300;
        int ID = 0;

        int remove_id[1000]; //array to store ids to be removed
        int counter = 0; //index of the array

        //Inserts fleetsize which is 300 nodes into the BST
        for(int i=0;i<fleetSize;i++){
            ID = idGen.getRandNum();
            remove_id[counter] = ID; //stores the id
            counter++; //increment the counter
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        //Remove 150 nodes
        for(int i=0;i<fleetSize / 2;i++){
            //remove each id stores in the remove_id stored
            fleet.remove(remove_id[i]);
        }

        //returns false if Fleet tree is not balance else return true
        if(fleet.testBalanceOfTree() == false)
            return false;


    }
    return true;

}


bool Tester::testBstPropertyRemove(){
    // Preconditions: None 
    // Postconditions: Return true if Tree has BST property preserved after multiple removals else return false 

    Random idGen(MINID,MAXID);
    Random typeGen(0,4);{

        Fleet fleet;
        int fleetSize = 300;
        int ID = 0;

        int remove_id[1000]; //array to store ids to be removed
        int counter = 0; //index of the array

        //Inserts 300 nodes into the BST
        for(int i=0;i<fleetSize;i++){
            ID = idGen.getRandNum();
            remove_id[counter] = ID; //stores the id
            counter++; //increment the counter
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        //Removes 150 nodes
        for(int i=0;i<fleetSize / 2;i++){
            //remove each id stores in the remove_id stored
            fleet.remove(remove_id[i]);
        }

        //returns false if BST property is not preserved else return true
        if(fleet.BSTcheck() == false)
            return false;

    }
    return true;

}

bool Tester::testRemoveLost(){
    // Preconditions: None
    // Postconditions: Returns true if all Lost ships are removed else return false

    Random idGen(MINID,MAXID);
    Random typeGen(0,4);{
        Fleet fleet;
        int fleetSize = 300;
        int ID = 0;

        int counter = 0;
        int lost_id[90005];

        //Inserts 300 nodes into the BST
        for(int i=0;i<fleetSize;i++){
            ID = idGen.getRandNum();
            lost_id[counter] = ID;
            counter++;
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        //Sets half of the node states to Lost
        for(int i=0;i<fleetSize / 2;i++){
            if(fleet.setState(lost_id[i], LOST) == false)
                return false;
        }

        //calls the function and remove all the lost ships
        fleet.removeLost();
        
        //check if any of the lost ship still exist
        for(int i=0;i<fleetSize / 2;i++){
            //if a lost ship exist return false 
            if(fleet.findShip(lost_id[i]) == true)
                return false;
        }

    }

    //if no lost ship exist return false
    return true;
}

bool Tester::testRemoveLostEdgeCase(){
    // Preconditions: None
    // Postconditions: Return true if a balanced tree is still balanced after removal of LOST ships else return false

    Fleet fleet;

    //insert node orderly that is each node is decreased/for left child and then increased for right after the parent root
    Ship ship1(11000,static_cast<SHIPTYPE>(1));
    Ship ship2(10050,static_cast<SHIPTYPE>(1));
    Ship ship3(14000,static_cast<SHIPTYPE>(1));
    Ship ship4(13000,static_cast<SHIPTYPE>(1));
    Ship ship5(16000,static_cast<SHIPTYPE>(1));
    Ship ship6(15000,static_cast<SHIPTYPE>(1));
    Ship ship7(18000,static_cast<SHIPTYPE>(1));
    Ship ship8(10040,static_cast<SHIPTYPE>(1));
    Ship ship9(10060,static_cast<SHIPTYPE>(1));

    //insert ships
    fleet.insert(ship1);
    fleet.insert(ship2);
    fleet.insert(ship3);
    fleet.insert(ship4);
    fleet.insert(ship5);
    fleet.insert(ship6);
    fleet.insert(ship7);
    fleet.insert(ship8);
    fleet.insert(ship9);

    //remove the right childs on he left side of tree making it imbalance
    fleet.setState(10060, LOST);
    fleet.setState(13000, LOST);

    fleet.removeLost();

    //check if imbalanced tree is balanced by rebalance after removal
    if(fleet.testBalanceOfTree() == true){
        //return true if its balance else return false
        return true;
    }

    return false;

}

bool Tester::testInsertTime(){
    // Preconditions: None
    // Postconditions: Returns true if insertion is performed in O(log n) else return false

    //Measuring the efficiency of insertion algorithm with system clock ticks
    Random idGen(MINID,MAXID);
    Random typeGen(0,4);{
        Fleet fleet;
        int fleetSize = 1000;
        int ID;

        //variable to count time difference
        int T1; //time for constructing a tree of 1000 nodes
        int T2; //time for constructing a tree of 2000 nodes

        //stores the clock ticks while running the program
        clock_t start, stop; 

        //starts the clock right before insertion then take the ending time with stop
        start = clock();

        //loop through and insert 1000 ships
        for(int i=0;i<fleetSize;i++){
            ID = idGen.getRandNum(); 
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }
        stop = clock();

        //calculates the difference to find the number of clock ticks the algorithm took for inserting 1000 nodes
        T1 = stop - start; 

        //variable for the second tree
        Fleet fleet2;
        int fleetSize2 = 2000;
        int ID2;

        //stores the clock ticks while running the program
        clock_t start2, stop2;

        //starts the clock right before insertion then take the ending time with stop
        start2 = clock();

        //loop through and insert 2000 ships
        for(int i=0;i<fleetSize2;i++){
            ID2 = idGen.getRandNum();            
            Ship ship(ID2,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet2.insert(ship);
        }
        stop2 = clock();

        //calculates the difference to find the number of clock ticks the algorithm took for inserting 2000 nodes
        T2 = stop2 - start2;

        //calculates the ratio by T2 divides 2 T1
        float final_ratio;
        final_ratio = (float)T2/(2 * T1);

        //checks if the ratio stays under the range of 1.1 with absolute error of 0.4 
        if(final_ratio > (1 - 0.4) && final_ratio < (1.1 + 0.4) ){
            return true; //return true if it inside range else return false
        }

    }
    return false;

}

bool Tester::testRemoveTime(){
    // Preconditions: None
    // Postconditions: Returns true if find Ship is performed in O(log n) else return false

    Random idGen(MINID,MAXID);
    Random typeGen(0,4);{
        Fleet fleet;
        int fleetSize = 1000;
        int ID = 0;

        //variable to count time difference
        int T1; //time for remove 1000 nodes from a tree
        int T2; //time for remove 2000 nodes from a tree

        int counter1 = 0;
        int remove_id[100000];

        //stores the clock ticks while running the program
        clock_t start, stop;

        //loop through and insert 1000 ships
        for(int i=0;i<fleetSize;i++){
            ID = idGen.getRandNum();   
            remove_id[counter1] = ID;
            counter1++;     
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        //starts the clock right before removal then take the ending time with stop
        start = clock();

        //loop through and remove 1000 nodes
        for(int i= 0 ; i< fleetSize; i++){
            fleet.remove(remove_id[i]);
        }

        stop = clock();

        //calculates the difference to find the number of clock ticks the algorithm took for delete 1000 node
        T1 = stop - start;

        //Tree 2
        Fleet fleet2;
        int fleetSize2 = 2000;
        int counter2 = 0;
        int remove_id2[100000];

        clock_t start2, stop2; //stores the clock ticks while running the program

        //loop through and insert 2000 ships
        for(int i=0;i<fleetSize2;i++){
            ID = idGen.getRandNum();   
            remove_id2[counter2] = ID;
            counter2++;     
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet2.insert(ship);
        }

        //starts the clock right before removal then take the ending time with stop
        start2 = clock();

        //loop through and remove 2000 nodes
        for(int i= 0 ; i< fleetSize2; i++){
            fleet2.remove(remove_id2[i]);
        }

        stop2 = clock();

        //calculates the difference to find the number of clock ticks the algorithm took for removing 2000 nodes
        T2 = stop2 - start2;

        //calculates the ratio by T2 divided by 2T1
        float final_ratio;
        final_ratio = (float)T2/( 2 * T1);

        //checks if the ratio stays under the range of 1.1 with absolute error of 0.4 
        if(final_ratio > (1 - 0.4) && final_ratio < (1.1 + 0.4) ){
            return true; //return true if it inside range, else return false
        }
    }
    return false;
    
}

bool Tester::testFindTime(){
    // Preconditions: None
    // Postconditions: Returns true if find Ship is performed in O(log n) else return false

    Random idGen(MINID,MAXID);
    Random typeGen(0,4);{
        Fleet fleet;
        int fleetSize = 1000;
        int ID = 0;

        //variable to count time difference
        int T1; //time for remove 1000 nodes from a tree
        int T2; //time for remove 2000 nodes from a tree

        int counter1 = 0;
        int find_id[100000];

        //stores the clock ticks while running the program
        clock_t start, stop;

        //loop through and insert 1000 ships
        for(int i=0;i<fleetSize;i++){
            ID = idGen.getRandNum();   
            find_id[counter1] = ID;
            counter1++;     
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        //starts the clock right before removal then take the ending time with stop
        start = clock();

        for(int i= 0 ; i< fleetSize; i++){
            if(fleet.findShip(find_id[i]) == false)
                return false;
        }

        stop = clock();

        //calculates the difference to find the number of clock ticks the algorithm took for find the 1000 node
        T1 = stop - start;

        //Tree 2
        Fleet fleet2;
        int fleetSize2 = 2000;
        int counter2 = 0;
        int find_id2[100000];

        clock_t start2, stop2; //stores the clock ticks while running the program

        //loop through and insert 2000 ships
        for(int i=0;i<fleetSize2;i++){
            ID = idGen.getRandNum();   
            find_id2[counter2] = ID;
            counter2++;     
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet2.insert(ship);
        }

        //starts the clock right before removal then take the ending time with stop
        start2 = clock();

        for(int i= 0 ; i< fleetSize2; i++){
            if(fleet2.findShip(find_id2[i]) == false)
                return false;
        }

        stop2 = clock();

        //calculates the difference to find the number of clock ticks the algorithm took for removing 2000 nodes
        T2 = stop2 - start2;

        //calculates the ratio by T2 divided by 2T1
        float final_ratio;
        final_ratio = (float)T2/( 2 * T1);

        //checks if the ratio stays under the range of 1.1 with absolute error of 0.4 
        if(final_ratio > (1 - 0.4) && final_ratio < (1.1 + 0.4) ){
            return true; //return true if it inside range, else return false
        }
    }
    return false;
    
}

bool Tester::testSetState(){
    // Preconditions: None
    // Postconditions: Returns true if ship state is Lost else returns false

    Random idGen(MINID,MAXID);
    Random typeGen(0,4);
    {
        Fleet fleet;
        int fleetSize = 10;
        int tempID = 0;
        int ID = 0;
        for(int i=0;i<fleetSize;i++){
            ID = idGen.getRandNum();
            if (i == fleetSize / 2) 
                tempID = ID;//we store this ID for later use
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        //return false if the inserted ship is not set to lost
        if(fleet.setState(tempID, LOST) == false)
            return false;

        //return false if function return true for an error ship
        if(fleet.setState(4000, LOST) == true)
            return false;
        
    }

    //returns true once both tests are passed
    return true;

}

bool Tester::testFindShip(){
    // Preconditions: None
    // Postconditions: return true if correct ship is found else return false

    Random idGen(MINID,MAXID);
    Random typeGen(0,4);
    {
        Fleet fleet;
        int fleetSize = 10;
        int tempID = 0;
        int ID = 0;
        for(int i=0;i<fleetSize;i++){
            ID = idGen.getRandNum();
            if (i == fleetSize / 2) 
                tempID = ID;//we store this ID for later use
            Ship ship(ID,static_cast<SHIPTYPE>(typeGen.getRandNum()));
            fleet.insert(ship);
        }

        //return false if the inserted ship is not found
        if(fleet.findShip(tempID) == false)
            return false;

        //return false if function return true for an error ship
        if(fleet.findShip(4000) == true)
            return false;


    }

    //returns true once both tests are passed
    return true;

}
