package com.haaivda.gchess_tutorial.gui;

import com.haaivda.gchess_tutorial.engine.board.Board;
import com.haaivda.gchess_tutorial.engine.board.Move;
import com.haaivda.gchess_tutorial.gui.Table.MoveLog;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.BorderLayout;
import java.awt.Dimension;
import java.util.ArrayList;
import java.util.List;

class GameHistoryPanel extends JPanel {

    private final DataModel model;
    private final JScrollPane scrollPane;

    GameHistoryPanel() {
        this.setLayout(new BorderLayout());
        this.model = new DataModel();
        final JTable table = new JTable(model);
        table.setRowHeight(15);
        this.scrollPane = new JScrollPane(table);
        scrollPane.setColumnHeaderView(table.getTableHeader());
        Dimension HISTORY_PANEL_DIMENSION = new Dimension(100, 400);
        scrollPane.setPreferredSize(HISTORY_PANEL_DIMENSION);
        this.add(scrollPane, BorderLayout.CENTER);
        this.setVisible(true);
    }

    void redo(Board board, MoveLog moveHistory) {
        int currentRow = 0;
        this.model.clear();
        for(Move move : moveHistory.getMoves()) {
            final String moveText = move.toString();
            if(move.getMovedPiece().getPieceAlliance().isWhite()) {
                this.model.setValueAt(moveText, currentRow, 0);
            } else if(move.getMovedPiece().getPieceAlliance().isBlack()) {
                this.model.setValueAt(moveText, currentRow, 1);
                // Increase when black has also moved!
                currentRow++;
            }
        }
        if(moveHistory.getMoves().size() > 0) {
            final Move lastMove = moveHistory.getMoves().get(moveHistory.size() - 1);
            final String moveText = lastMove.toString();

            if(lastMove.getMovedPiece().getPieceAlliance().isWhite()) {
                this.model.setValueAt(moveText + calculateCheckAndCheckMateHash(board), currentRow, 0);
            } else if(lastMove.getMovedPiece().getPieceAlliance().isBlack()) {
                this.model.setValueAt(moveText + calculateCheckAndCheckMateHash(board), currentRow - 1, 1);
            }
        }
        final JScrollBar vertical = scrollPane.getVerticalScrollBar();
        vertical.setValue(vertical.getMaximum());

    }

    private String calculateCheckAndCheckMateHash(Board board) {
        if(board.getCurrentPlayer().isInCheckMate()) {
            return "#";
        } else if(board.getCurrentPlayer().isInCheck()) {
            return "+";
        }
        return "";
    }

    private static class DataModel extends DefaultTableModel {

        private final List<Row> values;
        private static final String[] NAMES = {"White", "Black"};

        DataModel() {
            this.values = new ArrayList<>();
        }

        void clear() {
            this.values.clear();
            setRowCount(0);
        }

        @Override
        public int getRowCount() {
            if(this.values == null) {
                return 0;
            }
            return this.values.size();
        }

        @Override
        public int getColumnCount() {
            return NAMES.length;
        }

        @Override
        public Object getValueAt(int row, int column) {
            final Row currentRow = this.values.get(row);
            if(column == 0) {
                return currentRow.getWhiteMove();
            } else if(column == 1) {
                return currentRow.getBlackMove();
            }
            return null;
        }

        @Override
        public void setValueAt(Object aValue, int row, int column) {
            final Row currentRow;
            if(this.values.size() <= row) {
                currentRow = new Row();
                this.values.add(currentRow);
            } else {
                currentRow = this.values.get(row);
            }
            if(column == 0) {
                currentRow.setWhiteMove((String)aValue);
                fireTableRowsInserted(row, row);
            } else if(column == 1) {
                currentRow.setBlackMove((String)aValue);
                fireTableCellUpdated(row, column);
            }
        }

        @Override
        public Class<?> getColumnClass(int column) {
            return Move.class;
        }

        @Override
        public String getColumnName(int column) {
            return NAMES[column];
        }

    }

    private static class Row {
        private String whiteMove;
        private String blackMove;

        Row() {
        }

        String getWhiteMove() {
            return this.whiteMove;
        }

        String getBlackMove() {
            return this.blackMove;
        }

        void setWhiteMove(String move) {
            this.whiteMove = move;
        }

        void setBlackMove(String move) {
            this.blackMove = move;
        }
    }

}
