#pragma once

#include <memory>
#include <fstream>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"

class PauseGame : public Engine::State
{
public:
    PauseGame(std::shared_ptr<Context> &context);
    ~PauseGame();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

    void WFile(long score, std::string name = "noname");
private:
    std::shared_ptr<Context> m_context;
    sf::Text m_pauseTitle;
    sf::Text m_menuButton;

    bool m_isMenuButtonSelected;
    bool m_isMenuButtonPressed;

    struct User {
        std::string name;
        long score;
    };
    std::ifstream fin;
    std::ofstream fon;
};
