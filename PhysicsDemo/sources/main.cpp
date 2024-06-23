#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

#include "physics_demo_runner.hpp"

constexpr int SCREEN_WIDTH = 1600;
constexpr int SCREEN_HEIGHT = 900;

int main()
{
    physics_demo_runner demo(sf::Vector2i(SCREEN_WIDTH, SCREEN_HEIGHT));
    demo.run();
}
