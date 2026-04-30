#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "puzzle_solver.hpp"
#include <chrono>

/* Frontier queue tests start here*/
TEST_CASE("Simple push and pop test", "[frontier_queue]")
{
  frontier_queue<char> fq;
  REQUIRE(fq.empty());
  fq.push('A', 0, 1);
  REQUIRE_FALSE(fq.empty());
  REQUIRE(fq.contains('A'));

  frontier_queue<char> fq2;
  fq2.push('B', 1, 1);
  State<char> state = fq2.pop();
  REQUIRE(state.getValue() == 'B');
  REQUIRE(state.getPathCost() == 1);
  REQUIRE(state.getFCost() == 2);
  REQUIRE(fq2.empty());
}

TEST_CASE("Simple contains and replaceif test", "[frontier_queue]")
{
  frontier_queue<char> fq;
  REQUIRE_FALSE(fq.contains('A'));
  REQUIRE_FALSE(fq.contains('B'));
  fq.push('A', 1, 1);
  fq.push('B', 2, 2);
  fq.pop();
  REQUIRE_FALSE(fq.contains('A'));
  REQUIRE(fq.contains('B'));
  REQUIRE_FALSE(fq.contains('C'));

  frontier_queue<char> fq2;
  fq2.push('A', 100, 100);
  fq2.replaceif('A', 1);
  State<char> state = fq2.pop();
  REQUIRE(state.getValue() == 'A');
  REQUIRE(state.getPathCost() == 1);
  REQUIRE(state.getFCost() == 101);

  frontier_queue<char> fq3;
  fq3.push('A', 1, 100);
  fq3.replaceif('A', 50);
  State<char> state2 = fq3.pop();
  REQUIRE(state2.getPathCost() == 1);
}

// Heap reordering and edge cases test
TEST_CASE("Frontier queue heap reordering and edge cases", "[frontier_queue]")
{
  frontier_queue<int> fq;

  // Test 1: Push multiple items and verify min-heap property is maintained
  fq.push(1, 5, 10);  // f = 15
  fq.push(2, 3, 15);  // f = 18
  fq.push(3, 2, 20);  // f = 22
  fq.push(4, 8, 5);   // f = 13 (should be root)
  fq.push(5, 1, 25);  // f = 26

  // Pop in order and verify we get minimum f-cost each time
  State<int> first = fq.pop();
  REQUIRE(first.getValue() == 4);
  REQUIRE(first.getFCost() == 13);

  State<int> second = fq.pop();
  REQUIRE(second.getValue() == 1);
  REQUIRE(second.getFCost() == 15);

  State<int> third = fq.pop();
  REQUIRE(third.getValue() == 2);
  REQUIRE(third.getFCost() == 18);

  // Test 2: replaceif with heap reordering (update to lower cost)
  frontier_queue<int> fq2;
  fq2.push(10, 100, 50);  // f = 150
  fq2.push(20, 40, 60);   // f = 100
  fq2.push(30, 200, 10);  // f = 210

  // Update 10's cost from 100 to 5 (f should become 55)
  fq2.replaceif(10, 5);

  // Pop and verify 10 is now the minimum
  State<int> updated = fq2.pop();
  REQUIRE(updated.getValue() == 10);
  REQUIRE(updated.getPathCost() == 5);
  REQUIRE(updated.getFCost() == 55);

  // Test 3: replaceif does nothing when new cost is not lower
  frontier_queue<int> fq3;
  fq3.push(100, 50, 50);  // f = 100
  fq3.replaceif(100, 100); // Try to update with same cost
  State<int> unchanged = fq3.pop();
  REQUIRE(unchanged.getPathCost() == 50); // Should still be original

  frontier_queue<int> fq4;
  fq4.push(200, 30, 40);  // f = 70
  fq4.replaceif(200, 80); // Try to update with higher cost
  State<int> unchanged2 = fq4.pop();
  REQUIRE(unchanged2.getPathCost() == 30); // Should still be original

  // Test 4: Complex heap scenario with multiple levels
  frontier_queue<char> fq5;
  fq5.push('A', 10, 5);   // f = 15
  fq5.push('B', 3, 12);   // f = 15 (tie)
  fq5.push('C', 1, 10);   // f = 11 (minimum)
  fq5.push('D', 20, 0);   // f = 20
  fq5.push('E', 5, 8);    // f = 13

  // Pop all and verify order
  std::vector<char> pop_order;
  std::vector<int> f_costs;
  while (!fq5.empty()) {
    State<char> s = fq5.pop();
    pop_order.push_back(s.getValue());
    f_costs.push_back(s.getFCost());
  }

  // Verify f-costs are in non-decreasing order
  for (size_t i = 1; i < f_costs.size(); i++) {
    REQUIRE(f_costs[i] >= f_costs[i-1]);
  }
  REQUIRE(pop_order[0] == 'C');  // f = 11

  // Test 5: replaceif on a deep heap and verify structure
  frontier_queue<int> fq6;
  fq6.push(1, 50, 50);   // f = 100
  fq6.push(2, 40, 40);   // f = 80
  fq6.push(3, 30, 30);   // f = 60
  fq6.push(4, 60, 20);   // f = 80
  fq6.push(5, 70, 10);   // f = 80

  // Update node 1 to have very low f-cost
  fq6.replaceif(1, 5);   // f becomes 55

  State<int> should_be_one = fq6.pop();
  REQUIRE(should_be_one.getValue() == 1);
  REQUIRE(should_be_one.getFCost() == 55);
}

