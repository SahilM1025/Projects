/*****************************************
** File:    Chemist.cpp
** Project: CMSC 202 Project 2, Spring 2022
** Author:  Sahil Misbah
** Date:    3/15/2022
** Section: 10/11
** E-mail:  sahilm1@gl.umbc.edu 
**
** Contains the Chemist functions for the game.
**
***********************************************/
#include "Chemist.h"
using namespace std;


Chemist::Chemist() {
    m_myName = "beaker";
    m_numSubstances = 0;
}

Chemist::Chemist(string name) {
    SetName(name);
    m_numSubstances = 0;
}


string Chemist::GetName() {
    return m_myName;
}

void Chemist::SetName(string name) {
    m_myName = name;
}

int Chemist::CheckSubstance(Substance newSubstance) {

    // iterates through your substances and checks if substance exists
    // return matched index
    for (int i = 0; i < m_numSubstances; i++) {
        if (m_mySubstances[i].m_name == newSubstance.m_name) {
            return i;
        }
    }
    return -1;
}

void Chemist::AddSubstance(Substance newSubstance) {

    // checks to see if substance exists in your substance list
    if (CheckSubstance(newSubstance) == -1) {
        // Adds substance to list and increments num of substances
        m_mySubstances[m_numSubstances++] = newSubstance;
    }
}

void Chemist::IncrementQuantity(Substance newSubstance) {
    if (CheckSubstance(newSubstance) != -1) {
        m_mySubstances[CheckSubstance(newSubstance)].m_quantity += 1;
    }
}

bool Chemist::DecrementQuantity(Substance newSubstance) {
    if (m_mySubstances[CheckSubstance(newSubstance)].m_quantity > 0) {
        m_mySubstances[CheckSubstance(newSubstance)].m_quantity -= 1;
        return true;
    } else {
        return false;
    }
}

bool Chemist::CheckQuantity(Substance substance1, Substance substance2) {
    if (substance1.m_quantity > 0 && substance2.m_quantity > 0) {
        return true;
    } else {
        return false;
    }
}

Substance Chemist::GetSubstance(int index) {
    return m_mySubstances[index];
}

int Chemist::GetTotalSubstances() {
    int count = 0;
    for (int i = 0; i < PROJ2_SIZE; i++) {
        if (m_mySubstances[i].m_quantity > 0) {
            count += 1;
        }
    }
    return count;
}
