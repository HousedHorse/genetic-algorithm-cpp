#ifndef MEMBER_H
#define MEMBER_H

#include <iostream>

class Member{

  public:
    Member();
    friend std::ostream& operator<<(std::ostream& os, const Member& mem);
    friend class Population;

  private:
    int id;
    std::string DNA;
    int fitness;
    static int newId;

};

#endif
