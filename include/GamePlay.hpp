#pragma once

#include <memory>
#include <array>
#include <fstream>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

#include "Game.hpp"
#include "State.hpp"
#include "Snake.hpp"

class GamePlay : public Engine::State
{
public:
    GamePlay(std::shared_ptr<Context> &context);
    ~GamePlay();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;
    void Pause() override;
    void Start() override;

    void WFile(long score);

private:
    std::shared_ptr<Context> m_context;
    sf::Sprite m_grass;
    sf::Sprite m_food;
    std::array<sf::Sprite, 4> m_walls;
    Snake m_snake;

    sf::Text m_scoreText;
    long m_score;

    sf::Vector2f m_snakeDirection;
    sf::Time m_elapsedTime;

    bool m_isPaused;

    struct User {
        char name[50];
        long score;
    };
    std::ifstream fin;
    std::ofstream fon;
};
