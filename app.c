#ifdef __APPLE__
#include <OpenGL/gl.h>
#else 
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "gl_log.h"
#include "matrix4f.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

static const GLfloat g_vertex_buffer_data[] = {
    -0.8f, -0.8f, 0.0f, 
    0.8f, -0.8f, 0.0f, 
    0.8f,  0.8f,  0.0f,
//    -0.8f, 0.8f,  0.0f, 
//    0.8f, 0.8f,  0.0f, 
//    -0.8f, -0.8f, 0.0f,
};

static const GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f,
    
//    1.0f, 0.0f, 0.0f,
//    0.0f, 1.0f, 0.0f,
//    0.0f, 0.0f, 1.0f
};

typedef struct {
    GLuint vertexBuffer;
    GLuint attribLocation;
    int size;
} VBOData;

void setAttribute(VBOData data[]) {
    int i;
    int length = sizeof(data)/ sizeof(data[0]);
    for(i=0; i<length; i++) {
        VBOData d = data[i];
        glBindBuffer(GL_ARRAY_BUFFER, d.vertexBuffer);
        glEnableVertexAttribArray(d.attribLocation);
        glVertexAttribPointer(d.attribLocation, d.size, GL_FLOAT, GL_FALSE, 0, 0);
    }
}

const char gFragmentShader[] =
    "uniform float screenWidth;\n"
#ifdef GL_ES
    "precision mediump float;\n"
#endif
    "varying vec4 color;\n"
    "void main(){\n"
    //"   gl_FragColor = vec4(gl_FragCoord.x/screenWidth, 1.0, 0.0, 1.0);\n"
    "    gl_FragColor = color;\n"
    "}\n";

const char gVertexShader[] =
    "attribute vec4 vPosition;\n"
    "attribute vec4 vColor;\n"
    "uniform mat4 mvMatrix;\n"
    "uniform mat4 pMatrix;\n"
    "varying vec4 color;\n"
    "void main(){\n"
    "   gl_Position = pMatrix * mvMatrix * vPosition;\n"
    "   color = vColor;\n"
    "}\n";

int frame_count;
double previous_seconds;
void _update_fps_counter(GLFWwindow* window) {
    double current_seconds;
    double elapsed_seconds;
    current_seconds = glfwGetTime();
    elapsed_seconds = current_seconds - previous_seconds;
    if(elapsed_seconds > 0.25) {
        previous_seconds = current_seconds;
        char tmp[128];
        double fps = (double)frame_count / elapsed_seconds;
        sprintf(tmp, "opengl @ fps: %.2f", fps);
        glfwSetWindowTitle(window, tmp);
        frame_count = 0;
    }
    frame_count++;
}

void glfw_error_callback(int error, const char* description) {
    gl_log_error("GLFE ERROR: code %i\nmsg: %s\n", error, description);
}

void glfw_window_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

/*
 シェーダの情報を表示する
*/
void printShaderInfoLog(GLuint shader) {
  GLsizei bufSize;

  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

  if (bufSize > 1) {
    GLchar *infoLog;

    infoLog = (GLchar *)malloc(bufSize);
    
    if (infoLog != NULL) {
      GLsizei length;
      glGetShaderInfoLog(shader, bufSize, &length, infoLog);
      fprintf(stderr, "InfoLog:¥n%s¥n¥n", infoLog);
      free(infoLog);
    } else
      fprintf(stderr, "Could not allocate InfoLog buffer.¥n");
  }
}

/*
 プログラムの情報を表示する
**/
void printProgramInfoLog(GLuint program) {
  GLsizei bufSize;

  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufSize);

  if (bufSize > 1) {
    GLchar *infoLog;
    infoLog = (GLchar *)malloc(bufSize);
    if (infoLog != NULL) {
      GLsizei length;

      glGetProgramInfoLog(program, bufSize, &length, infoLog);
      fprintf(stderr, "InfoLog:¥n%s¥n¥n", infoLog);
      free(infoLog);
    } else
      fprintf(stderr, "Could not allocate InfoLog buffer.¥n");
  }
}

