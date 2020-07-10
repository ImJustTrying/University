/*
 * Kevin Vicente
 * April 07, 2020
 *
 * This is the interpreter implementation specified in the homework 5 document.
 */

// interpExpression(state: State, expr: Expr) => number | boolean
function interpExpression(state, expr) {
  //console.log(expr.kind);
  switch (expr.kind) {
    case "operator": {
      const e1 = interpExpression(state, expr.e1);
      const e2 = interpExpression(state, expr.e2);

      // Type check
      if (e1 === undefined || e2 === undefined) { return undefined; }
      if (typeof(e1) !== typeof(e2)) {
        console.log("Error: operation \"" + expr.op + "\" is not defined on types \""
          + typeof(e1) + "\" and \"" + typeof(e2) + "\"");
        return undefined;
      }

      switch (expr.op) {
        case "+": return e1 + e2;
        case "-": return e1 - e2;
        case "*": return e1 * e2;
        case "/": return e1 / e2;
        case "&&": return e1 && e2;
        case "||": return e1 || e2;
        case "<": return e1 < e2;
        case ">": return e1 > e2;
        case "===": return e1 === e2;
        default: console.log("Error: invalid operator \"" + expr.op + "\"");
      }
    } break;

    case "variable": {
      const prop = lib220.getProperty(state, expr.name);
      if (prop.found) { return prop.value; }
      else { console.log("Error: variable \"" + expr.name + "\" not bound"); }
    } break;

    case "number":
    case "boolean": {
      return expr.value;
    } break;

    default: console.log("Error: invalid parser output"); break;
  }

  console.log("end");
  return undefined;
}

// interpStatement(state: State, statement: Stmt) => ()
function interpStatement(state, statement) {
  switch (statement.kind) {
    case "let": {
      // If the name is already bound, throw an error.
      if (lib220.getProperty(state, statement.name).found) {
        console.log("Error: variable \"" + statement.name + "\" already bound");
        return;
      } else {
        lib220.setProperty(state, statement.name, interpExpression(state, statement.expression));
      }
    } break;

    case "assignment": {
      if (!lib220.getProperty(state, statement.name).found) {
        console.log("Error: variable \"" + statement.name + "\" not bound");
        return;
      } else {
        lib220.setProperty(state, statement.name, interpExpression(state, statement.expression));
      }
    } break;

    case "print": {
      console.log(interpExpression(state, statement.expression));
    } break;

    case "while": {
      while (interpExpression(state, statement.test)) {
        statement.body.map((stmt) => interpStatement(state, stmt));
      }
    } break;

    case "if": {
      if (interpExpression(state, statement.test)) {
        statement.truePart.map((stmt) => interpStatement(state, stmt));
      } else {
        statement.truePart.map((stmt) => interpStatement(state, stmt));
      }
    } break;
  }
}

// interpProgram(stmts: Stmt[]) => State
function interpProgram(stmts) {
  let state = {};
  stmts.map((stmt) => interpStatement(state, stmt));
  return state;
}


// Compute 10!
const program = "\
let n = 10;\
let i = 2;\
let product = 1;\
while (i < n || i === n) {\
  product = product * i;\
  i = i + 1;\
}";

test("interpExpression invalid types", function() {
  assert(interpExpression({}, parser.parseExpression("true || 5").value) === undefined);
  assert(interpExpression({x: true}, parser.parseExpression("1 + x").value) === undefined);
  assert(interpExpression({}, parser.parseExpression("3 - 2 + 4 > 5 / true").value) === undefined);
});

test("interpExpression multiple operations", function() {
  assert(interpExpression({x : false}, parser.parseExpression("true || false && x").value) === false);
  assert(interpExpression({x: 1, y:2, z:5}, parser.parseExpression("x + y * z").value) === 11);
});

test("interpExpression unbound variables", function() {
  assert(interpExpression({}, parser.parseExpression("x").value) === undefined);
  assert(interpExpression({y:1}, parser.parseExpression("y + x").value) === undefined);
});

test("interpStatement valid program", function() {
  // Compute 10!
  const parsed_program = parser.parseProgram(program).value;
  let state = {};

  for (let i = 0; i < parsed_program.length; i += 1) {
    interpStatement(state, parsed_program[i]);
    switch (i) {
      case 0: { assert(state.n === 10); } break;
      case 1: { assert(state.i === 2); } break;
      case 2: { assert(state.product === 1); } break;
      // We will have tested the while condition, and ran the body enough times to reach
      // the end of the while loop.
      case 3: {
        assert(state.i === 11);
        assert(state.product === 3628800);
      } break;
    }
  }
});

test("interpProgram valid program", function() {
  const state = interpProgram(parser.parseProgram(program).value);
  assert(state.n === 10);
  assert(state.i === 11);
  assert(state.product === 3628800);
});