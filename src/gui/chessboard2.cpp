#include "chessboard2.h"

// Include standard libraries
#include <string>
#include <sstream>

// Include Qt libraries
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QBitmap>
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QStyle>

// Namespaces
using namespace std;

Chessboard2::Chessboard2(QWidget *parent) :
    QWidget(parent)
{
    // Setup chessboard - TODO add resource file using cmake, so that images are packed in executable
    this->setFixedHeight(400);
    this->setFixedWidth(400);

    // test
    this->addPiece(Field(3,3), BLACK, ROOK);
    this->highlightField(Field(2,2));
    this->highlightField(Field(4,4));
    //this->unhighlightAllFields();
}

Chessboard2::~Chessboard2()
{
}

void Chessboard2::addPiece(const Field &position, const PieceColor &c, const PieceType &p)
{
    // Obtain image filename
    QString image_file = this->getImageFilename(c, p);

    // Set chesslabel with background image
    ChessLabel *l = new ChessLabel(position, this);
    QPixmap pm(image_file);
    l->setPixmap(pm);
    l->setMask(pm.mask());

    // Check whether piece already exists in that location; if so: remove it
    if(this->pieces.find(position) != this->pieces.end()) {
        ChessLabel *l = this->pieces[position];
        this->pieces.erase(position);
        delete l;
    }

    // Setup signals and slots
    //connect(l, SIGNAL(clicked()), this, SLOT(toggleHighlightMoves()));

    // Store new piece
    this->pieces[position] = l;
}

void Chessboard2::removePiece(const Field &position)
{
    if(this->pieces.find(position) != this->pieces.end()) {
        ChessLabel* l = this->pieces[position];
        this->pieces.erase(position);
        delete l;
    }
}

void Chessboard2::movePiece(const Field &from, const Field &to)
{
    if(this->pieces.find(from) != this->pieces.end()) {
        ChessLabel *l = this->pieces[from];
        this->pieces.erase(from);
        l->setField(to);
        this->pieces[to] = l;
    }
}

void Chessboard2::clearPieces()
{
    for(auto &f: this->pieces) {
        ChessLabel *l = f.second;
        delete l;
    }

    this->pieces.clear();
}

void Chessboard2::highlightField(const Field &position)
{
    if(this->highlights.find(position) == this->highlights.end()) {
        // Determine location of highlight
        ChessLabel* l = new ChessLabel(position, this);

        // Draw circle for highlighting
        QPixmap pm(l->width(),l->height());
        pm.fill(Qt::transparent);
        QPainter p(&pm);
        p.setRenderHint(QPainter::Antialiasing, true);
        // Pen settings
        QPen pen(Qt::lightGray, 0);
        p.setPen(pen);
        // Brush settings
        QBrush brush("#cccccc");
        p.setBrush(brush);
        // Draw circle
        p.drawEllipse(l->width()/2-10, l->height()/2-10, 2*10, 2*10);
        l->setPixmap(pm);
        l->setMask(pm.mask());

        // Add piece to highlighted fields
        this->highlights[position] = l;
    }
}

void Chessboard2::unhighlightField(const Field &position)
{
    if(this->highlights.find(position) != this->highlights.end()) {
        ChessLabel *l = this->highlights[position];
        this->highlights.erase(position);
        delete l;
    }
}

void Chessboard2::clearHighlights()
{
    for(auto &f: this->highlights) {
        ChessLabel *l = f.second;
        delete l;
    }

    this->highlights.clear();
}

QString Chessboard2::getImageFilename(const PieceColor &c, const PieceType &p)
{
    string s_color, s_type;
    stringstream ss;

    if(c == WHITE) {
        s_color = "white";
    } else {
        s_color = "black";
    }

    switch(p) {
    case KING:
        s_type = "king";
        break;
    case QUEEN:
        s_type = "queen";
        break;
    case ROOK:
        s_type = "rook";
        break;
    case KNIGHT:
        s_type = "knight";
        break;
    case BISHOP:
        s_type = "bishop";
        break;
    default:
        s_type = "pawn";
        break;
    }

    ss << "../images/" << s_type << "_" << s_color << ".png";
    return QString::fromStdString(ss.str());

}

void Chessboard2::paintEvent(QPaintEvent *p2)
{
    QPixmap pm("/home/gerald/git/gchess/images/chessboard.png");
    QPainter p(this);
    p.drawPixmap(0, 0, pm);
    QWidget::paintEvent(p2);
}
