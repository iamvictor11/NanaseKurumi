#include "xk/xkdialog.h"
#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("\x1b%%G");

    xkdialogresult result;
    xkdialogselected selected;
    result = xkdialogsave(
        XK_DIALOG_SHOW_HIDDEN,
        "text|*.txt|all|*.*",
        "untitled", "txt",
        ".",
        &selected
    );
    if (result == XK_DIALOG_ERROR) {}
    else if (result == XK_DIALOG_OKAY) { printf("dialogsave: %s\n", selected.paths[0]); xkdialogclose(selected); }
    else if (result == XK_DIALOG_CANCEL) {}

    getchar();
    return 0;
}