TEST_CASE("Simple hash test", "[puzzle]")
{
  Puzzle p1, p2, p3;
  p1.fromString("876543210");
  p2.fromString("012345678");
  p3.fromString("102345678");
  REQUIRE(p2.hash() == 305419896ULL);
  REQUIRE(p1.hash() != p3.hash());
}


TEST_CASE("Simple operator== and operator!= test", "[puzzle]")
{
  Puzzle p1, p2, p3;
  p1.fromString("012345678");
  p2.fromString("012345678");
  p3.fromString("102345678");
  REQUIRE(p1 == p2);
  REQUIRE_FALSE(p1 == p3);
  REQUIRE(p1 != p3);
  REQUIRE_FALSE(p1 != p2);
}



TEST_CASE("Simple heuristic test", "[puzzle]")
{
  Puzzle goal, p1, p2, p3;
  goal.fromString("012345678");
  p1.fromString("012345678");
  p2.fromString("102345678");
  p3.fromString("120345678");
  REQUIRE(p1.heuristic(goal) == 0);
  REQUIRE(p2.heuristic(goal) == 1);
  REQUIRE(p3.heuristic(goal) == 2);
}

TEST_CASE("Simple search test cost 0", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456780"));
  REQUIRE(puzzle2.fromString("123456780"));
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 0);
    REQUIRE(solver.getSolutionPath().size() == 1);
  }
  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 0);
    REQUIRE(solver.getSolutionPath().size() == 1);
  }
}

TEST_CASE("Simple search test cost 1", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456708")); // blank at (2,1) — one RIGHT from goal
  REQUIRE(puzzle2.fromString("123456780")); // blank at (2,2) — goal
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 1);
    REQUIRE(solver.getSolutionPath().size() == 2);
    std::vector<std::string> expected_path = {"123456708", "123456780"};
    REQUIRE(solver.getSolutionPath() == expected_path);
  }
  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 1);
    REQUIRE(solver.getSolutionPath().size() == 2);
    std::vector<std::string> expected_path = {"123456780", "123456708"};
    REQUIRE(solver.getSolutionPath() == expected_path);
  }
}



TEST_CASE("Simple search test cost 2", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456078")); // blank at (2,0) — two RIGHTs from goal
  REQUIRE(puzzle2.fromString("123456780")); // blank at (2,2) — goal
  {
    PuzzleSolver solver(puzzle1, puzzle2);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 2);
    REQUIRE(solver.getSolutionPath().size() == 3);
    std::vector<std::string> expected_path = {"123456078", "123456708", "123456780"};
    REQUIRE(solver.getSolutionPath() == expected_path);
  }

  { // symmetric case
    PuzzleSolver solver(puzzle2, puzzle1);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 2);
    REQUIRE(solver.getSolutionPath().size() == 3);
    std::vector<std::string> expected_path = {"123456780", "123456708", "123456078"};
    REQUIRE(solver.getSolutionPath() == expected_path);
  }
}


