// main.cpp
// C++17 + SDL3: mostra um diálogo de abrir arquivo e loga o path selecionado.

#include <SDL3/SDL.h>
#include <SDL3/SDL_dialog.h>
#include <string>

// Callback chamado quando o usuário escolhe (ou cancela) o diálogo
static void SDLCALL fileDialogCallback(void *userdata, const char *const *filelist, int filter)
{
    if (!filelist)
    {
        SDL_Log("Erro no diálogo: %s", SDL_GetError());
    }
    else if (!*filelist)
    {
        SDL_Log("Usuário cancelou o diálogo.");
    }
    else
    {
        SDL_Log("Arquivo selecionado: %s", filelist[0]);
    }
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != true)
    {
        SDL_Log("SDL_Init falhou: %s", SDL_GetError());
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL3 File Dialog Demo", 640, 480, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        SDL_Log("Erro ao criar janela: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Filtros (opcionais)
    static const SDL_DialogFileFilter filters[] = {
        {"Imagens", "png;jpg;jpeg;bmp"},
        {"Todos arquivos", "*"}};

    bool running = true;
    while (running)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
            else if (e.type == SDL_EVENT_KEY_DOWN)
            {
                if (e.key.key == SDLK_ESCAPE)
                {
                    running = false;
                }
                else if (e.key.key == SDLK_RETURN)
                {
                    // Abre diálogo quando pressionar "O"
                    SDL_ShowOpenFileDialog(
                        fileDialogCallback,
                        nullptr, // userdata opcional
                        window,  // janela pai
                        filters, // filtros
                        SDL_arraysize(filters),
                        nullptr, // diretório inicial
                        false    // allow_many
                    );
                }
            }
        }

        SDL_Delay(16); // loop simples
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
