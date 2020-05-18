/*
 * Kevin Vicente
 * February 2020
 *
 * This is the code for the third homework assignment for 220.
 * First, we define helper functions, then the functions that are specified in the homework document.
 * Tests for helper functions are defined afterwards, and finally we define a main function at the bottom of the script.
 */

// These are helper functions

// Returns a number k in [min,max)
function randomInt(min, max) {
  return Math.floor(Math.random() * (max - min)) + min;
}

// getMatchWithCandidate: (matches: Hire[], candidate: number) => Hire
function getMatchWithCandidate(matches, candidate) {
  let matched = matches.filter((h) => h.candidate === candidate);
  if (matched.length !== 1) { return undefined; }
  return matched[0];
}

// getMatchWithCompany: (matches: Hire[], company: number) => Hire
function getMatchWithCompany(matches, company) {
  let matched = matches.filter((h) => h.company === company);
  if (matched.length !== 1) { return undefined; }
  return matched[0];
}

// getIndexOfMatch: (matches: Hire[], match: Hire) => number
function getIndexOfMatch(matches, match) {
  for (let i = 0; i < matches.length; i += 1) {
    if (matches[i].company === match.company && matches[i].candidate === match.candidate) {
      return i;
    }
  }
  return undefined;
}

// isStableMatch: (company_preferences: number[][], candidate_preferences: number[][],
//                 matches: Hire[], index: number) => boolean
// Returns true iff the matching at matches[index] is stable
// Here, we assume the structure of our parameters are valid -- e.g. the dimensions of the two
// preference matrices are the same, index is in [0, matches.length), etc.
function isStableMatch(company_preferences, candidate_preferences, matches, index) {
  if (index < 0 || index >= matches.length) { return undefined; }
  if (company_preferences.length !== candidate_preferences.length ||
      matches.length !== company_preferences.length) { return undefined; }

  let match = matches[index];
  if (match.company < 0 || match.company >= matches.length ||
      match.candidate < 0 || match.candidate >= matches.length) { return undefined; }
  let company_pref = company_preferences[match.company];
  let candidate_pref = candidate_preferences[match.candidate];

  /*
   * We are going to search through the matched company's preferences, and for each
   * candidate check to see if the candidate prefers the matched company (match.company)
   * over it's current match. We do not check candidates which the matched company does not
   * prefer over it's current match. If we find such a candidate, then we check the matched
   * candidate's preferences for a company that meet the same critera. If we find both of
   * these, then we know the matching of the matched company and candidate is unstable.
   */

  for (let i = 0; i < company_pref.length; i += 1) {
    let candidate = company_pref[i];
    // We know that the company's preference list ordered by descending preference.
    // Thus, if we find our current candidate, we don't consider the remaining 
    // candidates since this company doesn't prefer them to their current match.
    if (candidate === match.candidate) { break; }

    let candidates_pref = candidate_preferences[candidate];
    let candidates_match = undefined;
    {
      let temp = getMatchWithCandidate(matches, candidate);
      if (temp === undefined) { return undefined; }
      candidates_match = temp.company;
    }

    // This will be true iff the candidate wants the matched company over it's current match
    if (candidates_pref.indexOf(match.company) < candidates_pref.indexOf(candidates_match)) {

      // Do the exact same thing with the matched candidate's preferences
      for (let j = 0; j < candidate_pref.length; j += 1) {
        let company = candidate_pref[j];
        if (company === match.company) { break; }
        let companys_pref = company_preferences[company];
        let companys_match = undefined;
        {
          let temp = getMatchWithCompany(matches, company);
          if (temp === undefined) { return undefined; }
          companys_match = temp.candidate;
        }

        if (companys_pref.indexOf(match.candidate) < companys_pref.indexOf(companys_match)) {
          return false;
        }
      }
    }
  }
  return true;
}



// Now we define the functions from the homework document

