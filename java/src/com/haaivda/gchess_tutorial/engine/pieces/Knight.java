package com.haaivda.gchess_tutorial.engine.pieces;

import com.haaivda.gchess_tutorial.engine.Alliance;
import com.haaivda.gchess_tutorial.engine.board.Board;
import com.haaivda.gchess_tutorial.engine.board.BoardUtils;
import com.haaivda.gchess_tutorial.engine.board.Move;
import com.haaivda.gchess_tutorial.engine.board.Move.MajorAttackMove;
import com.haaivda.gchess_tutorial.engine.board.Move.MajorMove;
import com.haaivda.gchess_tutorial.engine.board.Tile;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;


public class Knight extends Piece {
    private final int[] CANDIDATE_MOVE_COORDINATES = {-17, -15, -10, -6, 6, 10, 15, 17};

    public Knight(int piecePosition, Alliance pieceAlliance, boolean isFirstMove) {
        super(PieceType.KNIGHT, piecePosition, pieceAlliance, isFirstMove);
    }

    @Override
    public List<Move> calculateLegalMoves(Board board) {
        final List<Move> legalMoves = new ArrayList<>();
        
        for(int currentCandidateOffset : CANDIDATE_MOVE_COORDINATES) {
            final int candidateDestinationCoordinate = piecePosition + currentCandidateOffset;
            if(BoardUtils.isValidTileCoordinate(candidateDestinationCoordinate)){ 
                if(isFirstColumnExclusion(this.piecePosition, currentCandidateOffset) ||
                        isSecondColumnExclusion(this.piecePosition, currentCandidateOffset) ||
                        isSeventhColumnExclusion(this.piecePosition, currentCandidateOffset) ||
                        isEighthColumnExclusion(this.piecePosition, currentCandidateOffset)) {
                    continue;
                }
                final Tile destinationTile = board.getTile(candidateDestinationCoordinate);
                if(!destinationTile.isTileOccupied()) {
                    legalMoves.add(new MajorMove(board, this, candidateDestinationCoordinate));
                } else {
                    if (this.pieceAlliance != destinationTile.getPiece().getPieceAlliance()) {
                        legalMoves.add(new MajorAttackMove(board, this, candidateDestinationCoordinate, destinationTile.getPiece()));
                    } 
                }
            }            
        }
        return Collections.unmodifiableList(legalMoves);
    }

    @Override
    public Knight movePiece(Move move) {
        return new Knight(move.getDestinationCoordinate(), move.getMovedPiece().getPieceAlliance(), false);
    }
    
    @Override
    public String toString() {
        return PieceType.KNIGHT.toString();
    }
    
    private static boolean isFirstColumnExclusion(int currentPosition, int candidateOffset) {
        return BoardUtils.FIRST_COLUMN[currentPosition] && (candidateOffset == -17 || candidateOffset == -10 || 
                candidateOffset == 6 || candidateOffset == 15);
    }
    
    private static boolean isSecondColumnExclusion(int currentPosition, int candidateOffset) {
        return BoardUtils.SECOND_COLUMN[currentPosition] && (candidateOffset == -10 || candidateOffset == 6);
    }
    
    private static boolean isSeventhColumnExclusion(int currentPosition, int candidateOffset) {
        return BoardUtils.SEVENTH_COLUMN[currentPosition] && (candidateOffset == -6 || candidateOffset == 10);
    }
    
    private static boolean isEighthColumnExclusion(int currentPosition, int candidateOffset) {
        return BoardUtils.EIGHTH_COLUMN[currentPosition] && (candidateOffset == -15 || candidateOffset == -6 || 
                candidateOffset == 10 || candidateOffset == 17);
    }
}
