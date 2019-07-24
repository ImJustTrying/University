/*
 * Kevin Fernandes
 * December 2017
 *
 * This is a container for an unsigned integer, which is meant to serve both
 * as an identifier and as an index for the array the state belongs to. State
 * names are kept in the Dictionary<string, State> class.
 */

#ifndef STATE_H
#define STATE_H

class State {
private:
  unsigned id;

public:
  class IDError {};

  State(unsigned);
  State();

  int getID();
  void setID(unsigned);

  State& operator=(const State&);
  bool operator==(const State&);
  bool operator!=(const State&);
};

#endif // STATE_H
