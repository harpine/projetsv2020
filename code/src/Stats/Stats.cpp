#include <Stats/Stats.hpp>

void Stats::setactive(const int newId)
{
    currentId_ = newId;
}

std::string Stats::getCurrentTitle()
{
    return labels_.find(currentId_)->second;
}

void Stats::next()
{
    currentId_ = ((currentId_+1)%graphs_.size());
}

void Stats::previous()
{
    int newId(currentId_ -1);
    if (newId < 0)
    {
        currentId_ = graphs_.size() -1;
    }
    else
    {
        currentId_ = newId;
    }
}

void Stats::drawOn(sf::RenderTarget& target) const
{

    graphs_.find(currentId_)->second->drawOn(target);
}

void Stats::reset()
{
    for (auto& pair: graphs_)
    {
        pair.second.reset();
    }
}

void Stats::addGraph(int graphId, std::string const& title, std::vector<std::string> const& series,
              double min, double max, Vec2d size)
{

    if (labels_.find(graphId) == labels_.end())
    {
        labels_[graphId] = title;
        graphs_.emplace(std::pair<int, std::unique_ptr<Graph>>(graphId, new Graph(series, size, min, max)));
    }
    else
    {
        graphs_.find(graphId)->second.reset(new Graph(series, size, min, max));
        labels_.find(graphId)->second = title;
    }
    currentId_ = graphId;
}
