
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>

SDL_Window* displayWindow;


class Paddle
{
public:
    Paddle(float xx, float yy, float rotation1,  float speed1)
    {
        xPos = xx;
        yPos = yy;
        rotation = rotation1;
        speed = speed1;
    }
    void Draw(const char *image_path , bool RGB);
    void Move(const Uint8 *KeyboardState , float elapsed , bool player);
    float xPos;
    float yPos;
    float rotation;
    
    float getYPos()
    {
        return yPos;
    }
    float getXPos()
    {
        return xPos;
    }
    
    float speed;
    
    
};

class Ball
{
public:
    Ball(float xPos1 , float yPos1 , float speed1 , float yDirection1 , float xDirection1)
    {
        xPos = xPos1;
        yPos = yPos1;
        speed = speed1;
        yDirection = yDirection1;
        xDirection = xDirection1;
    }
    void Draw(const char *image_path , bool RGB);
    void Move(const Uint8 *KeyboardState , float elapsed);
    void Collide(float yPos , float xPos);
    
    float xPos;
    float yPos;
    
    float speed;
    
    float yDirection;
    float xDirection;
    
};
void setup()
{
    
SDL_Init(SDL_INIT_VIDEO);
displayWindow = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL);
SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
SDL_GL_MakeCurrent(displayWindow, context);
    
}


GLuint LoadTexture(const char *image_path , bool RGB)
{
    SDL_Surface *surface = IMG_Load(image_path);
    
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    if(RGB)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0,GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
    }
    else if (!RGB)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, 4, surface->w, surface->h, 0, GL_BGRA, GL_UNSIGNED_BYTE,
                     surface->pixels);
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    SDL_FreeSurface(surface);
    return textureID;
}

void Ball::Draw(const char *image_path , bool RGB)
{
    GLuint ballTexture = LoadTexture(image_path , true);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ballTexture);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(Ball::xPos , Ball::yPos , 0.0);
    
    GLfloat quad[] = {-0.05f , 0.07f , -0.05f , -0.05f , 0.05f , -0.05f , 0.05f , 0.07f};
    glVertexPointer(2, GL_FLOAT, 0 , quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
}

void Paddle::Draw(const char *image_path, bool RGB)
{
    GLuint paddleTexture = LoadTexture(image_path , true);
    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, paddleTexture);
    
    glMatrixMode(GL_MODELVIEW);
    
    glLoadIdentity();
    glTranslatef(Paddle::xPos , Paddle::yPos , 0.0);
    
    GLfloat quad[] = {-0.05f , 0.2f , -0.05f , -0.2f , 0.05f , -0.2f , 0.05f , 0.2f};
    glVertexPointer(2, GL_FLOAT, 0 , quad);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    GLfloat quadUVs[] = {0.0, 0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0};
    glTexCoordPointer(2, GL_FLOAT, 0, quadUVs);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glDrawArrays(GL_QUADS, 0, 4);
    glDisable(GL_TEXTURE_2D);
    
}

void Paddle::Move(const Uint8 *keys , float elapsed , bool player)
{
    if (!player)
    {
        if(keys[SDL_SCANCODE_W])
            {
                Paddle::yPos += Paddle::speed * elapsed;
                if(Paddle::yPos > 1.0f)
                {
                    yPos = 1.0f;
                }
            
            }
        if(keys[SDL_SCANCODE_S])
        {
            Paddle::yPos -= Paddle::speed * elapsed;
            if(Paddle::yPos < -1.0f)
            {
            yPos = -1.0f;
            }
        }
    }
    if (player)
    {
        if(keys[SDL_SCANCODE_UP])
        {
            Paddle::yPos += Paddle::speed * elapsed;
            if(Paddle::yPos > 1.0f)
            {
                yPos = 1.0f;
            }
       
        }
        if(keys[SDL_SCANCODE_DOWN])
        {
            Paddle::yPos -= Paddle::speed * elapsed;
            if(Paddle::yPos < -1.0f)
            {
                yPos = -1.0f;
            }
        }
    }
}

void Ball::Move(const Uint8 *KeyboardState, float elapsed)
{
    int upOrDown = rand() % 1 + 0;
    int leftOrRight = rand() % 1 + 0;
    Ball::yDirection = .35;
    Ball::xDirection = -.35;
    if(upOrDown == 1)
    {
        Ball::yDirection = .35;
    }
    else
    {
        Ball::yDirection = -.35;
    }
    if(leftOrRight == 1)
    {
        Ball::xDirection = -.35;
    }
    else
    {
        Ball::xDirection = .35;
    }
    if(Ball::speed == 0.0f)
    {
        if(KeyboardState[SDL_SCANCODE_SPACE])
        {
            Ball::speed = 2.0f;
        }
    }
    
    Ball::xPos += (Ball::xDirection * Ball::speed) * elapsed;
    Ball::yPos += (Ball::yDirection * Ball::speed) * elapsed;
    
}

void Ball::Collide(float yPos , float xPos)
{
    float height = 400.0f;
    float width = 300.0f;
    float playeryPos = abs(yPos * 400.0f);
    float tempxPos =(Ball::xPos * 300);
    float tempyPos =abs((Ball::yPos * 400)) + 21.0f;
    if (tempxPos == 1.0f)
    {
        if(tempxPos > (width - 44.0f) && (tempyPos == playeryPos+160 | tempyPos == playeryPos-160))
        {
            Ball::xDirection = -Ball::xDirection;
        }
        else
        {
            
        }
    }
    if(tempxPos == -1.0f)
    {
        if(tempxPos < (width +44.0f) && tempyPos == playeryPos+160 | tempyPos == playeryPos-160)
        {
            Ball::xDirection = -Ball::xDirection;
        }
    
    }
    
    
    if(tempyPos > height)
    {
        Ball::yDirection = -Ball::yDirection;
    }
  
}

void loop()
{
    const Uint8 *keys = SDL_GetKeyboardState(nullptr);
    float lastFrameTicks = 0.0f;
    bool done = false;
    SDL_Event event;
    Paddle paddle1(-1.0f , 0.0f , 0.0f, 5.0f);
    Paddle paddle2(1.0f , 0.0f , 0.0f, 5.0f);
    Ball ball(0.0f , 0.0f , 0.0f ,  0.0f , 5.0f);
	while (!done)
    {
		while (SDL_PollEvent(&event))
        {
			if (event.type == SDL_QUIT || event.type == SDL_WINDOWEVENT_CLOSE)
            {
				done = true;
                
			}
            
		}
        
        float ticks = (float)SDL_GetTicks()/1000.0f; // Keeping time in game.
        float elapsed = ticks - lastFrameTicks;
        lastFrameTicks = ticks;
        glClearColor(0.0f , 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
        paddle1.Draw("xDjNh.png" , false);
        paddle1.Move(keys, elapsed , true );
        float yPaddle1Pos = paddle1.getYPos();
        float xPaddle1Pos = paddle1.getXPos();
        ball.Collide(yPaddle1Pos, xPaddle1Pos);
        
        
        paddle2.Draw("xDjNh.png" , false);
        paddle2.Move(keys, elapsed , false );
        float yPaddle2Pos = paddle2.getYPos();
        float xPaddle2Pos = paddle2.getXPos();
        ball.Collide(yPaddle2Pos, xPaddle2Pos);
        
        ball.Draw("black_dots.png" , true);
        ball.Move(keys, elapsed);
    
        
        
        SDL_GL_SwapWindow(displayWindow);

	}

}


int main(int argc, char *argv[])
{
    
	setup();
    
    loop();
	
	
    
	
    
	SDL_Quit();
	return 0;
}