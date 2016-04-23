#include <QtWidgets/QApplication>
#include "fenetre_bm.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    fenetre_bm fenetre;
    fenetre.show();

    return app.exec();
}
