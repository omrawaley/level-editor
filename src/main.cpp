#include "editor.h"

int main(int argc, char* argv[])
{
    Editor editor;

    editor.start();

    while(!editor.quit)
    {
        editor.eventLoop();

        editor.update();

        editor.draw();
    }

    return 0;
}
