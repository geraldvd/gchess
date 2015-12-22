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
#include <QFont>

// Include project files
#include "chessboard.h"

// Namespaces
using namespace std;

Chessboard::Chessboard(QWidget *parent) :
    QLabel(parent),
    parent(parent),
    check_field(NULL)
{
    // Setup chessboard - TODO add resource file using cmake, so that images are packed in executable
    this->setFixedHeight(400);
    this->setFixedWidth(400);
    this->setStyleSheet("background-image: url(../images/chessboard.png)");
    this->setVisible(true);
}

Chessboard::~Chessboard()
{
}

void Chessboard::addPiece(const unsigned int &position, const PieceColor &c, const PieceType &p)
{
    // Obtain image filename
    QString image_file = this->getImageFilename(c, p);
    QString piece_html = this->getPieceHTML(c, p);

    // Set chesslabel with background image
    ChessLabel *l = new ChessLabel(position, this);
    QPixmap pm(image_file);
    l->setPixmap(pm);
    l->setMask(pm.mask());

    // Using Unicode pieces
//    l->setText(piece_html);
//    l->setAttribute(Qt::WA_TranslucentBackground);
//    QFont f = l->font();
//    f.setPointSize(36);
//    f.setBold(true);
//    f.setFamily("Arial");
//    l->setFont(f);

    l->setVisible(true);

    // Check whether piece already exists in that location; if so: remove it
    if(this->pieces.find(position) != this->pieces.end()) {
        ChessLabel *l = this->pieces[position];
        this->pieces.erase(position);
        delete l;
    }

    // Setup signals and slots
    connect(l, SIGNAL(clicked()), this->parent, SLOT(toggleHighlighting()));

    // Store new piece
    this->pieces[position] = l;
}

void Chessboard::removePiece(const unsigned int &position)
{
    if(this->pieces.find(position) != this->pieces.end()) {
        ChessLabel* l = this->pieces[position];
        this->pieces.erase(position);
        delete l;
    }
}

void Chessboard::movePiece(const unsigned int &from, const unsigned int &to)
{
    if(this->pieces.find(from) != this->pieces.end()) {
        // Move piece
        ChessLabel *l = this->pieces[from];
        this->pieces.erase(from);
        l->setPosition(to);

        // Replace piece if already in destination
        if(this->pieces.find(to) != this->pieces.end()) {
            this->removePiece(to);
        }

        // Store pointer to moved piece
        this->pieces[to] = l;
    }
}

void Chessboard::clearPieces()
{
    for(auto &f: this->pieces) {
        ChessLabel *l = f.second;
        delete l;
    }

    this->pieces.clear();
}

void Chessboard::highlightField(const Move &move)
{
    if(this->highlights.find(move.getPosition()) == this->highlights.end()) {
        // Determine location of highlight
        ChessLabel* l = new ChessLabel(move.getPosition(), this);

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
        l->setVisible(true);

        // Add move to label
        l->setMove(move);

        // Setup signals and slots
        connect(l, SIGNAL(clicked()), this->parent, SLOT(slotMovePiece()));

        // Add piece to highlighted fields
        this->highlights[move.getPosition()] = l;
    }
}

void Chessboard::unhighlightField(const unsigned int &position)
{
    if(this->highlights.find(position) != this->highlights.end()) {
        ChessLabel *l = this->highlights[position];
        this->highlights.erase(position);
        delete l;
    }
}

void Chessboard::clearHighlights()
{
    for(auto &f: this->highlights) {
        ChessLabel *l = f.second;
        delete l;
    }

    this->highlights.clear();
}

void Chessboard::checkField(const unsigned int &position)
{
    // Determine location of highlight
    this->check_field = new ChessLabel(position, this);

    // Highlight check position
    QPixmap pm(this->check_field->width(),this->check_field->height());
    pm.fill(Qt::red);
    this->check_field->setPixmap(pm);
    this->check_field->setMask(pm.mask());
    this->check_field->setVisible(true);
    this->check_field->lower();
}

void Chessboard::unCheckField()
{
    delete this->check_field;
    this->check_field = NULL;
}

QString Chessboard::getImageFilename(const PieceColor &c, const PieceType &p)
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

QString Chessboard::getPieceHTML(const PieceColor &c, const PieceType &p)
{
    string pieceHTML;
    stringstream ss;

    // Get piece HTML code
    switch(p) {
    case KING:
        pieceHTML = c==WHITE ? "&#9812;" : "&#9818;";
        break;
    case QUEEN:
        pieceHTML = c==WHITE ? "&#9813;" : "&#9819;";
        break;
    case ROOK:
        pieceHTML = c==WHITE ? "&#9814;" : "&#9820;";
        break;
    case KNIGHT:
        pieceHTML = c==WHITE ? "&#9816;" : "&#9822;";
        break;
    case BISHOP:
        pieceHTML = c==WHITE ? "&#9815;" : "&#9821;";
        break;
    default:
        pieceHTML = c==WHITE ? "&#9817;" : "&#9823;";
        break;
    }

    // Return formated html
    ss << "<div align='center'>" << pieceHTML << "</div>";
    return QString::fromStdString(ss.str());
}

//void Chessboard::paintEvent(QPaintEvent *p2)
//{
//    QPixmap pm("/home/gerald/git/gchess/images/chessboard.png");
//    QPainter p(this);
//    p.drawPixmap(0, 0, pm);
//    QWidget::paintEvent(p2);
//}
