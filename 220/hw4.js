/*
 * Kevin Vicente
 * March 28, 2020
 * This is the program for the fourth homework assignment.
 */

class FluentRestaurants {
  constructor (jsonData) {
    this.data = jsonData;
  }

  // fromState(stateStr: string) => FluentRestaurants
  fromState(stateStr) {
    return new FluentRestaurants(this.data.filter((obj) => obj.state === stateStr));
  }

  // ratingLeq(rating: number) => FluentRestaurants
  ratingLeq(rating) {
    return new FluentRestaurants(this.data.filter((obj) => obj.stars <= rating));
  }

  // ratingGeq(rating: number) => FluentRestaurants
  ratingGeq(rating) {
    return new FluentRestaurants(this.data.filter((obj) => obj.stars >= rating));
  }

  // category(categoryStr: string) => FluentRestaurants
  category(categoryStr) {
    return new FluentRestaurants(this.data.filter(function(obj) {
      // Filter the categories list for each object, checking if it contains categoryStr
      return obj.categories.reduce((categoryFound, nextCategory) =>
        categoryFound || categoryStr === nextCategory,
      false);
    }));
  }

  // hasAmbience(ambienceStr: string) => FluentRestaurants
  hasAmbience(ambienceStr) {
    return new FluentRestaurants(this.data.filter(function(obj) {
      // Get the ambience value if it's there, and return it
      const ambiences = lib220.getProperty(obj.attributes, "Ambience");
      if (!ambiences.found) { return false; }
      else {
        const ambience = lib220.getProperty(ambiences.value, ambienceStr);
        if (!ambience.found) { return false; }
        else { return ambience.value; }
      }
    }));
  }

  // bestPlace() => Restaurant
  bestPlace() {
    if (this.data.length === 0) { return {}; }
    // Find the restaurant with the greatest rating and review count, prioritized in that order
    return this.data.reduce(function(restaurant, next) {
      if (next.stars > restaurant.stars) { return next; }
      else if (next.stars === restaurant.stars) {
        if (next.review_count > restaurant.review_count) { return next; }
        else { return restaurant; }
      } else { return restaurant; }
    }, this.data[0]);
  }
}


/* For reference:
type Restaurant = {
  name: string,
  city: string,
  state: string,
  stars: number,
  review_count: number,
  attributes: {} | {
    Ambience: {
      [key: string]: boolean
    }
  },
  categories: string[]
}
*/

const testData =
[
  {
     name: "Restaurant1",
     city: "City1",
     state: "State1",
     stars: 3,
     review_count: 10,
     attributes: {
       Ambience: {
         casual: true,
         upscale: false
       }
     },
     categories: ["Restaurants", "Casual"]
  },
  {

     name: "Restaurant2.1",
     city: "City2",
     state: "State2",
     stars: 5,
     review_count: 3,
     attributes: {
       Ambience: {
         casual: false,
         upscale: true
       }
     },
     categories: ["Restaurants", "Upscale"]
  },
  {
     name: "Restaurant2.2",
     city: "City2",
     state: "State2",
     stars: 5,
     review_count: 8,
     attributes: {},
     categories: ["Restaurants"]
  }
];
const fr = new FluentRestaurants(testData);

// Tests below
test("state filtering", function() {
  const filtered = fr.fromState("State2").data;
  assert(filtered.length === 2);
  assert(filtered[0].state === "State2");
  assert(filtered[1].state === "State2");
});

test("rating filtering", function() {
  const filtered1 = fr.ratingGeq(3);
  assert(filtered1.data.length === 3);
  assert(filtered1.data[0].stars === 3);
  const filtered2 = filtered1.ratingLeq(4);
  assert(filtered2.data.length === 1);
  assert(filtered2.data[0].stars === 3);
});

test("category filtering", function() {
  const filtered1 = fr.category("Restaurants");
  assert(filtered1.data.length === 3);
  const filtered2 = filtered1.category("Casual");
  assert(filtered2.data.length === 1);
  assert(filtered2.category("Whatever").data.length === 0);
});

test("ambiance filtering", function() {
  const filtered1 = fr.hasAmbience("casual");
  assert(filtered1.data.length === 1);
  assert(filtered1.data[0].attributes.Ambience.casual);
  const filtered2 = fr.hasAmbience("whatever");
  assert(filtered2.data.length === 0);
});

test("bestPlace selection", function() {
  let testData = [{stars: 3, review_count: 1}, {stars: 5, review_count: 4}];
  let fr = new FluentRestaurants(testData);
  let choice = fr.bestPlace();

  assert(choice.stars === 5);
  testData[1].stars = 3;
  choice = fr.bestPlace();
  assert(choice.stars === 3 && choice.review_count === 4);
  testData[1].review_count = 1;
  choice = fr.bestPlace();
  assert(choice === testData[0]);
});