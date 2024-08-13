#include "ChangeName.hpp"
#include "MainMenu.hpp"

#include <SFML/Window/Event.hpp>

ChangeName::ChangeName(std::shared_ptr<Context>& context)
	: m_context(context), name(L"noname"),
	size(0)
{
}

ChangeName::~ChangeName()
{
}

void ChangeName::Init()
{
	// Enter name
	txt.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	txt.setString("Enter the name");
	txt.setOrigin(txt.getLocalBounds().width / 2,
		txt.getLocalBounds().height / 2);
	txt.setPosition(m_context->m_window->getSize().x / 2,
		m_context->m_window->getSize().y / 2 - 250.f);
	txt.setCharacterSize(50);

	enter.setFont(m_context->m_assets->GetFont(MAIN_FONT));
	enter.setString(L"");
	enter.setOrigin(enter.getLocalBounds().width / 2,
		enter.getLocalBounds().height / 2);
	enter.setPosition(m_context->m_window->getSize().x / 2 - 200.f,
		m_context->m_window->getSize().y / 2 - 25.f);
	enter.setCharacterSize(50);

}

void ChangeName::ProcessInput()
{
	sf::Event event;
	while (m_context->m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_context->m_window->close();
		}
		if (event.type == sf::Event::TextEntered)
		{
			if (event.text.unicode)
			{
				if (event.text.unicode == '\b' && !input.empty())
				{
					input.pop_back();
					size--;
				}
				else if (event.text.unicode != '\b' && size < 20 && event.text.unicode != ' ')
				{
					input += static_cast<wchar_t>(event.text.unicode);
					size++;
				}
			}
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::Escape:
			{
				m_context->m_states->Add(std::make_unique<MainMenu>(m_context, name), true);
				break;
			}
			case sf::Keyboard::Enter:
			{
				name = input;
				input.clear();
				break;
			}
			default:
			{
				break;
			}
			}
		}
		enter.setString(input);
	}
}

void ChangeName::Update(const sf::Time& deltaTime)
{
	
}

void ChangeName::Draw()
{
	m_context->m_window->clear(sf::Color::Blue);
	m_context->m_window->draw(txt);
	m_context->m_window->draw(enter);
	m_context->m_window->display();
}