package calc;

import calc.util.SheetException;

public interface Evaluable {
	public int eval(Sheet sheet) throws SheetException;
}
