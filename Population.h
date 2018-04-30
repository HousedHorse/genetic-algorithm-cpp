#ifndef POPULATION_H
#define POPULATION_H

#include "Member.h"
#include <iostream>
#include <vector>

class Population{

  public:
    Population();
    Population(int _size);
    Population(int _size, int _mr);
    ~Population();
    int getSize();
    int getGeneration();
    int getMR();
    void setMR(int mr);
    void addMembers(int n);
    void evolve(std::string target, bool verbose);
    friend std::ostream& operator<<(std::ostream& os, const Population& pop);

  private:
    int size;
    int generation;
    int mutationRate;
    int id;
    static int newId;
    std::vector<Member*> members;

};

#endif
