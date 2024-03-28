// test.c
#define GLAD_GL_IMPLEMENTATION
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iostream>
#include "voronoi.hpp"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>


#define POINTCOUNT 5
int windowX = 1024;
int windowY = 1024;
glm::mat4 projectionMatrix = glm::ortho(0.0f, static_cast<float>(windowX), 0.0f, static_cast<float>(windowY), -1.0f, 1.0f);

voronoi_diagram<double> vd;

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 projection;\n"
    "void main()\n"
    "{\n"
    " gl_Position = projection * vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
    "uniform vec4 ourColor;\n" 
    "out vec4 FragColor;\n" 
    "void main()\n"
    "{\n"
    " FragColor = ourColor;\n"
    "}\0";




void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);

}
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


void displayPoints(unsigned int shaderProgram, unsigned int VAO)
{
    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    timeValue = glfwGetTime();
    float redValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

    glUseProgram(shaderProgram);
    glUniform4f(vertexColorLocation, redValue, greenValue, 0.2f, 1.0f);

    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_POINTS, 0, POINTCOUNT*POINTCOUNT);
};
void displayCells(unsigned int shaderProgram, unsigned int VAO)
{
    GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    float timeValue = glfwGetTime();
    float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
    timeValue = glfwGetTime();
    float redValue = (sin(timeValue) / 2.0f) + 0.5f;
    int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

    glUseProgram(shaderProgram);
    glUniform4f(vertexColorLocation, redValue, greenValue, 0.2f, 1.0f);

    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glDrawArrays(GL_POINTS, 0, POINTCOUNT*POINTCOUNT);
}

int main(void)
{
    std::vector<GamePoint> points;
    std::vector<float> printPoints;
    std::vector<double> printCells;
    float poissonRadius;



// glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(windowX, windowY, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);



    /* Point initialization */
    poissonRadius = (windowX/POINTCOUNT + windowY/POINTCOUNT)/4;
    possionDiskSampling(points,POINTCOUNT,poissonRadius,windowX,windowY);
    std::cout << points.size() << std::endl;
    for (auto & point : points) 
    {
        printPoints.push_back(point.getX());
        printPoints.push_back(point.getY());
        printPoints.push_back(point.getZ());
    }
    buildVoronoi(points, vd);

    for (voronoi_diagram<double>::const_cell_iterator it = vd.cells().begin();it != vd.cells().end(); ++it) 
    {
        const voronoi_diagram<double>::cell_type &cell = *it;
        std::cout << cell.source_index() << std::endl;
        printCells.push_back(points[cell.source_index()].getX());
        printCells.push_back(points[cell.source_index()].getY());
        printCells.push_back(points[cell.source_index()].getZ());
        const voronoi_diagram<double>::edge_type *edge = cell.incident_edge();
        do {
        if (edge->is_primary())
        {
            auto vertex0 = edge->vertex0();
            auto vertex1 = edge->vertex1();
            printCells.push_back(vertex0->x());
            printCells.push_back(vertex0->y());
            printCells.push_back(vertex1->x());
            printCells.push_back(vertex1->y());
            printCells.push_back(points[cell.source_index()].getZ());
        }
        edge = edge->next();
        } while (edge != cell.incident_edge());
    
    }

    unsigned int VBO, VAO;
    unsigned int triangleVAO, triangleVBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, flattenedData.size() * sizeof(float), flattenedData.data(), GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, printPoints.size() * sizeof(float), printPoints.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    //cell buffer
  // Generate and bind VAO and VBO for triangles
    glGenVertexArrays(1, &triangleVAO);
    glGenBuffers(1, &triangleVBO);
    glBindVertexArray(triangleVAO);
    glBindBuffer(GL_ARRAY_BUFFER, triangleVBO);
    glBufferData(GL_ARRAY_BUFFER, printCells.size() * sizeof(double), printCells.data(), GL_STATIC_DRAW);
    // Set vertex attribute pointers for triangles
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Unbind VAO
    glBindVertexArray(0);

    // Use shader program for triangles
    glUseProgram(shaderProgram);

    // Draw triangles
   // glBindVertexArray(triangleVAO);
  //  glDrawArrays(GL_TRIANGLES, 0, trianglePoints.size() / 3);
   // glBindVertexArray(0);
   
    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
    ////////////////////////////////////////////////////////////////////////

    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);


    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);
        /* Render here */
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        displayPoints(shaderProgram,VAO);
/*
        GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        timeValue = glfwGetTime();
        float redValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, redValue, greenValue, 0.2f, 1.0f);

        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_POINTS, 0, POINTCOUNT*POINTCOUNT);
*/

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    /*cleanup*/
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
    return 0;
}