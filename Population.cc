#include <iostream>
#include <iomanip>
#include <algorithm>

#include "Population.h"

using namespace std;

int Population::newId = 1;

Population::Population() : Population(0) {}

Population::Population(int _size) : Population(_size,1) {}

Population::Population(int _size, int _mr) : size(_size), generation(0), id(newId++),
  mutationRate(_mr){

  // init members vector
  members = vector<Member*>(size);

  for(int i = 0; i < size; i++){
    members.at(i) = (new Member());
  }

}

Population::~Population(){

  // delete members
  for(int i = 0; i < size; i++){
    delete members.at(i);
  }

}

int Population::getSize(){ return size; }

int Population::getGeneration(){ return generation; }

int Population::getMR() { return mutationRate; }

void Population::setMR(int n) { mutationRate = n; };

void Population::addMembers(int n){

  for(int i = 0; i < n; i++)
    members.push_back(new Member);

  size += n;

}

void Population::evolve(string target, bool verbose = false){
  generation = 0;

  if(verbose){
    cout << "Preparing to evolve..." << endl;
    cout << "Target = " << target << endl;
    cout << "Press any key to continue..." << endl;
    cin.get();
  }

  bool match = false;
  Member* winner = NULL;

  if(verbose) cout << "Initializing population..." << endl;

  // init loop
  for(int i = 0; i < size; i++){
    // change the size of each member DNA to match the size of the target string
    members.at(i)->DNA.resize(target.size());

    // populate with random junk
    for(int j = 0; j < target.size(); j++){
      members.at(i)->DNA.at(j) = (unsigned char)rand() % 96 + 32;
    }
  }

  if(verbose){
    cout << "Done!" << endl;
    cout << "Evolving..." << endl;
  }

  // evolution loop
  while(!match){
    generation++;

    for(int i = 0; i < size; i++){
      members.at(i)->fitness = 0;

      for(int j = 0; j < target.size(); j++){
        if(members.at(i)->DNA.at(j) == target.at(j)) members.at(i)->fitness++;
      }

      // check to see if we're done
      if(members.at(i)->fitness == target.size()){ match = true; winner = members.at(i); break; }
    }

    if(match) break;

    // sort population by descending fitness
    sort(members.begin(), members.end(), [](Member* const a, Member* b)
        {return a->fitness > b-> fitness;});

    // select two parents to mate
    vector<Member*> parents { members.at(0), members.at(1) };

    // mate and mutate
    for(int i = 0; i < size; i++){
      for(int j = 0; j < target.size(); j++){
        int selection = rand() % parents.size();
        members.at(i)->DNA.at(j) = parents.at(selection)->DNA.at(j);

        // random chance for a mutation
        if (rand() % 1000 < mutationRate) members.at(i)->DNA.at(j)
          = (unsigned char)rand() % 96 + 32;
      }
    }

    if(verbose){
      cout << "----------------------------------" << endl;
      cout << "Generation: " << generation << endl;
      cout << "Two strongest candidates were:" << endl;
      cout << *(parents.at(0)) << endl << *(parents.at(1)) << endl;
      cout << "----------------------------------" << endl;
    }
  }

  cout << "Found a match in generation " << generation << "!" << endl;
  cout << *winner;

}

ostream& operator<<(ostream& os, const Population& pop){

  cout << " ---------------------------"                                    << endl;
  cout << "|    POPULATION: " << setw(10) << setfill('0') << pop.id << " |" << endl;
  cout << setfill(' ');
  cout << " ---------------------------"                                    << endl;
  cout << "| Mutation Rate: " << setw(10) << pop.mutationRate       << " |" << endl;
  cout << "|          Size: " << setw(10) << pop.size               << " |" << endl;
  cout << "|    Generation: " << setw(10) << pop.generation         << " |" << endl;
  cout << " ---------------------------"                                    << endl;

  return os;

}
