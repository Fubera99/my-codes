package calc;

import calc.util.CellName;
import calc.util.SheetException;

public class Sheet {
	Evaluable[][] sheet = null;

	public Sheet(int numOfRows, int numOfCols) throws IllegalArgumentException {
		if (numOfCols > 26 || numOfRows < 0 || numOfCols < 0)
			throw new IllegalArgumentException(
					"The number of rows and columns must be bigger than 0, and the number of columns must be less than 27.");
		sheet = new Evaluable[numOfCols][numOfRows];
	}

	public void insertToSheet(String cellName, Evaluable ref) {
		if (CellName.isCellNameValid(cellName)) {
			try {
				sheet[CellName.getRowIndexFromCellName(cellName)][CellName.getColIndexFromCellName(cellName)] = ref;
			} catch (SheetException e) {

			}
		}
	}

	public Evaluable getFromSheet(String cellName) {
		if (CellName.isCellNameValid(cellName)) {
			try {
				return sheet[CellName.getRowIndexFromCellName(cellName)][CellName.getColIndexFromCellName(cellName)];
			} catch (SheetException e) {
				return null;
			}
		} else
			return null;
	}

	public static int constructIntFromOperandStr(String operand, Sheet sheet) throws IllegalArgumentException {
		if (CellName.isCellNameValid(operand)) {
			try {
				return sheet.getFromSheet(operand).eval(sheet);
			} catch (SheetException e) {
				throw new IllegalArgumentException("Arguments were not valid: " + operand);
			}
		} else {
			try {
				return Integer.parseInt(operand);
			} catch (NumberFormatException e) {
				throw new IllegalArgumentException("Arguments were not valid: " + operand);
			}
		}
	}

	@Override
	public String toString() {
		int toPrint;
		StringBuilder sb = new StringBuilder();
		for (int i = 0; i < sheet.length; i++) {
			for (int j = 0; j < sheet[i].length; j++) {

				try {
					toPrint = sheet[i][j].eval(this);
					if (j == sheet[i].length - 1) {
						sb.append(toPrint);
					} else {
						sb.append(toPrint + " ");
					}

				} catch (Exception e) {
					if (j == sheet[i].length - 1) {
						sb.append("null");
					} else {
						sb.append("null ");
					}
				}
			}
			if (!(sheet.length - 1 == i)) {
				sb.append(System.lineSeparator());
			}
		}
		return sb.toString();
	}

}
