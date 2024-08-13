#include "PauseGame.hpp"
#include "MainMenu.hpp"

#include <SFML/Window/Event.hpp>

PauseGame::PauseGame(std::shared_ptr<Context> &context)
    : m_context(context), m_isMenuButtonSelected(false),
    m_isMenuButtonPressed(false)
{
}

PauseGame::~PauseGame()
{
}

void PauseGame::Init()
{
    // Title
    m_pauseTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
    m_pauseTitle.setString("Paused");
    m_pauseTitle.setOrigin(m_pauseTitle.getLocalBounds().width / 2,
                           m_pauseTitle.getLocalBounds().height / 2);
    m_pauseTitle.setPosition(m_context->m_window->getSize().x / 2,
                             m_context->m_window->getSize().y / 2);
}

void PauseGame::ProcessInput()
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
            case sf::Keyboard::Return:
            {
                // WFile(score, "sda");
                m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
                break;
            }
            case sf::Keyboard::Escape:
            {
                m_context->m_states->PopCurrent();
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

void PauseGame::Update(const sf::Time& deltaTime)
{
}

void PauseGame::Draw()
{
    m_context->m_window->draw(m_pauseTitle);
    m_context->m_window->display();
}

void PauseGame::WFile(long score, std::string name)
{
    User users[10], temp;
    short i;
    bool notin = true;

    fin.open("text.txt");
    for (i = 0; i < 10; i++)
    {
        fin >> users[i].name  >> users[i].score;
        if (users[i].score <= score)
        {
            temp.score = users[i].score;
            temp.name = users[i].name;

            users[i].score = score;
            users[i].name = name;

            name = temp.name;
            score = temp.score;
        }
    }
    fin.close();

    fon.open("text.txt");
    for (i = 0; i < 10; i++)
    {
        fon << users[i].name << ' ' << users[i].score << '\n';
    }

    fon.close();
}