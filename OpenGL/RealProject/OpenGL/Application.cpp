#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


    //创建一个有效的 OpenGL 渲染上下文后，用glewInit（）来初始化扩展入口点。如果 glewInit（） 返回 GLEW_OK，则初始化 成功，您可以使用可用的扩展以及核心 OpenGL 功能
    if (glewInit() != GLEW_OK) {
        std::cout << "Error!" << std::endl;
    }
    //输出当前显卡版本
    std::cout << glGetString(GL_VERSION) << std::endl;

    float positions[6] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f,-0.5f
    };//数据

    unsigned int buffer;//缓冲区的编号--当需要说明使用哪个缓冲区去渲染三角形的时候
    glGenBuffers(1, &buffer);//一处缓冲区
    glBindBuffer(GL_ARRAY_BUFFER, buffer);//选择需要使用的buffer缓冲区
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float),positions,GL_STATIC_DRAW);//创建并初始化缓冲区对象的数据存储
    //阅读文档可知，static在这里表示不再修改，并且不断使用，DRASW表示数据存储的内容由应用程序修改，并用作GL绘图和图像规范命令的源


    glEnableVertexAttribArray(0);//属性索引启用--》告诉OpenGL缓冲区的布局是什么
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);//属性索引值、几个浮点数代表一个数据、数据类型、是否需要标准化、需要向前移动到第二个顶点的字节数、指针代表下一个属性

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //在没有索引缓冲区时使用DrawCall方法
        glDrawArrays(GL_TRIANGLES, 0, 3);//起始索引处，索引数量


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

