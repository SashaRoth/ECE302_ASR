#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE
#include "catch.hpp"

#include "list.hpp"
#include "queue.hpp"
#include "PathFinder.hpp"
#include <chrono>
#include <iostream>

/* Provided test cases */

TEST_CASE("PathFinder: Test minimum requirements on ADT queue and invalid images")
{
    Queue<int> queue;

    REQUIRE(queue.isEmpty());
    queue.enqueue(12);
    REQUIRE_FALSE(queue.isEmpty());

    queue.enqueue(13);
    queue.enqueue(14);

    REQUIRE(queue.peekFront() == 12);
    queue.dequeue();

    REQUIRE(queue.peekFront() == 13);
    queue.dequeue();

    REQUIRE(queue.peekFront() == 14);
    queue.dequeue();
    REQUIRE(queue.isEmpty());
    REQUIRE_THROWS_AS(queue.peekFront(), std::out_of_range);
    REQUIRE_THROWS_AS(queue.dequeue(), std::out_of_range);

    // A simple 3x3 image with an invalid pixel color (BLUE)
    Image<Pixel> img(3, 3);
    img(0, 0) = WHITE;
    img(0, 1) = WHITE;
    img(0, 2) = WHITE;
    img(1, 0) = WHITE;
    img(1, 1) = BLUE;
    img(1, 2) = WHITE;
    img(2, 0) = WHITE;
    img(2, 1) = WHITE;
    img(2, 2) = WHITE;

    REQUIRE_THROWS_AS(PathFinder myFinder(img), std::invalid_argument);

    img(1, 1) = WHITE; // no RED pixel
    REQUIRE_THROWS_AS(PathFinder myFinder(img), std::invalid_argument);

    img(1, 1) = RED; // one RED pixel
    img(1, 2) = RED; // two RED pixels now
    REQUIRE_THROWS_AS(PathFinder myFinder(img), std::invalid_argument);

    img(1, 2) = BLACK; // one RED pixel, one BLACK pixel — valid
    REQUIRE_NOTHROW(PathFinder myFinder(img));

    Image<Pixel> img2 = readFromFile("../tests/maze00_extra_color.png");
    REQUIRE_THROWS_AS(PathFinder myFinder(img2), std::invalid_argument);

    Image<Pixel> img3 = readFromFile("../tests/maze00_no_start.png");
    REQUIRE_THROWS_AS(PathFinder myFinder(img3), std::invalid_argument);

    Image<Pixel> img4 = readFromFile("../tests/maze00_extra_start.png");
    REQUIRE_THROWS_AS(PathFinder myFinder(img4), std::invalid_argument);
}

TEST_CASE("PathFinder: Test basic getStart and getEnd", "[pathfinder]")
{
    // 3x3 image with one RED pixel at (1,1)
    Image<Pixel> img(3, 3);
    img(0, 0) = WHITE;
    img(0, 1) = WHITE;
    img(0, 2) = WHITE;
    img(1, 0) = WHITE;
    img(1, 1) = RED;
    img(1, 2) = WHITE;
    img(2, 0) = WHITE;
    img(2, 1) = WHITE;
    img(2, 2) = WHITE;

    PathFinder myFinder(img);
    REQUIRE(myFinder.getStart() == Coord(1, 1));
    REQUIRE(myFinder.getEnd() == Coord(-1, -1)); // not yet discovered by BFS
}



TEST_CASE("PathFinder: Test helper functions load, clear and checkImage", "[pathfinder]")
{
    Image<Pixel> img = readFromFile("../tests/maze00.png");

    PathFinder myFinder(img);
    REQUIRE_NOTHROW(myFinder.checkImage(img));
    REQUIRE(myFinder.getStart() == Coord(12, 2));

    myFinder.clear();
    REQUIRE(myFinder.getStart() == Coord(-1, -1));

    img(12, 2) = YELLOW; // invalid color
    REQUIRE_THROWS_AS(myFinder.checkImage(img), std::invalid_argument);

    img(12, 2) = WHITE; // no RED pixel
    REQUIRE_THROWS_AS(myFinder.checkImage(img), std::invalid_argument);

    img(12, 2) = RED; // one RED pixel
    img(12, 3) = RED; // two RED pixels now
    REQUIRE_THROWS_AS(myFinder.checkImage(img), std::invalid_argument);

    img(12, 3) = BLACK; // one RED pixel, one BLACK pixel — valid
    REQUIRE_NOTHROW(myFinder.checkImage(img));
}



