#ifndef PUZZLE_SOLVER_HPP
#define PUZZLE_SOLVER_HPP

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include "state.hpp"
#include "frontier_queue.hpp"
#include "puzzle.hpp"
#include "lib/gif.h"

/** @brief Writes a single puzzle state as one frame into an open GIF.
 *  @param gif The GifWriter object to write the frame to.
 *  @param curr The puzzle state to render as a frame.
 *  @param frame_duration Duration of the frame in centiseconds (100 = 1 second). */
void addFrameToGif(GifWriter &gif, const Puzzle &curr, int frame_duration);

/** @brief Demonstrates GIF creation from a hardcoded sequence of puzzle states.
 *  @note Standalone demo utility; does not use any PuzzleSolver state. */
void demoVisualize();

class PuzzleSolver
{
public:
  // Constructor, parameters are the initial and goal puzzles
  PuzzleSolver(const Puzzle &initialPuzzle, const Puzzle &goalPuzzle);

  /** @brief Get the cost of the solution found by the search function. */
  int getSolutionCost() const;

  /** @brief Get the solution path found by the search function.
   *  @return Each puzzle state in the path as a string, in order from initial to goal. */
  std::vector<std::string> getSolutionPath() const;

  /** @brief This function searches for a solution to the puzzle using the A* algorithm.
   *  @return true if a solution was found and false otherwise.
   *  If no solution is found, solution_cost will remain 0 and solution_path will remain empty. */
  bool search();

  void generateGIF(std::vector<Puzzle>);

private:
  Puzzle initial, goal;
  int solution_cost;
  std::vector<Puzzle> solution_path;

  frontier_queue<Puzzle> frontier;
  std::unordered_set<unsigned long long> explored;
  std::unordered_map<unsigned long long, int> frontier_costs;  // Maps puzzle hash to g-cost in frontier
  std::unordered_map<Puzzle, Puzzle> parent_map;
};

#endif