#include "Swarm.hpp"
#include "Lab.hpp"
#include "Application.hpp"
#include "SwarmBacterium.hpp"
#include "PetriDish.hpp"
#include <Utility/Utility.hpp> //servent à la fonction DrawDebug
#include <SFML/Graphics.hpp>

//Constructeur et destructeur:
Swarm::Swarm(std::string mId)
    : mId_(mId), leader_(nullptr) //vector initialisé nul par défaut
{}

Swarm::~Swarm()
{
    for (auto& swarmbacterium: swarmbacteria_)
    {
        delete swarmbacterium;
        swarmbacterium = nullptr;
    }
    swarmbacteria_.clear();
}

//Getters:
MutableColor Swarm::getInitialColor() const
{
    return getConfig()[mId_]["color"];
}

j::Value& Swarm::getConfig() const
{
    return getAppConfig()["swarms"];
}

std::string Swarm::getId() const
{
    return mId_;
}

bool Swarm::isLeader(const SwarmBacterium* swarmbacterium) const
{
    return (leader_ == swarmbacterium);
}

bool Swarm::hasNoLeader()
{
    return ( leader_==nullptr);
}
Vec2d Swarm::getPositionLeader() const
{
    return leader_->getPosition();
}

void Swarm::addSwarmBacterium(SwarmBacterium* swarmbacterium)
{
    if (swarmbacterium != nullptr)
    {
        swarmbacteria_.push_back(swarmbacterium);
    }
}

void Swarm::removeSwarmBacterium(SwarmBacterium* swarmbacterium)
{ 
    if (isLeader(swarmbacterium))
    {
        updateLeader();
    }
    swarmbacteria_.erase(std::remove(swarmbacteria_.begin(), swarmbacteria_.end(), swarmbacterium), swarmbacteria_.end());
}

void Swarm::updateLeader()
{
    SwarmBacterium* best(nullptr);
    double score(0);
    double current(0);

    for (auto& swarmbacterium: swarmbacteria_)
    {
        current = swarmbacterium->getScore();

        if (current > score)
        {
            score = current;
            best = swarmbacterium;
        }
    }
    leader_ = best;
}

void Swarm::drawDebug(sf::RenderTarget& targetWindow) //ne marche que s'il n'y a pas plus de 2 swarms
{
    sf::Color couleur;

    if (mId_ == "1")
    {
        couleur = sf::Color::Black;
    }
    else if (mId_ == "2")
    {
        couleur = sf::Color::Red;
    }

    for (size_t i(0); i < swarmbacteria_.size(); ++i)
    {
        if (i>0)
        {
            auto line = buildLine(swarmbacteria_[i]->getPosition(), swarmbacteria_[i-1]->getPosition(), couleur, 1.5);
            targetWindow.draw(line);
        }
    }
}
