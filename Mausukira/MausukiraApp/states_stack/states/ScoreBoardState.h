#ifndef SCOREBOARDSTATE_H
#define SCOREBOARDSTATE_H

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "State.h"
#include "TGUI/Backends/SFML/GuiSFML.hpp"
#include "TGUI/Widgets/EditBox.hpp"
#include "TGUI/Widgets/ListView.hpp"
#include "TGUI/Widgets/ScrollablePanel.hpp"

class ScoreBoardState : public State
{
    struct Score
    {
        std::string name;
        int score;
    };

public:
    ScoreBoardState(StateHandler& stateHandler, StateType type, sf::View view);
    ~ScoreBoardState() = default;

    void handleInput(sf::Event& event) override;
    void update(const sf::Time& dt) override;
    void draw() override;
    void writeScoresToFile();
    void readScoresFromFile();

private:
    void addToTable();
    void setupText();
    void setupBackground();
    void setupChildWindow(tgui::Theme& theme);
    void setupListView(tgui::Theme& theme, tgui::ScrollablePanel::Ptr& panel);

private:
    tgui::GuiSFML gui;
    sf::Font font;
    sf::Text mGameTitle;
    std::string mInputName;
    bool addScoreOnce{true};
    std::vector<Score> scores;

    std::shared_ptr<tgui::ListView> listView;
    std::shared_ptr<tgui::EditBox> editBoxName;
    std::shared_ptr<tgui::ChildWindow> child;
    std::shared_ptr<tgui::ScrollablePanel> setupScrollablePanel();
};

#endif// SCOREBOARDSTATE_H
