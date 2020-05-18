class MemObservable {
  constructor () {
    let observers = [];

    this.subscribe = function(observer) {
      observers.push(observer);
    }

    this.update = function(newValue) {
      observers.map((f) => f(newValue));
    }

    this.memo0 = function(f) {
      let r = { evaluated: false };
      return {
        get: function() {
          if (!r.evaluated) {
            r = { evaluated: true, v: f() }
            observers.map((g) => g(r.v));
          }
          return r.v;
        }
      }
    }
  }
}

function snode(head, tail) {
  return {
    isEmpty: () => false,
    head: () => head,
    tail: () => tail.get()
  };
}

let m = new MemObservable();
m.subscribe((i) => console.log(i.head()));
function grow(n) { return snode(n, m.memo0(() => grow(n + 1))); }
let naturals = grow(0);
for (let i = 0; i < 10; i += 1) { naturals = naturals.tail(); }