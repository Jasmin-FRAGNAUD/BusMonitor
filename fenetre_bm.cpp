#include "fenetre_bm.h"

// adresse ip (127.0.0.1 ; LocalHost) et port (7800) du BC

fenetre_bm::fenetre_bm()
{
    setupUi(this);  // generation de la fenetre (ui)

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

    liste_messages->append(tr("Tentative de connexion au BC en cours..."));

    socket->connectToHost(QHostAddress::LocalHost,7800);


    taille_message = 0;  // on remet la variable de taille du message a 0
}

// destructeur de fenetre_bm
fenetre_bm::~fenetre_bm(){
}

void fenetre_bm::connecte()
{
    // Si le serveur a �t� d�marr� correctement
    liste_messages->append(tr("Connexion r�ussie !"));
    liste_messages->append(tr(""));
    liste_messages->append(tr("Affichage des trames sous la forme :"));
    liste_messages->append(tr("Destinataire_Emetteur_Message."));
}

//fonction appell�e si on a la reception d'un message sur le socket
void fenetre_bm::donneesRecues()
{
    // 1 : on re�oit un paquet (ou un sous-paquet) d'un des clients

    // on r�cup�re le message
    QDataStream in(socket);

    if (taille_message == 0) // Si on ne conna�t pas encore la taille du message, on essaie de la r�cup�rer
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16)) // On n'a pas re�u la taille du message en entier
             return;

        in >> taille_message; // Si on a re�u la taille du message en entier, on la r�cup�re
    }

    // Si on conna�t la taille du message, on v�rifie si on a re�u le message en entier
    if (socket->bytesAvailable() < taille_message) // Si on n'a pas encore tout re�u, on arr�te la m�thode
        return;


    // Si ces lignes s'ex�cutent, c'est qu'on a re�u tout le message : on peut le r�cup�rer !
    QString message;
    in >> message;


    liste_messages->append(message);

    // 3 : remise de la taille du message � 0 pour permettre la r�ception des futurs messages
    taille_message = 0;
}

void fenetre_bm::erreurSocket(QAbstractSocket::SocketError erreur)
{
    switch(erreur) // On affiche un message diff�rent selon l'erreur qu'on nous indique
    {
        case QAbstractSocket::HostNotFoundError:
            liste_messages->append("ERREUR : le serveur n'a pas pu �tre trouv�.");
            break;
        case QAbstractSocket::ConnectionRefusedError:
            liste_messages->append("ERREUR : V�rifiez si le programme \"BC\" a bien �t� lanc�.");
            break;
        case QAbstractSocket::RemoteHostClosedError:
            liste_messages->append("ERREUR : le serveur a coup� la connexion.");
            break;
        default:
            liste_messages->append("ERREUR : "+socket->errorString());
    }
}
