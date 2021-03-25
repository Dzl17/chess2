#include <GL/glew.h> // Loader de extensiones de OpenGL
#include <GLFW/glfw3.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

//#define STB_IMAGE_IMPLEMENTATION // Para que stb_image pueda utilizarse
//#include "libs/stb_image.h"
#include "../dependencies/blah/src/third_party/stb_image.h"

#define RGB_DIV 255.0f // Para normalizar colores de RGB a [0-1]

bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height);
void loadIcon(GLFWwindow* window, const char* filename);

static void glfw_error_callback(int error, const char* description) // Para imprimir errores
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

int maian(int, char**)
{
	// Setup window
	glfwSetErrorCallback(glfw_error_callback); // Redirigir errores a glfw_error_callback
	if (!glfwInit()) return 1; // Si hay error de inicio de glfw cierra el programa

	// GL 3.0 + GLSL 130
	const char* glsl_version = "#version 130";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // Para indicar la version de la API de cliente
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // Evita que la ventana cambie de tamaño

	GLFWwindow* window = glfwCreateWindow(1280, 720, "Chess 2", nullptr, nullptr); // Crear ventana
	
	if (window == nullptr) return 1; // Cerrar programa si la ventana no se crea
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Activar vsync

	loadIcon(window, "../data/img/boredlion.png"); // Cargar icono de ventana

	bool err = glewInit() != GLEW_OK; // Inicio de glew
	if (err) // Si hay error de inicio de glew, se cierra el programa
	{
		fprintf(stderr, "Failed to initialize OpenGL loader (glew)\n");
		return 1;
	}

	int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height); // Ajustas las variables al tamaño de la ventana
	glViewport(0, 0, screen_width, screen_height); // No realmente necesario, mejor utilizarlo

	// Setup de Dear ImGui
	IMGUI_CHECKVERSION();
	ImGui::CreateContext(); // Crea el contexto de imgui
	ImGuiIO& io = ImGui::GetIO(); // Carga el sistema de IO
	ImGui_ImplGlfw_InitForOpenGL(window, true); // Bindings a plataforma y renderizado (opengl)
	ImGui_ImplOpenGL3_Init(glsl_version);		// para poder utilizar imgui con opengl
	ImGui::StyleColorsDark(); // Modo oscuro

	// Textura del mapa
	int my_image_width = 0;
	int my_image_height = 0;
	GLuint my_image_texture = 0;
	bool ret = LoadTextureFromFile("../data/img/grid.png", &my_image_texture, &my_image_width, &my_image_height);
	IM_ASSERT(ret); // Comprobar que la textura se carga correctamente

	// Textura de imagen de prueba
    int testTexture_width = 0;
    int testTexture_height = 0;
    GLuint testTexture = 0;
    bool ret2 = LoadTextureFromFile("../data/img/testimg.jpg", &testTexture, &testTexture_width, &testTexture_height);
    IM_ASSERT(ret2); // Comprobar que la textura se carga correctamente

    // Variables extra
    bool onSettings = false;
    static float col1[3] = { 1.0f, 0.0f, 0.2f };

	while (!glfwWindowShouldClose(window)) // Bucle principal
	{
		glfwPollEvents();
		//glClearColor(201.0f/RGB_DIV, 204.0f/RGB_DIV, 161.0f/RGB_DIV, 1.00f);
		glClearColor(col1[0], col1[1], col1[2], 1.00f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Pasar inputs a imgui, inicia nuevo frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

        // Ventana de imagen
        ImGui::Begin("OpenGL Texture Text");
		ImGui::Text("size = %d x %d", testTexture_width, testTexture_height);
		ImGui::Image((void*)(intptr_t)testTexture, ImVec2((float)testTexture_width, (float)testTexture_height));
		ImGui::End();

		// Ventana de botones
		//ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 1.0f)); // Set window background to red
		ImGui::SetNextWindowSize(ImVec2(300,720));
		ImGui::SetNextWindowPos(ImVec2(0,0));
		ImGui::PushStyleVar(ImGuiStyleVar_WindowTitleAlign, ImVec2(0.5f, 0.5f));
		ImGui::Begin("Menu", nullptr, ImGuiWindowFlags(ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize));
		if (ImGui::Button("Nueva partida", ImVec2(285, 50))) ;
		if (ImGui::Button("Pausar partida", ImVec2(285, 50))) ;
		if (ImGui::Button("Ajustes", ImVec2(285, 50))) onSettings = !onSettings;
		if (ImGui::Button("Salir", ImVec2(285, 50))) glfwSetWindowShouldClose(window, 1); // EXPLOTA EXPLOTA MI CORASÓN
		ImGui::End();
		//ImGui::PopStyleColor();

		// Ventana de ajustes
		if (onSettings) {
            ImGui::SetNextWindowSize(ImVec2(400,300));
            ImGui::SetNextWindowPos(ImVec2(440,210));
		    ImGui::Begin("Ajustes", nullptr, ImGuiWindowFlags(ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize));
		    // GUI DE AJUSTES HERE
		    float c[3] = {1.0f, 1.0f, 1.0f};
		    //ImGui::ColorPicker3("Color", c, ImGuiColorEditFlags());
		    //ImGui::ColorButton("Hey", ImVec4( 0.33f, 0.77f, 0.2f, 1.0f));
            ImGui::ColorEdit3("color 1", col1);
		    ImGui::End();
		}

		// Ventana de juego (probablemente será eliminado)
		ImGui::SetNextWindowSize(ImVec2(960, 500));
		ImGui::SetNextWindowPos(ImVec2(310, 10));
		ImGui::Begin("Juego", nullptr, ImGuiWindowFlags(ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize));
		ImGui::Image((void*)(intptr_t)my_image_texture, ImVec2((float) my_image_width, (float) my_image_height));
		ImGui::End();
		ImGui::PopStyleVar();

		ImGui::ShowDemoWindow();

		// Render dear imgui into screen
		ImGui::EndFrame();
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

bool LoadTextureFromFile(const char* filename, GLuint* out_texture, int* out_width, int* out_height)
{
	// Load from file
	int image_width = 16;
	int image_height = 16;
	unsigned char* image_data = stbi_load(filename, &image_width, &image_height, nullptr, 4);
	if (image_data == nullptr) return false;

	// Create a OpenGL texture identifier
	GLuint image_texture;
	glGenTextures(1, &image_texture);
	glBindTexture(GL_TEXTURE_2D, image_texture);

	// Setup filtering parameters for display
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // This is required on WebGL for non power-of-two textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); // Same

	// Upload pixels into texture
#if defined(GL_UNPACK_ROW_LENGTH) && !defined(__EMSCRIPTEN__)
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
#endif
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
	stbi_image_free(image_data);

	*out_texture = image_texture;
	*out_width = image_width;
	*out_height = image_height;

	return true;
}

void loadIcon(GLFWwindow* window, const char* filename)
{
	GLFWimage images[1];
	images[0].pixels = stbi_load(filename, &images[0].width, &images[0].height, 0, 4); //rgba channels 
	glfwSetWindowIcon(window, 1, images);
	stbi_image_free(images[0].pixels);
}