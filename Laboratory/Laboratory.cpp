//Title: Laboratory.cpp
//Author: Sahil Misbah
//Date: 3/15/2022
//Description: This is the main driver for Laboratory

#include "Lab.h"


#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int main () {
  srand(time(NULL));
  Lab newLab;
  newLab.StartLab();
  return 0;
}
