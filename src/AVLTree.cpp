#include "AVLTree.hpp"
#include <thread>

int AVLTree::getHeight(AVLNode* node){return node?node->height:0;}
int AVLTree::getBalanceFactor(AVLNode* node){return node?getHeight(node->left)-getHeight(node->right):0;}

void AVLTree::updatePositions(AVLNode* node,float xOffset,float yOffset,float spacing){ if(!node) return; node->position = rootPosition + sf::Vector2f(xOffset,yOffset); updatePositions(node->left, xOffset-spacing, yOffset+80, spacing/1.5f); updatePositions(node->right, xOffset+spacing, yOffset+80, spacing/1.5f); }

AVLNode* AVLTree::rotateRight(AVLNode* y, sf::RenderWindow& window, sf::Font& font){ AVLNode* x=y->left; AVLNode* T2=x->right; animateRotation(window,font,y,"LL"); x->right=y; y->left=T2; y->height=std::max(getHeight(y->left),getHeight(y->right))+1; x->height=std::max(getHeight(x->left),getHeight(x->right))+1; updatePositions(root,0,0); return x; }
AVLNode* AVLTree::rotateLeft(AVLNode* x, sf::RenderWindow& window, sf::Font& font){ AVLNode* y=x->right; AVLNode* T2=y->left; animateRotation(window,font,x,"RR"); y->left=x; x->right=T2; x->height=std::max(getHeight(x->left),getHeight(x->right))+1; y->height=std::max(getHeight(y->left),getHeight(y->right))+1; updatePositions(root,0,0); return y; }

AVLNode* AVLTree::insertNode(AVLNode* node,int value,sf::RenderWindow& window,sf::Font& font,float xOffset,float yOffset){ if(!node) return new AVLNode(value, rootPosition+sf::Vector2f(xOffset,yOffset)); if(value<node->data) node->left=insertNode(node->left,value,window,font,xOffset-60,yOffset+80); else if(value>node->data) node->right=insertNode(node->right,value,window,font,xOffset+60,yOffset+80); else return node; node->height=1+std::max(getHeight(node->left),getHeight(node->right)); int bf=getBalanceFactor(node); if(bf>1 && value<node->left->data) return rotateRight(node,window,font); if(bf<-1 && value>node->right->data) return rotateLeft(node,window,font); if(bf>1 && value>node->left->data){ node->left=rotateLeft(node->left,window,font); return rotateRight(node,window,font);} if(bf<-1 && value<node->right->data){ node->right=rotateRight(node->right,window,font); return rotateLeft(node,window,font);} return node; }

void AVLTree::drawNode(sf::RenderWindow& window,sf::Font& font,AVLNode* node,sf::Vector2f parentPosition) const{ if(!node) return; if(parentPosition!=sf::Vector2f(-1,-1)){ sf::Vertex line[] = { sf::Vertex(parentPosition,sf::Color::Red), sf::Vertex(node->position,sf::Color::Red)}; window.draw(line,2,sf::Lines);} sf::CircleShape nodeShape(30); nodeShape.setFillColor(sf::Color::White); nodeShape.setOutlineColor(sf::Color::Black); nodeShape.setOutlineThickness(2); nodeShape.setPosition(node->position - sf::Vector2f(30,30)); sf::Text nodeText(std::to_string(node->data),font,20); nodeText.setFillColor(sf::Color::Black); nodeText.setPosition(node->position.x-10,node->position.y-15); window.draw(nodeShape); window.draw(nodeText); drawNode(window,font,node->left,node->position); drawNode(window,font,node->right,node->position); }

void AVLTree::animateRotation(sf::RenderWindow& window, sf::Font& font, AVLNode* node, const std::string& rotationType){ sf::Text rotationText(rotationType,font,30); rotationText.setFillColor(sf::Color::Yellow); rotationText.setPosition(node->position.x-50,node->position.y-100); window.clear(sf::Color::Black); draw(window,font); window.draw(rotationText); window.display(); sf::sleep(sf::milliseconds(1000)); }

AVLTree::AVLTree():root(nullptr),rootPosition(400,50){}
void AVLTree::insert(int value,sf::RenderWindow& window,sf::Font& font){ root=insertNode(root,value,window,font,0,0); updatePositions(root,0,0);} 
void AVLTree::draw(sf::RenderWindow& window,sf::Font& font) const{ drawNode(window,font,root,{-1,-1}); }
