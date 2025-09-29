#include "Graph.hpp"
#include <algorithm>
#include <sstream>
#include <thread>
#include <chrono>
#include <queue>
#include <limits>
#include <functional>

bool Graph::isInPath(int from,int to,const std::vector<int>& path){ if(path.size()<2) return false; for(size_t i=0;i+1<path.size();++i) if((path[i]==from && path[i+1]==to)||(path[i]==to && path[i+1]==from)) return true; return false; }
std::vector<int> Graph::reconstructPath(const std::map<int,int>& prev,int start,int end){ std::vector<int> p; for(int at=end; at!=-1 && at!=0; at=prev.at(at)){ p.push_back(at); if(at==start) break; } std::reverse(p.begin(),p.end()); return p; }
void Graph::updateVisualization(sf::RenderWindow& window,const std::vector<int>& path,bool finalPath){ window.clear(sf::Color::Black); draw(window,path,finalPath); window.display(); std::this_thread::sleep_for(std::chrono::milliseconds(800)); }

Graph::Graph(){ if(!font.loadFromFile("DejaVuSans.ttf")) throw std::runtime_error("Error loading font"); currentStatus="Waiting to start..."; setupGraph(); }
const sf::Font& Graph::getFont() const { return font; }

void Graph::addNode(int id, sf::Vector2f pos){ nodePositions[id]=pos; sf::CircleShape node(20); node.setPosition(pos); node.setFillColor(sf::Color::White); node.setOutlineColor(sf::Color::Black); node.setOutlineThickness(2); nodes[id]=node; }
void Graph::addEdge(int from,int to,int weight){ adjList[from].push_back({to,weight}); adjList[to].push_back({from,weight}); }

void Graph::setupGraph(){ addNode(1,{100,100}); addNode(2,{300,100}); addNode(3,{500,100}); addNode(4,{100,300}); addNode(5,{300,300}); addNode(6,{500,300}); addNode(7,{200,500}); addNode(8,{400,500}); addEdge(1,2,4); addEdge(2,3,3); addEdge(1,4,2); addEdge(2,5,6); addEdge(3,6,2); addEdge(4,5,5); addEdge(5,6,4); addEdge(4,7,3); addEdge(5,7,8); addEdge(5,8,7); addEdge(6,8,6); addEdge(7,8,4); }

void Graph::draw(sf::RenderWindow& window,const std::vector<int>& path,bool finalPath){
    for(const auto& pair:adjList){ int from=pair.first; for(const Edge& edge:pair.second){ sf::Vector2f startPos=nodePositions[from]+sf::Vector2f(20,20); sf::Vector2f endPos=nodePositions[edge.to]+sf::Vector2f(20,20); sf::Vertex line[]={ sf::Vertex(startPos,sf::Color::White), sf::Vertex(endPos,sf::Color::White)}; if(isInPath(from,edge.to,path)){ sf::Color c= finalPath? sf::Color::Green: sf::Color::Yellow; line[0].color=c; line[1].color=c; } window.draw(line,2,sf::Lines); sf::Text weightText; weightText.setFont(font); weightText.setString(std::to_string(edge.weight)); weightText.setCharacterSize(15); weightText.setFillColor(sf::Color::White); weightText.setPosition((startPos+endPos)/2.0f); window.draw(weightText);} }
    for(const auto& pair: nodes){ int id=pair.first; auto node=pair.second; if(finalPath && std::find(path.begin(),path.end(),id)!=path.end()) node.setFillColor(sf::Color::Green); window.draw(node); sf::Text idText; idText.setFont(font); idText.setString(std::to_string(id)); idText.setCharacterSize(20); idText.setFillColor(sf::Color::Black); idText.setPosition(nodePositions[id]+sf::Vector2f(15,10)); window.draw(idText);} 
    sf::Text statusText; statusText.setFont(font); statusText.setString(currentStatus); statusText.setCharacterSize(16); statusText.setFillColor(sf::Color::White); statusText.setPosition(10,570); window.draw(statusText);
    std::stringstream distanceStr; distanceStr << "Current distances from start: "; for(const auto& p: distances) distanceStr << p.first << ": " << (p.second==std::numeric_limits<int>::max()? std::string("INF"): std::to_string(p.second)) << ", "; sf::Text distanceText; distanceText.setFont(font); distanceText.setString(distanceStr.str()); distanceText.setCharacterSize(16); distanceText.setFillColor(sf::Color::Yellow); distanceText.setPosition(10,550); window.draw(distanceText);
}

std::vector<int> Graph::dijkstra(int start,int end,sf::RenderWindow& window){ std::map<int,int> dist, prev; std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<>> pq; currentStatus="Initializing distances to infinity..."; for(const auto& p: nodes){ int id=p.first; dist[id]=std::numeric_limits<int>::max(); prev[id]=-1; } dist[start]=0; distances=dist; currentStatus="Setting distance to start node "+std::to_string(start)+" as 0"; updateVisualization(window,{}); pq.push({0,start}); while(!pq.empty()){ int u=pq.top().second; int d=pq.top().first; pq.pop(); if(d>dist[u]){ currentStatus = "Skipping node "+std::to_string(u)+" as we found a better path already"; continue; } nodes[u].setFillColor(sf::Color::Cyan); currentStatus = "Processing node "+std::to_string(u)+" (current distance: "+std::to_string(d)+")"; auto currentPath=reconstructPath(prev,start,u); updateVisualization(window,currentPath); if(u==end){ currentStatus = "Found shortest path to target node "+std::to_string(end)+"!"; updateVisualization(window,currentPath,true); std::this_thread::sleep_for(std::chrono::seconds(5)); nodes[u].setFillColor(sf::Color::White); return currentPath; } for(const Edge& e: adjList[u]){ int v=e.to, w=e.weight; currentStatus = "Checking edge "+std::to_string(u)+" -> "+std::to_string(v)+" (weight: "+std::to_string(w)+")"; updateVisualization(window,currentPath); if(dist[u]+w < dist[v]){ dist[v]=dist[u]+w; prev[v]=u; distances=dist; currentStatus = "Found better path to "+std::to_string(v)+" through "+std::to_string(u)+" (new distance: "+std::to_string(dist[v])+")"; pq.push({dist[v],v}); updateVisualization(window,currentPath);} } nodes[u].setFillColor(sf::Color::White);} return reconstructPath(prev,start,end); }