//PuzzleSolver tests start here

/** Two time-consuming tests are given here for your reference. Uncomment them to try locally.
 * The test case of cost 31 should execute within 1 minute locally to avoid timeout on the autograder.*/


TEST_CASE("Time-consuming search test cost 8", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456780"));
  REQUIRE(puzzle2.fromString("012563478"));
  REQUIRE(puzzle1 != puzzle2);
  REQUIRE(puzzle1.heuristic(puzzle2) == 8);

  PuzzleSolver solver(puzzle2, puzzle1);
  REQUIRE(solver.search());
  REQUIRE(solver.getSolutionCost() == 8);
  Puzzle curr = puzzle2;
  int remaining = 8;
  std::vector<Puzzle::Action> actions = {Puzzle::RIGHT, Puzzle::RIGHT, Puzzle::DOWN, Puzzle::LEFT, Puzzle::LEFT, Puzzle::DOWN, Puzzle::RIGHT, Puzzle::RIGHT};
  for (const auto &a : actions)
  {
    std::pair<bool, Puzzle> result = curr.apply(a);
    REQUIRE(result.first);
    curr = result.second;
    remaining -= 1;
    PuzzleSolver inner(curr, puzzle1);
    REQUIRE(inner.search());
    REQUIRE(inner.getSolutionCost() == remaining);
    REQUIRE(curr.heuristic(puzzle1) <= inner.getSolutionCost());
  }
  REQUIRE(curr == puzzle1);
}


TEST_CASE("Time-consuming search test cost 31", "[PuzzleSolver]")
{
  Puzzle puzzle1, puzzle2;
  REQUIRE(puzzle1.fromString("123456780"));
  REQUIRE(puzzle2.fromString("867254301"));
  PuzzleSolver solver(puzzle2, puzzle1);
  auto start = std::chrono::high_resolution_clock::now();
  REQUIRE(solver.search());
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  REQUIRE(solver.getSolutionCost() == 31);
  std::cout << "\n**********************************************************\n"
            << std::endl;
  std::cout << "Time taken to find solutions in the hardest puzzle: " << elapsed.count() << " seconds" << std::endl;
  std::cout << "\n**********************************************************\n"
            << std::endl;
}


// You still need to write your own unit test

//Additional frontier queue edge cases (e.g., replaceif with equal cost, pop order with ties)
TEST_CASE("Frontier queue edge cases", "[frontier_queue]"){
  frontier_queue<char> sashas_fq;
  REQUIRE(sashas_fq.empty());
  State<char> example('A', 0, 1);
  sashas_fq.push('A', 0, 1);

  //searching for nonexistent value with contains()
  REQUIRE_FALSE(sashas_fq.contains('B'));

  //calling getCurrentPathCost() on nonexistent value
  REQUIRE(sashas_fq.getCurrentPathCost('B') == -1);

  //popping from empty frontier
  REQUIRE(sashas_fq.pop().getValue() == example.getValue()); //should pop correctly
  REQUIRE_THROWS_AS(sashas_fq.pop(), std::out_of_range);
}

//Puzzle hash collisions or equality edge cases
TEST_CASE("Puzzle hash collisions", "[puzzle]")
{
  Puzzle sashas_p1, sashas_p2;
  sashas_p1.fromString("012345678");
  sashas_p2.fromString("102345678");
  // Different puzzles should have different hashes
  REQUIRE(sashas_p1.hash() != sashas_p2.hash());
}

//Solver correctness on a puzzle of your choice
TEST_CASE("Solver correctness on random puzzle", "[PuzzleSolver]")
{
  Puzzle sashas_p1, sashas_p2;
  REQUIRE(sashas_p1.fromString("123456780")); // goal
  REQUIRE(sashas_p2.fromString("123456078")); // blank at (2,0), 7 and 8 shifted
  {
    PuzzleSolver solver(sashas_p2, sashas_p1);
    REQUIRE(solver.search());
    REQUIRE(solver.getSolutionCost() == 2);
    // Verify first and last states
    REQUIRE(solver.getSolutionPath().front() == "123456078");
    REQUIRE(solver.getSolutionPath().back() == "123456780");
  }
}