#include "TableScore.hpp"
#include "MainMenu.hpp"

#include <SFML/Window/Event.hpp>

TableScore::TableScore(std::shared_ptr<Context>& context)
	: m_context(context), m_isTxtButtonSelected(false),
	m_isTxtButtonPressed(false), m_isClearButtonSelected(false),
	m_isClearButtonPressed(false), m_isMenuButtonSelected(true),
	m_isMenuButtonPressed(false)
{
}

TableScore::~TableScore()
{
}

void TableScore::Init()
{
	User users[10];

	// Table title
	m_TableTitle.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_TableTitle.setString("Table of Score");
	m_TableTitle.setOrigin(m_TableTitle.getLocalBounds().width / 2,
		m_TableTitle.getLocalBounds().height / 2);
	m_TableTitle.setPosition(m_context->m_window->getSize().x / 2,
		m_context->m_window->getSize().y / 2 - 250.f);
	m_TableTitle.setCharacterSize(50);

	// Menu
	m_menuButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_menuButton.setString("Menu");
	m_menuButton.setOrigin(m_menuButton.getLocalBounds().width / 2,
						   m_menuButton.getLocalBounds().height / 2);
	m_menuButton.setPosition(m_context->m_window->getSize().x / 2,
						     m_context->m_window->getSize().y / 2 - 50.f);
	m_menuButton.setCharacterSize(20);
	
	// Text File
	m_txtButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_txtButton.setString("Txt File");
	m_txtButton.setOrigin(m_txtButton.getLocalBounds().width / 2,
		m_txtButton.getLocalBounds().height / 2);
	m_txtButton.setPosition(m_context->m_window->getSize().x / 2,
		m_context->m_window->getSize().y / 2 - 25.f);
	m_txtButton.setCharacterSize(20);

	// Clear
	m_clearButton.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	m_clearButton.setString("Clear File");
	m_clearButton.setOrigin(m_clearButton.getLocalBounds().width / 2,
							m_clearButton.getLocalBounds().height / 2);
	m_clearButton.setPosition(m_context->m_window->getSize().x / 2,
							  m_context->m_window->getSize().y / 2 + 20.f);
	m_clearButton.setCharacterSize(20);

	fin.open("text.txt");
	for (int i = 0; i < 10; i++) {
		fin >> users[i].name;
		fin >> users[i].score;

		Name[i].setFont(m_context->m_assets->GetFont(MAIN_FONT));
		Name[i].setString(users[i].name);
		Name[i].setOrigin(Name[i].getLocalBounds().width / 2,
			Name[i].getLocalBounds().height / 2);
		Name[i].setPosition(m_context->m_window->getSize().x / 2 - 200.f,
			m_context->m_window->getSize().y / 2 - 320 + i * 32.f);
		Name[i].setCharacterSize(20);

		Score[i].setFont(m_context->m_assets->GetFont(MAIN_FONT));
		Score[i].setString(std::to_string(users[i].score));
		Score[i].setOrigin(Score[i].getLocalBounds().width / 2,
			Score[i].getLocalBounds().height / 2);
		Score[i].setPosition(m_context->m_window->getSize().x / 2 - 100.f,
			m_context->m_window->getSize().y / 2 - 320 + i * 32.f);
		Score[i].setCharacterSize(20);
	}
	fin.close();
}

void TableScore::ProcessInput()
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
				if (!m_isMenuButtonSelected && !m_isClearButtonSelected)
				{
					m_isMenuButtonSelected = true;
					m_isTxtButtonSelected = false;
					m_isClearButtonSelected = false;
				}
				else if (!m_isTxtButtonSelected && m_isClearButtonSelected)
				{
					m_isMenuButtonSelected = false;
					m_isTxtButtonSelected = true;
					m_isClearButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Down:
			{
				if (!m_isClearButtonSelected && !m_isMenuButtonSelected)
				{
					m_isMenuButtonSelected = false;
					m_isTxtButtonSelected = false;
					m_isClearButtonSelected = true;
				}
				else if (!m_isTxtButtonSelected && m_isMenuButtonSelected)
				{
					m_isMenuButtonSelected = false;
					m_isTxtButtonSelected = true;
					m_isClearButtonSelected = false;
				}
				break;
			}
			case sf::Keyboard::Return:
			{
				m_isMenuButtonPressed = false;
				m_isTxtButtonPressed = false;
				m_isClearButtonPressed = false;

				if (m_isMenuButtonSelected)
				{
					m_isMenuButtonPressed = true;
				}
				else if (m_isTxtButtonSelected)
				{
					m_isTxtButtonPressed = true;
				}
				else if (m_isClearButtonSelected)
				{
					m_isClearButtonPressed = true;
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

void TableScore::Update(const sf::Time& deltaTime)
{
	if (m_isMenuButtonSelected)
	{
		m_menuButton.setFillColor(sf::Color::Black);
		m_txtButton.setFillColor(sf::Color::White);
		m_clearButton.setFillColor(sf::Color::White);
	}
	else if (m_isTxtButtonSelected)
	{
		m_menuButton.setFillColor(sf::Color::White);
		m_txtButton.setFillColor(sf::Color::Black);
		m_clearButton.setFillColor(sf::Color::White);
	}
	else
	{
		m_menuButton.setFillColor(sf::Color::White);
		m_txtButton.setFillColor(sf::Color::White);
		m_clearButton.setFillColor(sf::Color::Black);
	}

	if (m_isMenuButtonPressed)
	{
		m_context->m_states->Add(std::make_unique<MainMenu>(m_context), true);
	}
	else if (m_isTxtButtonPressed)
	{
		// text file
	}
	else if (m_isClearButtonPressed)
	{
		// clear file
		fclear.open("text.txt");
		User users[10];

		for (int i = 0; i < 10; i++) {
			strcpy_s(users[i].name, "noname");
			users[i].score = 0;

			fclear << users[i].name << ' ' << users[i].score << '\n';
			Name[i].setString(users[i].name);
			Score[i].setString(std::to_string(users[i].score));
		}

		fclear.close();
	}
}

void TableScore::Draw()
{
	m_context->m_window->clear(sf::Color::Blue);
	m_context->m_window->draw(m_TableTitle);
	m_context->m_window->draw(m_menuButton);
	for (int i = 0; i < 10; i++) {
		m_context->m_window->draw(Name[i]);
		m_context->m_window->draw(Score[i]);
	}
	m_context->m_window->draw(m_txtButton);
	m_context->m_window->draw(m_clearButton);
	m_context->m_window->display();
}