#include "GameOver.hpp"
#include "GamePlay.hpp"
#include "MainMenu.hpp"

#include <SFML/Window/Event.hpp>

GameOver::GameOver(std::shared_ptr<Context> &context)
    : m_context(context), m_isRetryButtonSelected(true),
      m_isRetryButtonPressed(false), m_isExitButtonSelected(false),
      m_isExitButtonPressed(false), m_isMenuButtonPressed(false),
      m_isMenuButtonSelected(false)
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{
    // Title
    m_gameOverTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameOverTitle.setString("Game Over");
    m_gameOverTitle.setOrigin(m_gameOverTitle.getLocalBounds().width / 2,
                              m_gameOverTitle.getLocalBounds().height / 2);
    m_gameOverTitle.setPosition(m_context->m_window->getSize().x / 2,
                                m_context->m_window->getSize().y / 2 - 150.f);

    // Retry Button
    m_retryButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_retryButton.setString("Retry");
    m_retryButton.setOrigin(m_retryButton.getLocalBounds().width / 2,
                            m_retryButton.getLocalBounds().height / 2);
    m_retryButton.setPosition(m_context->m_window->getSize().x / 2,
                              m_context->m_window->getSize().y / 2 - 50.f);
    m_retryButton.setCharacterSize(20);

    // Menu button
    m_menuButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_menuButton.setString("Menu");
    m_menuButton.setOrigin(m_menuButton.getLocalBounds().width / 2,
        m_menuButton.getLocalBounds().height / 2);
    m_menuButton.setPosition(m_context->m_window->getSize().x / 2,
        m_context->m_window->getSize().y / 2 - 25.f);
    m_menuButton.setCharacterSize(20);

    // Exit Button
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
                           m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2,
                             m_context->m_window->getSize().y / 2 + 0.f);
    m_exitButton.setCharacterSize(20);
}

void GameOver::ProcessInput()
{
    sf::Event event;
    while (m_context->m_window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_context->m_window->close();
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::Up:
            {
                if (!m_isRetryButtonSelected && !m_isExitButtonSelected)
                {
                    m_isRetryButtonSelected = true;
                    m_isMenuButtonSelected = false;
                    m_isExitButtonSelected = false;
                }
                else if (!m_isMenuButtonSelected && m_isExitButtonSelected)
                {
                    m_isRetryButtonSelected = false;
                    m_isMenuButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!m_isExitButtonSelected && !m_isRetryButtonSelected)
                {
                    m_isRetryButtonSelected = false;
                    m_isMenuButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                else if (!m_isMenuButtonSelected && m_isRetryButtonSelected)
                {
                    m_isRetryButtonSelected = false;
                    m_isMenuButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                m_isRetryButtonPressed = false;
                m_isExitButtonPressed = false;
                m_isMenuButtonPressed = false;

                if (m_isRetryButtonSelected)
                {
                    m_isRetryButtonPressed = true;
                }
                else if (m_isMenuButtonSelected)
                {
                    m_isMenuButtonPressed = true;
                }
                else if (m_isExitButtonSelected)
                {
                    m_isExitButtonPressed = true;
                }

                break;
            }
            default:
            {
                break;
            }
            }
        }
    }
}

void GameOver::Update(const sf::Time& deltaTime)
{
    if (m_isRetryButtonSelected)
    {
        m_retryButton.setFillColor(sf::Color::Black);
        m_menuButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else if (m_isMenuButtonSelected)
    {
        m_retryButton.setFillColor(sf::Color::White);
        m_menuButton.setFillColor(sf::Color::Black);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else
    {
        m_retryButton.setFillColor(sf::Color::White);
        m_menuButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::Black);
    }

    if (m_isRetryButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    else if (m_isMenuButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
    }
    else if (m_isExitButtonPressed)
    {
        m_context->m_window->close();
    }
}

void GameOver::Draw()
{
    m_context->m_window->clear(sf::Color::Blue);
    m_context->m_window->draw(m_gameOverTitle);
    m_context->m_window->draw(m_retryButton);
    m_context->m_window->draw(m_menuButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}
