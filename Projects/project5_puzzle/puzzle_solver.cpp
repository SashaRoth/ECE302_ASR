#include "puzzle_solver.hpp"

void addFrameToGif(GifWriter &gif, const Puzzle &curr, int frame_duration)
{
  Image<Pixel> image = curr.toPicture();
  int gif_height = image.height();
  int gif_width = image.width();

  // 4 channels (RGBA)
  std::vector<uint8_t> rgb_data(gif_height * gif_width * 4);

  // convert the image to RGBA format for the GIF
  for (int r = 0; r < image.height(); ++r)
  {
    for (int c = 0; c < image.width(); ++c)
    {
      Pixel color = (image(r, c) == WHITE) ? Pixel{255, 255, 255} : Pixel{238, 142, 139};
      int index = (r * gif_width + c) * 4;
      rgb_data[index + 0] = color.red;
      rgb_data[index + 1] = color.green;
      rgb_data[index + 2] = color.blue;
      rgb_data[index + 3] = 255;
    }
  }

  GifWriteFrame(&gif, rgb_data.data(), gif_width, gif_height, frame_duration, 8, true);
} // end addFrameToGif

void demoVisualize()
{
  Puzzle puzzle_default;
  GifWriter gif;
  Image<Pixel> img = puzzle_default.toPicture();
  int frame_duration = 100; // 100 centiseconds = 1 second
  GifBegin(&gif, "puzzle_solver_output.gif", img.width(), img.height(), frame_duration, 8, true);

  Puzzle puzzle;
  puzzle.fromString("123046758");
  addFrameToGif(gif, puzzle, frame_duration);
  puzzle.fromString("123406758");
  addFrameToGif(gif, puzzle, frame_duration);
  puzzle.fromString("123456708");
  addFrameToGif(gif, puzzle, frame_duration);
  puzzle.fromString("123456780");
  addFrameToGif(gif, puzzle, frame_duration);

  GifEnd(&gif);
} // end demoVisualize

PuzzleSolver::PuzzleSolver(const Puzzle &initialPuzzle, const Puzzle &goalPuzzle)
    : initial(initialPuzzle), goal(goalPuzzle), solution_cost(0)
{
} // end constructor

int PuzzleSolver::getSolutionCost() const
{
  return solution_cost;
}

std::vector<std::string> PuzzleSolver::getSolutionPath() const
{
  std::vector<std::string> result;
  for (const Puzzle &p : solution_path)
    result.push_back(p.toString());
  return result;
}

bool PuzzleSolver::search()
{
  solution_cost = 0;
  solution_path.clear();
  frontier_costs.clear();
  explored.clear();
  parent_map.clear();
  
  std::vector<Puzzle::Action> actions = {Puzzle::LEFT, Puzzle::RIGHT, Puzzle::UP, Puzzle::DOWN};
  frontier.push(initial, 0, initial.heuristic(goal));
  frontier_costs[initial.hash()] = 0;

  State<Puzzle> current = frontier.pop();
  frontier_costs.erase(current.getValue().hash());
  explored.insert(current.getValue().hash());
  
  while(current.getValue() != goal){
    std::vector<Puzzle> neighbors;

    for(Puzzle::Action action : actions){
      std::pair<bool, Puzzle> result = current.getValue().apply(action);
      bool valid = result.first;
      Puzzle nextNeighbor = result.second;

      if(valid && !explored.count(nextNeighbor.hash())){
        neighbors.push_back(nextNeighbor);
      }
    }

    for(Puzzle neighbor : neighbors){
      int neighbor_g = current.getPathCost() + 1;
      int neighbor_h = neighbor.heuristic(goal);
      unsigned long long neighbor_hash = neighbor.hash();

      auto it = frontier_costs.find(neighbor_hash);
      if(it != frontier_costs.end()){
        // Neighbor is already in frontier, update if the current path is better
        if(neighbor_g < it->second) {
          frontier.replaceif(neighbor, neighbor_g);
          frontier_costs[neighbor_hash] = neighbor_g;
          parent_map[neighbor] = current.getValue();
        }
      } else if(!explored.count(neighbor_hash)){
        // Not in frontier, add new to frontier
        frontier.push(neighbor, neighbor_g, neighbor_h);
        frontier_costs[neighbor_hash] = neighbor_g;
        parent_map[neighbor] = current.getValue();
      }
    }

    if(frontier.empty()){
      return false;
    }
    current = frontier.pop();
    frontier_costs.erase(current.getValue().hash());
    explored.insert(current.getValue().hash());
  }

  solution_cost = current.getPathCost();

  Puzzle current_backtrack = current.getValue();
  while(current_backtrack != initial){
    solution_path.push_back(current_backtrack);
    current_backtrack = parent_map.at(current_backtrack);
  }
  solution_path.push_back(initial);
  std::reverse(solution_path.begin(), solution_path.end());

  return true;
}