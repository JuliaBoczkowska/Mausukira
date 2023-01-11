#include "ScoreBoardState.h"
#include "TGUI/Widgets/Button.hpp"
#include "TGUI/Widgets/ChildWindow.hpp"
#include "TGUI/Widgets/EditBox.hpp"
#include "TGUI/Widgets/ListView.hpp"
#include "TGUI/Widgets/Picture.hpp"
#include "TGUI/Widgets/ScrollablePanel.hpp"
#include "TGUI/Widgets/Scrollbar.hpp"
#include "Window.h"
#include "states_stack/SharedContext.h"
#include "states_stack/StateHandler.h"
#include <fstream>

ScoreBoardState::ScoreBoardState(StateHandler& stateHandler, StateType type, sf::View view)
    : State(stateHandler, type, view)
    , gui(context().window())
{
    setupBackground();
    tgui::Theme theme{"resources/BabyBlue.txt"};
    tgui::ScrollablePanel::Ptr panel = setupScrollablePanel();
    setupListView(theme, panel);
    setupChildWindow(theme);
    setupText();


    readScoresFromFile();
    for (auto& elem: scores)
    {
        auto score = std::to_string(elem.score);
        std::u32string scoreString(score.begin(), score.end());
        std::u32string nameString(elem.name.begin(), elem.name.end());
        listView->addItem({nameString, scoreString});
    }
}
void ScoreBoardState::setupBackground()
{
    context().window().setView(context().window().getDefaultView());
    auto picture = tgui::Picture::create("resources/tiles/background.png");
    picture->setSize({"100%", "100%"});
    gui.add(picture);
}
tgui::ScrollablePanel::Ptr ScoreBoardState::setupScrollablePanel()
{
    auto panel = tgui::ScrollablePanel::create();
    panel->setPosition({"30%", "27%"});
    panel->setSize(400, 500);
    gui.add(panel);
    return panel;
}

void ScoreBoardState::setupListView(tgui::Theme& theme, tgui::ScrollablePanel::Ptr& panel)
{
    listView = tgui::ListView::create();
    listView->setSize(400, 500);
    listView->setRenderer(theme.getRenderer("ListView"));
    listView->setExpandLastColumn(true);
    listView->addColumn("Name");
    listView->addColumn("Score");
    listView->setColumnWidth(0, 110);
    panel->add(listView);
}

void ScoreBoardState::setupText()
{
    auto size = context().window().getSize();
    mGameTitle.setColor(sf::Color::White);
    mGameTitle.setCharacterSize(50);
    font.loadFromFile("resources/arial.ttf");
    mGameTitle.setFont(font);
    mGameTitle.setString({"Scoreboard!"});
    mGameTitle.setOrigin(
        mGameTitle.getLocalBounds().left + mGameTitle.getLocalBounds().width / 2.0f,
        mGameTitle.getLocalBounds().top + mGameTitle.getLocalBounds().height / 2.0f);
    mGameTitle.setPosition(size.x / 2.0f, 200);
}


void ScoreBoardState::setupChildWindow(tgui::Theme& theme)
{
    child = tgui::ChildWindow::create();
    child->setRenderer(theme.getRenderer("ChildWindow"));
    child->setClientSize({250, 120});
    child->setPosition({"40%", "50%"});
    child->setVisible(false);
    child->setTitle("Add your score");
    gui.add(child);

    auto addScore = tgui::Button::create();
    addScore->setPosition({"30%", "80%"});
    addScore->setText("Add score");
    addScore->setSize(200, 50);
    addScore->onPress(
        [=]
        {
            if (addScoreOnce)
            {
                child->setVisible(true);
                addScoreOnce = false;
            }
        });
    gui.add(addScore);

    auto mainMenu = tgui::Button::create("MainMenu");
    mainMenu->setSize(200, 50);
    mainMenu->setPosition({"50%", "80%"});
    mainMenu->onPress(
        [this]()
        {
            mStateHandler.switchTo(StateType::MENU_STATE);
            mStateHandler.removeState(mStateType);
        });
    gui.add(mainMenu);

    editBoxName = tgui::EditBox::create();
    editBoxName->setSize(100, 30);
    editBoxName->setPosition(75, 25);
    editBoxName->setDefaultText("Your name :3");
    child->add(editBoxName);

    auto button = tgui::Button::create();
    button->setPosition(75, 70);
    button->setText("Save");
    button->setSize(100, 30);
    button->onPress(
        [&]
        {
            mInputName = editBoxName->getText().toAnsiString();
            addToTable();
            child->setVisible(false);
        });

    child->add(button);
}
void ScoreBoardState::handleInput(sf::Event& event)
{
    gui.handleEvent(event);
}

void ScoreBoardState::update(const sf::Time& dt)
{
}

void ScoreBoardState::draw()
{
    context().window().setView(context().window().getDefaultView());
    gui.draw();
    context().window().draw(mGameTitle);
}

void ScoreBoardState::addToTable()
{
    readScoresFromFile();
    scores.push_back(Score{mInputName, context().score});
    sort(scores.begin(), scores.end(),
         [](const Score& a, const Score& b)
         {
             return a.score > b.score;
         });
    writeScoresToFile();
    listView->removeAllItems();
    for (auto& elem: scores)
    {
        auto score = std::to_string(elem.score);
        std::u32string scoreString(score.begin(), score.end());
        std::u32string nameString(elem.name.begin(), elem.name.end());
        listView->addItem({nameString, scoreString});
    }
}


void ScoreBoardState::writeScoresToFile()
{
    std::ofstream file("scores.txt");
    for (const auto& score: scores)
    {
        file << score.name << "," << score.score << std::endl;
    }
    file.close();
}

void ScoreBoardState::readScoresFromFile()
{
    scores.clear();
    std::ifstream file("scores.txt");
    std::string line;
    while (getline(file, line))
    {
        std::string name;
        int value;
        std::stringstream ss(line);
        getline(ss, name, ',');
        ss >> value;
        scores.push_back({name, value});
    }
    file.close();
}
