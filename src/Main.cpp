#include "app/layers/AppLayer.hpp"
#include "app/layers/OverlayLayer.hpp"
#include "core/Application.hpp"
#include "core/utils/LoggerConfig.hpp"

int main()
{
    core::utils::LoggerConfig::Initialize("String Art Logger", "logs/log.txt");

    core::ApplicationSpecification appSpec;
    appSpec.Name = "String Art";
    appSpec.WindowSpec.Width = 1280;
    appSpec.WindowSpec.Height = 720;

    core::Application application(appSpec);
    application.PushLayer<AppLayer>();
    application.PushLayer<OverlayLayer>();
    application.Run();

    core::utils::LoggerConfig::Shutdown();
}
