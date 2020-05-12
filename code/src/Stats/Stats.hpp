#pragma once

#include <vector>
#include <Stats/Graph.hpp>
#include <Interface/Drawable.hpp>
#include <Interface/Updatable.hpp>

class Stats : public Drawable, public Updatable
{
public:
    //setter:
    //met le currentID_ à jour
    void setActive(const int newId);

    //autres méthodes:
    //Retourne le titre du graph courant
    std::string getCurrentTitle() const;
    //Permet de passer au graph suivant
    void next();
    //Permet de passer au graph précédent
    void previous();
    //Permet de dessiner le graphe
    void drawOn(sf::RenderTarget& target) const;
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

