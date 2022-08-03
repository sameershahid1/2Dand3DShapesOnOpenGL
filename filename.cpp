#include <GL/glew.h> // include GLEW and new version of GL on Windows
#include <GLFW/glfw3.h> // GLFW helper library
#include<iostream>
#include<math.h>
using namespace std;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UP && action == GLFW_PRESS)
    {
       glClearColor(0.06f,0.5f,0.17f,1.0f);
    }
    if(key==GLFW_KEY_ESCAPE&&action==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,GLFW_TRUE);
    }
    if(key==GLFW_KEY_DOWN&&action==GLFW_PRESS)
    {

    }

}
/*
    Source Code of the Vertex Shader and Fragment Shader, the reason 
    we are creating the Source code of vertex and Fragment is that
    because by default the Source code does not exit in our OpenGL.
*/
const char* vertexShaderSource="#version 330 core\n"
"layout (location=0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"    gl_Position=vec4(aPos.x,aPos.y,aPos.z,1.0)\n;"
"}\0";

const char* fragmentShaderSource="#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
      "FragColor=vec4(0.8f,0.3f,0.02f,1.0f);\n"
"}\0";

int main() 
{
  // start GL context and O/S window using the GLFW helper library
  if (!glfwInit()) 
  {
    cout<<"You fucked up the GLFW3 File\n";
    return -1;
  } 

  int width=0,height=0;

  //Telling which OpenGL version should we be using 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800,600, "Hello Triangle", NULL, NULL);
  if (!window) {
    cout<<"ERROR: You fucked up the GLFW3 file";
    glfwTerminate();
    return 1;
  }
  glfwMakeContextCurrent(window);

  // start GLEW extension handler
  glewExperimental = GL_TRUE;
  glewInit();

  // // get version info
  // const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
  // const GLubyte* version = glGetString(GL_VERSION); // version as a string
  // printf("Renderer: %s\n", renderer);
  // printf("OpenGL version supported %s\n", version);

  // tell GL to only draw onto a pixel if the shape is closer to the viewer
  glEnable(GL_DEPTH_TEST); // enable depth-testing
  glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"



  /* OTHER STUFF GOES HERE NEXT */
  glfwGetFramebufferSize(window,&width,&height);
  glViewport(0,0,width,height);  
  GLfloat vertices[]=
  {
     -0.5f,-0.5f*float(sqrt(3))/3,0.0f,
      0.5f,-0.5f*float(sqrt(3))/3,0.0f,
      0.0f,0.5f*float(sqrt(3))*2/3,0.0f,
  };

  GLuint vertexShader=glCreateShader(GL_VERTEX_SHADER);//Getting the Vertex Shader from the memmory
  glShaderSource(vertexShader,1,&vertexShaderSource,NULL);//Creating the Source Code of the Vertex Shader
  glCompileShader(vertexShader);//Compilling the Vertex Shader Source Code

  GLuint fragmentShader=glCreateShader(GL_FRAGMENT_SHADER);//Getting the fragment Shader from the memmory
  glShaderSource(fragmentShader,1,&fragmentShaderSource,NULL);//Creating the Source the code Vertex Shader
  glCompileShader(fragmentShader);//Compilling the Source Code of the Fragment Shader
  /*
     Now we trying to wrap the vertex shader and fragment shader in a single shadder
  */
  GLuint shaderProgram=glCreateProgram();//Creating the shader program
  glAttachShader(shaderProgram,vertexShader);//Attaching the Vertex Shader with the Shader Program
  glAttachShader(shaderProgram,fragmentShader);//Attaching the Fragment Shader with the Shader Program
  glLinkProgram(shaderProgram);

  glDeleteShader(vertexShader);//Deleing the Vertex Shader
  glDeleteShader(fragmentShader);//Deleing the Fragment Shader

  /*
      The Vertex Buffer Object are used for sending big chunck of data at the
      same time to our Graphic card, because it takes so much to send it,
      that's why it is recommended to send it at the same time.
      The Vertex Buffer are not the same as Front and Back Buffer.
      These Buffers are used to send data to our Graphic card to render the vertics.
  */    
 
  GLuint VBO,VAO;//Vertex Buffer Object and Vertex Array Object
  glGenVertexArrays(1,&VAO);//Vertex Array Object must be Generated First
  glGenBuffers(1,&VBO);//Generating Vertex Buffer
  glBindVertexArray(VAO);//Binding the Vertex Array Object
  glBindBuffer(GL_ARRAY_BUFFER,VBO);//It points to current Object.
  glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);//Passing the Data to the buffer
  
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
  glEnableVertexAttribArray(0);
  


  glClearColor(0.07f,0.13f,0.17f,1.0f);
  while(!glfwWindowShouldClose(window))
  {
    //Clearing the buffers
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

    /* Render here */
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,3);


    //KeyBoard Actions
    glfwSetKeyCallback(window,key_callback);
     
    /* Swaping front and back buffers data with each other */
    glfwSwapBuffers(window);

    /* Poll for and process events */
    glfwPollEvents();
  }
  
  glDeleteVertexArrays(1,&VAO);
  glDeleteBuffers(1,&VBO);
  glDeleteProgram(shaderProgram);

  glfwDestroyWindow(window);
  // close GL context and any other GLFW resources
  glfwTerminate();
  return 0;
}
