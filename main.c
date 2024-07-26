#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "./Modules/Nuklear/nuklear.h"
#include "./Modules/Nuklear/nuklear_glfw_gl4.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080
#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

int main(void) {
    GLFWwindow *win;
    struct nk_context *ctx;

    /* Initialize GLFW */
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW\n");
        return -1;
    }

    /* Create a GLFW windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Nuklear Demo", NULL, NULL);
    if (!win) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(win);
    glfwSetWindowSize(win, WINDOW_WIDTH, WINDOW_HEIGHT);

    /* Initialize Nuklear */
    ctx = nk_glfw3_init(win, NK_GLFW3_INSTALL_CALLBACKS, NULL);  // Added NULL for the context

    /* Load Fonts: if none of these are loaded a default font will be used */
    /* Load Cursor: if you uncomment cursor loading please hide the cursor */
    struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&atlas);
    /* struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "./extra_font/DroidSans.ttf", 14, 0); */
    nk_glfw3_font_stash_end();

    /* Set Nuklear style */
    nk_style_default(ctx);

    /* Main loop */
    while (!glfwWindowShouldClose(win)) {
        /* Input */
        glfwPollEvents();
        nk_glfw3_new_frame();

        /* GUI */
        if (nk_begin(ctx, "Demo", nk_rect(50, 50, 220, 220),
            NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
            NK_WINDOW_CLOSABLE | NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE)) {
            nk_layout_row_static(ctx, 30, 80, 1);
            if (nk_button_label(ctx, "Button")) {
                /* event handling */
            }
        }
        nk_end(ctx);

        /* Draw */
        int win_width, win_height;
        glfwGetWindowSize(win, &win_width, &win_height);
        glViewport(0, 0, win_width, win_height);
        glClear(GL_COLOR_BUFFER_BIT);
        nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
        glfwSwapBuffers(win);
    }

    /* Cleanup */
    nk_glfw3_shutdown();
    glfwDestroyWindow(win);
    glfwTerminate();
    return 0;
}