// Demo of how long it takes to find a path (not included in grader)
TEST_CASE("Demo Pathfinding Duration Test", "[pathfinder]")
{
    Image<Pixel> img0 = readFromFile("../tests/maze00.png");
    REQUIRE_NOTHROW(PathFinder my_solver0(img0));

    PathFinder my_solver(img0);

    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    my_solver.findPath();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time for Pathfinding of maze00: " << elapsed_seconds.count() << "s\n";

    my_solver.writeSolutionToFile("../tests/myoutput00_NSWE.png");
    REQUIRE(compareImagesExit("../tests/output00_NSWE.png", "../tests/myoutput00_NSWE.png"));

    // Clear and reinitialize the solver using a different strategy
    my_solver.clear();
    my_solver.load(img0);
    my_solver.findPath("WENS");
    my_solver.writeSolutionToFile("../tests/myoutput00_WENS.png");
    REQUIRE(compareImagesExit("../tests/output00_WENS.png", "../tests/myoutput00_WENS.png"));

    Image<Pixel> img1 = readFromFile("../tests/maze01.png");
    my_solver.clear();
    my_solver.load(img1);
    // maze01 is unsolvable
    REQUIRE_THROWS_AS(my_solver.findPath(), std::runtime_error);
    my_solver.clear();

    Image<Pixel> img2 = readFromFile("../tests/maze02.png");
    my_solver.load(img2);

    start = std::chrono::steady_clock::now();
    my_solver.findPath();
    end = std::chrono::steady_clock::now();
    elapsed_seconds = end - start;
    std::cout << "Elapsed time for Pathfinding of maze02: " << elapsed_seconds.count() << "s\n";

    my_solver.writeSolutionToFile("../tests/myoutput02_NSWE.png");
    REQUIRE(compareImagesExit("../tests/output02_NSWE.png", "../tests/myoutput02_NSWE.png"));
    my_solver.clear();
}

// Demo of findPathWithVisualization (not included in grader)
TEST_CASE("Demo Pathfinding Gif Creation", "[pathfinder]")
{
    Image<Pixel> img0 = readFromFile("../tests/maze00.png");
    PathFinder my_solver(img0);

    // maze00: small maze, record every BFS step (frame_gap=1), 20ms per frame
    // Produces myoutput00.gif and myoutput00_final_visual.png
    my_solver.findPathWithVisualization("../tests/myoutput00", 20, 1);
    my_solver.clear();

    Image<Pixel> img1 = readFromFile("../tests/maze01.png");
    my_solver.load(img1);
    // maze01: unsolvable — throws, but partial search is still recorded in the GIF
    // Record 1 frame every 50 BFS steps, 5ms per frame
    //REQUIRE_THROWS(my_solver.findPathWithVisualization("../tests/myoutput01", 5, 50));
    my_solver.clear();

    Image<Pixel> img2 = readFromFile("../tests/maze02.png");
    my_solver.load(img2);
    // maze02: larger but solvable, same frame settings as maze01
    my_solver.findPathWithVisualization("../tests/myoutput02", 5, 50);
    my_solver.clear();
}

/* Write your own unit tests here */

//Basic solver functionality

TEST_CASE("queue: Basic operations", "[queue]"){

  Queue<Coord> q;

  REQUIRE(q.isEmpty());

  q.enqueue(Coord(1, 1));
  REQUIRE_FALSE(q.isEmpty());

  q.enqueue(Coord(2, 2));
  q.enqueue(Coord(3, 3));
  q.enqueue(Coord(4, 4));

  REQUIRE(q.peekFront() == Coord(1, 1));

  q.dequeue();
  REQUIRE(q.peekFront() == Coord(2, 2));

  q.dequeue();
  REQUIRE(q.peekFront() == Coord(3, 3));
}

