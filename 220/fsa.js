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
      }
    }
  }
}



class FSA {
  constructor(transitions) {
    let currentState = new State();
    let arrayOfStates = [];

    function createState(name, transitions) {
      let newState = new State();
      newState.setName(name);
      transitions.map(function(transition) {
        // This extracts input and state from { input: state } as strings
        const input = Object.keys(transition)[0];
        const state = lib220.getProperty(transition, input).value;
        newState.addTransition(input, state);
      });

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
    }

    this.where = () => currentState.getName();
    this.change = function(input) {
      let a = arrayOfStates
        .filter((state) => state.getName() === currentState.nextState(input));
      if (a.length === 1) { currentState = a[0]; }
      return this;
    }
    this.f = () => arrayOfStates;

    transitions.map(function(element) {
      createState(element[0], element.slice(1, element.length));
    });
  }
}


let t0 = {};
let t1 = {};
lib220.setProperty(t0, "0", "t0");
lib220.setProperty(t1, "1", "t1");
let fsa = new FSA([["t0", t0, t1], ["t1", t0, t1]]);
console.log(fsa.change("1").where());