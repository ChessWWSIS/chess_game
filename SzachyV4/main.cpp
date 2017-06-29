#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;

class Pionek
{
    public:

};

int main()
{

    sf::RenderWindow okno(sf::VideoMode(800,800),"Szachy");
    sf::Event wydarzenie;
    sf::Vector2i pozycjaMyszy;
//    sf::Vector2f pozycjaMyszyNaScenie;

    sf::Texture tekstura, zaznaPola, bierki;

    tekstura.loadFromFile( "images/szachownica.jpg" );
    zaznaPola.loadFromFile("images/zaznaPola.png");
    bierki.loadFromFile("images/bierki.png");

    sf::Sprite szachownica, zaznaczeniePola;
    sf::Sprite f[32];

    szachownica.setTexture(tekstura);
    zaznaczeniePola.setTexture(zaznaPola);


    bool czyPoleZaznaczone, graWToku = false;
    int indeksPionka;

    while(okno.isOpen())
    {
        while(okno.pollEvent(wydarzenie))
        {
            if(wydarzenie.type == sf::Event::KeyPressed && wydarzenie.key.code ==
               sf::Keyboard::Escape)
                okno.close();
        }

        okno.draw(szachownica);
        if (graWToku == false)
        {
            for (int i = 0; i < 8; i++)
                {
                    f[i].setTexture(bierki);
                    f[i].setTextureRect(sf::IntRect(500, 100, 100, 100));
                    okno.draw(f[i]);
                    f[i].setPosition(100*i, 100);
                }

            for (int i = 8; i < 16; i++)
                {
                    f[i].setTexture(bierki);
                    f[i].setTextureRect(sf::IntRect(500, 0, 100, 100));
                    okno.draw(f[6]);
                    f[i].setPosition(100*i, 600);
                }

            for (int i = 16; i < 18; i++)
                {
                    f[i].setTexture(bierki);
                    f[i].setTextureRect(sf::IntRect(0, 100, 100, 100));
                    okno.draw(f[i]);
                    f[i].setPosition(0,0);
                    okno.draw(f[i]);
                    f[i].setPosition(700,0);
                }

            for (int i = 18; i < 20; i++)
                {
                    f[i].setTexture(bierki);
                    f[i].setTextureRect(sf::IntRect(0, 0, 100, 100));
                    okno.draw(f[i]);
                    f[i].setPosition(0,700);
                    okno.draw(f[i]);
                    f[i].setPosition(700,700);
                }

            for (int i = 20; i < 22; i++)
                {
                    f[i].setTexture(bierki);
                    f[i].setTextureRect(sf::IntRect(100, 100, 100, 100));
                    okno.draw(f[i]);
                    f[i].setPosition(100,0);
                    okno.draw(f[i]);
                    f[i].setPosition(600,0);
                }

            for (int i = 22; i < 24; i++)
                {
                    f[i].setTexture(bierki);
                    f[i].setTextureRect(sf::IntRect(100, 0, 100, 100));
                    okno.draw(f[i]);
                    f[i].setPosition(100,700);
                    okno.draw(f[i]);
                    f[i].setPosition(600,700);
                }

            for (int i = 24; i < 26; i++)
                {
                    f[i].setTexture(bierki);
                    f[i].setTextureRect(sf::IntRect(200, 100, 100, 100));
                    okno.draw(f[i]);
                    f[i].setPosition(200,0);
                    okno.draw(f[i]);
                    f[i].setPosition(500,0);
                }

            for (int i = 26; i < 28; i++)
                {
                    f[i].setTexture(bierki);
                    f[i].setTextureRect(sf::IntRect(200, 0, 100, 100));
                    okno.draw(f[i]);
                    f[i].setPosition(200,700);
                    okno.draw(f[i]);
                    f[i].setPosition(500,700);
                }


            f[28].setTexture(bierki);
            f[28].setTextureRect(sf::IntRect(300, 100, 100, 100));
            okno.draw(f[28]);
            f[28].setPosition(300,000);

            f[29].setTexture(bierki);
            f[29].setTextureRect(sf::IntRect(300, 0, 100, 100));
            okno.draw(f[29]);
            f[29].setPosition(300,700);

            f[30].setTexture(bierki);
            f[30].setTextureRect(sf::IntRect(400, 100, 100, 100));
            okno.draw(f[30]);
            f[30].setPosition(400,000);

            f[31].setTexture(bierki);
            f[31].setTextureRect(sf::IntRect(400, 0, 100, 100));
            okno.draw(f[31]);
            f[31].setPosition(400,700);


        }
    //    graWToku = true;



        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            pozycjaMyszy = sf::Mouse::getPosition( okno );
            pozycjaMyszy.x = (pozycjaMyszy.x / 100) * 100;
            pozycjaMyszy.y = (pozycjaMyszy.y / 100) * 100;
            czyPoleZaznaczone = true;
            for (int i = 0; i < 32; i++)
            {
                if (f[i].getPosition().x == sf::Mouse::getPosition( okno ).x && f[i].getPosition().y == sf::Mouse::getPosition( okno ).y)
                {
                    //tutaj opcje dla pionkow
                }
            }


        }
        if (czyPoleZaznaczone == true)
        {
            okno.draw(zaznaczeniePola);
        }

        zaznaczeniePola.setPosition(pozycjaMyszy.x, pozycjaMyszy.y);

        okno.display();

    }

return 0;

}
