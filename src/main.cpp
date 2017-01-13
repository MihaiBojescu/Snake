#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../includes/game.h"
#include "../includes/scores.h"
#include "../includes/menus.h"
#include "../includes/files.h"

GLFWwindow* window;
game *Game;
menu *mainMenu;
menu *score;
textHelper *scorePrinter;
scores *scoreBoard;

float unselectedColors[3] = {0.7f, 0.7f, 0.7f};
float selectedColors[3] = {0.9f, 0.5f, 0.2f};

int minBetween(int a, int b)
{
    return a > b ? b : a;
}

void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    if(key == GLFW_KEY_UP && action == GLFW_PRESS)
        if(mainMenu->getDisabled() == true && score->getDisabled() == true)
            Game->setDirection((point){0, -1});
        else if(mainMenu->getDisabled() == false)
            mainMenu->selectItem(-1);

    if(key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        if(mainMenu->getDisabled() == true && score->getDisabled() == true)
            Game->setDirection((point){0, 1});
        else if(mainMenu->getDisabled() == false)
            mainMenu->selectItem(1);

    if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        Game->setDirection((point){1, 0});

    if(key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        Game->setDirection((point){-1, 0});

    if(key == GLFW_KEY_ENTER && action == GLFW_PRESS)
        if(mainMenu->getDisabled() == false)
            switch(mainMenu->getSelectedItem())
            {
                case 0:
                    Game = new game(1);
                    mainMenu->setDisabled(true);
                    score->setDisabled(true);
                    break;
                case 1:
                    delete score;
                    score = new menu(20, 600, unselectedColors, unselectedColors);
                    score->addItem("Scores");

                    scoreBoard = new scores("game.scoreBoard");
                    for(int i = 0; i < (scoreBoard->getScores().size() < 6 ? scoreBoard->getScores().size() : 6); i++)
                        score->addItem(scoreBoard->getScores()[i]);
                    delete scoreBoard;

                    mainMenu->setDisabled(true);
                    score->setDisabled(false);
                    break;
                case 2:
                    glfwSetWindowShouldClose(window, GLFW_TRUE);
                    break;
            }
        else if(score->getDisabled() == false)
        {
            score->setDisabled(true);
            mainMenu->setDisabled(false);
        }

    #ifdef DEBUG
    if(key == GLFW_KEY_F && action == GLFW_PRESS)
        Game->generateFoodPiece();
    if(key == GLFW_KEY_H && action == GLFW_PRESS)
        Game->generateFoodPiece(1);
    #endif
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    #ifdef DEBUG
    std::cout<<"key: "<<key<<"\n";
    #endif
}

int main(int argc, char **argv)
{
	if(!glfwInit())
	{
		return -1;
	}

    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(800, 800, "Snake", NULL, NULL);
	if(window == NULL)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);
    glViewport(0, 0, 800, 800);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mainMenu = new menu(20, 600, unselectedColors, selectedColors);
    mainMenu->addItem("Main menu");
    mainMenu->addItem("Play");
    mainMenu->addItem("Scores");
    mainMenu->addItem("Exit");
    mainMenu->setDisabled(false);

    score = new menu(20, 600, unselectedColors, unselectedColors);
    score->addItem("Scores");
    score->setDisabled(true);

    scorePrinter = new textHelper("/usr/share/fonts/TTF/DejaVuSansMono-Bold.ttf", 20);

	do{
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT);
	    if(Game != NULL)
	    {
            if(Game->gameLoop() == 1)
            {
                writeScores("game.scoreBoard", "User " + std::to_string(Game->getScores()[0]));
                delete Game;

                Game = NULL;
                mainMenu->setDisabled(false);
            }
            else
            {
                Game->drawGame();
                scorePrinter->renderTextAt("Score: " + std::to_string(Game->getScores()[0]), 0, 780, 1, unselectedColors);
            }
        }
        else
        {
            mainMenu->draw();
            score->draw();
        }

        glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while(glfwWindowShouldClose(window) == 0);

    if(Game != NULL)
    {
        writeScores("game.scoreBoard", "User " + std::to_string(Game->getScores()[0]));
        delete Game;
    }

    delete mainMenu;
    delete score;
	glfwTerminate();

	return 0;
}

