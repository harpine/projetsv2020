#pragma once

#include <vector>
#include <Stats/Graph.hpp>

class Stats 
{
public:
    //setter:
    //met le currentID_ à jour
    void setactive(const int newId);

    //autres méthodes:
    //Retourne le titre du graph courant
    std::string getCurrentTitle();
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

private:
    std::map<int, std::string> labels_;
    std::map<std::string, std::unique_ptr<Graph>> graphs_; //int
    int currentId_;
};

