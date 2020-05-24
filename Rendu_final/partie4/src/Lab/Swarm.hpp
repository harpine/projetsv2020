#ifndef SWARM_HPP
#define SWARM_HPP

#include "Bacterium.hpp"
#include <vector>

class SwarmBacterium;

class Swarm
{
public:
    //Constructeur et destructeur:
    Swarm (const std::string &mId);
    ~Swarm();

    //Getters:

    //renvoie la couleur initial du swarm
    MutableColor getInitialColor() const;
    //renvoie la configuration associée à swarm
    j::Value& getConfig() const;
    //retourne l'id du groupe
    std::string getId() const;
    //retourner si la bactérie en paramètre est leader ou non
    bool isLeader(const SwarmBacterium* swarmbacterium) const;
    //retourne si le swarm a un leader ou non
    bool hasNoLeader();
    //retourne la position du leader
    Vec2d getPositionLeader() const;

    //Ajout/rentranchement:

    //ajoute une bactérie au groupe
    void addSwarmBacterium(SwarmBacterium* swarmbacterium);
    //enlève une bactérie au groupe
    void removeSwarmBacterium(SwarmBacterium* swarmbacterium);

    //Autres méthodes:

    //update le leader du groupe
    void updateLeader();
    //permet de contrôler l'appartenance à un swarm de plusieurs bactéries visuellement
    //nous a servi pour effectuer du debug mais trouvons intéressant de la laisser
    void drawDebug(sf::RenderTarget& targetWindow);

private:
    //Attributs:
    std::string mId_;
    std::vector <SwarmBacterium*> swarmbacteria_;
    SwarmBacterium* leader_;
};

#endif // SWARM_HPP
