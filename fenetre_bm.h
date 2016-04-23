#ifndef FENETRE_BM_H
#define FENETRE_BM_H

#include <QtGui>
#include <QtNetwork>
#include "ui_fenetre_bm.h"

class fenetre_bm : public QWidget, private Ui::fenetre_bm
{
    Q_OBJECT

private slots:
    void donneesRecues();
    void connecte();
    void erreurSocket(QAbstractSocket::SocketError erreur);
    
public:
    fenetre_bm();
    ~fenetre_bm();
    
private:
    QTcpSocket *socket;
    quint16 taille_message;
    QList<QTcpSocket *> clients;
};

#endif // FENETRE_BM_H
