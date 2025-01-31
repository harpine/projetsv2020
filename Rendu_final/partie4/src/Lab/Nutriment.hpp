#ifndef NUTRIMENT_HPP
#define NUTRIMENT_HPP

#include "CircularBody.hpp"
#include <Utility/Types.hpp>
#include <SFML/Graphics.hpp>
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>

class Nutriment : public CircularBody, public Drawable, public Updatable
{
public:
    //Constructeur:
    Nutriment(const Quantity quantity, const Vec2d& poscenter);

    //Getters et setter:

    //permet d'accéder aux configs des nutriments sans
    //devoir écrire ["nutriments"]
    virtual j::Value const& getConfig() const = 0;
    //permet de fixer la quantité du nutriment
    void setQuantity(Quantity newquantity);
    //Retourne la quantité du nutriment
    Quantity getQuantity() const;

    //Autres méthodes:

    //permet d'enlever la quantité donnée en paramètre au nutriment
    Quantity takeQuantity(const Quantity totake);
    //dessine les nutriments dans la boîte de petri
    //et affiche la quantité de nutriment à côté de ceux-ci si le
    //mode debug est activé
    virtual void drawOn(sf::RenderTarget& target) const override;
    //calcul l'évolution du nutriment après écoulement d'un pas de temps dt
    virtual void update(sf::Time dt) override;
    //indique si le nutriment est épuisé
    bool isDepleted() const;

private:
    //Attribut:
    Quantity quantity_;

    //Méthode:

    //indique si la croissance est possible
    bool canGrow() const;

};

#endif // NUTRIMENT_HPP