TEST_CASE("checkImage: Invalid image edge cases", "[pathfinder]"){
    Image<Pixel> img_extracolor = readFromFile("../tests/maze00_extra_color.png");
    Image<Pixel> img_extrastart = readFromFile("../tests/maze00_extra_start.png");
    Image<Pixel> img_nostart = readFromFile("../tests/maze00_no_start.png");
    
    //constructor delegates to load, which delegates to checkImage
    REQUIRE_THROWS_AS(PathFinder my_solver(img_extracolor), std::invalid_argument);
    REQUIRE_THROWS_AS(PathFinder my_solver(img_extrastart), std::invalid_argument);
    REQUIRE_THROWS_AS(PathFinder my_solver(img_nostart), std::invalid_argument);

}

TEST_CASE("findPath: Simple maze 00", "[pathfinder]"){
    Image<Pixel> img0 = readFromFile("../tests/maze00.png");
    PathFinder my_solver(img0);
    Coord NSWE_end = Coord(14, 0);
    Coord WENS_end = Coord(10, 0);

    REQUIRE(my_solver.getEnd() == Coord());
    
    my_solver.findPath("NSWE");
    my_solver.writeSolutionToFile("../tests/sashasoutput00_NSWE.png");
    REQUIRE(compareImages("../tests/sashasoutput00_NSWE.png", "../tests/output00_final_visual.png"));
    my_solver.clear();

    my_solver.load(img0);
    my_solver.findPath("WENS");
    my_solver.writeSolutionToFile("../tests/sashasoutput00_WENS.png");
    REQUIRE_FALSE(compareImages("../tests/sashasoutput00_WENS.png", "../tests/output00_final_visual.png")); //using different strategy, image should be different
    my_solver.clear();
}

TEST_CASE("findPath: Maze with no exit 01", "[pathfinder]"){
    Image<Pixel> img1 = readFromFile("../tests/maze01.png");
    PathFinder my_solver(img1);
    
    REQUIRE_THROWS_AS(my_solver.findPath("NSWE"), std::runtime_error);
    my_solver.writeSolutionToFile("../tests/sashasoutput01_NSWE.png");
    REQUIRE(compareImages("../tests/sashasoutput01_NSWE.png", "../tests/output01_final_visual.png"));
    my_solver.clear();

    my_solver.load(img1);
    REQUIRE_THROWS_AS(my_solver.findPath("WENS"), std::runtime_error);
    my_solver.writeSolutionToFile("../tests/sashasoutput01_WENS.png");
    REQUIRE(compareImages("../tests/sashasoutput01_WENS.png", "../tests/output01_final_visual.png")); //in maze with no exit, different strategies yield same image
    my_solver.clear();
}


TEST_CASE("findPath: Big maze 02", "[pathfinder]"){
    Image<Pixel> img2 = readFromFile("../tests/maze02.png");
    PathFinder my_solver(img2);

    REQUIRE(my_solver.getEnd() == Coord());
    
    my_solver.findPath("NSWE");
    my_solver.writeSolutionToFile("../tests/sashasoutput02_NSWE.png");
    REQUIRE(compareImages("../tests/sashasoutput02_NSWE.png", "../tests/output02_final_visual.png"));
    my_solver.clear();

    my_solver.load(img2);
    my_solver.findPath("WENS");
    my_solver.writeSolutionToFile("../tests/sashasoutput02_WENS.png");
    REQUIRE(compareImagesExit("../tests/sashasoutput02_WENS.png", "../tests/output02_final_visual.png")); //different strategy should yield same exit in this case
    my_solver.clear();
}

TEST_CASE("findPath: Second large maze 03", "[pathfinder]"){
    Image<Pixel> img3 = readFromFile("../tests/maze03.png");
    PathFinder my_solver(img3);

    REQUIRE(my_solver.getEnd() == Coord());
    
    my_solver.findPath("NSWE");
    my_solver.writeSolutionToFile("../tests/sashasoutput03_NSWE.png");
    REQUIRE(compareImagesExit("../tests/sashasoutput03_NSWE.png", "../tests/output03_NSWE.png"));
    my_solver.clear();
}

TEST_CASE("findPath: Start on exit", "[pathfinder]"){
    Image<Pixel> img = readFromFile("../tests/maze03.png");
    PathFinder my_solver(img);

    REQUIRE(my_solver.getEnd() == Coord());
    
    my_solver.findPath("NSWE");
    my_solver.writeSolutionToFile("../tests/sashasoutput03_NSWE.png");
    REQUIRE(compareImagesExit("../tests/sashasoutput03_NSWE.png", "../tests/output03_NSWE.png"));
    my_solver.clear();
}