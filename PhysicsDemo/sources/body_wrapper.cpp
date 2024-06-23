#include "body_wrapper.hpp"
#include "vector_adapter.hpp"
body_wrapper::body_wrapper(sf::Vector2f position): body_(std::make_unique<seng::body>(to_seng_vector2(position))){}