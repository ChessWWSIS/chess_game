#include <SFML/Graphics.hpp>
#include <SFML/Config.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>


using namespace std;

sf::RenderWindow okno(sf::VideoMode(800,800),"Szachy");
sf::Event wydarzenie;
sf::Vector2i pozycjaMyszy, nowaPozycjaMyszy;
//    sf::Vector2f pozycjaMyszyNaScenie;

sf::Texture tekstura, zaznaPola, bierki, zaznaAtak;



sf::Sprite szachownica;
sf::Sprite f[32];
sf::Sprite zaznaczeniePola[61];




bool graWToku = false;
bool czyBiale[32];
bool ruchBialych = true;
int czyPoleZaznaczone = 0;
bool warunkowy = false;


int board [8][8];
int nowaPozycja(int x, int y);
bool czyNastRPionka[16];
int zaznaczonyPionek = -1;
int maxZaznaczen = 0;

int main()
{
    // ładowanie tekstur
    tekstura.loadFromFile( "images/szachownica.jpg" );
    zaznaPola.loadFromFile("images/zaznaPola.png");
    bierki.loadFromFile("images/bierki.png");
    zaznaAtak.loadFromFile("images/zaznaAtak.png");

    szachownica.setTexture(tekstura);

    for (int i = 0; i < 16; i++)
        {
            czyNastRPionka[i] = false;
        }

    for (int i = 0; i < 61; i++)
    {
        zaznaczeniePola[i].setTexture(zaznaPola);
    }


    for (int i = 0; i < 8; i++)
    {
        f[i].setTexture(bierki);
        //pobieranie grafiki konkretnego pionka | ponizej na tej samej zasadzie to dziala
        f[i].setTextureRect(sf::IntRect(500, 100, 100, 100));

        //przypisywanie id do tablicy | ponizej na tej samej zasadzie to dziala
        board[1][i] = i+1;
    }

    //rysowanie bialych pionkow
    for (int i = 8; i < 16; i++)
    {
        f[i].setTexture(bierki);
        f[i].setTextureRect(sf::IntRect(500, 0, 100, 100));
        board[6][i-8] = i+1;
    }

    //rysowanie czarnych wiez
    f[16].setTexture(bierki);
    f[16].setTextureRect(sf::IntRect(0, 100, 100, 100));
    board[0][0] = 17;

    f[17].setTexture(bierki);
    f[17].setTextureRect(sf::IntRect(0, 100, 100, 100));
    board[0][7] = 18;

    //rysowanie bialych wiez
    f[18].setTexture(bierki);
    f[18].setTextureRect(sf::IntRect(0, 0, 100, 100));
    board[7][0] = 19;

    f[19].setTexture(bierki);
    f[19].setTextureRect(sf::IntRect(0, 0, 100, 100));
    board[7][7] = 20;

    //rysowanie czarnych koni
    f[20].setTexture(bierki);
    f[20].setTextureRect(sf::IntRect(100, 100, 100, 100));
    board[0][1] = 21;

    f[21].setTexture(bierki);
    f[21].setTextureRect(sf::IntRect(100, 100, 100, 100));
    board[0][6] = 22;

    //rysowanie bialych koni
    f[22].setTexture(bierki);
    f[22].setTextureRect(sf::IntRect(100, 0, 100, 100));
    board[7][1] = 23;

    f[23].setTexture(bierki);
    f[23].setTextureRect(sf::IntRect(100, 0, 100, 100));
    board[7][6] = 24;

    //rysowanie czarnych goncow
    f[24].setTexture(bierki);
    f[24].setTextureRect(sf::IntRect(200, 100, 100, 100));
    board[0][2] = 25;

    f[25].setTexture(bierki);
    f[25].setTextureRect(sf::IntRect(200, 100, 100, 100));
    board[0][5] = 26;

    //rysowanie bialych goncow
    f[26].setTexture(bierki);
    f[26].setTextureRect(sf::IntRect(200, 0, 100, 100));
    board[7][2] = 27;

    f[27].setTexture(bierki);
    f[27].setTextureRect(sf::IntRect(200, 0, 100, 100));
    board[7][5] = 28;

    //rysowanie czarnego hetmana
    f[28].setTexture(bierki);
    f[28].setTextureRect(sf::IntRect(400, 100, 100, 100));
    board[0][3] = 29;

    //rysowanie bialego hetmana
    f[29].setTexture(bierki);
    f[29].setTextureRect(sf::IntRect(400, 0, 100, 100));
    board[7][3] = 30;

    //rysowanie czarnego krola
    f[30].setTexture(bierki);
    f[30].setTextureRect(sf::IntRect(300, 100, 100, 100));
    board[0][4] = 31;

    //rysowanie bialego krola
    f[31].setTexture(bierki);
    f[31].setTextureRect(sf::IntRect(300, 0, 100, 100));
    board[7][4] = 32;



    // główna pętla gry
    while(okno.isOpen())
    {
        //zamykanie gry
        while(okno.pollEvent(wydarzenie))
        {
            if(wydarzenie.type == sf::Event::KeyPressed && wydarzenie.key.code ==
                    sf::Keyboard::Escape)
                okno.close();
        }

        okno.draw(szachownica);



        //p pionków
        for (int i = 0; i < 32; i++)
        {
            okno.draw(f[i]);
        }
        if (graWToku == false)
        {

            //rysowanie czarnych pionkow

            for (int i = 0; i < 8; i++)
            {
                //ustawianie na konkrektnej pozycji | ponizej na tej samej zasadzie to dziala
                f[i].setPosition(100*i, 100);
                //przypisywanie id do tablicy | ponizej na tej samej zasadzie to dziala
                czyBiale[i] = false;
            }

            //rysowanie bialych pionkow
            for (int i = 8; i < 16; i++)
            {
                f[i].setPosition(100*(i-8), 600);
                czyBiale[i] = true;
            }

            //rysowanie czarnych wiez
            f[16].setPosition(0,0);
            czyBiale[16] = false;

            f[17].setPosition(700,0);
            czyBiale[17] = false;

            //rysowanie bialych wiez
            f[18].setPosition(0,700);
            czyBiale[18] = true;

            f[19].setPosition(700,700);
            czyBiale[19] = true;

            //rysowanie czarnych koni
            f[20].setPosition(100,0);
            czyBiale[20] = false;

            f[21].setPosition(600,0);
            czyBiale[21] = false;

            //rysowanie bialych koni
            f[22].setPosition(100,700);
            czyBiale[22] = true;

            f[23].setPosition(600,700);
            czyBiale[23] = true;

            //rysowanie czarnych goncow
            f[24].setPosition(200,0);
            czyBiale[24] = false;

            f[25].setPosition(500,0);
            czyBiale[25] = false;

            //rysowanie bialych goncow
            f[26].setPosition(200,700);
            czyBiale[26] = true;

            f[27].setPosition(500,700);
            czyBiale[27] = true;

            //rysowanie czarnego hetmana
            f[28].setPosition(300,000);
            czyBiale[28] = false;

            //rysowanie bialego hetmana
            f[29].setPosition(300,700);
            czyBiale[29] = true;

            //rysowanie czarnego krola
            f[30].setPosition(400,000);
            czyBiale[30] = false;

            //rysowanie bialego krola
            f[31].setPosition(400,700);
            czyBiale[31] = true;


        }
        graWToku = true;



        //pobieranie pozycji kliknięcia
//        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
//        {
//            pozycjaMyszy = sf::Mouse::getPosition( okno );
//            pozycjaMyszy.x = (pozycjaMyszy.x / 100) * 100;
//            pozycjaMyszy.y = (pozycjaMyszy.y / 100) * 100;
//
//            czyPoleZaznaczone = !czyPoleZaznaczone;
//
//
//        }
        if (wydarzenie.type == sf::Event::MouseButtonPressed)
        {
            if (wydarzenie.mouseButton.button == sf::Mouse::Left)
            {

                if ((wydarzenie.mouseButton.x / 100) * 100 != pozycjaMyszy.x || (wydarzenie.mouseButton.y / 100) * 100 != pozycjaMyszy.y)
                {
                    czyPoleZaznaczone++;
                }
                pozycjaMyszy.x = (wydarzenie.mouseButton.x / 100) * 100;
                pozycjaMyszy.y = (wydarzenie.mouseButton.y / 100) * 100;




            }


        }


        //zaznaczanie mozliwych ruchow
        if (czyPoleZaznaczone == 0)
        {

        }
        else if (czyPoleZaznaczone % 2 > 0)
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
                        if (czyNastRPionka[i] == false)
                        {
                            for (int j = 0; j < 2; j++)
                            {

                                for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x-100 == f[k].getPosition().x && f[i].getPosition().y+100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                    {
                                        okno.draw(zaznaczeniePola[j+2]);
                                        zaznaczeniePola[j+2].setPosition(f[i].getPosition().x-100,f[i].getPosition().y+100);
                                        maxZaznaczen = j+3;
                                    }
                                    else if (f[i].getPosition().x+100 == f[k].getPosition().x && f[i].getPosition().y+100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                    {
                                        okno.draw(zaznaczeniePola[j+4]);
                                        zaznaczeniePola[j+4].setPosition(f[i].getPosition().x+100,f[i].getPosition().y+100);
                                        maxZaznaczen = j+5;
                                    }
                                    else if (f[i].getPosition().x == f[k].getPosition().x && f[i].getPosition().y+((j+1)*100) == f[k].getPosition().y)
                                    {
                                        warunkowy = true;
                                    }
                                }
                                if (warunkowy == false)
                                    {
                                        okno.draw(zaznaczeniePola[j]);
                                        zaznaczeniePola[j].setPosition(f[i].getPosition().x,f[i].getPosition().y+((j+1)*100));
        //                                okno.draw(zaznaczeniePola);
        //                                zaznaczeniePola.setPosition(f[i].getPosition().x,f[i].getPosition().y+200);
                                        maxZaznaczen += 1;

                                    }
                            }
                            warunkowy = false;
                        }
                        else
                        {
                            for (int k = 0; k < 32; k++)
                            {
                                if (f[i].getPosition().x-100 == f[k].getPosition().x && f[i].getPosition().y+100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                {
                                    okno.draw(zaznaczeniePola[1]);
                                    zaznaczeniePola[1].setPosition(f[i].getPosition().x-100,f[i].getPosition().y+100);
                                    maxZaznaczen += 1;
                                }
                                else if (f[i].getPosition().x+100 == f[k].getPosition().x && f[i].getPosition().y+100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                {
                                    okno.draw(zaznaczeniePola[2]);
                                    zaznaczeniePola[2].setPosition(f[i].getPosition().x+100,f[i].getPosition().y+100);
                                    maxZaznaczen += 1;
                                }
                                if (f[i].getPosition().x == f[k].getPosition().x && f[i].getPosition().y+100 == f[k].getPosition().y)
                                {
                                    warunkowy = true;
                                }
                            }
                            if (warunkowy == false)
                            {
                                okno.draw(zaznaczeniePola[0]);
                                zaznaczeniePola[0].setPosition(f[i].getPosition().x,f[i].getPosition().y+100);
                                maxZaznaczen += 1;

                            }
                            warunkowy = false;

                        }
                    }
                    //zaznaczanie dla bialych pionkow
                    else if (i >= 8 && i < 16)
                    {
                       if (czyNastRPionka[i] == false)
                        {
                            for (int j = 0; j < 2; j++)
                            {

                                for (int k = 0; k < 32; k++)
                                {
                                    if (f[i].getPosition().x-100 == f[k].getPosition().x && f[i].getPosition().y-100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                    {
                                        okno.draw(zaznaczeniePola[j+2]);
                                        zaznaczeniePola[j+2].setPosition(f[i].getPosition().x-100,f[i].getPosition().y-100);
                                        maxZaznaczen = j+3;
                                    }
                                    else if (f[i].getPosition().x+100 == f[k].getPosition().x && f[i].getPosition().y-100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                    {
                                        okno.draw(zaznaczeniePola[j+4]);
                                        zaznaczeniePola[j+4].setPosition(f[i].getPosition().x+100,f[i].getPosition().y-100);
                                        maxZaznaczen = j+5;
                                    }
                                    else if (f[i].getPosition().x == f[k].getPosition().x && f[i].getPosition().y-((j+1)*100) == f[k].getPosition().y)
                                    {
                                        warunkowy = true;
                                    }
                                }
                                if (warunkowy == false)
                                    {
                                        okno.draw(zaznaczeniePola[j]);
                                        zaznaczeniePola[j].setPosition(f[i].getPosition().x,f[i].getPosition().y-((j+1)*100));
        //                                okno.draw(zaznaczeniePola);
        //                                zaznaczeniePola.setPosition(f[i].getPosition().x,f[i].getPosition().y+200);
                                        maxZaznaczen += 1;

                                    }
                            }
                            warunkowy = false;
                        }
                        else
                        {
                            for (int k = 0; k < 32; k++)
                            {
                                if (f[i].getPosition().x-100 == f[k].getPosition().x && f[i].getPosition().y-100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                {
                                    okno.draw(zaznaczeniePola[1]);
                                    zaznaczeniePola[1].setPosition(f[i].getPosition().x-100,f[i].getPosition().y-100);
                                    maxZaznaczen += 1;
                                }
                                else if (f[i].getPosition().x+100 == f[k].getPosition().x && f[i].getPosition().y-100 == f[k].getPosition().y && czyBiale[k] != ruchBialych)
                                {
                                    okno.draw(zaznaczeniePola[2]);
                                    zaznaczeniePola[2].setPosition(f[i].getPosition().x+100,f[i].getPosition().y-100);
                                    maxZaznaczen += 1;
                                }
                                if (f[i].getPosition().x == f[k].getPosition().x && f[i].getPosition().y-100 == f[k].getPosition().y)
                                {
                                    warunkowy = true;
                                }
                            }
                            if (warunkowy == false)
                            {
                                okno.draw(zaznaczeniePola[0]);
                                zaznaczeniePola[0].setPosition(f[i].getPosition().x,f[i].getPosition().y-100);
                                maxZaznaczen += 1;

                            }
                            warunkowy = false;

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
                                okno.draw(zaznaczeniePola[l+7]);
                                zaznaczeniePola[l+7].setPosition(f[i].getPosition().x,f[i].getPosition().y+(l*100));
                                maxZaznaczen = l+8;
                            }
                            if (j == 0) j++;
                            okno.draw(zaznaczeniePola[j+22]);
                            zaznaczeniePola[j+22].setPosition(f[i].getPosition().x+(j*100),f[i].getPosition().y);
                            maxZaznaczen = j+23;
                        }
                    }
                    //zaznaczanie dla wszystkich koni
                    else if (i >= 20 && i < 24)
                    {
                        okno.draw(zaznaczeniePola[0]);
                        zaznaczeniePola[0].setPosition(f[i].getPosition().x+100,f[i].getPosition().y+200);
                        okno.draw(zaznaczeniePola[1]);
                        zaznaczeniePola[1].setPosition(f[i].getPosition().x+100,f[i].getPosition().y-200);
                        okno.draw(zaznaczeniePola[2]);
                        zaznaczeniePola[2].setPosition(f[i].getPosition().x-100,f[i].getPosition().y+200);
                        okno.draw(zaznaczeniePola[3]);
                        zaznaczeniePola[3].setPosition(f[i].getPosition().x-100,f[i].getPosition().y-200);
                        okno.draw(zaznaczeniePola[4]);
                        zaznaczeniePola[4].setPosition(f[i].getPosition().x+200,f[i].getPosition().y+100);
                        okno.draw(zaznaczeniePola[5]);
                        zaznaczeniePola[5].setPosition(f[i].getPosition().x+200,f[i].getPosition().y-100);
                        okno.draw(zaznaczeniePola[6]);
                        zaznaczeniePola[6].setPosition(f[i].getPosition().x-200,f[i].getPosition().y+100);
                        okno.draw(zaznaczeniePola[7]);
                        zaznaczeniePola[7].setPosition(f[i].getPosition().x-200,f[i].getPosition().y-100);
                        maxZaznaczen = 8;
                    }
                    //znaznaczanie dla wszystkich goncow
                    else if (i >= 24 && i < 28)
                    {
                        for (int j = -7; j < 8; j++)
                        {
                            for (int l = -7; l < 8; l++)
                            {
                                if (l == 0) l++;
                                okno.draw(zaznaczeniePola[l+7]);
                                zaznaczeniePola[l+7].setPosition(f[i].getPosition().x+(l*100),f[i].getPosition().y+(l*100));
                                maxZaznaczen = l+8;
                            }
                            if (j == 0) j++;
                            okno.draw(zaznaczeniePola[j+22]);
                            zaznaczeniePola[j+22].setPosition(f[i].getPosition().x-(j*100),f[i].getPosition().y+(j*100));
                            maxZaznaczen = j+23;
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
                                okno.draw(zaznaczeniePola[l+7]);
                                zaznaczeniePola[l+7].setPosition(f[i].getPosition().x+(l*100),f[i].getPosition().y+(l*100));
                                maxZaznaczen = l+8;
                            }
                            if (j == 0) j++;
                            okno.draw(zaznaczeniePola[j+22]);
                            zaznaczeniePola[j+22].setPosition(f[i].getPosition().x-(j*100),f[i].getPosition().y+(j*100));
                            maxZaznaczen = j+23;
                        }
                        for (int j = -7; j < 8; j++)
                        {
                            for (int l = -7; l < 8; l++)
                            {
                                if (l == 0) l++;
                                okno.draw(zaznaczeniePola[l+37]);
                                zaznaczeniePola[l+37].setPosition(f[i].getPosition().x,f[i].getPosition().y+(l*100));
                                maxZaznaczen = l+38;
                            }
                            if (j == 0) j++;
                            okno.draw(zaznaczeniePola[j+52]);
                            zaznaczeniePola[j+52].setPosition(f[i].getPosition().x+(j*100),f[i].getPosition().y);
                            maxZaznaczen = j+53;
                        }
                    }
                    //zaznaczanie dla kroli
                    else if (i >=30 && i <32)
                    {

                        okno.draw(zaznaczeniePola[0]);
                        zaznaczeniePola[0].setPosition(f[i].getPosition().x+100,f[i].getPosition().y+100);
                        okno.draw(zaznaczeniePola[1]);
                        zaznaczeniePola[1].setPosition(f[i].getPosition().x+100,f[i].getPosition().y-100);
                        okno.draw(zaznaczeniePola[2]);
                        zaznaczeniePola[2].setPosition(f[i].getPosition().x+100,f[i].getPosition().y);
                        okno.draw(zaznaczeniePola[3]);
                        zaznaczeniePola[3].setPosition(f[i].getPosition().x-100,f[i].getPosition().y+100);
                        okno.draw(zaznaczeniePola[4]);
                        zaznaczeniePola[4].setPosition(f[i].getPosition().x-100,f[i].getPosition().y-100);
                        okno.draw(zaznaczeniePola[5]);
                        zaznaczeniePola[5].setPosition(f[i].getPosition().x-100,f[i].getPosition().y);
                        okno.draw(zaznaczeniePola[6]);
                        zaznaczeniePola[6].setPosition(f[i].getPosition().x,f[i].getPosition().y+100);
                        okno.draw(zaznaczeniePola[7]);
                        zaznaczeniePola[7].setPosition(f[i].getPosition().x,f[i].getPosition().y-100);
                        maxZaznaczen = 8;
                    }



                }
            }


        }

        //zmiana pozycji
        else if (czyPoleZaznaczone % 2 == 0)
        {
            if (czyBiale[zaznaczonyPionek] == ruchBialych)
            {
                for (int i = 0; i < maxZaznaczen; i++)
                {
                    if (pozycjaMyszy.x == zaznaczeniePola[i].getPosition().x && pozycjaMyszy.y == zaznaczeniePola[i].getPosition().y)
                    {

//                        board[pozycjaMyszy.y/100][pozycjaMyszy.x/100] = zaznaczonyPionek+1;
//                        board[int(f[zaznaczonyPionek].getPosition().y/100+0.5)][int(f[zaznaczonyPionek].getPosition().x/100+0.5)] = 0;
                        f[zaznaczonyPionek].setPosition(pozycjaMyszy.x,pozycjaMyszy.y);

                        for (int j = 0; j < 32; j++)
                        {

                            if (f[j].getPosition().x == f[zaznaczonyPionek].getPosition().x && f[j].getPosition().y == f[zaznaczonyPionek].getPosition().y && j != zaznaczonyPionek)
                            {
                                f[j].setPosition(1000,1000);
                                break;
                            }
                        }

                        if (zaznaczonyPionek < 16)
                        {
                            czyNastRPionka[zaznaczonyPionek] = true;
                        }
                        ruchBialych = !ruchBialych;


                    }
                    else
                    {
                        czyPoleZaznaczone = 0;
                    }
                }
                maxZaznaczen = 0;

            }






        }



        okno.display();

    }

    return 0;

}
