#include "Swarm.hpp"
#include "Lab.hpp"
#include "Application.hpp"
#include "SwarmBacterium.hpp"
#include "PetriDish.hpp"

Swarm::Swarm(std::string mId) //(unsigned int mId)
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
MutableColor Swarm::getInitialColor() const
{
    return getConfig()[mId_]["color"];
}

j::Value& Swarm::getConfig() const
{
    return getAppConfig()["swarms"];
}

std::string Swarm::getId() const //unsigned int?
{
    return mId_;
}

std::vector <SwarmBacterium*> Swarm::getSwarmBacteria() const
{
    return swarmbacteria_;
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
    swarmbacteria_.push_back(swarmbacterium);
}

void Swarm::removeSwarmBacterium(SwarmBacterium* swarmbacterium)
{
    swarmbacteria_.erase(std::remove(swarmbacteria_.begin(), swarmbacteria_.end(), swarmbacterium), swarmbacteria_.end());
    //std::cerr << "enlevee" << swarmbacteria_.size();
}

void Swarm::update()
{
    std::cerr << "vide " << swarmbacteria_.empty() << std::endl;
//        for (auto& swarmbacterium: swarmbacteria_)
//        {
//            std::cerr << "kesake";
//            if (leader_ == nullptr)
//            {
//                leader_ = swarmbacterium;
//            }
//            else if (getAppEnv().getPositionScore(swarmbacterium->getPosition()) > getAppEnv().getPositionScore(leader_->getPosition()))
//            {
//                leader_ = swarmbacterium;
//            }
//        }
//    }
    SwarmBacterium* best(nullptr);
    double score(0);
    double current(0);
    for (auto& swarmbacterium: swarmbacteria_)
    {
        current = getAppEnv().getPositionScore(swarmbacterium->getPosition());
        if (current > score)
        {
            score = current;
            best = swarmbacterium;
        }

    }
    leader_ = best;
    //}
}

#include <Utility/Utility.hpp>
#include <SFML/Graphics.hpp>

void Swarm::drawDebug(sf::RenderTarget& targetWindow)
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
        //à enlever:
        if (i>0)
        {
            auto line = buildLine(swarmbacteria_[i]->getPosition(), swarmbacteria_[i-1]->getPosition(), couleur, 3);
            targetWindow.draw(line);
        }
    }
}
