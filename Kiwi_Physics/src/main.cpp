#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "vec2.hpp"
#include "body.hpp"

int main()
{
    sf::Clock clock;
    float frameTime;

    float dt = 0.00001f;
    float accumulator = 0.0f;

    sf::RenderWindow window(sf::VideoMode(800, 800), "Kiwi Physics");
    window.setFramerateLimit(60);
    float hw = window.getSize().x * 0.5f;
    float hh = window.getSize().y * 0.5f;
    ph::CircleBody c(Vec2(hw, 0.0f), 32.0f, 32.0f);

    sf::CircleShape shape(c.getRadius(), 600U);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(c.getRadius(), c.getRadius());

    while (window.isOpen())
    {
        frameTime = clock.restart().asSeconds();
        if (frameTime > 0.2f)
        {
            frameTime = 0.2f;
        }
        accumulator += frameTime;

        while (accumulator >= dt)
        {
            if (c.getPos().y + c.getRadius() > hh * 2.0f)
            {
                //c.setVelocity(Vec2(c.getVelocity().x, -c.getVelocity().y * 0.75));
                //c.addPos(Vec2(0.0f, -c.getPos().y - c.getRadius() + hh * 2.0f));
                c.addPos(Vec2(0.0f, -hh * 2.0f));

            }

            if (c.getPos().x - c.getRadius() > hw * 2.0f)
            {
                c.addPos(Vec2(-hw * 2.0f, 0.0f));
            }
            c.addForce(Vec2(0.0f, c.getVelocity().y * c.getRadius() * 0.5));
            c.addForce(Vec2(0.0f, -9.81f) * c.getMass() * 50);
            c.move(dt);
            accumulator -= dt;
        }

        float alpha = accumulator / dt;
        Vec2 pos(c.getInterpolatedPos(alpha));

        shape.setPosition(pos.x, pos.y);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}