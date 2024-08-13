#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"
#include <fstream>

class TableScore : public Engine::State
{
public:
    TableScore(std::shared_ptr<Context>& context);
    ~TableScore();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

private:
    std::shared_ptr<Context> m_context;
    sf::Text m_TableTitle;
    sf::Text m_menuButton;
    sf::Text m_clearButton;
    sf::Text m_txtButton;
    
    sf::Text Name[10];
    sf::Text Score[10];

    bool m_isMenuButtonSelected;
    bool m_isMenuButtonPressed;
    
    bool m_isClearButtonSelected;
    bool m_isClearButtonPressed;
    
    bool m_isTxtButtonSelected;
    bool m_isTxtButtonPressed;

    std::ifstream fin;
    std::ofstream fclear;
    struct User {
        char name[50];
        long score;
    };
};