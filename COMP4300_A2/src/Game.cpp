#include "Game.h"
#include "math.h"
#include "Vec2.h"

Game::Game(const std::string & config)
{ 
    init(config);
}

void Game::init(const std::string & path)
{
    // TODO
    // read in config file here
    std::ifstream fin("config.txt");
    std::string token,fdir;
    int winx, winy, FL, FS,size,f_r,f_g,f_b;
    sf::Font arial;

    while (fin.good())
    {
        fin>>token;
        if (token == "Window")
        {
            fin>>winx>>winy>>FL>>FS;
        }
        else if (token == "Font")
        {
            fin>>fdir>>size>>f_r>>f_g>>f_b;
            if (!arial.loadFromFile("fonts/arial.ttf"))
            {
                // if we can't load the font, print an error to the error console and exit
                std::cerr << "Could not load font!\n";
                exit(-1);
            }

            std::cout<<"font done";
        }
        else if (token == "Player")
        {
            PlayerConfig myPlayer;
            //fin>>myPlayer.SR>>CR>>S>>FR>>FG>>FB>>OR>>OG>>OB>>OT>>V;
        }
        else if (token == "Enemy")
        {

        }
        else if (token == "Bullet")
        {

        }
    }
    // set up default window parameters
    m_window.create(sf::VideoMode(1280, 720), "Assignment 2");
    m_window.setFramerateLimit(60);

    spawnPlayer();
    spawnEnemy();
}

void Game::run()
{
    // TODO: add pause functionality in here
    while (m_running)
    {
        m_entities.update();
        sEnemySpawner();
        sMovement();
        sCollision();
        sUserInput();
        sRender();
    }
}

void Game::setPaused(bool paused)
{
    // TODO
}

// respawn the player in the middle of the screen
void Game::spawnPlayer()
{
    // TODO: Finish adding all properties of the player with the correct values from the config
    Vec2 middle(m_window.getSize().x/2,m_window.getSize().y/2);
    // We create every entity by calling EntityManager.addEntity(tag)
    auto entity         = m_entities.addEntity("player");
    entity->cTransform  = new CTransform(middle, Vec2(1, 1), 0);
    entity->cShape      = new CShape(32, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4);
    m_player = entity;
}

// spawn an enemy at a random position
void Game::spawnEnemy()
{
    // TODO
    //getwin size 
    Vec2 pos(rand()%m_window.getSize().x, rand()%m_window.getSize().y);
    std::shared_ptr<Entity> entity   = m_entities.addEntity("enemy");
    entity->cTransform               = new CTransform(pos, Vec2(1, 1), 0);
    entity->cShape                   = new CShape(20, 9, sf::Color(rand()%255, rand()%255, rand()%255), sf::Color(255, 1, 255), 2);
    m_player = entity;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
    // TODO
    float anglediff,angle;
    
    int sides = e->cShape->circle.getPointCount();
    float radius = e->cShape->circle.getRadius();
    anglediff = 360/sides;

    for (int i=0; i<sides; i++)
    {
        angle = (anglediff * i)*M_PI /180;
        Vec2 speed(e->cTransform->speed.x, e->cTransform->speed.y);
        auto entity = m_entities.addEntity("smallenemies");
        entity ->cTransform = new CTransform((e->cTransform->pos),speed,angle);
        entity->cShape = new CShape(4, sides, sf::Color(rand()%255, rand()%255, rand()%255), sf::Color(255, 0, 0), 4);
    }

    
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & target)
{
    // TODO
    Vec2 distance;
    float angle;
    distance = target-entity->cTransform->pos;
    angle = atan2f(distance.y,distance.x);
    std::cout<<"Angle: "<<angle;
    Vec2 speed(10  * cos(angle), 10  * sin(angle));

    //m_bulletConfig.s * angle
    auto e = m_entities.addEntity("bullet");
    e->cTransform  = new CTransform(entity->cTransform->pos,speed, 0);
    e->cShape      = new CShape(8, 10, sf::Color(255,255,255), sf::Color(255, 0, 0), 4);
    
    std::cout<<"Spawn Bullet";
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
    // TODO
    
}

void Game::sMovement()
{
    // TODO
    /*
    // Sample movement speed update
    for (auto e : m_entities.getEntities())
    {
        if (e->cLifespan->lifespan)
        {
            if((e->cLifespan->clock)>(e->cLifespan->lifespan))
            {
                std::cout<<"move";
            }
        }
    }*/
    m_player->cTransform->pos.x += m_player->cTransform->speed.x;
    m_player->cTransform->pos.y += m_player->cTransform->speed.y;
}

void Game::sCollision()
{
    
    Vec2 distanceVec;
    float radiusDist,dist;

    for (auto b : m_entities.getEntities("bullet"))
    {
        for (auto e : m_entities.getEntities("enemy"))
        {
            distanceVec = (e->cTransform->pos - b->cTransform->pos);
            dist = sqrt(distanceVec.x * distanceVec.x + distanceVec.y *distanceVec.y);
            radiusDist = e->cShape->circle.getRadius() + b->cShape->circle.getRadius();
            if(radiusDist > dist)
            {
                spawnSmallEnemies(e);
                std::cout<<"Collided";
                e->destroy();
            }

        }
    } 
}

void Game::sEnemySpawner()
{
    // TODO
}

void Game::sRender()
{
    // TODO
    // sample drawing of the temporary Entity that we have created
    m_window.clear();

    for(auto e : m_entities.getEntities())
    {
        e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

    // set the rotation of the shape based on the entity's transform->angle
        e->cTransform->angle += 1.0f;
        e->cShape->circle.setRotation(e->cTransform->angle);

    // draw the entity's sf::CircleShape
        m_window.draw(e->cShape->circle);
    }
    // set the position of the shape based on the entity's transform->pos

    m_window.display();
}

void Game::sUserInput()
{
    // TODO
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        // this event triggers when the window is closed
        if (event.type == sf::Event::Closed)
        {
            m_running = false;
        }

        // this event is triggered when a key is pressed
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::W:
                    std::cout << "W Key Pressed\n";
                    break;
                case sf::Keyboard::E:
                    spawnEnemy();
                    std::cout << "E Key Pressed\n";
                    break;
            }
        }

        if (event.type == sf::Event::KeyReleased)
        {
            switch (event.key.code)
            {
                case sf::Keyboard::W:
                    std::cout << "W Key Released\n";
                    break;
            }
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                spawnBullet(m_player, Vec2(event.mouseButton.x,event.mouseButton.y));
                //std::cout << "Left Mouse Button Clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
            }

            if (event.mouseButton.button == sf::Mouse::Right)
            {
                std::cout << "Right Mouse Button Clicked at (" << event.mouseButton.x << "," << event.mouseButton.y << ")\n";
            }
        }
    }
}
