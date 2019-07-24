#include "State.h"

State::State() {
  id = 0;
}

State::State(unsigned i) {
  id = i;
}

int State::getID() {
  return id;
}

void State::setID(unsigned i) {
  id = i;
  return;
}

State& State::operator=(const State& s) {
  id = s.id;
  return *this;
}

bool State::operator==(const State& s) {
  if (s.id == id) {
    return true;
  } else {
    return false;
  }
}

bool State::operator!=(const State& s) {
  if (s.id != id) {
    return true;
  } else {
    return false;
  }
}