void GetShaderInfoLog(GLuint shader) {
  GLsizei bufSize;

  /* シェーダのコンパイル時のログの長さを取得する */
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &bufSize);

  if (bufSize > 1) {
    GLchar *infoLog = (GLchar *)malloc(bufSize);

    if (infoLog != NULL) {
      GLsizei length;

      /* シェーダのコンパイル時のログの内容を取得する */
      glGetShaderInfoLog(shader, bufSize, &length, infoLog);
      printf("InfoLog:\n%s\n\n", infoLog);
      free(infoLog);
    } else
      printf("Could not allocate InfoLog buffer.\n");
  }
}

GLuint loadShader(GLenum shaderType, const char *pSource) {
  GLuint shader = glCreateShader(shaderType);
  glShaderSource(shader, 1, &pSource, NULL);
  glCompileShader(shader);
  GLint compiled;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
  if (compiled != GL_TRUE) {
    printShaderInfoLog(shader);
  }
  return shader;
}

GLuint createProgram(const char *pVertexSource, const char *pFragmentSource) {
  GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
  GetShaderInfoLog(vertexShader);
  GLuint fragmentShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
  GetShaderInfoLog(fragmentShader);

  GLuint program = glCreateProgram();
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);
  GLint linkStatus = GL_FALSE;
  glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

  if (linkStatus != GL_TRUE) {
    printProgramInfoLog(program);
    fprintf(stderr, "Link Error\n");
  }
  return program;
}

void render() {
  GLuint vertexBuffer;

  glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  GLuint gProgram = createProgram(gVertexShader, gFragmentShader);
  GLuint gvPositionHandle = glGetAttribLocation(gProgram, "vPosition");
  glUseProgram(gProgram);

  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
               g_vertex_buffer_data, GL_STATIC_DRAW);

  // 1rst attribute buffer : vertices
  glEnableVertexAttribArray(gvPositionHandle);

  // uniform
  GLint uniform;
  uniform = glGetUniformLocation(gProgram, "screenWidth");
  glUniform1f(uniform, SCREEN_WIDTH);

  // Rotation Matrix
  float mag = 0.5f;
  float modelViewMatrix[16], projectionMatrix[16];
  // ModelViewMatrix
  Matrix4f_create(modelViewMatrix);
  Matrix4f_identify(modelViewMatrix);
  Matrix4f_scale(modelViewMatrix, 0.5f);
  //Matrix4f_rotateZ(modelViewMatrix, 20);
  Matrix4f_create(projectionMatrix);
  Matrix4f_identify(projectionMatrix);

  GLint mv_matrix_uniform, projection_matrix_uniform;
  mv_matrix_uniform = glGetUniformLocation(gProgram, "mvMatrix");
  projection_matrix_uniform = glGetUniformLocation(gProgram, "pMatrix");
  glUniformMatrix4fv(mv_matrix_uniform, 1, GL_FALSE, modelViewMatrix);
  glUniformMatrix4fv(projection_matrix_uniform, 1, GL_FALSE, projectionMatrix);

  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glVertexAttribPointer(gvPositionHandle,  // attribute 0. No particular reason
                        3,                 // size
                        GL_FLOAT,          // type
                        GL_FALSE,          // normalized?
                        0,                 // stride
                        (void *)0          // array buffer offset
                        );

  // color vbo
  GLuint colors_vbo = 0;
  glGenBuffers(1, &colors_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
  GLuint gvColorHandle = glGetAttribLocation(gProgram, "vColor");

  glEnableVertexAttribArray(gvColorHandle);
  glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
  glVertexAttribPointer(gvColorHandle, 3, GL_FLOAT, GL_FALSE, 0, 0);

  // Draw the triangle !
  glDrawArrays(
      GL_TRIANGLES, 0,
      sizeof(g_vertex_buffer_data) / sizeof(g_vertex_buffer_data[0]) /
          3);  // Starting from vertex 0; 3 vertices total -> 1 triangle

}

int init() {
  GLFWwindow *window;

  /* Initialize the library */
  if (!glfwInit()) return -1;

  // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);  // yes, 3 and 2!!!
  // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /* Create a windowed mode window and its OpenGL context */
  window =
      glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  /* Make the window's context current */
  glfwMakeContextCurrent(window);
  glViewport(0, 0, 640, 480);

  glfwSetErrorCallback(glfw_error_callback);
  glfwSetWindowSizeCallback(window, glfw_window_size_callback);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)) {
    _update_fps_counter(window);
    /* Render here */
    render();
    /* Swap front and back buffers */
    glfwSwapBuffers(window);
    /* Poll for and process events */
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}

int main() { init(); }
