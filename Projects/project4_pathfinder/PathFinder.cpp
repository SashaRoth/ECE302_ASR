#include "PathFinder.hpp"
#include <stdexcept>
#include <cstdlib>
#include <iostream>

PathFinder::PathFinder(const Image<Pixel> &img)
{
    load(img);
}

PathFinder::~PathFinder()
{
    clear();
}

void PathFinder::load(const Image<Pixel> &img)
{
    checkImage(img);
    image = img;
    explored.assign(image.height(), std::vector<bool>(image.width(), false));
    Pixel curr;                                 
    for(int i = 0; i<image.height(); i++){
       for(int j = 0; j<image.width(); j++){
            curr = image(i, j);
            if(curr == RED){
            initial = Coord(i, j);
           }
        }
    }
    return;
}

void PathFinder::clear()
{
   while(!actions.isEmpty()){
    actions.dequeue();
   }
   image = Image<Pixel>();
   initial = Coord();
   final = Coord();
   explored.assign(image.height(), std::vector<bool>(image.width(), false));
   return; // TODO
}

void PathFinder::checkImage(const Image<Pixel> &img) const
{
    Pixel curr;
    int redcount = 0;
    for(int i = 0; i<img.height(); i++){
        for(int j = 0; j<img.width(); j++){
           curr = img(i, j);
           if(curr == RED){
            redcount++;
           }
           else if(curr != BLACK && curr != WHITE){
            throw std::invalid_argument("Image cannot contain non-black/white/red pixels");
           }
        }
    }
    if(redcount != 1){
        throw std::invalid_argument("Image must contain exactly one red pixel");
    }
    return;
}

Coord PathFinder::getStart() const
{
    return initial;
}

Coord PathFinder::getEnd() const
{
    return final;
}

void PathFinder::findPath(const std::string &strategy)
{
   if(isEnd(initial)){  //check if the initial pixel is the exit
    image(initial.row, initial.col) = GREEN;
    final = initial;
    return;
   } 
   Coord next;
   Coord curr;
   char direction;
   actions.enqueue(initial);
   explored[initial.row][initial.col] = true; //mark start as explored

   while(true){
    if(actions.isEmpty()){ //if there are no potential actions, no exit found
        throw std::runtime_error("No exit found");
    }

    curr = actions.peekFront(); //make the current state the first coord in queue
    actions.dequeue();

    for(int i = 0; i < 4; i++){
        direction = strategy[i];

        switch(direction){
            case 'N':
                next = Coord(curr.row-1, curr.col);
                break;
            case 'S':
                next = Coord(curr.row+1, curr.col);
                break;
            case 'W':
                next = Coord(curr.row, curr.col-1);
                break;
            case 'E':
                next = Coord(curr.row, curr.col+1);
                break;
        }

        if(next.col < 0 || next.col >= image.width() || next.row < 0 || next.row >= image.height()){ //bounds checking
            ;
        }
        else if(image(next.row, next.col) == BLACK){ //if the next pixel is a border, skip it
            ;
        }
        else if(explored[next.row][next.col]){ //if the next pixel has already been explored, skip it
            ;
        }
        else{
            next.link(curr); //next node is either the exit or a valid action; link its parent for backtracking

            if(isEnd(next)){ //if the next pixel is the exit, mark it as green
                image(next.row, next.col) = GREEN;
                final = next;
                backtrack(next);
                return;
            }
            else{ //if neither applies, add the pixel to the queue
                actions.enqueue(next);
                explored[next.row][next.col] = true;
                image(next.row, next.col) = BLUE;
            } 
        }
    }
   }
}

// BONUS: Same BFS as findPath(), plus GIF visualization
void PathFinder::findPathWithVisualization(const std::string &outfile, int frame_duration, int frame_gap, const std::string &strategy)
{
    // --- GIF setup (do not modify) ---
    int cell_size = 1; // each maze cell maps to a 1x1 pixel; increase for a larger GIF
    int gif_height = image.height() * cell_size;
    int gif_width = image.width() * cell_size;

    int frame_counter = 0; // tracks BFS steps; write a frame every frame_gap steps

    GifWriter gif;
    if (!GifBegin(&gif, (outfile + ".gif").c_str(), gif_width, gif_height, frame_duration, 8, true))
    {
        throw std::runtime_error("Failed to create GIF file.");
    }

    // ========================== BONUS TODO ==========================
    // This function is identical to findPath(), with three additions for visualization.
    // Copy your BFS logic from findPath() and add the following:
    //
    // --- Addition 1: Record each explored cell as a frame ---
    //   After you mark a coordinate as visited (e.g., color it BLUE), increment frame_counter.
    //   When frame_counter reaches frame_gap, write a frame and reset the counter:
    //
    //       frame_counter++;
    //       if (frame_counter >= frame_gap) {
    //           addFrameToGif(gif, frame_duration);
    //           frame_counter = 0;
    //       }
    //
    // --- Addition 2: Save the final image to a PNG ---
    //   After marking the solution path (GREEN exit, YELLOW path), write:
    //
    //       writeToFile(image, outfile + "_final_visual.png");
    //
    // --- Addition 3: Close the GIF before every exit point ---
    //   Before every return or throw in this function, you MUST call:
    //
    //       GifEnd(&gif);
    //
    //   This includes the normal success path AND the no-path-found error path.
    // ===========================================================

    GifEnd(&gif);
}

