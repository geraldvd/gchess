package com.haaivda.gchess_tutorial.engine.board;

import com.haaivda.gchess_tutorial.engine.pieces.Piece;

import java.util.Collections;
import java.util.HashMap;
import java.util.Map;


public abstract class Tile {
    protected final int tileCoordinate;
    private final static Map<Integer, Tile> EMPTY_TILES_CACHE = createAllPossibleEmptyTile();
    
    private Tile(int tileCoordinate) {
        this.tileCoordinate = tileCoordinate;
    }

    public int getTileCoordinate() {
        return this.tileCoordinate;
    }

    public static Tile createTile(int tileCoordinate, Piece piece) {
        return piece != null ? new OccupiedTile(tileCoordinate, piece) : EMPTY_TILES_CACHE.get(tileCoordinate);
    }
        
    private static Map<Integer, Tile> createAllPossibleEmptyTile() {
        final Map<Integer, Tile> emptyTileMap = new HashMap<>();
        for(int i = 0; i < BoardUtils.NUM_TILES; i++) {
            emptyTileMap.put(i, new EmptyTile(i));
        }
        
        return Collections.unmodifiableMap(emptyTileMap);
    }
    
    public abstract boolean isTileOccupied();
    public abstract Piece getPiece();
    
    public static final class EmptyTile extends Tile {
        private EmptyTile(int tileCoordinate) {
            super(tileCoordinate);
        }
        
        @Override
        public String toString() {
            return "-";
        }

        @Override
        public boolean isTileOccupied() {
            return false;
        }

        @Override
        public Piece getPiece() {
            return null;
        }
    }
    
    public static final class OccupiedTile extends Tile {
        private final Piece pieceOnTile;
        
        private OccupiedTile(int tileCoordinate, Piece piece) {
            super(tileCoordinate);
            this.pieceOnTile = piece;
        }
        
        @Override
        public String toString() {
            return this.pieceOnTile.getPieceAlliance().isBlack() ? this.pieceOnTile.toString().toLowerCase() : this.pieceOnTile.toString().toUpperCase();
        }

        @Override
        public boolean isTileOccupied() {
            return true;
        }

        @Override
        public Piece getPiece() {
            return pieceOnTile;
        }
    }
}
