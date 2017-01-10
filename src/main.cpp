#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../includes/game.h"
#include "../includes/AI.h"
#include "../includes/menus.h"

GLFWwindow* window;
game *Game;
menu *mainMenu;
menu *scores;

void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    if(key == GLFW_KEY_UP && action == GLFW_PRESS)
        if(mainMenu->getDisabled() == true && scores->getDisabled() == true)
            Game->setDirection((point){0, -1});
        else if(mainMenu->getDisabled() == false)
            mainMenu->selectItem(-1);

    if(key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        if(mainMenu->getDisabled() == true && scores->getDisabled() == true)
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
                    break;
                case 1:
                    mainMenu->setDisabled(true);
                    scores->setDisabled(false);
                    break;
                case 2:
                    break;
            }
        else if(scores->getDisabled() == false)
        {
            scores->setDisabled(false);
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

    float unselectedColors[3] = {0.7f, 0.7f, 0.7f};
    float selectedColors[3] = {1.0f, 1.0f, 1.0f};

    mainMenu = new menu(20, 600, unselectedColors, selectedColors);
    mainMenu->addItem("Main menu");
    mainMenu->addItem("Play");
    mainMenu->addItem("Scores");
    mainMenu->addItem("Exit");
    mainMenu->setDisabled(false);

    scores = new menu(20, 600, unselectedColors, unselectedColors);
    scores->addItem("Scores");
    scores->setDisabled(true);

    Game = new game(1, 3);

	do{
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	    glClear(GL_COLOR_BUFFER_BIT);
        if(Game->gameLoop() == 1)
        {
            std::cout<<"Score: "<<Game->getScores()[0]<<".\n";
            delete Game;
            Game = NULL;
        }
        else
        {
            Game->drawGame();
            mainMenu->draw();
            scores->draw();
        }
        glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while(glfwWindowShouldClose(window) == 0 && Game != NULL);

    if(Game != NULL)
    {
        std::cout<<"Score: "<<Game->getScores()[0]<<".\n";
        delete Game;
        delete mainMenu;
        delete scores;
    }
	glfwTerminate();

	return 0;
}

