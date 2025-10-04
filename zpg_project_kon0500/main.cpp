#include "Application.h"

int main() {
    Application app;
    app.initialization();
    app.createShaders();
    app.run();
    return 0;
}
