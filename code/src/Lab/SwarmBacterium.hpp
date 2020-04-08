#ifndef SWARMBACTERIUM_HPP
#define SWARMBACTERIUM_HPP
#include "Bacterium.hpp"
#include <Utility/DiffEqSolver.hpp>
 #include "Swarm.hpp"
#include <SFML/Graphics.hpp>

class SwarmBacterium: public Bacterium, public DiffEqFunction
{
public:
    //constructeurs/destructeurs:
    SwarmBacterium(const Vec2d& poscenter, Swarm*& swarm); //unsigned int mId); ??
    virtual ~SwarmBacterium() override;

    //getters:
    virtual j::Value& getConfig() const override;
    //permet d'accéder aux configurations de Swarmbacterium
    Vec2d getSpeedVector() const;
    //renvoie la vitesse courante (direction * une valeur)

    //autres méthodes:
    virtual void drawOn(sf::RenderTarget& target) const override;
    virtual Bacterium* copie() override;
    //copie une bactérie
    virtual void move(sf::Time dt) override;
    virtual Vec2d f(Vec2d position, Vec2d speed) const override;
    //virtual void update(sf::Time dt) override;
    //permet de mettre à jour les données et actions de la bactérie swarm
private:
    Swarm* swarm_;
};

#endif // SWARMBACTERIUM_HPP
