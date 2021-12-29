#include <entry.h>
#include "testlayer.h"

class Test : public Application {
    public:
        Test(ApplicationCommandLineArgs args) {
            pushLayer(new TestLayer());
        }

        ~Test() {};
};

Application* createApplication(ApplicationCommandLineArgs args) {
    return new Test(args);
}