#include <iostream>
#include <iomanip>

#include "Member.h"

using namespace std;

int Member:: newId = 1;

Member::Member() : id(newId++), DNA(""), fitness(0){}

ostream& operator<<(ostream& os, const Member& mem){
  cout << "MEMBER: " << setw(10) << setfill('0') << mem.id << endl;
  cout << setfill(' ');
  cout << "       DNA: " << mem.DNA     << endl;
  cout << "   Fitness: " << mem.fitness << endl;

  return os;
}
