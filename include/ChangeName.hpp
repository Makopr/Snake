#pragma once

#include <memory>

#include <SFML/Graphics/Text.hpp>

#include "State.hpp"
#include "Game.hpp"

class ChangeName : public Engine::State
{
public:
    ChangeName(std::shared_ptr<Context>& context);
    ~ChangeName();

    void Init() override;
    void ProcessInput() override;
    void Update(const sf::Time& deltaTime) override;
    void Draw() override;

private:
    std::shared_ptr<Context> m_context;
    sf::Text txt;
    sf::Text enter;
    std::wstring input;
    std::wstring name;
    short size;
};