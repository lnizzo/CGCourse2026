//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include "../common/debugging.h"
//
//
//
//int main(int argc, char** argv) {
//
//	GLFWwindow* window;
//
//    /* Initialize the library */
//    if (!glfwInit())
//        return -1;
//
//
//    // Request OpenGL 4.1
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//
//    // Ask specifically for the core profile (recommended)
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//    // macOS requires this for 3.2+ contexts
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//
//    /* Create a windowed mode window and its OpenGL context */
//    window = glfwCreateWindow(512, 512, "code_02_my_first_triangle", NULL, NULL);
//
//
//    if (!window)
//    {
//        glfwTerminate();
//        return -1;
//    }
//
//    /* Make the window's context current */
//    glfwMakeContextCurrent(window); 
//
//
//    // Load GL symbols *after* the context is current
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        std::fprintf(stderr, "Failed to initialize GLAD\n");
//        glfwDestroyWindow(window);
//        glfwTerminate();
//        return EXIT_FAILURE;
//    }
//
//
//    /* query for the hardware and software specs and print the result on the console*/
//    printout_opengl_glsl_info();
//
//    ///* create render data in RAM */
//    GLuint positionAttribIndex = 0;
//    float positions[] = { 0.0, 0.0,  // 1st vertex
//                          0.5, 0.0,  // 2nd vertex
//                          0.5, 0.5,  // 3rd vertex  
//                          0.0, 0.5   // 4th vertex
//    };
//
//
//    ///* create  a vertex array object */
//    GLuint va;
//    glGenVertexArrays(1, &va);
//    glBindVertexArray(va);
//
//    ///* create a buffer for the render data in video RAM */
//    GLuint positionsBuffer;
//    glGenBuffers(1, &positionsBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, positionsBuffer);
//
//    ///* declare what data in RAM are filling the bufferin video RAM */
//    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, positions, GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(positionAttribIndex);
//    ///* specify the data format */
//    glVertexAttribPointer(positionAttribIndex, 2, GL_FLOAT, false, 0, 0);
//
//    ///* create render data in RAM */
//    GLuint colorAttribIndex = 1;
//    float colors[] = {  1.0, 0.0, 0.0,    // 1st vertex's color
//                        0.0, 1.0, 0.0,   // 2nd vertex's color
//                        0.0, 0.0, 1.0,
//                        1.0, 1.0, 1.0
//                    };
//
//    ///* create a buffer for the render data in video RAM */
//    GLuint colorBuffer;
//    glGenBuffers(1, &colorBuffer);
//    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
//
//    ///* declare what data in RAM are filling the bufferin video RAM */
//    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 12, colors, GL_STATIC_DRAW);
//
//    glEnableVertexAttribArray(colorAttribIndex);
//    ///* specify the data format */
//    glVertexAttribPointer(colorAttribIndex, 3, GL_FLOAT, false, 0, 0);
//
//    GLuint indices[] = { 0,1,2,0,2,3 };
//    GLuint indexBuffer;
//    glGenBuffers(1, &indexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, indices, GL_STATIC_DRAW);
//
//
//    ///* create a vertex shader */
//    std::string  vertex_shader_src = "#version 410\n \
//        in vec2 aPosition;\
//        in vec3 aColor;\
//        out vec3 vColor;\
//        uniform float uDelta;\
//        void main(void)\
//        {\
//         gl_Position = vec4(aPosition+vec2(uDelta,0.0), 0.0, 1.0);\
//         vColor = aColor;\
//        }\
//       ";
//    const GLchar* vs_source = (const GLchar*)vertex_shader_src.c_str();
//    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertex_shader, 1, &vs_source, NULL);
//    glCompileShader(vertex_shader);
//  
//
//    ///* create a fragment shader */
//    std::string   fragment_shader_src = "#version 410 \n \
//        layout (location = 0) out vec4 color;\
//        in vec3 vColor;\
//        uniform float uDelta;\
//        void main(void)\
//        {\
//            color = vec4(vColor+vec3(uDelta,0.0,0.0), 1.0);\
//        }";
//    const GLchar* fs_source = (const GLchar*)fragment_shader_src.c_str();
//    
//    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragment_shader, 1, &fs_source, NULL);
//    glCompileShader(fragment_shader);
//    
//
//    GLuint program_shader = glCreateProgram();
//    glAttachShader(program_shader, vertex_shader);
//    glAttachShader(program_shader, fragment_shader);
//     
//    glBindAttribLocation(program_shader, positionAttribIndex, "aPosition");
//    glBindAttribLocation(program_shader, colorAttribIndex, "aColor");
//    glLinkProgram(program_shader);
//   
//
//    GLint linked;
//    validate_shader_program(program_shader);
//    glGetProgramiv(program_shader, GL_LINK_STATUS, &linked);
//    if (linked) {
//        glUseProgram(program_shader);
//    }
//    
//    GLint loc = glGetUniformLocation(program_shader, "uDelta");
//
//    /* cal glGetError and print out the result in a more verbose style
//    * __LINE__ and __FILE__ are precompiler directive that replace the value with the
//    * line and file of this call, so you know where the error happened
//    */
//    check_gl_errors(__LINE__, __FILE__);
//
//    float d = 0.01;
//    float delta = 0;
//
//    glClearColor(0.2, 0.2, 0.2, 1);
//    while (!glfwWindowShouldClose(window))
//    {
//        if (delta < 0 || delta > 0.5)
//            d = -d;
//        delta += d;
//
//        glUniform1f(loc, delta);
//
//        /* Render here */
//        
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//       
//        // glDrawArrays(GL_TRIANGLES, 0, 6);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
//
//        /* Swap front and back buffers */
//        glfwSwapBuffers(window);
//
//        /* Poll for and process events */
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//
//	return 0;
//}

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include <iostream>
//#include "../common/debugging.h"
//
//int main(int argc, char** argv) {
//
//    GLFWwindow* window;
//
//    if (!glfwInit())
//        return -1;
//
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//
//    window = glfwCreateWindow(512, 512, "code_02_interleaved_buffer", NULL, NULL);
//
//    if (!window) {
//        glfwTerminate();
//        return -1;
//    }
//
//    glfwMakeContextCurrent(window);
//
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//        std::fprintf(stderr, "Failed to initialize GLAD\n");
//        glfwDestroyWindow(window);
//        glfwTerminate();
//        return EXIT_FAILURE;
//    }
//
//    printout_opengl_glsl_info();
//
//    // --- PUNTO A: RIORGANIZZAZIONE ARRAY IN RAM (INTERLEAVED) ---
//    // Struttura: Posizione (X, Y) | Colore (R, G, B)
//    float vertices[] = {
//        0.0f, 0.0f,  1.0f, 0.0f, 0.0f,  // Vertice 0: Rosso
//        0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // Vertice 1: Verde
//        0.5f, 0.5f,  0.0f, 0.0f, 1.0f,  // Vertice 2: Blu
//        0.0f, 0.5f,  1.0f, 1.0f, 1.0f   // Vertice 3: Bianco
//    };
//
//    GLuint indices[] = { 0, 1, 2, 0, 2, 3 };
//
//    // --- PUNTO B: UN SOLO ARRAY BUFFER IN VRAM ---
//    GLuint va;
//    glGenVertexArrays(1, &va);
//    glBindVertexArray(va);
//
//    GLuint vbo;
//    glGenBuffers(1, &vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    // Carichiamo l'intero array 'vertices' che contiene sia posizioni che colori
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    // EBO per gli indici (rimane invariato)
//    GLuint indexBuffer;
//    glGenBuffers(1, &indexBuffer);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
//
//    // --- PUNTO C: CAMBIARE STRIDE E OFFSET ---
//    GLuint positionAttribIndex = 0;
//    GLuint colorAttribIndex = 1;
//
//    // Lo stride è la distanza tra l'inizio di un vertice e il successivo:
//    // 2 float (pos) + 3 float (colore) = 5 float totali
//    GLsizei stride = 5 * sizeof(float);
//
//    // Configurazione Posizione (Inizia all'offset 0)
//    glEnableVertexAttribArray(positionAttribIndex);
//    glVertexAttribPointer(positionAttribIndex, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
//
//    // Configurazione Colore (Inizia dopo i 2 float della posizione)
//    glEnableVertexAttribArray(colorAttribIndex);
//    glVertexAttribPointer(colorAttribIndex, 3, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));
//
//
//
//    // --- SHADERS (Invariati) ---
//    std::string vertex_shader_src = "#version 410\n \
//        in vec2 aPosition;\
//        in vec3 aColor;\
//        out vec3 vColor;\
//        uniform float uDelta;\
//        void main(void)\
//        {\
//         gl_Position = vec4(aPosition+vec2(uDelta,0.0), 0.0, 1.0);\
//         vColor = aColor;\
//        }\
//       ";
//
//    std::string fragment_shader_src = "#version 410 \n \
//        layout (location = 0) out vec4 color;\
//        in vec3 vColor;\
//        uniform float uDelta;\
//        void main(void)\
//        {\
//            color = vec4(vColor+vec3(uDelta,0.0,0.0), 1.0);\
//        }";
//
//    // Compilazione e Linking (Semplificato per brevità)
//    const GLchar* vs_source = (const GLchar*)vertex_shader_src.c_str();
//    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertex_shader, 1, &vs_source, NULL);
//    glCompileShader(vertex_shader);
//
//    const GLchar* fs_source = (const GLchar*)fragment_shader_src.c_str();
//    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragment_shader, 1, &fs_source, NULL);
//    glCompileShader(fragment_shader);
//
//    GLuint program_shader = glCreateProgram();
//    glAttachShader(program_shader, vertex_shader);
//    glAttachShader(program_shader, fragment_shader);
//    glBindAttribLocation(program_shader, positionAttribIndex, "aPosition");
//    glBindAttribLocation(program_shader, colorAttribIndex, "aColor");
//    glLinkProgram(program_shader);
//
//    glUseProgram(program_shader);
//    GLint loc = glGetUniformLocation(program_shader, "uDelta");
//
//    check_gl_errors(__LINE__, __FILE__);
//
//    float d = 0.01f;
//    float delta = 0.0f;
//
//    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
//
//    // --- LOOP DI RENDERING ---
//    while (!glfwWindowShouldClose(window))
//    {
//        if (delta < 0 || delta > 0.5) d = -d;
//        delta += d;
//
//        glUniform1f(loc, delta);
//
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        // Il comando di disegno non cambia: usa gli indici per pescare dal buffer interleaved
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
//
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    glfwTerminate();
//    return 0;
//}

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include "../common/debugging.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

