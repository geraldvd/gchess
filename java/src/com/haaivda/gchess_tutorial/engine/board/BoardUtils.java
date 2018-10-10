package com.haaivda.gchess_tutorial.engine.board;


import java.util.Map;

public class BoardUtils {
    public static final boolean[] FIRST_COLUMN = initColumn(0);
    public static final boolean[] SECOND_COLUMN = initColumn(1);
    public static final boolean[] SEVENTH_COLUMN = initColumn(6);
    public static final boolean[] EIGHTH_COLUMN = initColumn(7);

    public static final boolean[] EIGHTH_RANK = initRow(0);
    public static final boolean[] SEVENTH_RANK = initRow(1);
    public static final boolean[] SIXTH_RANK = initRow(2);
    public static final boolean[] FIFTH_RANK = initRow(3);
    public static final boolean[] FOURTH_RANK = initRow(4);
    public static final boolean[] THIRD_RANK = initRow(5);
    public static final boolean[] SECOND_RANK = initRow(6);
    public static final boolean[] FIRST_RANK = initRow(7);

    public static final String[] ALGEBRAIC_NOTATION = initializeAlgebraicNotation();
    public static final Map<String, Integer> POSITION_TO_COORDINATE = initializePositionToCoordindateMap();


    public static final int NUM_TILES = 64;
    public static final int NUM_TILES_PER_ROW = 8;
    public static final int NUM_TILES_PER_COLUMN = 8;

    private BoardUtils() {
        throw new RuntimeException("You cannot instantiate me!");
    }

    private static boolean[] initColumn(int columnNumber) {
        final boolean[] column = new boolean[NUM_TILES];
        do {
            column[columnNumber] = true;
            columnNumber += NUM_TILES_PER_ROW;
        } while(columnNumber < NUM_TILES);
        return column;
    }

    private static boolean[] initRow(int rowNumber) {
        final boolean[] row = new boolean[NUM_TILES];
        rowNumber *= 8;
        for(int i = rowNumber; i < rowNumber + NUM_TILES_PER_COLUMN; i++) {
            row[i] = true;
        }
        return row;
    }

    private static String[] initializeAlgebraicNotation() {
        // TODO
        return null;
    }

    private static Map<String, Integer> initializePositionToCoordindateMap() {
        // TODO
        return null;
    }

    public static boolean isValidTileCoordinate(int candidateMovePosition) {
        return candidateMovePosition >= 0 && candidateMovePosition < NUM_TILES;
    }

    public static int getCoordinatePosition(String position) {
        return POSITION_TO_COORDINATE.get(position);

    }

    public static String getPositionAtCoordinate(int coordinate) {
        return ALGEBRAIC_NOTATION[coordinate];
    }
}
