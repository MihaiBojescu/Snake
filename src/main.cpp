#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "../includes/game.h"

GLFWwindow* window;
game *Game;

void key_callback(GLFWwindow* window, int key, int scanCode, int action, int mods)
{
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
        Game->setDirection((point){0, -1});
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
        Game->setDirection((point){0, 1});
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS)
        Game->setDirection((point){1, 0});
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS)
        Game->setDirection((point){-1, 0});
    #ifdef DEBUG
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
        Game->generateFoodPiece();
    if (key == GLFW_KEY_H && action == GLFW_PRESS)
        Game->generateFoodPiece(1);
    #endif
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
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
    Game = new game(1, 3);

	do{
        if(Game->gameLoop() == 1)
        {
            std::cout<<"Score: "<<Game->getScores()[0]<<".\n";
            delete Game;
            Game = NULL;
        }
        else Game->drawGame();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	while(glfwWindowShouldClose(window) == 0 && Game != NULL);

    if(Game != NULL)
    {
        std::cout<<"Score: "<<Game->getScores()[0]<<".\n";
        delete Game;
    }
	glfwTerminate();

	return 0;
}
