#include "app/layers/AppLayer.h"
#include "app/layers/OverlayLayer.h"
#include "core/Application.h"
#include "core/utils/LoggerConfig.hpp"

int main()
{
    core::utils::LoggerConfig::Initialize("String Art Logger", "logs/log.txt");

    core::ApplicationSpecification appSpec;
    appSpec.Name = "Architecture";
    appSpec.WindowSpec.Width = 1280;
    appSpec.WindowSpec.Height = 720;

    core::Application application(appSpec);
    application.PushLayer<AppLayer>();
    application.PushLayer<OverlayLayer>();
    application.Run();

    core::utils::LoggerConfig::Shutdown();
}
