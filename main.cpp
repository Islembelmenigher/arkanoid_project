#include <SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include <SFML/System.hpp>
#include<sfml/Audio.hpp>
#include <time.h>
#include<iostream>
using namespace sf;






int main()
{
// m is used for counting the number of the bricks
int m=100;
    srand(time(0));

    RenderWindow app(VideoMode(520, 450), "Arkanoid!");
    app.setFramerateLimit(60);

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("C:/Users/Lenovo/Documents/game_f/audio/endm.wav"))
    {
        // Error handling if the audio file fails to load
       std::cout<<" could not load the audio"<<std::endl;
    }
    sf::Music backgroundMusic;
        if (!backgroundMusic.openFromFile("C:/Users/Lenovo/Documents/game_f/audio/gameplay.wav"))
        {
            // Handle error loading the sound
            std::cout<<" could not load the audio"<<std::endl;
        }
        backgroundMusic.setLoop(true);
        backgroundMusic.play();
        sf::Music win;
            if (!win.openFromFile("C:/Users/Lenovo/Documents/game_f/audio/win.wav"))
            {
                // Handle error loading the sound
                std::cout<<" could not load the audio"<<std::endl;
            }

    Font font;
    if (!font.loadFromFile("C:/Users/Lenovo/Documents/game_f/fonts/ARIALI 1.ttf"))
    {
        // Error handling if the font fails to load
        // Handle the error as per your requirements
        std::cout<<" could not load the font"<<std::endl;
    }

    // Create text object
    Text text;
    text.setFont(font);
    text.setCharacterSize(28);
    text.setFillColor(Color::Black);
    text.setPosition(100, 200);
    text.setString("You failed! Press Space to restart");
// this part is just to create a background colore for the text
    RectangleShape textBackground;
    textBackground.setSize(Vector2f(text.getLocalBounds().width, text.getLocalBounds().height));
    textBackground.setFillColor(Color::Yellow);
    textBackground.setPosition(text.getPosition());

    // Adjust text and background positions
    float textX = (app.getSize().x - text.getLocalBounds().width) / 2.0f;
    float textY = (app.getSize().y - text.getLocalBounds().height) / 2.0f;
    text.setPosition(textX, textY);
    textBackground.setPosition(textX, textY);
    sf::Sound sound;
    sound.setBuffer(buffer);

    Texture t1,t2,t3,t4;
    t1.loadFromFile("C:/Users/Lenovo/Documents/game_f/images/block02.png");
    t2.loadFromFile("C:/Users/Lenovo/Documents/game_f/images/background.png");
    t3.loadFromFile("C:/Users/Lenovo/Documents/game_f/images/ball.png");
    t4.loadFromFile("C:/Users/Lenovo/Documents/game_f/images/paddle.png");

    Sprite sBackground(t2), sBall(t3), sPaddle(t4);
    sPaddle.setPosition(300,440);

    Sprite block[1000];

    int n=0;
    for (int i=1;i<=10;i++)
    for (int j=1;j<=10;j++)
      {
         block[n].setTexture(t1);
         block[n].setPosition(i*43,j*20);
         n++;
      }
    std::cout<<"the num of blocks is : "<<n<<std::endl;

    float dx=6, dy=5;
    float x=300, y=300;

    bool ballMoving = true;
    bool gameOver = false;

    while (app.isOpen())
    {
       Event e;
       while (app.pollEvent(e))
       {
         if (e.type == Event::Closed)
             app.close();
         else if (e.type == Event::KeyPressed)
                 {
                     if (e.key.code == Keyboard::Space && gameOver)
                     {
                         // Reset the game if spacebar is pressed and game over
                         ballMoving = true;
                         gameOver = false;
                         text.setString("");
                         backgroundMusic.play();

                     }
                 }
       }
       if (ballMoving)
          {
    x+=dx;
    for (int i=0;i<n;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) )
             {
            //if the ball toch a block it will be moved outside the view
            block[i].setPosition(-100,0);
            dx=-dx;
//counting the new number of the blocks

            m=m-1;
            std::cout<<"the num of blocks is : "<<m<<std::endl;
        }

    y+=dy;
    for (int i=0;i<n;i++)
        if ( FloatRect(x+3,y+3,6,6).intersects(block[i].getGlobalBounds()) )
             {
            //if the ball toch a block it will be moved outside the view
            block[i].setPosition(-100,0);
            dy=-dy;
            //counting the new number of the blocks
           // m=n;
            m=m-1;
        std::cout<<"the num of blocks is : "<<m<<std::endl;



        }


    if (x<0 || x>520)  dx=-dx;
    if (y<0 || y>450)  dy=-dy;

    if (Keyboard::isKeyPressed(Keyboard::Right)){
        if (sPaddle.getPosition().x + sPaddle.getLocalBounds().width < app.getSize().x)
            sPaddle.move(7,0);
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)){
        if (sPaddle.getPosition().x > 0)
        sPaddle.move(-7,0);
    }
   if (m==0){    //here we check if the player is a winer

      ballMoving = false;
       gameOver = true;
       text.setString("You won!!!!!");
       backgroundMusic.stop();
       win.play();
        std::cout<<" you won !!!!!!"<<std::endl;
   }
    if ( FloatRect(x,y,12,12).intersects(sPaddle.getGlobalBounds()) ) dy=-(rand()%5+2);
    if (y > 450)
            {
                // Ball hit the bottom
                ballMoving = false;
                gameOver = true;
                text.setString("You failed! Press Space to restart");
                std::cout<<" you failed"<<std::endl;


                               sound.play();


                               // Stop the background music
                               backgroundMusic.stop();

            }
}

    sBall.setPosition(x,y);

    app.clear();
    app.draw(sBackground);
    app.draw(sBall);
    app.draw(sPaddle);


    for (int i=0;i<n;i++)
     app.draw(block[i]);
    if (gameOver){
        app.draw(textBackground);
                app.draw(text);


    }

    app.display();
    }

  return 0;
}
