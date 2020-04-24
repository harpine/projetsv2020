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
    virtual j::Value const& getConfig() const = 0;
    //permet d'accéder aux configs des nutriments sans
    //devoir écrire ["nutriments"]
    void setQuantity(Quantity newquantity);
    //permet de fixer la quantité du nutriment
    Quantity getQuantity() const;
    //Retourne la quantité du nutriment

    //Autres méthodes:
    Quantity takeQuantity(const Quantity totake);
    //permet d'enlever la quantité donnée en paramètre au nutriment
    virtual void drawOn(sf::RenderTarget& target) const override;
    //dessine les nutriments dans la boîte de petri
    //et affiche la quantité de nutriment à côté de ceux-ci si le
    //mode debug est activé
    virtual void update(sf::Time dt) override;
    //calcul l'évolution du nutriment après écoulement d'un pas de temps dt
    bool isDepleted() const;
    //indique si le nutriment est épuisé

private:
    //Attribut:
    Quantity quantity_;

    //Méthode:
    bool canGrow() const;
    //indique si la croissance est possible
};

#endif // NUTRIMENT_HPP
