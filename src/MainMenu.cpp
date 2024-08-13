 #include "MainMenu.hpp"
#include "GamePlay.hpp"
#include "TableScore.hpp"
#include "ChangeName.hpp"

#include <SFML/Window/Event.hpp>

MainMenu::MainMenu(std::shared_ptr<Context> &context, std::wstring name)
    : m_context(context), m_isPlayButtonSelected(true),
      m_isPlayButtonPressed(false), m_isExitButtonSelected(false),
      m_isExitButtonPressed(false), m_isNameButtonSelected(false),
      m_isNameButtonPressed(false), m_isScoreButtonSelected(false),
      m_isScoreButtonPressed(false)
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
    m_context->m_assets->AddFont(MAIN_FONT, "assets/fonts/hermes.ttf");

    // Title
    m_gameTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_gameTitle.setString("Snake Game");
    m_gameTitle.setOrigin(m_gameTitle.getLocalBounds().width / 2,
                          m_gameTitle.getLocalBounds().height / 2);
    m_gameTitle.setPosition(m_context->m_window->getSize().x / 2,
                            m_context->m_window->getSize().y / 2 - 150.f);
    // m_gameTitle.setCharacterSize(100);

    // Play Button
    m_playButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_playButton.setString("Play");
    m_playButton.setOrigin(m_playButton.getLocalBounds().width / 2,
                           m_playButton.getLocalBounds().height / 2);
    m_playButton.setPosition(m_context->m_window->getSize().x / 2,
                             m_context->m_window->getSize().y / 2 - 50.f);
    m_playButton.setCharacterSize(20);

    // Name Button
    m_nameButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_nameButton.setString("Change name");
    m_nameButton.setOrigin(m_playButton.getLocalBounds().width / 2,
        m_nameButton.getLocalBounds().height / 2);
    m_nameButton.setPosition(m_context->m_window->getSize().x / 2 - 40.f,
        m_context->m_window->getSize().y / 2 - 20.f);
    m_nameButton.setCharacterSize(20);
    
    // Score Button
    m_scoreButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_scoreButton.setString("Table of score");
    m_scoreButton.setOrigin(m_playButton.getLocalBounds().width / 2,
        m_scoreButton.getLocalBounds().height / 2);
    m_scoreButton.setPosition(m_context->m_window->getSize().x / 2 - 45.f,
        m_context->m_window->getSize().y / 2 + 15.f);
    m_scoreButton.setCharacterSize(20);

    // Exit Button
    m_exitButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_exitButton.setString("Exit");
    m_exitButton.setOrigin(m_exitButton.getLocalBounds().width / 2,
                           m_exitButton.getLocalBounds().height / 2);
    m_exitButton.setPosition(m_context->m_window->getSize().x / 2,
                             m_context->m_window->getSize().y / 2 + 50.f);
    m_exitButton.setCharacterSize(20);
}

void MainMenu::ProcessInput()
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
                if (!m_isPlayButtonSelected && m_isNameButtonSelected)
                {
                    m_isPlayButtonSelected = true;
                    m_isNameButtonSelected = false;
                    m_isScoreButtonSelected = false;
                    m_isExitButtonSelected = false;
                }
                else if (!m_isNameButtonSelected && m_isScoreButtonSelected)
                {
                    m_isPlayButtonSelected = false;
                    m_isNameButtonSelected = true;
                    m_isScoreButtonSelected = false;
                    m_isExitButtonSelected = false;
                }
                else if (!m_isScoreButtonSelected && m_isExitButtonSelected)
                {
                    m_isPlayButtonSelected = false;
                    m_isNameButtonSelected = false;
                    m_isScoreButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                break;
            }
            case sf::Keyboard::Down:
            {
                if (!m_isNameButtonSelected && m_isPlayButtonSelected)
                {
                    m_isPlayButtonSelected = false;
                    m_isNameButtonSelected = true;
                    m_isScoreButtonSelected = false;
                    m_isExitButtonSelected = false;
                }
                else if (!m_isScoreButtonSelected && m_isNameButtonSelected)
                {
                    m_isPlayButtonSelected = false;
                    m_isNameButtonSelected = false;
                    m_isScoreButtonSelected = true;
                    m_isExitButtonSelected = false;
                }
                else if (!m_isExitButtonSelected)
                {
                    m_isPlayButtonSelected = false;
                    m_isNameButtonSelected = false;
                    m_isScoreButtonSelected = false;
                    m_isExitButtonSelected = true;
                }
                break;
            }
            case sf::Keyboard::Return:
            {
                m_isPlayButtonPressed = false;
                m_isExitButtonPressed = false;
                m_isNameButtonPressed = false;
                m_isScoreButtonPressed = false;

                if (m_isPlayButtonSelected)
                {
                    m_isPlayButtonPressed = true;
                }
                else if (m_isNameButtonSelected)
                {
                    m_isNameButtonPressed = true;
                }
                else if (m_isScoreButtonSelected)
                {
                    m_isScoreButtonPressed = true;
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

void MainMenu::Update(const sf::Time& deltaTime)
{
    if (m_isPlayButtonSelected)
    {
        m_playButton.setFillColor(sf::Color::Black);
        m_nameButton.setFillColor(sf::Color::White);
        m_scoreButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else if (m_isNameButtonSelected)
    {
        m_nameButton.setFillColor(sf::Color::Black);
        m_playButton.setFillColor(sf::Color::White);
        m_scoreButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else if (m_isScoreButtonSelected)
    {
        m_scoreButton.setFillColor(sf::Color::Black);
        m_playButton.setFillColor(sf::Color::White);
        m_nameButton.setFillColor(sf::Color::White);
        m_exitButton.setFillColor(sf::Color::White);
    }
    else
    {
        m_exitButton.setFillColor(sf::Color::Black);
        m_nameButton.setFillColor(sf::Color::White);
        m_scoreButton.setFillColor(sf::Color::White);
        m_playButton.setFillColor(sf::Color::White);
    }

    if (m_isPlayButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<GamePlay>(m_context), true);
    }
    else if (m_isNameButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<ChangeName>(m_context), true);
    }
    else if (m_isScoreButtonPressed)
    {
        m_context->m_states->Add(std::make_unique<TableScore>(m_context), true);
    }
    else if (m_isExitButtonPressed)
    {
        m_context->m_window->close();
    }
}

void MainMenu::Draw()
{
    // sf::Texture t;
    // t.loadFromFile("assets/textures/back.png");
    // sf::Sprite s(t);
    m_context->m_window->clear(sf::Color::Blue);
    // Background
    // m_context->m_window->draw(s);
    m_context->m_window->draw(m_gameTitle);
    m_context->m_window->draw(m_playButton);
    m_context->m_window->draw(m_nameButton);
    m_context->m_window->draw(m_scoreButton);
    m_context->m_window->draw(m_exitButton);
    m_context->m_window->display();
}
