package calc;

import calc.util.SheetException;
import calc.util.CellName;

public class Equation implements Evaluable {
	final String validOperators = "+-*/";
	String operand1;
	String operand2;
	Character operator;

	@Override
	public int eval(Sheet sheet) throws SheetException, ArithmeticException {
		int op1 = Sheet.constructIntFromOperandStr(operand1, sheet);
		int op2 = Sheet.constructIntFromOperandStr(operand2, sheet);
		if (operator == '/' && op2 == 0) {
			throw new ArithmeticException("Division by zero.");
		} else if (operator == '-' && (op1 - op2 < 0))
			throw new ArithmeticException("The result would be negative.");
		if (operator == '+') {
			return op1 + op2;
		} else if (operator == '-') {
			return op1 - op2;
		} else if (operator == '/') {
			return op1 / op2;
		} else {
			return op1 * op2;
		}
	}

	public Equation(String toEval) throws IllegalArgumentException {
		String parts[];
		if (toEval.contains("+")) {
			parts = toEval.split("\\+");
			operator = '+';
		} else if (toEval.contains("-")) {
			parts = toEval.split("-");
			operator = '-';
		} else if (toEval.contains("*")) {
			parts = toEval.split("\\*");
			operator = '*';
		} else if (toEval.contains("/")) {
			parts = toEval.split("/");
			operator = '/';
		} else
			throw new IllegalArgumentException("Unknown operator.");

		if (!CellName.isCellNameValid(parts[0])) {
			try {
				Integer.parseInt(parts[0]);
			} catch (NumberFormatException e) {
				throw new IllegalArgumentException("Invalid format.");
			}
		} else if (!CellName.isCellNameValid(parts[1])) {
			try {
				Integer.parseInt(parts[1]);
			} catch (NumberFormatException e) {
				throw new IllegalArgumentException("Invalid format.");
			}
		}
		if (parts.length != 2) {
			throw new IllegalArgumentException(
					"Invalid format. Example for a valid format: \"C1+B7\", and valid operators are: + - * /");
		}
		operand1 = parts[0];
		operand2 = parts[1];
	}
}
