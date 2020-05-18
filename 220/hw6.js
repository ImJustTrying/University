/*
 * Kevin Vicente
 * April 2020
 */

 // Returns a number k in [min,max)
function randomInt(min, max) {
  return Math.floor(Math.random() * (max - min)) + min;
}

class State {
  constructor() {
    let name = "";
    let transitions = [];

    this.getName = () => name;
    this.setName = function(newName) {
      name = newName;
      return this;
    }

    this.addTransition = function(input, to) {
      let transition = {};
      lib220.setProperty(transition, input, to);
      transitions.push(transition);
      return this;
    }

    this.nextState = function(input) {
      let trans = transitions.filter(function(transition) {
        let next = lib220.getProperty(transition, input);
        return next.found;
      });

      if (trans.length === 0) {
        return "";
      } else if (trans.length === 1) {
        return lib220.getProperty(trans[0], input).value;
      } else {
        return lib220.getProperty(trans[randomInt(0, trans.length)], input).value;
      }
    }
  }
}


// Don't know why this is a class...
class Memento {
  constructor() {
    let state = new State();
    this.getState = () => state;
    this.storeState = (newState) => state = newState;
  }
}


class FSA {
  constructor() {
    let currentState = new State();
    let arrayOfStates = [];

    this.createState = function(name, transitions) {
      let newState = new State();
      newState.setName(name);
      for (let i = 0; i < transitions.length; i += 1) {
        // This extracts input and state from { input: state } as strings
        const input = Object.keys(transitions[i])[0];
        const state = lib220.getProperty(transitions[i], input).value;
        newState.addTransition(input, state);
      }

      if (arrayOfStates.length === 0) {
        currentState = newState;
      }

      let s = arrayOfStates.filter((state) => state.getName() === name);
      if (s.length === 0) {
        arrayOfStates.push(newState);
      } else {
        let i = arrayOfStates.indexOf(s[0]);
        arrayOfStates[i] = newState;
        if (currentState.getName() === name) {
          currentState = newState;
        }
      }

      return this;
    }

    this.getStateDescription = () => currentState.getName();
    this.createMemento = function() {
      let memento = new Memento();
      memento.storeState(currentState);
      return memento;
    }

    this.restoreMemento = function(memento) {
      currentState = memento.getState();
      return this;
    }

    this.nextState = function(input) {
      let name = currentState.nextState(input);
      let state = arrayOfStates.filter((state) => state.getName() === name);
      if (state.length === 1) {
        currentState = state[0];
      }
      return this;
    }
  }
}



test("State.nextState deterministic & nondeterministic", function() {
  let state = new State();
  state.addTransition("0", "s0");
  state.addTransition("1", "s1");
  assert(state.nextState("0") === "s0");
  assert(state.nextState("1") === "s1");

  state.addTransition("1", "s2");
  let s1_count = 0;
  let s2_count = 0;
  for (let i = 0; i < 10; i += 1) {
    let next = state.nextState("1");
    if (next === "s1") { s1_count += 1; }
    else if (next === "s2") { s2_count += 1; }
  }
  assert(s1_count > 0 && s2_count > 0);
});

test("FSA.nextState valid & undefined inputs", function() {
  let fsa = new FSA();
  let t0 = {};
  let t1 = {};
  lib220.setProperty(t0, "0", "s0");
  lib220.setProperty(t1, "1", "s1");

  fsa.createState("s0", [t0, t1]);
  fsa.createState("s1", [t0, t1]);
  assert(fsa.nextState("0").getStateDescription() === "s0");
  assert(fsa.nextState("1").getStateDescription() === "s1");
  assert(fsa.nextState("A").getStateDescription() === "s1");
});

test("FSA.createState redefining states", function() {
  let fsa = new FSA();
  let transitions = [{},{},{},{}];
  lib220.setProperty(transitions[0], "0", "s0");
  lib220.setProperty(transitions[1], "1", "s1");
  lib220.setProperty(transitions[2], "0", "s1");
  lib220.setProperty(transitions[3], "1", "s0");

  fsa.createState("s0", [transitions[0], transitions[1]]);
  fsa.createState("s1", [transitions[0], transitions[1]]);

  assert(fsa.nextState("0").getStateDescription() === "s0");
  assert(fsa.nextState("1").getStateDescription() === "s1");

  fsa.createState("s0", [transitions[2], transitions[3]]);

  // Move to s0
  fsa.nextState("0");
  assert(fsa.nextState("1").getStateDescription() === "s0");
  assert(fsa.nextState("0").getStateDescription() === "s1");
});

test("FSA memento", function() {
  let fsa = new FSA();
  let transitions = [{},{},{},{}];
  lib220.setProperty(transitions[0], "0", "s0");
  lib220.setProperty(transitions[1], "1", "s1");
  lib220.setProperty(transitions[2], "0", "s1");
  lib220.setProperty(transitions[3], "1", "s0");

  fsa.createState("s0", [transitions[0], transitions[1]]);
  fsa.createState("s1", [transitions[0], transitions[1]]);

  let memento = fsa.createMemento();
  fsa.nextState("1");
  assert(fsa.getStateDescription() === "s1");
  fsa.restoreMemento(memento);
  assert(fsa.getStateDescription() === "s0");

  // Change the transitions on the s0 state
  fsa.createState("s0", [transitions[2], transitions[3]]);
  assert(fsa.nextState("0").getStateDescription() === "s1");
  fsa.restoreMemento(memento);
  assert(fsa.getStateDescription() === "s0");
  assert(fsa.nextState("0").getStateDescription() === "s0");
});