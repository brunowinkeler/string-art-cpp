#include "Application.hpp"
#include "SDL3_ttf/SDL_ttf.h"
#include "app/FontManager.hpp"
#include "app/Resources.hpp"
#include "app/io/ConfigsReader.hpp"
#include "core/utils/LoggerConfig.hpp"

namespace app
{
    namespace constants
    {
        constexpr const char* CONFIGS_FILE_PATH = "configs.json";
    } // namespace constants

    Application::Application()
        : m_fontManager(app::FontManager::GetInstance())
    {
        if (SDL_Init(SDL_INIT_VIDEO) != true)
        {
            core::utils::Logger::error("SDL_Init failed: {}", SDL_GetError());
            exit(1);
        }

        if (!m_fontManager.Initialize())
        {
            core::utils::Logger::error("FontManager initialization failed");
            exit(1);
        }

        ReadConfigs();
        auto configs = io::ConfigsReader(constants::CONFIGS_FILE_PATH).GetConfigs();
        m_renderer = new Renderer(configs);

        LoadFonts();
    }

    Application::~Application()
    {
        m_fontManager.Shutdown();
    }

    void Application::LoadFonts()
    {
        if (!m_fontManager.LoadFont("default", std::string(Resources::Fonts::DEFAULT.path), 16))
        {
            core::utils::Logger::error("Failed to load default font");
        }

        core::utils::Logger::info("Fonts loaded successfully");
    }

    void Application::ReadConfigs()
    {
        io::ConfigsReader configsReader(constants::CONFIGS_FILE_PATH);
        auto configs = configsReader.GetConfigs();

        core::utils::Logger::info("Window Title: {}", configs.windowTitle);
        core::utils::Logger::info("Window Width: {}", configs.windowWidth);
        core::utils::Logger::info("Window Height: {}", configs.windowHeight);
        core::utils::Logger::info("Number of Lines to Draw: {}", configs.numLinesToDraw);
        core::utils::Logger::info("Number of Nails: {}", configs.numNails);
        core::utils::Logger::info("Input Image Path: {}", configs.inputImagePath);

        core::utils::Logger::info("Configurations read successfully!");
    }

    void Application::Run()
    {
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

        m_renderer->Render();
    }
}
