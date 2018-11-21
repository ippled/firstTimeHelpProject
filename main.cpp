#include <SFML/Graphics.hpp>
#include "GuiManager.h"
#include "CheckBox.h"
#include <iostream>
#include "math.h"

using namespace sf;
using namespace std;

#define sizeH 720
#define sizeW 1280
#define GRAY Color(110,110,110)
#define BOXNUMBER 5

enum State {mainMenu, choosingLevel, inGame, options, pause, credits, firstTimeHelp};

typedef struct
{
    int id, posX, posY;
    bool toggle;
    RectangleShape render;
} CheckBox;

RectangleShape createCheckBox(int id, int posX, int posY, bool toggle)
{
    RectangleShape box;
    box.setPosition(posX, posY);
    box.setSize(Vector2f(50,50));
    box.setOutlineThickness(5);
    box.setOutlineColor(GRAY);
    box.setFillColor(Color::Black);

    return box;
}

int main()
{
    GuiManager manager2("ank.ttf");
    State state = firstTimeHelp;
    Font font;
    Texture bg, checkedimg, level, pers, mouseimg, headphonesimg; // A AJOUTER
    Sprite background, backgroundlvl, perso, mouse, headphones; // A AJOUTER
    Sprite checked[BOXNUMBER];
    GuiManager manager("SoftMarshmallow.otf");

    int clickedBox;
    CheckBox box[BOXNUMBER];
    box[0] = {0,440,200, true};
    box[1] = {1,440,300, true};
    box[2] = {1,440,400, true};

    if(!bg.loadFromFile("main_menu.jpg"))
        return EXIT_FAILURE;
    if(!checkedimg.loadFromFile("checked.png"))
        return EXIT_FAILURE;
    if (!level.loadFromFile("level1.png"))
        return EXIT_FAILURE;
    if (!pers.loadFromFile("persostat.png"))
        return EXIT_FAILURE;
    if (!mouseimg.loadFromFile("mouse.png")) // A AJOUTER
        return EXIT_FAILURE;                    // A AJOUTER
    if (!headphonesimg.loadFromFile("headphones.png")) // A AJOUTER
        return EXIT_FAILURE;                            // A AJOUTER

    perso.setTexture(pers);
    perso.setPosition(720,385); // A MODIFIER

    mouse.setTexture(mouseimg); // A AJOUTER
    mouse.setPosition(50,400);  // A AJOUTER

    headphones.setTexture(headphonesimg); //  A AJOUTER
    headphones.setPosition(50,550);       // A AJOUTER

    backgroundlvl.setTexture(level);
    backgroundlvl.setPosition(620,230); // A MODIFIER

    RenderWindow window(VideoMode(sizeW,sizeH), "Brath", Style::Close);
    window.setVerticalSyncEnabled(false);
    background.setTexture(bg);

    int i;
    for (i = 0; i < BOXNUMBER; i++)
    {
        checked[i].setTexture(checkedimg);
        checked[i].setPosition(box[i].posX, box[i].posY);
    }

    if(!font.loadFromFile("SoftMarshmallow.otf"))
        return EXIT_FAILURE;
//////////////////////////////////////////////// MENU PRINCIPAL //////////////////////////////////////
    int PLAY = manager.addText("Play", {0.67*sizeW, 200}, 70, Color::White);
    int OPTIONS = manager.addText("Settings", {0.67*sizeW, 300}, 70, Color::White);
    int CREDITS = manager.addText("Credits", {0.67*sizeW, 400}, 70, Color::White);
    int EXIT = manager.addText("Leave game", {0.67*sizeW, 600}, 70, Color::White);
    int TITLE = manager.addText("Brath", {0.25*sizeW, 100}, 80, Color::White);

//////////////////////////////////////////////// TOUT CECI EST A MODIFIER /////////////////////////////////////////////
    int ALLYOUNEED = manager.addText("ALL YOU NEED TO KNOW", {350,10},60);
    int CONTROLS = manager2.addText("Controls:", {100,150},40);
    int WAYS = manager2.addText("Follow your instinct", {670,150},40);
    int ZKEY = manager2.addText("Z", {190,220},50);
    int QKEY = manager2.addText("Q", {130,280},50);
    int SKEY = manager2.addText("S", {190,280},50);
    int DKEY = manager2.addText("D", {250,280},50);

    int MOUSE = manager2.addText("Mouse can be used.", {90,400}, 40);
    int HEADPHONES = manager2.addText("Better experience\nwith headphones.", {90,520}, 40);
    int TIPS = manager2.addText("Pay attention to the\nbackground instructions.", {650,530}, 40);
    int CLICKANYWHERE = manager2.addText("Click anywhere to continue...", {730,670}, 40);
    manager2.changeColor(CLICKANYWHERE, Color(110,110,110));

    int idAvancer = manager2.addText("Jump", {160,340},40);
    int idDroite = manager2.addText("Right", {160,340},40);
    int idGauche = manager2.addText("Left", {160,340},40);

//////////////////////////////////////////////////////////////////////////////////////////////////////
    int choix = 0;
    manager.changeColor(choix, GRAY);
    manager.changeCharacterSize(choix, 80);
    Event event;
    window.setFramerateLimit(60);
displaymenu:
    while(window.isOpen())
    {

        switch(state)
        {
        case mainMenu:
            window.clear(Color::Black);
            window.draw(background);
            manager.renderText(&window, 0);
            manager.renderText(&window, 1);
            manager.renderText(&window, 2);
            manager.renderText(&window, 3);
            manager.renderText(&window, 4);
            window.display();

            while (window.pollEvent(event))
            {
                switch(event.type)
                {
                case Event::Closed:
                    window.close();
                    break;

                case Event::KeyPressed:
                    if (choix == -1) choix = 0;
                    if (event.key.code == Keyboard::Up && choix > 0)
                    {
                        manager.unselectText(choix);
                        choix--;
                        manager.selectText(choix);
                    }
                    else if (event.key.code == Keyboard::Down && choix < 3)
                    {
                        manager.unselectText(choix);
                        choix++;
                        manager.selectText(choix);
                    }

                    if (event.key.code == Keyboard::Space || event.key.code == Keyboard::Return)
                    {
                        if (event.mouseMove.x >= 0.67*sizeW && event.mouseMove.x <= 1250 && event.mouseMove.y >= 215 && event.mouseMove.y <= 690)
menuclicked:
                            switch(choix)
                            {
                            case 0:
                                state = inGame;
                                window.close();
                                break; // Bouton jouer
                            case 1:
                                state = options;

                                break; // Bouton options
                            case 2:
                                state = credits;
                                window.close();
                                break; // Bouton crédits
                            case 3:
                                window.close();
                                break; // Bouton quitter
                            }
                    }
                    break;

                case Event::MouseMoved:
                    if (event.mouseMove.x >= 0.65*sizeW && event.mouseMove.x <= 0.95*sizeW && (event.mouseMove.y >= 215 && event.mouseMove.y <= 490) || (event.mouseMove.y >= 615 && event.mouseMove.y <= 690) )
                    {
                        if (event.mouseMove.y >= 215 && event.mouseMove.y <= 290)
                        {
                            choix = 0; // Bouton jouer
                            manager.selectText(0);
                            manager.unselectText(1);
                            manager.unselectText(2);
                            manager.unselectText(3);
                        }
                        else if (event.mouseMove.y >= 315 && event.mouseMove.y <= 390)
                        {
                            choix = 1; // Bouton options
                            manager.unselectText(0);
                            manager.selectText(1);
                            manager.unselectText(2);
                            manager.unselectText(3);
                        }
                        else if (event.mouseMove.y >= 415 && event.mouseMove.y <= 490)
                        {
                            choix = 2; // Bouton crédits
                            manager.unselectText(0);
                            manager.unselectText(1);
                            manager.selectText(2);
                            manager.unselectText(3);
                        }
                        else if (event.mouseMove.y >= 615 && event.mouseMove.y <= 690)
                        {
                            choix = 3; // Boutton quitter
                            manager.unselectText(0);
                            manager.unselectText(1);
                            manager.unselectText(2);
                            manager.selectText(3);
                        }
                    }
                    else
                    {
                        manager.unselectText(0);
                        manager.unselectText(1);
                        manager.unselectText(2);
                        manager.unselectText(3);
                        choix = -1;
                    }
                    break;

                case Event::MouseButtonPressed:
                    if (event.mouseButton.button == Mouse::Left)
                        goto menuclicked;
                    break;

                }
            }

            break;

        case firstTimeHelp:
            state = firstTimeHelp;

            while(window.isOpen())
            {
                // TOUS LES WINDOW A MODIFIER
                window.clear(Color::Black);
                window.draw(background);
                window.draw(backgroundlvl);
                window.draw(perso);
                window.draw(mouse);
                window.draw(headphones);

                // 3 PROCHAINES LIGNES A MODIFIER
                    manager.renderText(&window, ALLYOUNEED);
                for (int i = 0; i < 12; i++)
                    manager2.renderText(&window, i);

                // A MODIFIER EGALEMENT
                if (Mouse::getPosition(window).x >= 190 && Mouse::getPosition(window).x <= 240 && Mouse::getPosition(window).y >= 220 && Mouse::getPosition(window).y <= 270 || event.key.code == Keyboard::Z)
                    manager2.renderText(&window, idAvancer);
                else if (Mouse::getPosition(window).x >= 250 && Mouse::getPosition(window).x <= 300 && Mouse::getPosition(window).y >= 280 && Mouse::getPosition(window).y <= 330 || event.key.code == Keyboard::D)
                    manager2.renderText(&window, idDroite);
                else if (Mouse::getPosition(window).x >= 130 && Mouse::getPosition(window).x <= 180 && Mouse::getPosition(window).y >= 280 && Mouse::getPosition(window).y <= 320 || event.key.code == Keyboard::Q)
                    manager2.renderText(&window, idGauche);

                window.display();
                // CE WHILE EST A MODIFIER, PSK JAI ENLEVE LE BOUTON ET ON DOIT JUSTE CLIQUER NIMPORTE OU
                while (window.pollEvent(event))
                {
                    switch(event.type)
                    {
                    case Event::Closed:
                        window.close();
                        break;
                    case Event::MouseButtonPressed:
                            state = mainMenu;
                            goto displaymenu;
                        break;
                    }
                }
            }
            break;
/////////////////////// FIN DES MODIFICATIONS
