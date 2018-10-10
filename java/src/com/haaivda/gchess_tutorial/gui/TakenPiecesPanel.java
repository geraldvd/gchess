package com.haaivda.gchess_tutorial.gui;

import com.google.common.primitives.Ints;
import com.haaivda.gchess_tutorial.engine.board.Move;
import com.haaivda.gchess_tutorial.engine.pieces.Piece;
import com.haaivda.gchess_tutorial.gui.Table.MoveLog;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.border.EtchedBorder;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class TakenPiecesPanel extends JPanel {

    private final JPanel northPanel;
    private final JPanel southPanel;

    private static final EtchedBorder PANEL_BORDER = new EtchedBorder(EtchedBorder.RAISED);
    private static final Color PANEL_COLOR = Color.decode("0xFDFE6");
    private static final Dimension TAKEN_PIECES_DIMENSION = new Dimension(40, 80);

    public TakenPiecesPanel() {
        super(new BorderLayout());
        this.setBackground(PANEL_COLOR);
        this.setBorder(PANEL_BORDER);
        this.northPanel = new JPanel(new GridLayout(8, 2));
        this.southPanel = new JPanel(new GridLayout(8, 2));
        this.northPanel.setBackground(PANEL_COLOR);
        this.southPanel.setBackground(PANEL_COLOR);
        this.add(this.northPanel, BorderLayout.NORTH);
        this.add(this.southPanel, BorderLayout.SOUTH);
        this.setPreferredSize(TAKEN_PIECES_DIMENSION);
    }

    public void redo(MoveLog moveLog) {
        this.southPanel.removeAll();
        this.northPanel.removeAll();

        final List<Piece> whiteTakenPieces = new ArrayList<>();
        final List<Piece> blackTakenPieces = new ArrayList<>();

        for(Move move : moveLog.getMoves()) {
            if(move.isAttack()) {
                final Piece takenPiece = move.getAttackedPiece();
                if(takenPiece.getPieceAlliance().isWhite()) {
                    whiteTakenPieces.add(takenPiece);
                } else if(takenPiece.getPieceAlliance().isBlack()) {
                    blackTakenPieces.add(takenPiece);
                } else {
                    throw new RuntimeException("Should not reach here, only Black and White can exist.");
                }
            }
        }
        Collections.sort(whiteTakenPieces, new Comparator<Piece>() {
            @Override
            public int compare(Piece o1, Piece o2) {
                return Ints.compare(o1.getPieceValue(), o2.getPieceValue());
            }
        });
        Collections.sort(blackTakenPieces, new Comparator<Piece>() {
            @Override
            public int compare(Piece o1, Piece o2) {
                return Ints.compare(o1.getPieceValue(), o2.getPieceValue());
            }
        });
        for(Piece takenPiece : whiteTakenPieces) {
            try {
                String fileName = Table.PIECE_ICON_PATH + takenPiece.toString() + "_" + takenPiece.getPieceAlliance().toString() + ".png";
                final BufferedImage image = ImageIO.read(new File(fileName));
                final ImageIcon icon = new ImageIcon(image);
                final JLabel imageLabel = new JLabel(); // TODO
                this.southPanel.add(imageLabel);
            } catch(IOException e) {
                e.printStackTrace();
            }
        }
        for(Piece takenPiece : blackTakenPieces) {
            try {
                String fileName = Table.PIECE_ICON_PATH + takenPiece.toString() + "_" + takenPiece.getPieceAlliance().toString() + ".png";
                final BufferedImage image = ImageIO.read(new File(fileName));
                final ImageIcon icon = new ImageIcon(image);
                final JLabel imageLabel = new JLabel(); // TODO
                this.northPanel.add(imageLabel);
            } catch(IOException e) {
                e.printStackTrace();
            }
        }
        this.validate();
    }
}