// generateInput: (n: number) => number[][]
function generateInput(n) {
  // We need to generate n permutations of the naturals from 0 to n-1.
  let preferenceMatrix = [];
  for (let i = 0; i < n; i += 1) {
    // This is an implementation of the Fisher-Yates shuffle.
    let upToN = [];
    let shuffled = [];
    for (let j = 0; j < n; j += 1) { upToN.push(j); }

    while (upToN.length > 0) {
      const k = randomInt(0, upToN.length);
      shuffled.push(upToN[k]);
      upToN.splice(k, 1);
    } // shuffled will be a random permutation of naturals between 0 and n-1.

    preferenceMatrix.push(shuffled);
  }
  return preferenceMatrix;
}

// oracle(f: (number[][], number[][]) => Hire[]) => ()
function oracle(f) {
  const numTests = 20;
  for (let t = 1; t <= numTests; t += 1) {
    const n = 10;
    const companies = generateInput(n);
    const candidates = generateInput(n);
    const hires = f(companies, candidates);

    // Tests below
    test("Size check", function() {
      assert(candidates.length === companies.length);
      assert(hires.length === candidates.length);
    });

    test("All companies and candidates are matched once", function() {
      let companies_matched = [];
      let candidates_matched = [];

      /*
       * First, check that the company/candidate index is valid.
       * Next, check if the company/candidate has already been encountered.
       * If it has, it is an error, since every company/candidate should match to exactly
       * one other candidate/company. Then, push the company/candidate index into the
       * respective "matched" array. This ensures that all of the companies/candidates are
       * not matched more than once.
       */
      for (let i = 0; i < hires.length; i += 1) {
        assert(hires[i].candidate >= 0 && hires[i].candidate < n);
        assert(hires[i].company >= 0 && hires[i].company < n);

        assert(!companies_matched.includes(hires[i].company));
        assert(!candidates_matched.includes(hires[i].candidate));

        candidates_matched.push(hires[i].candidate);
        companies_matched.push(hires[i].company);
      }

      // This will check that every company/candidate index appeared in the solution.
      for (let i = 0; i < companies_matched.length; i += 1) {
        assert(companies_matched.includes(i));
        assert(candidates_matched.includes(i));
      }
    });

    test("Matches are stable", function() {
      for (let i = 0; i < hires.length; i += 1) {
        assert(isStableMatch(companies, candidates, hires, i));
      }
    });
  }
}

