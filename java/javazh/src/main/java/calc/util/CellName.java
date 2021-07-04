package calc.util;

public class CellName {
	final static String cellIndexes = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	public static boolean isCellNameValid(String cellName) {
		if (cellName.contains(" ") || cellName.contains("\t") || cellName.contains("\n"))
			return false;
		try {
			return cellIndexes.contains(String.valueOf(cellName.charAt(0))) && (Integer.parseInt(cellName.substring(1)) >= 0);
		} catch (NumberFormatException e) {
			return false;
		}

	}

	public static int getColIndexFromCellName(String cellName) throws SheetException {
		if (isCellNameValid(cellName)) {
			return cellIndexes.indexOf(cellName.charAt(0));
		} else
			throw new SheetException(
					"The cell name was not valid. Valid cell name eg: C3, but given cell name was " + cellName);
	}

	public static int getRowIndexFromCellName(String cellName) throws SheetException {
		if (isCellNameValid(cellName)) {
			return Integer.parseInt(cellName.substring(1));
		} else
			throw new SheetException(
					"The cell name was not valid. Valid cell name eg: C3, but given cell name was " + cellName);
	}
}
