/*****************************************
** File:    Lab.cpp
** Project: CMSC 202 Project 2, Spring 2022
** Author:  Sahil Misbah
** Date:    3/15/2022
** Section: 10/11
** E-mail:  sahilm1@gl.umbc.edu 
**
** Contains the main functionality of the game.
** Your player is a chemist and the goal is to
** combine multiple elements together in order to
** find all possible compounds.
**
***********************************************/

// libraries included
#include "Lab.h"
#include "Chemist.h"
#include "Substance.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// Constants
const char COMMA = ',';
const int NUM_OF_ELEMENTS = 29;


// Name: Lab() Default Constructor
  // Desc - Instantiates an object of type Lab
  // Preconditions - None
  // Postconditions - None
Lab::Lab() {}

// hasSubstances 
// checks if m_myChemist has substances returns the boolean for check
bool hasSubstances(Chemist m_myChemist) {

    bool hasSubstances = false; // chemist starts with no substances so false

    // iterate through chemist's substances and checks if quantity is > 0
    for (int i = 0 ; i < PROJ2_SIZE; i++) {
        if (m_myChemist.GetSubstance(i).m_quantity > 0) {
            hasSubstances = true;
        }
    }

    return hasSubstances;
}


// Name: LoadSubstances
  // Desc - Loads each substance into m_substances from file
  //        The loads all substances from m_substances into m_myChemist's substance array
  // Preconditions - Requires file with valid substance data
  // Postconditions - m_substance is populated with substance structs
void Lab::LoadSubstances() {

    ifstream wordFile;  // proj2_data file
    string name;        // name of element/compound
    string type;        // type of element/compound
    string formula;     // formula of element/compound
    string substance1;  // first substance of element/compound
    string substance2;  // second substance of element/compound
    int quantity = 1;   // quantity of substances
    
    // opens file
    wordFile.open(PROJ2_DATA);

    if (wordFile.is_open()) {

        // gets the name, type, formula, and substances from file
        for (int i = 0; i < PROJ2_SIZE; i++) {
            getline(wordFile, name, COMMA);
            getline(wordFile, type, COMMA);
            getline(wordFile, formula, COMMA);
            getline(wordFile, substance1, COMMA);
            getline(wordFile, substance2);
            
            // populates substances array
            m_substances[i] = (Substance(name, type, formula, substance1, substance2, quantity));

            // adds the substances to the chemists substance list
            m_myChemist.AddSubstance(m_substances[i]);
        }
    
    // file was not found
    } else {
        cout << "File could not be found!!" << endl;
    }

    // closes the file
    wordFile.close();
}


// Name: StartLab()
  // 1. Displays Lab Title
  // 2. Loads all substances and their recipes into m_substances (Load Substances)
  // 3. Asks user for their chemist's name (store in m_myChemist as m_myName)
  // 4. Copies all substances from m_substances into the chemist's substance array
  // 5. Manages the game itself including win conditions continually calling the main menu 
  // Preconditions - None
  // Postconditions - m_substances and m_myChemist's substances populated
void Lab::StartLab() {

    string chemistName; // chemist's name

    // displays lab title
    LabTitle();

    // asks user for their name
    cout << PROJ2_SIZE << " substances loaded." << endl;
    cout << "What is the name of your chemist? " << endl;
    getline(cin, chemistName);

    // makes name the name of chemist
    m_myChemist = Chemist(chemistName);

    // loads substances to array
    LoadSubstances();

    // users input from MainMenu()
    int userChoice = MainMenu();

    // runs the game until they quit (5)
    do {
        
        switch (userChoice) {
                case 1:
                    // displays all substances and it's quantities
                    DisplaySubstances();
                    userChoice = MainMenu();
                    break;

                case 2:
                    // adds random element to your substance list
                    SearchSubstances();
                    userChoice = MainMenu();
                    break;

                case 3:
                    // combines two substances together to make compound
                    CombineSubstances();
                    userChoice = MainMenu();
                    break;

                case 4:
                    // calculates the chemist's score using number of substances they have
                    CalcScore();
                    userChoice = MainMenu();
                    break;

                default:
                    cout << "Invalid" << endl;
                    cin.clear();
                    cin.ignore(10, '\n');
                    break;
        }

    } while (userChoice != 5);
}


// Name: DisplayMySubstances()
  // Desc - Iterates over m_myChemist's substances
  // Preconditions - Player's chemist has substances
  // Postconditions - Displays a numbered list of substances
void Lab::DisplaySubstances() {
    
    // checks if user has substances first
    if (hasSubstances(m_myChemist)) {
        cout << "My chemist has " << m_myChemist.GetTotalSubstances() << " different substances in inventory currently" << endl;
        
        // displays all substances and their quantities
        for (int i = 0; i < PROJ2_SIZE; i++) {
            cout << (i + 1) << "." << " " << m_myChemist.GetSubstance(i).m_name << " " << "(" << m_myChemist.GetSubstance(i).m_formula << ")" 
            << " " << m_myChemist.GetSubstance(i).m_quantity << endl;
        }
      // else they have no substances
    } else {
        cout << "My chemist has 0 different substances in inventory currently" << endl;
    }
}


// Name: MainMenu()
  // Desc - Displays and manages menu
  // Preconditions - Player has an Chemist
  // Postconditions - Returns input number including exit
int Lab::MainMenu() {
    int userChoice;

    // display menu
    cout << endl;
    cout << "What would you like to do?" << endl;
    cout << "1. Display your Chemist's Substances" << endl;
    cout << "2. Search for Elements" << endl;
    cout << "3. Attempt to Merge Substances" << endl;
    cout << "4. See Score" << endl;
    cout << "5. Quit" << endl;

    // take in input
    cin >> userChoice;
    cout << endl;

    return userChoice;
}


