#ifndef NUTRIMENT_HPP
#define NUTRIMENT_HPP
#include "CircularBody.hpp"
#include "Utility/Types.hpp"
#include <SFML/Graphics.hpp>

class Nutriment : public CircularBody
{
public:
    //constructeurs
    Nutriment(const Quantity quantity, const Vec2d& poscenter);

    //getters/setters
    void setQuantity(Quantity newquantity);

    //méthodes
    Quantity takeQuantity(const Quantity totake);
    //permet d'enlever la quantité donnée en paramètre au nutriment
    void drawOn(sf::RenderTarget& target) const;
    //dessine les nutriments dans la boîte de petri
    //et affiche la quantité de nutriment à côté de ceux-ci si le
    //mode debug est activé
    j::Value const& getConfig() const;
    //permet d'accéder aux configs des nutriments sans devoir écrire ["nutriments"]
    void update(sf::Time dt);
    //calcul l'évolution du nutriment après écoulement d'un pas de temps dt
    bool cangrow() const;
    //indique si la croissance est possible
    bool depleted() const;
    //indique si le nutriment est épuisé


private:
    Quantity quantity_;
};

#endif // NUTRIMENT_HPP
