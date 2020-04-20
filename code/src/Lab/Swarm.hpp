#ifndef SWARM_HPP
#define SWARM_HPP

#include "Bacterium.hpp"
#include <vector>

class SwarmBacterium;

class Swarm
{
public:
    //Constructeur et destructeur:
    Swarm (std::string mId);
    ~Swarm();

    //Getters:
    MutableColor getInitialColor() const;
    //renvoie la couleur initial du swarm
    j::Value& getConfig() const;
    //renvoie la configuration associée à swarm
    std::string getId() const;
    //retourne l'id du groupe
    bool isLeader(const SwarmBacterium* swarmbacterium) const;
    //retourner si la bactérie en paramètre est leader ou non
    bool hasNoLeader();
    //retourne si le swarm a un leader ou non
    Vec2d getPositionLeader() const;
    //retourne la position du leader

    //Ajout/rentranchement:
    void addSwarmBacterium(SwarmBacterium* swarmbacterium);
    //ajoute une bactérie au groupe
    void removeSwarmBacterium(SwarmBacterium* swarmbacterium);
    //enlève une bactérie au groupe

    //Autres méthodes:
    void updateLeader();
    //update le leader du groupe
    void drawDebug(sf::RenderTarget& targetWindow);
    //permet de contrôler l'appartenance à un swarm de plusieurs bactéries visuellement
    //nous a servi pour effectuer du debug mais trouvons intéressant de la laisser

private:
    //Attributs:
    std::string mId_;
    std::vector <SwarmBacterium*> swarmbacteria_;
    SwarmBacterium* leader_;
};

#endif // SWARM_HPP
