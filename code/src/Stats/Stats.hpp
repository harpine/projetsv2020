#pragma once

#include <vector>
#include <Stats/Graph.hpp>
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>

class Stats : public Drawable, public Updatable
{
public:
    //Setter:
    //met le currentID_ à jour
    void setActive(const int newId);

    //Autres méthodes:
    //retourne le titre du graph courant
    std::string getCurrentTitle() const;
    //permet de passer au graph suivant
    void next();
    //permet de passer au graph précédent
    void previous();
    //permet de dessiner le graphe
    void drawOn(sf::RenderTarget& target) const override;
    //reset les graphs
    void reset();
    //ajoute un graph
    void addGraph(int graphId, std::string const& title, std::vector<std::string> const& series,
                  double min, double max, Vec2d size);
    //permet de mettre à jour les données à une certaine fréquence
    virtual void update(sf::Time dt) override;

private:
    std::map<int, std::string> labels_;
    std::map<int, std::unique_ptr<Graph>> graphs_;
    int currentId_;
    sf::Time compteur_;
};

