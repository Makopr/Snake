#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"

class MainMenu : public Engine::State
{
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_gameTitle;
    sf::Text m_playButton;
    sf::Text m_nameButton;
    sf::Text m_scoreButton;
    sf::Text m_exitButton;

    bool m_isPlayButtonSelected;
    bool m_isPlayButtonPressed;

    bool m_isNameButtonSelected;
    bool m_isNameButtonPressed;
     
    bool m_isScoreButtonSelected;
    bool m_isScoreButtonPressed;

    bool m_isExitButtonSelected;
    bool m_isExitButtonPressed;

    std::wstring name;
public:
    MainMenu(std::shared_ptr<Context> &context, std::wstring name = L"noname");
    ~MainMenu();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
};