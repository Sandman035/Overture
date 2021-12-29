#pragma once

#include <defines.h>
#include <core/application.h>

extern Application* createApplication(const ApplicationCommandLineArgs args);

i32 main(i32 argc, char ** argv)
{
    auto app = createApplication({argc, argv});
    app->run();
    delete app;
    return 0;
}