// main.cpp
// C++17 + SDL3 + SDL3_image + SDL3_ttf
// Enter -> abre diálogo; ao selecionar, mostra a imagem e escreve o path na janela.

#include <SDL3/SDL.h>
#include <SDL3/SDL_dialog.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <string>
#include <memory>

static Uint32 FILE_SELECTED_EVENT;

struct ImageTex
{
    SDL_Texture *tex = nullptr;
    int w = 0, h = 0;
};

struct TextTex
{
    SDL_Texture *tex = nullptr;
    int w = 0, h = 0;
};

static void destroyTexture(SDL_Texture *&t)
{
    if (t)
    {
        SDL_DestroyTexture(t);
        t = nullptr;
    }
}

static SDL_Texture *loadTexture(SDL_Renderer *r, const std::string &path, int &w, int &h)
{
    SDL_Surface *surf = IMG_Load(path.c_str());
    if (!surf)
    {
        SDL_Log("IMG_Load failed: %s", SDL_GetError());
        return nullptr;
    }
    w = surf->w;
    h = surf->h;
    SDL_Texture *tex = SDL_CreateTextureFromSurface(r, surf);
    SDL_DestroySurface(surf);
    return tex;
}

static SDL_Texture *renderText(SDL_Renderer *r, TTF_Font *font, const std::string &text, SDL_Color color, int &w, int &h)
{
    if (!font)
        return nullptr;
    SDL_Surface *surf = TTF_RenderText_Blended(font, text.c_str(), text.size(), color);
    if (!surf)
    {
        SDL_Log("TTF_RenderUTF8_Blended failed: %s", SDL_GetError());
        return nullptr;
    }
    w = surf->w;
    h = surf->h;
    SDL_Texture *tex = SDL_CreateTextureFromSurface(r, surf);
    SDL_DestroySurface(surf);
    return tex;
}

static void drawImageFit(SDL_Renderer *r, SDL_Texture *tex, int imgW, int imgH, const SDL_FRect &area)
{
    if (!tex)
        return;
    float arImg = (float)imgW / (float)imgH;
    float arBox = area.w / area.h;
    float w, h;
    if (arImg > arBox)
    {
        w = area.w;
        h = w / arImg;
    }
    else
    {
        h = area.h;
        w = h * arImg;
    }
    SDL_FRect dst{area.x + (area.w - w) * 0.5f, area.y + (area.h - h) * 0.5f, w, h};
    SDL_RenderTexture(r, tex, nullptr, &dst);
}

// Callback do diálogo: empurra um evento com o path (alocado via SDL_strdup)
static void SDLCALL fileDialogCallback(void *userdata, const char *const *filelist, int filter)
{
    SDL_Event ev{};
    ev.type = FILE_SELECTED_EVENT;
    ev.user.data1 = (filelist && filelist[0]) ? SDL_strdup(filelist[0]) : nullptr;
    SDL_PushEvent(&ev);
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) != true)
    {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return 1;
    }

    // SDL_ttf
    if (TTF_Init() != true)
    {
        SDL_Log("TTF_Init failed: %s", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    SDL_Window *window = SDL_CreateWindow("SDL3 File Dialog + Image + Path", 960, 640, SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        SDL_Log("CreateWindow failed: %s", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, nullptr);
    if (!renderer)
    {
        SDL_Log("CreateRenderer failed: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Fonte (ajuste o caminho de uma fonte .ttf válida ou use uma do sistema)
    // Exemplos comuns (depende do OS): "/System/Library/Fonts/SFNS.ttf" (macOS) ou "C:/Windows/Fonts/arial.ttf"
    const char *fontPath = "resources/arial.ttf"; // altere conforme seu sistema
    std::unique_ptr<TTF_Font, void (*)(TTF_Font *)> font(
        TTF_OpenFont(fontPath, 18), [](TTF_Font *f)
        { if (f) TTF_CloseFont(f); });
    if (!font)
    {
        SDL_Log("TTF_OpenFont failed for '%s': %s", fontPath, SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Evento customizado para receber o path do callback
    FILE_SELECTED_EVENT = SDL_RegisterEvents(1);
    if (FILE_SELECTED_EVENT == 0)
    {
        SDL_Log("SDL_RegisterEvents failed");
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Filtros
    static const SDL_DialogFileFilter filters[] = {
        {"Images", "png;jpg;jpeg;bmp"},
        {"All files", "*"}};

    ImageTex image{};
    TextTex pathText{};
    std::string currentPath;

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
                    SDL_ShowOpenFileDialog(
                        fileDialogCallback,
                        nullptr,
                        window,
                        filters,
                        SDL_arraysize(filters),
                        nullptr,
                        false);
                }
            }
            else if (e.type == FILE_SELECTED_EVENT)
            {
                const char *path = static_cast<const char *>(e.user.data1);
                if (path)
                {
                    // Carrega imagem
                    destroyTexture(image.tex);
                    image.tex = loadTexture(renderer, path, image.w, image.h);
                    if (!image.tex)
                    {
                        SDL_Log("Failed to load image: %s", path);
                    }
                    else
                    {
                        SDL_Log("Arquivo selecionado: %s", path);
                    }

                    // Renderiza texto com o path
                    destroyTexture(pathText.tex);
                    SDL_Color white{230, 230, 230, 255};
                    pathText.tex = renderText(renderer, font.get(), path, white, pathText.w, pathText.h);
                    currentPath = path;

                    SDL_free((void *)path); // libera a cópia do callback
                }
                else
                {
                    SDL_Log("Dialog canceled or error: %s", SDL_GetError());
                }
            }
        }

        int ww, wh;
        SDL_GetWindowSize(window, &ww, &wh);
        SDL_SetRenderDrawColor(renderer, 18, 18, 20, 255);
        SDL_RenderClear(renderer);

        // Área de imagem (com margem para o texto no rodapé)
        float bottomTextH = (pathText.tex ? (float)pathText.h + 16.f : 0.f);
        SDL_FRect imgArea{0.f, 0.f, (float)ww, (float)wh - bottomTextH};
        if (image.tex)
        {
            drawImageFit(renderer, image.tex, image.w, image.h, imgArea);
        }

        // Texto com o path (rodapé)
        if (pathText.tex)
        {
            SDL_FRect dst{8.f, (float)wh - (float)pathText.h - 8.f, (float)pathText.w, (float)pathText.h};
            SDL_RenderTexture(renderer, pathText.tex, nullptr, &dst);
        }
        else
        {
            // Dica inicial
            const char *hint = "Press ENTER to open an image. ESC to quit.";
            int tw = 0, th = 0;
            SDL_Texture *tmp = renderText(renderer, font.get(), hint, SDL_Color{160, 160, 160, 255}, tw, th);
            if (tmp)
            {
                SDL_FRect dst{8.f, (float)wh - (float)th - 8.f, (float)tw, (float)th};
                SDL_RenderTexture(renderer, tmp, nullptr, &dst);
                SDL_DestroyTexture(tmp);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    destroyTexture(image.tex);
    destroyTexture(pathText.tex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