// runOracle: (f: (companies: number[][], candidates: number[][]) => Run) => ()
function runOracle(f) {
  const numTests = 20;
  for (let t = 0; t < numTests; t += 1) {
  const n = 10;
  const companies = generateInput(n);
  const candidates = generateInput(n);
  const run = f(companies, candidates);

  test("Run sizes and outputs are valid", function() {
    assert(run.out.length <= n);
    assert(run.trace.length <= 2 * n * n);

    for (let i = 0; i < run.out.length; i += 1) {
      assert(run.out[i].company >= 0 && run.out[i].company < n);
      assert(run.out[i].candidate >= 0 && run.out[i].candidate < n);
    }

    for (let i = 0; i < run.trace.length; i += 1) {
      assert(run.trace[i].from >= 0 && run.trace[i].from < n);
      assert(run.trace[i].to >= 0 && run.trace[i].to < n);
    }
  });

  test("trace order is valid", function() {
    let numCompanyOffers = [];
    let numCandidateOffers = [];

    // numCompanyOffers will keep track of how many offers company i has made at numCompanyOffers[i].
    // All companies start with 0 offers, similarly for numCandidateOffers
    for (let i = 0; i < n; i += 1) {
      numCompanyOffers.push(0);
      numCandidateOffers.push(0);
    }

    for (let i = 0; i < run.trace.length; i += 1) {
      const offer = run.trace[i];
      const proposer = offer.from;
      const proposee = offer.to;

      // The proposer must make an offer to the next person on their preference list, which we find
      // via numCompanyOffers[proposer] if the proposer is the company, and similarly for a candidate.
      if (offer.fromCo) {
        assert(companies[proposer][numCompanyOffers[proposer]] === proposee);
        numCompanyOffers[proposer] += 1;
      } else {
        assert(candidates[proposer][numCandidateOffers[proposer]] === proposee);
        numCandidateOffers[proposer] += 1;
      }
    }
  });

  test("trace produces out", function() {
    // For each offer, update the matchings and after doing so for every available offer, check that
    // the computed matchings and the output provided by the function we are testing are equivalent.
    let matchings = [];
    for (let i = 0; i < run.trace.length; i += 1) {
      const offer = run.trace[i];
      const proposer = offer.from;
      const proposee = offer.to;
      const company = (offer.fromCo) ? proposer : proposee;
      const candidate = (!offer.fromCo) ? proposer : proposee;

      const proposer_matching = (offer.fromCo) ? getMatchWithCompany(matchings, proposer) : getMatchWithCandidate(matchings, proposer);
      assert(proposer_matching === undefined);

      const proposee_matching = (offer.fromCo) ? getMatchWithCandidate(matchings, proposee) : getMatchWithCompany(matchings, proposee);
      if (proposee_matching === undefined) {
        matchings.push({company:company,candidate:candidate});
      } else {
        // Check if the proposee preferes the proposer to it's current match -- if so, switch their matching
        const proposee_preference = (offer.fromCo) ? candidates[proposee] : companies[proposee];
        const proposee_match = (offer.fromCo) ? proposee_matching.company : proposee_matching.candidate;

        if (proposee_preference.indexOf(proposee_match) > proposee_preference.indexOf(proposer)) {
          const index = getIndexOfMatch(matchings, proposee_matching);
          if (offer.fromCo) { matchings[index].company = proposer; }
          else { matchings[index].candidate = proposer; }
        }
      }
    }
    
    // Check that the constructed matchings are the same as the run.out matchings
    assert(matchings.length === run.out.length);
    for (let i = 0; i < matchings.length; i += 1) {
      const index = getIndexOfMatch(run.out, matchings[i]);
      assert(index !== undefined);
      assert(run.out[index].company === matchings[i].company);
      assert(run.out[index].candidate === matchings[i].candidate);
    }
  });
  }
}



// Here we write tests for the helper functions
test("isStableMatch edge cases and invalid input", function() {
  assert(isStableMatch([[]], [[]], [], 0) === undefined);
  assert(isStableMatch([[0]], [[0]], [{company:0, candidate:0}], 0));
  assert(isStableMatch([[0]], [[0]], [{company:1, candidate:1}], 0) === undefined);
});

test("isStableMatch full cases", function() {
  const company_pref = [[0,1], [1,0]];
  const candidate_pref = [[0,1], [1,0]];
  const stable_matching = [{company:0,candidate:0},{company:1,candidate:1}];
  const unstable_matching = [{company:0,candidate:1},{company:1,candidate:0}];

  assert(isStableMatch(company_pref, candidate_pref, stable_matching, 0));
  assert(isStableMatch(company_pref, candidate_pref, stable_matching, 1));
  assert(!isStableMatch(company_pref, candidate_pref, unstable_matching, 0));
  assert(!isStableMatch(company_pref, candidate_pref, unstable_matching, 1));
});

test("generateInput dimensions", function() {
  const n = 5;
  const matrix = generateInput(n);

  assert(matrix.length === n);
  for (let i = 0; i < n; i += 1) {
    assert(matrix[i].length === n);
  }
});

test("generateInput variation", function() {
  const n = 10;
  const matrix1 = generateInput(n);
  const matrix2 = generateInput(n);
  let num_matching = 0;

  for (let i = 0; i < n; i += 1) {
    for (let j = 0; j < n; j += 1) {
      if (matrix1[i][j] === matrix2[i][j]) { num_matching += 1; }
    }
  }
  assert(num_matching < n * n);
});


// Main
function main() {
  const oracleLib = require("oracle");
  oracle(wheat1);
  oracle(chaff1);
  runOracle(oracleLib.traceWheat1);
  runOracle(oracleLib.traceChaff1);
}

main()