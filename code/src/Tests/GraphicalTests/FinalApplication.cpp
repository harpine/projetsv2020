/*
 * prjsv 2020
 * Marco Antognini & Jamila Sam
 */

#include <Config.hpp>
#include <Lab/SimpleBacterium.hpp>
#include <Lab/Swarm.hpp>
#include <Lab/SwarmBacterium.hpp>
#include <Lab/TwitchingBacterium.hpp>
#include <Lab/MadBacterium.hpp>
#include <Lab/PoisonousBacterium.hpp>
#include "FinalApplication.hpp"
#include <Random/Random.hpp>

#include <cassert>

IMPLEMENT_MAIN(FinalApplication);

void FinalApplication::onRun()
{
    // Basic setup
    Application::onRun();
	// add graphs for statistics
	setStats(true);
    addGraph(s::GENERAL, { s::SIMPLE_BACTERIA, s::TWITCHING_BACTERIA, s::SWARM_BACTERIA, s::POISONOUS_BACTERIA, s::MAD_BACTERIA, s::NUTRIMENT_SOURCES, s::DISH_TEMPERATURE, s::POISON}, 0, 150);
    addGraph(s::NUTRIMENT_QUANTITY, {s::NUTRIMENT_QUANTITY}, 0, 2000);
    addGraph(s::SIMPLE_BACTERIA, { s::BETTER, s::WORSE}, 0, 10);
    addGraph(s::TWITCHING_BACTERIA, { s::TENTACLE_LENGTH, s::TENTACLE_SPEED}, 0, 150);
    addGraph(s::BACTERIA, { s::SPEED}, 0, 50);
    addGraph(s::POISONOUS_BACTERIA, { s::BETTER, s::WORSE}, 0, 10);
    addGraph(s::MAD_BACTERIA, {s::BETTER, s::WORSE, s::SPEED}, 0, 60);
	setActiveGraph(0);
}

void FinalApplication::onSimulationStart()
{
	Application::onSimulationStart();
    getEnv().addSwarm(new Swarm("1"));
    getEnv().addSwarm(new Swarm("2"));
    getEnv().addSwarm(new Swarm("3"));
    getEnv().addSwarm(new Swarm("4"));
}

void FinalApplication::onEvent(sf::Event event, sf::RenderWindow&)
{
    if (event.type == sf::Event::KeyReleased) {
        switch (event.key.code) {
        default:
            break;

        case sf::Keyboard::S:
            getEnv().addBacterium(new SimpleBacterium(getCursorPositionInView()));
            break;

        case sf::Keyboard::T:
            getEnv().addBacterium(new TwitchingBacterium(getCursorPositionInView()));
            break;

        case sf::Keyboard::M:
            getEnv().addBacterium(new MadBacterium(getCursorPositionInView()));
            break;

        case sf::Keyboard::P:
            getEnv().addBacterium(new PoisonousBacterium(getCursorPositionInView()));
            break;

        case sf::Keyboard::K:
            getEnv().addSpray(new Spray(getCursorPositionInView()));
            break;

        case sf::Keyboard::Num1: {
            auto swarm = getEnv().getSwarmWithId("1");
            assert(swarm != nullptr);
            getEnv().addBacterium(new SwarmBacterium(getCursorPositionInView(), swarm));
        } break;

        case sf::Keyboard::Num2: {
            auto swarm = getEnv().getSwarmWithId("2");
            assert(swarm != nullptr);
            getEnv().addBacterium(new SwarmBacterium(getCursorPositionInView(), swarm));
        } break;
        case sf::Keyboard::Num3: {
            auto swarm = getEnv().getSwarmWithId("3");
            assert(swarm != nullptr);
            getEnv().addBacterium(new SwarmBacterium(getCursorPositionInView(), swarm));
        } break;
        case sf::Keyboard::Num4: {
            auto swarm = getEnv().getSwarmWithId("4");
            assert(swarm != nullptr);
            getEnv().addBacterium(new SwarmBacterium(getCursorPositionInView(), swarm));
        } break;
        case sf::Keyboard::H: {
        //nous avons 8 types de bactéries au total
            int randomNumber(uniform(0,7));
            switch (randomNumber)    {
            default:
                break;
            case(0):
                getEnv().addBacterium(new SimpleBacterium(getCursorPositionInView()));
                break;
            case(1):
               getEnv().addBacterium(new TwitchingBacterium(getCursorPositionInView()));
               break;
            case(2):
               getEnv().addBacterium(new MadBacterium(getCursorPositionInView()));
               break;
            case 3:
               getEnv().addBacterium(new PoisonousBacterium(getCursorPositionInView()));
               break;
            case 4:
            case 5:
            case 6:
            case 7:
            {
                auto swarm = getEnv().getSwarmWithId(std::to_string(randomNumber - 3));
                assert(swarm != nullptr);
                getEnv().addBacterium(new SwarmBacterium(getCursorPositionInView(), swarm));
               } break;
            }
        } break;
        case sf::Keyboard::F:
            getEnv().flash();
            break;
    }
    }
}

