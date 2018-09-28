package com.haaivda.gchess_tutorial.board;

import com.haaivda.gchess_tutorial.pieces.Knight;
import com.haaivda.gchess_tutorial.Alliance;
import com.haaivda.gchess_tutorial.pieces.Bishop;
import com.haaivda.gchess_tutorial.pieces.King;
import com.haaivda.gchess_tutorial.pieces.Pawn;
import com.haaivda.gchess_tutorial.pieces.Piece;
import com.haaivda.gchess_tutorial.pieces.Queen;
import com.haaivda.gchess_tutorial.pieces.Rook;
import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class Board {
    private final List<Tile> gameBoard;
    
    private Board(Builder builder) {
        this.gameBoard = createGameBoard(builder);
    }
    
    private static List<Tile> createGameBoard(Builder builder) {
        List<Tile> tiles = new ArrayList<>();
        for(int i = 0; i<BoardUtils.NUM_TILES; i++) {
            tiles.add(Tile.createTile(i, builder.boardConfig.get(i)));
        }
        
        return Collections.unmodifiableList(tiles);
    }
    
    public static Board createStandardBoard() {
        Builder builder = new Builder();
        
        // White pieces
        builder.setPiece(new Rook(63, Alliance.WHITE));
        builder.setPiece(new Knight(62, Alliance.WHITE));
        builder.setPiece(new Bishop(61, Alliance.WHITE));
        builder.setPiece(new King(60, Alliance.WHITE));
        builder.setPiece(new Queen(59, Alliance.WHITE));
        builder.setPiece(new Bishop(58, Alliance.WHITE));
        builder.setPiece(new Knight(57, Alliance.WHITE));
        builder.setPiece(new Rook(56, Alliance.WHITE));
        builder.setPiece(new Pawn(55, Alliance.WHITE));
        builder.setPiece(new Pawn(54, Alliance.WHITE));
        builder.setPiece(new Pawn(53, Alliance.WHITE));
        builder.setPiece(new Pawn(52, Alliance.WHITE));
        builder.setPiece(new Pawn(51, Alliance.WHITE));
        builder.setPiece(new Pawn(50, Alliance.WHITE));
        builder.setPiece(new Pawn(49, Alliance.WHITE));
        builder.setPiece(new Pawn(48, Alliance.WHITE));
    }
    
    public Tile getTile(int candidateMovePosition) {
        return null;
    }
    
    public static class Builder {
        Map<Integer, Piece> boardConfig;
        Alliance nextMoveMaker;
        
        public Builder() {
            this.boardConfig = new HashMap<>();
        }
        
        public Builder setPiece(Piece piece) {
            this.boardConfig.put(piece.getPiecePosition(), piece);
            return this;
        }
        
        public Builder setMoveMaker(Alliance nextMoveMaker) {
            this.nextMoveMaker = nextMoveMaker;
            return this;
        }
        
        public Board build() {
            return new Board(this);
        }
    }
    
}
