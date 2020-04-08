#ifndef SWARM_HPP
#define SWARM_HPP
#include "Bacterium.hpp"
#include <vector>

class SwarmBacterium;

class Swarm
{
public:
    //constructeurs:
    Swarm (std::string mId);
    //Swarm(unsigned int mId); ??
    ~Swarm();

    //getters setters:
    MutableColor getInitialColor() const;
    //renvoie la couleur initial du swarm
    j::Value& getConfig() const;
    //renvoie la configuration associée à swarm
    std::string getId() const;// unsigned int getmId(); ??
    std::vector <SwarmBacterium*> getSwarmBacteria() const;
    //retourne l'id du groupe
    bool isLeader(const SwarmBacterium* swarmbacterium) const;
    //retourner si la bactérie en paramètre est leader ou non
    bool hasNoLeader();
    //retourne si le swarm a un leader ou non
    Vec2d getPositionLeader() const;
    //retourne la position du leader

    // ajout/rentranchement:
    void addSwarmBacterium(SwarmBacterium* swarmbacterium);
    //ajoute une bactérie au groupe
    void removeSwarmBacterium(SwarmBacterium* swarmbacterium);
    //enlève une bactérie au groupe
    //autres méthodes:
    void update();

    void drawDebug(sf::RenderTarget& targetWindow);


private:
    std::string mId_;//unsigned int mId_; ??
    std::vector <SwarmBacterium*> swarmbacteria_;
    SwarmBacterium* leader_;


};

#endif // SWARM_HPP