// Variabili globali per gestire il disegno della box
GLuint vaoBox, vboBox, eboBox;
int numIndices = 0;

/**
 * Funzione che crea una griglia di rettangoli (suddivisi in triangoli)
 * nello spazio Normalized Device Coordinates (da -1 a 1).
 */
void create_box2d(int xsize, int ysize) {
    std::vector<float> vertices;
    std::vector<GLuint> indices;

    float dx = 2.0f / (float)xsize;
    float dy = 2.0f / (float)ysize;

    // 1. Generazione Vertici (Interleaved: Posizione x,y + Colore r,g,b)
    for (int j = 0; j <= ysize; ++j) {
        for (int i = 0; i <= xsize; ++i) {
            // Coordinate posizione da -1.0 a 1.0
            float x = -1.0f + i * dx;
            float y = -1.0f + j * dy;
            vertices.push_back(x);
            vertices.push_back(y);

            // Colore procedurale basato sulla posizione
            vertices.push_back((x + 1.0f) / 2.0f); // R
            vertices.push_back((y + 1.0f) / 2.0f); // G
            vertices.push_back(0.5f);              // B
        }
    }

    // 2. Generazione Indici
    // Ogni cella (rettangolo) ha 4 vertici. Indice = riga * (numero_colonne + 1) + colonna
    for (int j = 0; j < ysize; ++j) {
        for (int i = 0; i < xsize; ++i) {
            GLuint bottomLeft = j * (xsize + 1) + i;
            GLuint bottomRight = bottomLeft + 1;
            GLuint topLeft = (j + 1) * (xsize + 1) + i;
            GLuint topRight = topLeft + 1;

            // Triangolo 1: taglio da Bottom-Left a Top-Right
            indices.push_back(bottomLeft);
            indices.push_back(bottomRight);
            indices.push_back(topRight);

            // Triangolo 2: taglio da Bottom-Left a Top-Right
            indices.push_back(bottomLeft);
            indices.push_back(topRight);
            indices.push_back(topLeft);
        }
    }

    numIndices = (int)indices.size();

    // 3. Setup Buffer OpenGL
    glGenVertexArrays(1, &vaoBox);
    glBindVertexArray(vaoBox);

    glGenBuffers(1, &vboBox);
    glBindBuffer(GL_ARRAY_BUFFER, vboBox);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &eboBox);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboBox);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

    // Attributi Interleaved
    GLsizei stride = 5 * sizeof(float);
    // Posizione (location 0)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride, (void*)0);
    // Colore (location 1)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(2 * sizeof(float)));

    glBindVertexArray(0);
}


