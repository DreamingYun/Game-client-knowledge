#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

static unsigned int CompileShader(unsigned int type,const std::string& source) {
    //着色器类型在define时对应int
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();//== &source[0]
    //创建着色器的源码
    glShaderSource(id, 1, &src, nullptr);
    //编译着色器
    glCompileShader(id);

    //错误检测
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);//从着色器对象返回参数--状态
    if (result == GL_FALSE) {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);//从着色器对象返回参数--错误信息长度
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "编译"<< (type == GL_VERTEX_SHADER  ? "vertex" : "fragment") << "着色器失败了！原因是：" << message << std::endl;
        glDeleteShader(id);//删除着色器
        return 0;
    }


    return id;
}

//编写着色器
static int createShader(const std::string& vertexShader, const std::string& fragmentShader) {
    //顶点着色器和片段着色器
    unsigned int program = glCreateProgram();//创建一个程序
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    //着色器附加到程序上
    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);//链接好程序
    glValidateProgram(program);//验证程序的可执行文件是否可在当前OpenGL状态下执行
    
    //删除中间文件
    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

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


    //顶点着色器-储存顶点数据
    std::string vertexShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) in vec4 position;" //索引值为0,2元素的数据类型（在这里转为了4元素）
        "\n"
        "void main()\n"
        "{\n"
        "  gl_Position = position;\n"
        "}\n";

    //片段着色器-输出颜色
    std::string fragmentShader =
        "#version 330 core\n"
        "\n"
        "layout(location = 0) out vec4 color;" //索引值为0,2元素的数据类型
        "\n"
        "void main()\n"
        "{\n"
        "  color = vec4(1.0,0.0,0.0,1.0);\n"
        "}\n";

    unsigned int shader = createShader(vertexShader, fragmentShader);
    glUseProgram(shader);//将程序对象作为当前渲染状态的一部分进行安装


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

    glDeleteProgram(shader);//清理着色器
    glfwTerminate();
    return 0;
}

