# Jacob Worgan ASE Assignment

Repository for the ASE assignment and code.

## Project Idea
For my project, I decided to work on creating a navigation system for AI agents. I have done some work for a previous yr2 BA CATA project in which I developed a simple NPC (non-playable character) AI system, implemented using a behaviour tree system. [It can be found here on github](https://github.com/terrinamatsu/VillagerAI) and [a video showcasing it in action here.](https://www.jacobworgan.co.uk/projects/villager-ai) Python code used in this project is taken from this source. 

Building on this, I wanted to implement a Navigation Mesh system to allow these NPC agents to move in a 3D world, as opposed to the original project's UI based approach. Python code from this project is called within the system used here, although it is not fully linked as yet to the actual pathfinding. 

This is a Qt application with a couple of user interface features, allowing for the adjustment of the number of agents from 1 to 10,000, as well as the speed of the simulation, from 0x (paused) to 5x.

Pathfinding, as mentioned, is achieved using a Navigation Mesh system, with an A* algorithm used to plot villager's paths between what are currently randomised points projected onto the navigation mesh using point-triangle projection made up of several individual projection algorithms, being a point-plane projection, point on triangle check, and a point-line segment projection. This is described in more detail in the accompanying CGI Techniques paper. 

Movement is also synchronised using a std::chrono timer.

Tests for the core Villager and Navigation components are included as well, with failing tests indicating the next stage of development. 

## Building

[build instructions can be found here](docs/BUILDING.md)