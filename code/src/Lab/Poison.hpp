#ifndef POISON_HPP
#define POISON_HPP
#include "CircularBody.hpp"
#include "Utility/MutableColor.hpp"
#include <Interface/Drawable.hpp>
#include <Utility/Types.hpp>
#include <SFML/Graphics.hpp>

class Bacterium;
class SimpleBacterium;
class TwitchingBacterium;
class SwarmBacterium;
class PoisonousBacterium;
class MadBacterium;


class Poison: public CircularBody, public Drawable
{
public:
    //Constructeurs et destructeurs:
    Poison(const Vec2d &poscenter);
    ~Poison();
    Poison(const Poison& other);

    //Getters/Setters
    //permet d'accéder aux configs des poisons sans
    //devoir écrire ["poison"]
    j::Value& getConfig() const;
    //retourne la quantité du nutriment
    Quantity getQuantity() const;
    //permet de manger le poison
    void eatPoison();
    //renvoie si le poison a été mangé ou non
    bool iseaten() const;
    //renvoie le nombre d'instances
    static int getCompteur();

    //Autres méthodes:
    //permet de dessiner un poison
    void drawOn(sf::RenderTarget &target) const override;
    //calculent pour chaque type de bactérie la quantité cédée par le poison
    virtual Quantity eatenBy(Bacterium& bact);
    //(appelle eatablePoison qui appelle par polymorphisme les eatenBy ci dessous)
    virtual Quantity eatenBy(SimpleBacterium& bact);
    virtual Quantity eatenBy(TwitchingBacterium& bact);
    virtual Quantity eatenBy(SwarmBacterium& bact);
    virtual Quantity eatenBy(PoisonousBacterium& bact);
    virtual Quantity eatenBy(MadBacterium& bact);

private:
    MutableColor color_;
    Quantity quantity_;
    static int compteur_;


};

#endif // POISON_HPP
