#include "Application.hpp"
#include "SDL3_ttf/SDL_ttf.h"
#include "io/ConfigsReader.hpp"
#include "utils/LoggerConfig.hpp"

namespace app
{
    namespace constants
    {
        constexpr const char* CONFIGS_FILE_PATH = "resources/configurations/configs.json";
    } // namespace constants

    Application::Application()
        : m_renderer(nullptr)
        , m_window(nullptr)
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) != true)
        {
            utils::logger::error("SDL_Init failed: {}", SDL_GetError());
            exit(1);
        }

        // SDL_ttf
        if (TTF_Init() != true)
        {
            utils::logger::error("TTF_Init failed: {}", SDL_GetError());
            TTF_Quit();
            SDL_Quit();
            exit(1);
        }

        m_window = SDL_CreateWindow("SDL3 File Dialog + Image + Path", 960, 640, SDL_WINDOW_RESIZABLE);
        if (!m_window)
        {
            utils::logger::error("CreateWindow failed: {}", SDL_GetError());
            TTF_Quit();
            SDL_Quit();
            exit(1);
        }

        m_renderer = SDL_CreateRenderer(m_window, nullptr);
        if (!m_renderer)
        {
            utils::logger::error("CreateRenderer failed: {}", SDL_GetError());
            SDL_DestroyWindow(m_window);
            TTF_Quit();
            SDL_Quit();
            exit(1);
        }

        readConfigs();
    }

    Application::~Application()
    {
        // Clean up SDL
        SDL_DestroyRenderer(m_renderer);
        SDL_DestroyWindow(m_window);
        TTF_Quit();
        SDL_Quit();
    }

    void Application::readConfigs()
    {
        io::ConfigsReader configsReader(constants::CONFIGS_FILE_PATH);
        auto configs = configsReader.getConfigs();

        utils::logger::info("Window Title: {}", configs.windowTitle);
        utils::logger::info("Window Width: {}", configs.windowWidth);
        utils::logger::info("Window Height: {}", configs.windowHeight);
        utils::logger::info("Number of Lines to Draw: {}", configs.numLinesToDraw);
        utils::logger::info("Number of Nails: {}", configs.numNails);
        utils::logger::info("Input Image Path: {}", configs.inputImagePath);
    }

    void Application::run()
    {
        // Main application loop
        bool running = true;
        SDL_Event event;
        while (running)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                {
                    running = false;
                }
            }

            // Update and render
            SDL_RenderClear(m_renderer);
            // Render your application content here
            SDL_RenderPresent(m_renderer);
        }
    }
}