// Name: SearchSubstances()
  // Desc - Attempts to search for raw substances (must be type "element")
  // Preconditions - Raw substances loaded
  // Postconditions - Increases quantity in Chemist's posession of substances
void Lab::SearchSubstances() {

    int randomNum = rand() % NUM_OF_ELEMENTS;   // makes a random number
    string randomElement;   // random element
    
    // increases quantity of random substance obtained
    m_myChemist.IncrementQuantity(m_substances[randomNum]); 

    // random element name
    randomElement = m_substances[randomNum].m_name;

    cout << randomElement << " found!" << endl;

}


// Name: CombineSubstances()
  // Desc - Attempts to combine known substances. If combined, quantity of substance decreased
  // 1. Requests user to choose two substances (RequestSubstance)
  // 2. Checks to see if formula exists for combining two chosen substances
  //     (checks sub1, sub2 and sub2, sub1) using SearchFormula
  // 3. If there is an available formula for two chosen substances, checks
  //     quantity for two chosen substance.
  // If no quantity for two substances, tells user that there is no available quantity
  // If quantity is available, decreases quantity for two chosen substances
  //     from the chemist then increases new substance
  // 4. If there is no available formula, tells user that nothing happens when you try and merge two chosen substances
  // Preconditions - Chemist is populated with substances
  // Postconditions - Increments quantity of substance "made", decreases quantity of source items
void Lab::CombineSubstances() {

    int choice1;    // first element to combine
    int choice2;    // second element to combine
    int index;      // index of formula
    bool inSupply = false;  // checks if chemist has both elements
    Substance combination;  // the compound

    // checks if user has substance first
    if (hasSubstances(m_myChemist)) {

        // calls request substance for both elements
        RequestSubstance(choice1);
        RequestSubstance(choice2);

        // creates substances for both elements
        Substance element1 = m_myChemist.GetSubstance(choice1);
        Substance element2 = m_myChemist.GetSubstance(choice2);

        index = SearchFormulas(element1.m_formula, element2.m_formula);

        // checks if chemist has both elements
        if (m_myChemist.CheckQuantity(element1, element2)) {
            inSupply = true;
        }

        // inSupply is true and index was a valid compound
        if (inSupply && index != -1) {

                // decrements the quantity of both elements
                m_myChemist.DecrementQuantity(element1);
                m_myChemist.DecrementQuantity(element2);

                combination = m_substances[index];

                // increments the quantity of the compound
                m_myChemist.IncrementQuantity(combination);

                cout << element1.m_name << " combined with " << element2.m_name << " to make " << combination.m_name << "!" << endl;
                cout << "Your chemist has built " << combination.m_name << "." << endl;
            }
            else if (!inSupply) {
                cout << "No available quantity" << endl;
            }
            else if (index == -1) {
                cout << "Cannot combine " << element1.m_name << " and " << element2.m_name << endl;
            }

    } else {
        cout << "You have no substances" << endl;
    }
}


// Name: RequestSubstance()
  // Desc - Allows the user to choose a substance to try and merge.
  //        Returns the index of chosen substance
  // Preconditions - Chemist has substances to try and merge
  // Postconditions - Returns integer of substance selected by user
void Lab::RequestSubstance(int &choice) {

    bool run = true;    // run loop
    int input;          // input element to combine

    while (run) {
        cout << "Which substances would you like to merge?" << endl;
        cout << "To list known substances enter -1 " << endl; 
        cin >> input;
        cout << endl;

        // if input is -1 then display all substances
        if (input == -1) {
            DisplaySubstances();
        }
        // checks if input is between 
        else if (input <= NUM_OF_ELEMENTS && input > 0) {
            choice = input - 1;
            run = false;
        }
        else {
            cout << "Invalid Element" << endl;
        }
    }
}


// Name: SearchFormula()
  // Desc - Searches formulas for two strings (name of item)
  // Preconditions - m_substances is populated
  // Postconditions - Returns int index of matching formula
int Lab::SearchFormulas(string formula1, string formula2) {
    
    Substance substance;    // makes a substance

    // substance is equal to all substances
    for (int i = 0; i < PROJ2_SIZE; i++) {
        substance = m_substances[i];

        // finds the compunds in the array
        if (substance.m_type == "compound") {

            // checks to match the required elements to the formula, returns matched index
            if ((substance.m_substance1 == formula1 && substance.m_substance2 == formula2) 
                || (substance.m_substance2 == formula1 && substance.m_substance1 == formula2)) {
                return i;
            }
        }
    }
    // if there was no match
    return -1;
}

// Name: CalcScore()
  // Desc - Displays current score for Chemist
  // Preconditions - Chemist is populated with substances
  // Postconditions - Displays total number of substances found. Displays
  //        percentange found as number found divided by total available
void Lab::CalcScore() {

    // checks if chemist has substances first
    if (hasSubstances(m_myChemist)) {
        cout << "***The Chemist***" << endl;
        cout << "The Great Chemist " << m_myChemist.GetName() << endl;
        cout << "There are " << PROJ2_SIZE << " substances to find" << endl;

        // number of found substances
        cout << "You have found " << m_myChemist.GetTotalSubstances() << " so far" << endl;

        // calculates the score
        cout << "This is " << ((double)(m_myChemist.GetTotalSubstances()) / (double)PROJ2_SIZE) * 100 << " %" << endl;
    } else {
        cout << "You have no substances" << endl;
    }
}
