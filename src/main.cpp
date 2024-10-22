#include <iostream>
#include "renderer.h"
#include "engine.h"

int main(int argc, char **argv)
{
    Engine engine;
    // if (argc == 2)
    // {
    engine.setStartPattern("C:\\Users\\trasoloallaoui\\C++\\git\\GoL\\src\\pattern.txt"); // argv[2]);
    // }
    Renderer renderer(engine);
    renderer.render();
    return 0;
}