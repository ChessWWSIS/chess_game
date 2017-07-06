#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>

using namespace std;

int main()
{

    sf::RenderWindow okno(sf::VideoMode(800,800),"Szachy");
    sf::Event wydarzenie;
    sf::Vector2i pozycjaMyszy, nowaPozycjaMyszy;
//    sf::Vector2f pozycjaMyszyNaScenie;

    sf::Texture tekstura, zaznaPola, bierki;

    tekstura.loadFromFile( "images/szachownica.jpg" );
    zaznaPola.loadFromFile("images/zaznaPola.png");
    bierki.loadFromFile("images/bierki.png");

    sf::Sprite szachownica, zaznaczeniePola;
    sf::Sprite f[32];

    szachownica.setTexture(tekstura);
    zaznaczeniePola.setTexture(zaznaPola);


    bool graWToku = false;
    bool czyPoleZaznaczone = false;


    int board [8][8];
    int nowaPozycja(int x, int y);
    int czyNastRPionka[16];
    int zaznaczonyPionek;

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
                board[i][6] = i+1;
            }

            for (int i = 8; i < 16; i++)
            {
                f[i].setTexture(bierki);
                f[i].setTextureRect(sf::IntRect(500, 0, 100, 100));
                okno.draw(f[i]);
                f[i].setPosition(100*(i-8), 600);
                board[i-8][6] = i+1;
            }


            f[16].setTexture(bierki);
            f[16].setTextureRect(sf::IntRect(0, 100, 100, 100));
            okno.draw(f[16]);
            f[16].setPosition(0,0);
            board[0][0] = 17;

            f[17].setTexture(bierki);
            f[17].setTextureRect(sf::IntRect(0, 100, 100, 100));
            okno.draw(f[17]);
            f[17].setPosition(700,0);
            board[0][7] = 18;

            f[18].setTexture(bierki);
            f[18].setTextureRect(sf::IntRect(0, 0, 100, 100));
            okno.draw(f[18]);
            f[18].setPosition(0,700);
            board[7][0] = 19;

            f[19].setTexture(bierki);
            f[19].setTextureRect(sf::IntRect(0, 0, 100, 100));
            okno.draw(f[19]);
            f[19].setPosition(700,700);
            board[7][7] = 20;

            f[20].setTexture(bierki);
            f[20].setTextureRect(sf::IntRect(100, 100, 100, 100));
            okno.draw(f[20]);
            f[20].setPosition(100,0);
            board[0][1] = 21;

            f[21].setTexture(bierki);
            f[21].setTextureRect(sf::IntRect(100, 100, 100, 100));
            okno.draw(f[21]);
            f[21].setPosition(600,0);
                board[0][6] = 22;

            f[22].setTexture(bierki);
            f[22].setTextureRect(sf::IntRect(100, 0, 100, 100));
            okno.draw(f[22]);
            f[22].setPosition(100,700);
            board[7][1] = 23;

            f[23].setTexture(bierki);
            f[23].setTextureRect(sf::IntRect(100, 0, 100, 100));
            okno.draw(f[23]);
            f[23].setPosition(600,700);
            board[7][6] = 24;

            f[24].setTexture(bierki);
            f[24].setTextureRect(sf::IntRect(200, 100, 100, 100));
            okno.draw(f[24]);
            f[24].setPosition(200,0);
            board[0][2] = 25;

            f[25].setTexture(bierki);
            f[25].setTextureRect(sf::IntRect(200, 100, 100, 100));
            okno.draw(f[25]);
            f[25].setPosition(500,0);
            board[0][5] = 26;

            f[26].setTexture(bierki);
            f[26].setTextureRect(sf::IntRect(200, 0, 100, 100));
            okno.draw(f[26]);
            f[26].setPosition(200,700);
            board[7][2] = 27;

            f[27].setTexture(bierki);
            f[27].setTextureRect(sf::IntRect(200, 0, 100, 100));
            okno.draw(f[27]);
            f[27].setPosition(500,700);
            board[7][5] = 28;

            f[28].setTexture(bierki);
            f[28].setTextureRect(sf::IntRect(300, 100, 100, 100));
            okno.draw(f[28]);
            f[28].setPosition(300,000);
            board[0][3] = 29;

            f[29].setTexture(bierki);
            f[29].setTextureRect(sf::IntRect(300, 0, 100, 100));
            okno.draw(f[29]);
            f[29].setPosition(300,700);
            board[7][3] = 30;

            f[30].setTexture(bierki);
            f[30].setTextureRect(sf::IntRect(400, 100, 100, 100));
            okno.draw(f[30]);
            f[30].setPosition(400,000);
            board[0][4] = 31;

            f[31].setTexture(bierki);
            f[31].setTextureRect(sf::IntRect(400, 0, 100, 100));
            okno.draw(f[31]);
            f[31].setPosition(400,700);
            board[7][4] = 32;


        }
        //graWToku = true;



        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            pozycjaMyszy = sf::Mouse::getPosition( okno );
            pozycjaMyszy.x = (pozycjaMyszy.x / 100) * 100;
            pozycjaMyszy.y = (pozycjaMyszy.y / 100) * 100;

            czyPoleZaznaczone = !czyPoleZaznaczone;


        }
        if (czyPoleZaznaczone == false)
        {
            for (int i = 0; i < 32; i++)
            {
                if (f[i].getPosition().x == pozycjaMyszy.x && f[i].getPosition().y == pozycjaMyszy.y)
                {
                    zaznaczonyPionek = i;

//zaznaczaie mozliwych ruchow
                //zaznaczanie dla czarnych pionkow
                    if (i < 8)
                    {
                        if (czyNastRPionka[i] == 0)
                        {
                            okno.draw(zaznaczeniePola);
                            zaznaczeniePola.setPosition(f[i].getPosition().x,f[i].getPosition().y+100);
                            okno.draw(zaznaczeniePola);
                            zaznaczeniePola.setPosition(f[i].getPosition().x,f[i].getPosition().y+200);
                        }
                        else
                        {
                            okno.draw(zaznaczeniePola);
                            zaznaczeniePola.setPosition(f[i].getPosition().x,f[i].getPosition().y+100);
                        }
                    }
                //zaznaczanie dla bialych pionkow
                    else if (i >= 8 && i < 16)
                    {
                        if (czyNastRPionka[i] == 0)
                        {
                            okno.draw(zaznaczeniePola);
                            zaznaczeniePola.setPosition(f[i].getPosition().x,f[i].getPosition().y-100);
                            okno.draw(zaznaczeniePola);
                            zaznaczeniePola.setPosition(f[i].getPosition().x,f[i].getPosition().y-200);
                        }
                        else
                        {
                            okno.draw(zaznaczeniePola);
                            zaznaczeniePola.setPosition(f[i].getPosition().x,f[i].getPosition().y-100);
                        }
                    }
                //zaznaczanie wszystkich wiez
                    else if (i >= 16 && i < 20)
                    {
                        for (int j = -7; j < 8; j++)
                        {
                                for (int l = -7; l < 8; l++)
                                {
                                    if (l == 0) l++;
                                    okno.draw(zaznaczeniePola);
                                    zaznaczeniePola.setPosition(f[i].getPosition().x,f[i].getPosition().y+(l*100));
                                }
                            if (j == 0) j++;
                            okno.draw(zaznaczeniePola);
                            zaznaczeniePola.setPosition(f[i].getPosition().x+(j*100),f[i].getPosition().y);
                        }
                    }
                //zaznaczanie dla wszystkich koni
                    else if (i >= 20 && i < 24)
                    {
                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x+100,f[i].getPosition().y+200);
                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x+100,f[i].getPosition().y-200);
                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x-100,f[i].getPosition().y+200);
                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x-100,f[i].getPosition().y-200);
                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x+200,f[i].getPosition().y+100);
                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x+200,f[i].getPosition().y-100);
                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x-200,f[i].getPosition().y+100);
                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x-200,f[i].getPosition().y-100);
                    }
                //znaznaczanie dla wszystkich goncow
                    else if (i >= 24 && i < 28)
                    {
                        for (int j = -7; j < 8; j++)
                        {
                                for (int l = -7; l < 8; l++)
                                {
                                    if (l == 0) l++;
                                    okno.draw(zaznaczeniePola);
                                    zaznaczeniePola.setPosition(f[i].getPosition().x+(l*100),f[i].getPosition().y+(l*100));
                                }
                            if (j == 0) j++;
                            okno.draw(zaznaczeniePola);
                            zaznaczeniePola.setPosition(f[i].getPosition().x-(j*100),f[i].getPosition().y+(j*100));
                        }
                    }
                //zaznaczenie dla hetmanów
                    else if (i >=28 && i < 30)
                    {
                        for (int j = -7; j < 8; j++)
                        {
                                for (int l = -7; l < 8; l++)
                                {
                                    if (l == 0) l++;
                                    okno.draw(zaznaczeniePola);
                                    zaznaczeniePola.setPosition(f[i].getPosition().x+(l*100),f[i].getPosition().y+(l*100));
                                    okno.draw(zaznaczeniePola);
                                    zaznaczeniePola.setPosition(f[i].getPosition().x,f[i].getPosition().y+(l*100));
                                }
                            if (j == 0) j++;
                            okno.draw(zaznaczeniePola);
                            zaznaczeniePola.setPosition(f[i].getPosition().x-(j*100),f[i].getPosition().y+(j*100));
                            okno.draw(zaznaczeniePola);
                            zaznaczeniePola.setPosition(f[i].getPosition().x+(j*100),f[i].getPosition().y);
                        }
                    }
                //zaznaczanie dla kroli
                    else if (i >=30 && i <32)
                    {

                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x+100,f[i].getPosition().y+100);
                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x+100,f[i].getPosition().y-100);
                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x+100,f[i].getPosition().y);
                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x-100,f[i].getPosition().y+100);
                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x-100,f[i].getPosition().y-100);
                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x-100,f[i].getPosition().y);
                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x,f[i].getPosition().y+100);
                        okno.draw(zaznaczeniePola);
                        zaznaczeniePola.setPosition(f[i].getPosition().x,f[i].getPosition().y-100);
                    }



                }
            }


        }

        else if (czyPoleZaznaczone == true)
        {

            //zmiana pozycji

            f[zaznaczonyPionek].setPosition(pozycjaMyszy.x,pozycjaMyszy.y);



        }



        okno.display();

    }

return 0;

}
