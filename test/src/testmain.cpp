#include <entry.h>
#include "testlayer.h"

class Test : public Application {
    public:
        Test(ApplicationInfo info, ApplicationCommandLineArgs args) : Application(info, args) {
            pushLayer(new TestLayer("main layer"));
			pushLayer(new Layer("name"));
        }

        ~Test() {};
};

Application* createApplication(ApplicationCommandLineArgs args) {
	ApplicationInfo info;
	info.height = 900;
	info.width = 1600;
	
    return new Test(info, args);
}
