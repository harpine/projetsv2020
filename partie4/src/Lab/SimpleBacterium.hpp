#ifndef SIMPLEBACTERIUM_HPP
#define SIMPLEBACTERIUM_HPP

#include "Bacterium.hpp"
#include <JSON/JSON.hpp>
#include <Utility/DiffEqSolver.hpp>
#include <SFML/Graphics.hpp>

class SimpleBacterium : public Bacterium, public DiffEqFunction
{

public:
    //Constructeur:
    SimpleBacterium(const Vec2d& poscenter);

    //Getters & setters:
    //permet de simplifier l'accès aux configurations
    virtual j::Value& getConfig() const override;
    j::Value& getWorseConfig() const;
    j::Value& getBetterConfig() const;
    //renvoie la vitesse courante (direction * une valeur)
    Vec2d getSpeedVector() const;

    //Autres méthodes:

    //calcul de la force
    virtual Vec2d f(Vec2d position, Vec2d speed) const override;
    //permet à une bactérie de se déplacer
    virtual void move(sf::Time dt) override;
    //copie une bactérie
    virtual Bacterium* copie() override;
    //représentation graphique de la bactérie simple
    virtual void drawOn(sf::RenderTarget& target) const override;
    //permet de mettre à jour les données et actions de la bactérie simple
    virtual void update(sf::Time dt) override;

private:
    //Attributs:

    //compteur qui fait varier l'amplitude des flagelles en fonction du temps
    double t_flagelle_;
    //probabilité de la bactérie à basculer
    double probability_;
    //compteur stockant le temps écoulé depuis le dernier basculement
    sf::Time tumbleClock_;

    //Méthodes :

    //représentation dela flagelle
    void drawOnFlagelle(sf::RenderTarget& target) const;
    //mise à jour de la flagelle
    void updateFlagelle(sf::Time dt);
    //retourne le booléen indiquant s'il y a basculement ou non
    bool tumbleAttempt(sf::Time dt);
    //fait basculer la bactérie
    void tumble();
};

#endif // SIMPLEBACTERIUM_HPP