// Converts the current state of `image` into an RGBA pixel buffer and appends it as one GIF frame.
void PathFinder::addFrameToGif(GifWriter &gif, int frame_duration)
{
    int cell_size = 1; // each maze cell maps to a 1x1 pixel; increase for a larger GIF
    int gif_height = image.height() * cell_size;
    int gif_width = image.width() * cell_size;

    // Allocate RGBA buffer (4 bytes per pixel)
    std::vector<uint8_t> rgb_data(gif_height * gif_width * 4);

    // Map each maze cell's Pixel constant to an RGB color
    for (int r = 0; r < image.height(); ++r)
    {
        for (int c = 0; c < image.width(); ++c)
        {
            Pixel color;
            if (image(r, c) == WHITE)
            {
                color = {255, 255, 255};
            }
            else if (image(r, c) == BLACK)
            {
                color = {0, 0, 0};
            }
            else if (image(r, c) == RED)
            {
                color = {255, 0, 0};
            }
            else if (image(r, c) == GREEN)
            {
                color = {0, 255, 0};
            }
            else if (image(r, c) == BLUE)
            {
                color = {0, 0, 255};
            }
            else if (image(r, c) == YELLOW)
            {
                color = {255, 255, 0};
            }
            else
            {
                color = {0, 0, 0}; // default: treat unknown pixels as black
            }

            // Write this cell's color into the RGBA buffer (scaled by cell_size)
            for (int i = 0; i < cell_size; ++i)
            {
                for (int j = 0; j < cell_size; ++j)
                {
                    int pixel_row = r * cell_size + i;
                    int pixel_col = c * cell_size + j;
                    int index = (pixel_row * gif_width + pixel_col) * 4;
                    rgb_data[index + 0] = color.red;
                    rgb_data[index + 1] = color.green;
                    rgb_data[index + 2] = color.blue;
                    rgb_data[index + 3] = 255; // fully opaque
                }
            }
        }
    }

    // Append the completed frame to the GIF
    GifWriteFrame(&gif, rgb_data.data(), gif_width, gif_height, frame_duration, 8, true);
}

// Writes the current image (with any path markings) to a PNG file.
void PathFinder::writeSolutionToFile(const std::string &filename)
{
    writeToFile(image, filename);
}

bool PathFinder::isEnd(const Coord &potential) const
{
    if(potential.col < 0 || potential.col >= image.width() || 
        potential.row < 0 || potential.row >= image.height()){ //bounds checking
            return false;
        }
    if(image(potential.row, potential.col) == WHITE){
        if(potential.row == 0 || potential.row == (image.height() - 1)){
            return true;
        }
        if(potential.col == 0 || potential.col == (image.width() - 1)){
            return true;
        }
    }
    return false;
}

void PathFinder::backtrack(Coord end)
{
    Coord curr = end;
    Coord prev = curr.get_parent();
    while(prev != initial){
        image(prev.row, prev.col) = YELLOW;
        curr = prev;
        prev = curr.get_parent();
    }
    return;
}

// Returns true if both images have GREEN pixels at exactly the same coordinates.
// Ignores differences between non-GREEN pixels (e.g., BLUE vs WHITE visited markings).
bool compareImagesExit(const std::string &img1_str, const std::string &img2_str)
{
    Image<Pixel> img1 = readFromFile(img1_str);
    Image<Pixel> img2 = readFromFile(img2_str);
    if (img1.width() != img2.width() || img1.height() != img2.height())
    {
        return false;
    }
    for (int r = 0; r < img1.height(); ++r)
    {
        for (int c = 0; c < img1.width(); ++c)
        {
            if (img1(r, c) != img2(r, c) && (img1(r, c) == GREEN || img2(r, c) == GREEN))
            {
                return false;
            }
        }
    }
    return true;
}

// Returns true if every pixel in both images is identical (exact match).
bool compareImages(const std::string &img1_str, const std::string &img2_str)
{
    Image<Pixel> img1 = readFromFile(img1_str);
    Image<Pixel> img2 = readFromFile(img2_str);
    if (img1.width() != img2.width() || img1.height() != img2.height())
    {
        return false;
    }
    for (int r = 0; r < img1.height(); ++r)
    {
        for (int c = 0; c < img1.width(); ++c)
        {
            if (img1(r, c) != img2(r, c))
            {
                return false;
            }
        }
    }
    return true;
}