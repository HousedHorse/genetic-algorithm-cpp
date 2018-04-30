#include <iostream>
#include <time.h>

#include "Population.h"

using namespace std;

int main(){
  srand(time(NULL));

  Population p(10000, 10);
  cout << p << endl;

  string s = "Hi, this is a test string we want to find with the genetic algorithm.";

  p.evolve(s, true);

}
