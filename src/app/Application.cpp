#include "Application.hpp"
#include "SDL3_ttf/SDL_ttf.h"
#include "app/FontManager.hpp"
#include "io/ConfigsReader.hpp"
#include "utils/LoggerConfig.hpp"

namespace app
{
    namespace constants
    {
        constexpr const char* CONFIGS_FILE_PATH = "resources/configurations/configs.json";
    } // namespace constants

    Application::Application()
        : m_fontManager(app::FontManager::getInstance())
    {
        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) != true)
        {
            utils::logger::error("SDL_Init failed: {}", SDL_GetError());
            exit(1);
        }

        if (!m_fontManager.initialize())
        {
            utils::logger::error("FontManager initialization failed");
            exit(1);
        }

        readConfigs();
        auto configs = io::ConfigsReader(constants::CONFIGS_FILE_PATH).getConfigs();
        m_renderer = new Renderer(configs);

        loadFonts();
    }

    Application::~Application()
    {
        m_fontManager.shutdown();
    }

    void Application::loadFonts()
    {
        if (!m_fontManager.loadFont("default", "resources/fonts/arial.ttf", 16))
        {
            utils::logger::error("Failed to load default font");
        }

        utils::logger::info("Fonts loaded successfully");
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

        utils::logger::info("Configurations read successfully!");
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
        }

        m_renderer->render();
    }
}
