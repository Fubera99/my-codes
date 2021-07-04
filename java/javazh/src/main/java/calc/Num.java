package calc;

import calc.util.SheetException;

public class Num implements Evaluable {
	int num;

	@Override
	public int eval(Sheet sheet) throws SheetException {
		return num;
	}

	public Num(int num) {
		if (num < 0)
			throw new IllegalArgumentException("The number cannot be negative.");
		this.num = num;
	}
}