void save_screenshot(GLFWwindow* window, const std::string& filename) {
    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    // Prepariamo un buffer per contenere i pixel (3 canali: R, G, B)
    std::vector<unsigned char> pixels(3 * width * height);

    // Leggiamo i pixel dal buffer frontale
    glReadPixels(0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels.data());

    // NOTA: OpenGL legge i pixel dal basso verso l'alto (0,0 è l'angolo in basso a sinistra).
    // Molte librerie di immagini si aspettano l'origine in alto a sinistra.
    // Dobbiamo invertire le righe verticalmente.
    std::vector<unsigned char> flipped_pixels(3 * width * height);
    for (int y = 0; y < height; y++) {
        memcpy(&flipped_pixels[y * width * 3],
            &pixels[(height - 1 - y) * width * 3],
            width * 3);
    }

    // Salviamo in formato PNG
    stbi_write_png(filename.c_str(), width, height, 3, flipped_pixels.data(), width * 3);

    std::cout << "Screenshot salvato come: " << filename << std::endl;
}

int main(int argc, char** argv) {
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(512, 512, "Exercise: Box2D Grid", NULL, NULL);
    if (!window) { glfwTerminate(); return -1; }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;

    // Creiamo la griglia (es. 3 colonne, 2 righe come richiesto)
    create_box2d(3, 2);

    // Shader minimali
    std::string vertex_shader_src = "#version 410\n"
        "layout(location = 0) in vec2 aPosition;"
        "layout(location = 1) in vec3 aColor;"
        "out vec3 vColor;"
        "void main() {"
        "  gl_Position = vec4(aPosition, 0.0, 1.0);"
        "  vColor = aColor;"
        "}";

    std::string fragment_shader_src = "#version 410\n"
        "in vec3 vColor;"
        "out vec4 color;"
        "void main() {"
        "  color = vec4(vColor, 1.0);"
        "}";

    // Compilazione e link rapido (omettendo controlli errore per brevità)
    const GLchar* vs_ptr = vertex_shader_src.c_str();
    const GLchar* fs_ptr = fragment_shader_src.c_str();
    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &vs_ptr, NULL);
    glCompileShader(vs);
    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &fs_ptr, NULL);
    glCompileShader(fs);
    GLuint program = glCreateProgram();
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glUseProgram(program);

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Se vuoi vedere la struttura dei triangoli, scommenta la riga sotto:
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    bool sKeyPressed = false; // Serve a tracciare se il tasto era già premuto nel frame precedente

    while (!glfwWindowShouldClose(window)) {
        
        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(vaoBox);
        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);

        int currentSState = glfwGetKey(window, GLFW_KEY_S);

        if (currentSState == GLFW_PRESS && !sKeyPressed) {
            save_screenshot(window, "griglia_finale.png");
            sKeyPressed = true; // Segniamo che è premuto, così al prossimo frame non rientra qui
        }
        // Se il tasto viene rilasciato, resettiamo la variabile
        else if (currentSState == GLFW_RELEASE) {
            sKeyPressed = false;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}