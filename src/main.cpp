//Library Includes
#include <GL/glew.h> //include glew.h before glfw3.h or else
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//Standard Includes
#include <iostream>
#include <fstream>
#include <map>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef linux
#include <limits.h>
#include <unistd.h>
#endif

//Custom Includes
#include <Shader.hpp>
#include <Model.hpp>
#include <Renderer.hpp>
#include <OpenGLError.hpp>

void readSettings(std::map<std::string,struct setting> &settings,std::string fileName);
void writeSettings(std::map<std::string,struct setting> settings,std::string fileName);
std::string getexedir();

void keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods);
void windowSizeCallback(GLFWwindow* window, int w, int h);






struct setting{
    std::string preset;
    std::string current;
};




//Global Variables
GLFWwindow* window;
bool fullscreen;
int width,height; //current viewport width and height
std::map<std::string,struct setting> settings;
glm::mat4 proj,view,mvp;



int main(){

   

    //Default settings
    settings.insert( std::pair<std::string,struct setting>("fullscreen",{"false","false"}));
    settings.insert( std::pair<std::string,struct setting>("width",{"854","854"}));
    settings.insert( std::pair<std::string,struct setting>("height",{"480","480"}));
    settings.insert( std::pair<std::string,struct setting>("debugmode",{"false","false"}));


    readSettings(settings,"settings.txt"); 
    writeSettings(settings,"settings.txt");

    if (!glfwInit()) throw "Error: GLFW could not initialize.";

    GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* vidMode = glfwGetVideoMode(primaryMonitor);
    std::string title = "OpenGl-GLFW-Template";


    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	//glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);


    if(settings["fullscreen"].current == "true"){
        fullscreen = true;
        glfwWindowHint(GLFW_RED_BITS, vidMode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, vidMode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, vidMode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, vidMode->refreshRate);
        window = glfwCreateWindow(vidMode->width,vidMode->height,title.c_str(),primaryMonitor, NULL);
        width = vidMode->width;
        height = vidMode->height;
    }
    else{
        fullscreen = false;
        window = glfwCreateWindow(std::atoi(settings["width"].current.c_str()),std::atoi(settings["height"].current.c_str()),title.c_str(),NULL, NULL);
        width = std::atoi(settings["width"].current.c_str());
        height = std::atoi(settings["height"].current.c_str());
    }

    if (!window){
        glfwTerminate();
    }


    glfwSetWindowSizeCallback(window, windowSizeCallback);
    glfwSetKeyCallback(window, keyPressed);

    glfwMakeContextCurrent(window); 
    if (glewInit() != GLEW_OK) throw "Error: GLEW could not Initialize"; //Only call within a valid OpenGL context
    std::cout << std::endl << "OpenGL " << glGetString(GL_VERSION) << std::endl; // Print OpenGL Version
    glDebugMessageCallback(MessageCallback, 0); //Set OpenGL Error Messgage Callback

    //Set projection units to pixel space with origin at center
    proj = glm::ortho(-width/2.0f, width/2.0f,-height/2.0f, height/2.0f, -1.0f, 1.0f);
    //Set default camera view
	view = glm::scale(glm::mat4(1.0f),glm::vec3(1.0f/*Default ScaleX*/,1.0f/*Default ScaleY*/,1.0f)) * glm::translate(glm::mat4(1.0f), glm::vec3(-0/*Default PanX*/,-0/*Default PanY*/,0));
    
    glClearColor(0.1,0.1,0.1,1); //Set Background Color


    Renderer renderer;

    Shader shader(getexedir()+"../res/shaders/basic/vertex.vsh",getexedir()+"../res/shaders/basic/fragment.fsh");
    shader.Bind();


    glfwSwapInterval(0);	




    


    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT); //Clear using Background Color

        mvp = proj * view;
        shader.SetUniformMat4f("u_MVP",mvp);
    










        glfwSwapBuffers(window);

        glfwPollEvents();

    }

    glfwTerminate();


    return 0;
}

void readSettings(std::map<std::string,struct setting> &settings,std::string fileName){

    std::fstream file;
    std::string path = getexedir() + fileName;

    file.open(path,std::fstream::in);

    std::string line;

    std::string key;
    std::string value;

    int index;

    while(std::getline(file,line)){
        index = line.find('=',0);
        key = line.substr(0,index);
        value = line.substr(index + 1 ,line.length()-(index+1));
        if(settings.find(key) != settings.end()){
            settings[key].current = value;
        }
    }
    file.close();
}



void writeSettings(std::map<std::string,struct setting> settings,std::string fileName){

    std::fstream file;
    std::string path = getexedir() + fileName;

    file.open(path,std::fstream::out);

    for(const auto& pair : settings ){
        std::string line = pair.first + "=" + pair.second.current;
        file << line;
        file << std::endl;
    }
    file.close();
}


void windowSizeCallback(GLFWwindow* window, int w, int h)
{
    width = w;
    height = h;

    glViewport(0,0,width,height);
    proj = glm::ortho(-width/2.0f, width/2.0f,-height/2.0f, height/2.0f, -1.0f, 1.0f);


}

void keyPressed(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_F11 && action == GLFW_PRESS){
        //Fullscreen Toggle
        GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
        const GLFWvidmode* vidMode = glfwGetVideoMode(primaryMonitor);
        if(fullscreen){
            int w = std::atoi(settings["width"].current.c_str());
            int h = std::atoi(settings["height"].current.c_str());
            glfwSetWindowMonitor(window, NULL, (vidMode->width/2)-(w/2), (vidMode->height/2)-(h/2),w,h,GLFW_DONT_CARE);
            width = std::atoi(settings["width"].current.c_str());
            height = std::atoi(settings["height"].current.c_str());
        }
        else{
            glfwSetWindowMonitor(window, primaryMonitor, 0, 0, vidMode->width,vidMode->height,vidMode->refreshRate);
            width = vidMode->width;
            height = vidMode->height;
        }
        fullscreen = !fullscreen;
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwDestroyWindow(window);
    }
    


        
}



#if defined(_WIN32)
std::string getexedir(){

    char result[ MAX_PATH ];
    std::string exe = std::string( result, GetModuleFileNameA( NULL, result, MAX_PATH ) );
    std::string dir = exe.substr(0,exe.find_last_of("/\\")) + "/";

    return dir;
}
#elif defined(linux)
std::string getexedir()
{
    char result[ PATH_MAX ];
    ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
    std::string exe = std::string( result, (count > 0) ? count : 0 );
    std::string dir = exe.substr(0,exe.find_last_of("/\\")) + "/";

    return dir;
}
#elif
std::string getexedir(){
    return "";
}
#endif

