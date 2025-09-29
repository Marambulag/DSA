#include "Maze.hpp"
#include <algorithm>
#include <random>
#include <thread>
#include <queue>

Maze::Maze(int width,int height,int cellSize):width(width),height(height),cellSize(cellSize),start(1,1),end(width-2,height-2){ grid.resize(width, std::vector<Cell>(height, WALL)); generateMaze(); grid[start.x][start.y]=START; grid[end.x][end.y]=END; }

void Maze::generateMaze(){
	for(int x=0;x<width;++x) for(int y=0;y<height;++y) grid[x][y]=WALL;
	// Use randomized Prim's to create more natural branching
	generatePrim();
	grid[start.x][start.y]=START; grid[end.x][end.y]=END;
}

void Maze::generateDFS(Position pos){ grid[pos.x][pos.y]=PATH; std::vector<Position> directions={{0,-2},{0,2},{-2,0},{2,0}}; std::shuffle(directions.begin(), directions.end(), std::mt19937(std::random_device()())); for(const Position& d: directions){ int nx=pos.x+d.x, ny=pos.y+d.y; if(nx>0 && ny>0 && nx<width-1 && ny<height-1 && grid[nx][ny]==WALL){ grid[nx][ny]=PATH; grid[pos.x + d.x/2][pos.y + d.y/2]=PATH; generateDFS({nx,ny}); } } }

bool Maze::solveMaze(sf::RenderWindow& window){ return solveDFS(start, window); }

bool Maze::solveMazeBFS(sf::RenderWindow& window){
	std::queue<Position> q; q.push(start);
	std::vector<std::vector<Position>> prev(width, std::vector<Position>(height, Position(-1,-1)));
	grid[start.x][start.y]=VISITED;
	while(!q.empty()){
		Position pos=q.front(); q.pop();
		if(pos.x==end.x && pos.y==end.y){
			// Reconstruct path and animate
			Position cur = pos;
			while(!(cur.x==start.x && cur.y==start.y)){
				grid[cur.x][cur.y]=SOLUTION;
				draw(window); window.display(); sf::sleep(sf::milliseconds(40));
				Position p = prev[cur.x][cur.y];
				if (p.x==-1 && p.y==-1) break; // safety
				cur = p;
			}
			grid[start.x][start.y]=START; grid[end.x][end.y]=END;
			draw(window); window.display();
			return true;
		}
		draw(window); window.display(); sf::sleep(sf::milliseconds(40));
		std::vector<Position> neighbors={{0,-1},{0,1},{-1,0},{1,0}};
		for(const Position& dir: neighbors){ int nx=pos.x+dir.x, ny=pos.y+dir.y; if(nx>=0 && ny>=0 && nx<width && ny<height && (grid[nx][ny]==PATH || grid[nx][ny]==END)){
				if (prev[nx][ny].x==-1){ prev[nx][ny]=pos; q.push({nx,ny}); grid[nx][ny]=VISITED; }
		} }
	}
	return false;
}

bool Maze::solveDFS(Position pos, sf::RenderWindow& window){
	if (pos.x < 0 || pos.y < 0 || pos.x >= width || pos.y >= height) return false;
	if (pos.x==end.x && pos.y==end.y){ grid[pos.x][pos.y]=SOLUTION; return true; }
	if (grid[pos.x][pos.y] != PATH && grid[pos.x][pos.y] != START) return false;
	grid[pos.x][pos.y]=VISITED;
	draw(window); window.display(); sf::sleep(sf::milliseconds(80));
	std::vector<Position> neighbors={{0,-1},{0,1},{-1,0},{1,0}};
	for(const Position& dir: neighbors){
		int nx=pos.x+dir.x, ny=pos.y+dir.y;
		if (solveDFS({nx,ny}, window)){
			grid[pos.x][pos.y]=SOLUTION; draw(window); window.display(); sf::sleep(sf::milliseconds(40)); return true;
		}
	}
	// backtrack
	if (grid[pos.x][pos.y] != START) grid[pos.x][pos.y]=PATH;
	return false;
}

void Maze::draw(sf::RenderWindow& window){
	for(int x=0;x<width;++x) for(int y=0;y<height;++y){
		sf::RectangleShape cell({static_cast<float>(cellSize), static_cast<float>(cellSize)});
		cell.setPosition(static_cast<float>(x*cellSize), static_cast<float>(y*cellSize));
		switch(grid[x][y]){
			case WALL: cell.setFillColor(sf::Color(30,30,34)); break;
			case PATH: cell.setFillColor(sf::Color(235,238,242)); break;
			case VISITED: cell.setFillColor(sf::Color(120,160,240)); break;
			case START: cell.setFillColor(sf::Color(80,200,120)); break;
			case END: cell.setFillColor(sf::Color(220,80,90)); break;
			case SOLUTION: cell.setFillColor(sf::Color(255,215,0)); break;
		}
		cell.setOutlineThickness(1.f);
		cell.setOutlineColor(sf::Color(0,0,0,35));
		window.draw(cell);
	}
}

void Maze::generatePrim(){
	// Randomized Prim's algorithm on a grid
	std::vector<Position> frontier;
	auto inBounds = [&](int x,int y){ return x>0 && y>0 && x<width-1 && y<height-1; };
	auto addFrontier = [&](int x,int y){ if(inBounds(x,y) && grid[x][y]==WALL) { frontier.emplace_back(x,y); grid[x][y]=VISITED; } };

	// start from start cell snapped to odd coordinates
	int sx = (start.x % 2 == 0) ? start.x+1 : start.x;
	int sy = (start.y % 2 == 0) ? start.y+1 : start.y;
	grid[sx][sy] = PATH;
	addFrontier(sx+2, sy); addFrontier(sx-2, sy); addFrontier(sx, sy+2); addFrontier(sx, sy-2);

	std::mt19937 rng(std::random_device{}());
	while(!frontier.empty()){
		std::uniform_int_distribution<size_t> dist(0, frontier.size()-1);
		size_t idx = dist(rng);
		Position f = frontier[idx];
		frontier.erase(frontier.begin()+idx);

		// find neighbors that are PATH two steps away
		std::vector<Position> neighbors;
		std::vector<Position> dirs={{2,0},{-2,0},{0,2},{0,-2}};
		for(const auto& d : dirs){ int nx=f.x+d.x, ny=f.y+d.y; if(inBounds(nx,ny) && grid[nx][ny]==PATH) neighbors.emplace_back(nx,ny); }
		if(neighbors.empty()) continue;
		std::uniform_int_distribution<size_t> dist2(0, neighbors.size()-1);
		Position n = neighbors[dist2(rng)];

		// carve the wall between f and n
		int wx = (f.x + n.x)/2, wy = (f.y + n.y)/2;
		grid[f.x][f.y] = PATH; grid[wx][wy] = PATH;

		// add new frontier around f
		addFrontier(f.x+2, f.y); addFrontier(f.x-2, f.y); addFrontier(f.x, f.y+2); addFrontier(f.x, f.y-2);
	}

	// Mark any VISITED frontier remnants back to WALL
	for(int x=0;x<width;++x) for(int y=0;y<height;++y) if(grid[x][y]==VISITED) grid[x][y]=WALL;
}


void Maze::resetTraversal(){
	for(int x=0;x<width;++x) for(int y=0;y<height;++y){
		if (grid[x][y]==VISITED || grid[x][y]==SOLUTION) grid[x][y]=PATH;
	}
	grid[start.x][start.y]=START; grid[end.x][end.y]=END;
}
