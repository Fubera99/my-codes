package tests;

import calc.util.CellName;
import calc.util.SheetException;
import calc.Equation;
import calc.Num;
import calc.Sheet;

import static org.junit.Assert.assertTrue;
import static org.junit.Assert.assertEquals;

import org.junit.Test;

public class Tests {

	@Test
	public void isCellNameValidTest() {
		assertEquals(CellName.isCellNameValid("C 2"), false);
		assertEquals(CellName.isCellNameValid("c2"), false);
		assertEquals(CellName.isCellNameValid("Casd"), false);
		assertEquals(CellName.isCellNameValid("C2"), true);
		assertEquals(CellName.isCellNameValid("Z2"), true);
	}

	@Test
	public void getRowIndexFromCellNameTest() {
		try {
			assertEquals(CellName.getRowIndexFromCellName("C2"), 2);

			assertEquals(CellName.getRowIndexFromCellName("C10"), 10);
		} catch (SheetException e) {
			assertTrue(false);
		}
	}

	@Test
	public void getColIndexFromCellNameTest() {
		try {
			assertEquals(CellName.getColIndexFromCellName("A1"), 0);
			assertEquals(CellName.getColIndexFromCellName("Z1"), 25);
		} catch (SheetException e) {
			assertTrue(false);
		}
	}

	@Test
	public void numTest() {
		Num num = new Num(2);
		try {
			assertEquals(num.eval(null), 2);
		} catch (SheetException e) {
			assertTrue(false);
		}
	}

	@Test(expected = IllegalArgumentException.class)
	public void error1() {
		// Creating an @Equation with spaces should throw an exception.
		Equation eq1 = new Equation("C2 + C3");
	}

	@Test(expected = IllegalArgumentException.class)
	public void error2() {
		// Creating an @Equation with lower case should throw an exception.
		Equation eq2 = new Equation("c2+c3");
	}

	@Test(expected = IllegalArgumentException.class)
	public void error3() {
		// Creating an @Equation with undefined operator should throw an exception.
		Equation eq3 = new Equation("C2?C3");
	}

	@Test
	public void printTest() {
		Sheet s = new Sheet(2, 3);
		s.insertToSheet("A0", new Num(6));
		s.insertToSheet("A1", new Num(2));
		s.insertToSheet("A2", new Num(2));
		s.insertToSheet("B0", new Num(5));
		s.insertToSheet("B1", new Num(6));
		s.insertToSheet("B2", new Num(9));
		assertEquals(s.toString(), ("6 5" + System.lineSeparator() + "2 6" + System.lineSeparator() + "2 9"));
	}

	@Test
	public void equationTest() {
		Sheet s = new Sheet(3, 3);
		s.insertToSheet("A0", new Num(6));
		s.insertToSheet("A1", new Num(2));
		s.insertToSheet("A2", new Num(2));
		s.insertToSheet("B0", new Num(5));
		s.insertToSheet("B1", new Num(6));
		s.insertToSheet("B2", new Num(9));
		s.insertToSheet("C0", new Equation("A0+B0"));
		s.insertToSheet("C1", new Equation("A1+B1"));
		s.insertToSheet("C2", new Equation("A2+B2"));
		assertEquals(s.toString(), ("6 5 11" + System.lineSeparator() + "2 6 8" + System.lineSeparator() + "2 9 11"));
	}

	@Test
	public void equationTestDuplicate() {
		Sheet s = new Sheet(4, 3);
		s.insertToSheet("A0", new Num(6));
		s.insertToSheet("A1", new Num(2));
		s.insertToSheet("A2", new Num(2));
		s.insertToSheet("B0", new Num(5));
		s.insertToSheet("B1", new Num(6));
		s.insertToSheet("B2", new Num(9));
		s.insertToSheet("C0", new Equation("A0+B0"));
		s.insertToSheet("C1", new Equation("A1+B1"));
		s.insertToSheet("C2", new Equation("A2+B2"));
		s.insertToSheet("D0", new Equation("C0/2"));
		s.insertToSheet("D1", new Equation("C1/2"));
		s.insertToSheet("D2", new Equation("C2/2"));
		assertEquals(s.toString(), ("6 5 11 5" + System.lineSeparator() + "2 6 8 4" + System.lineSeparator() + "2 9 11 5"));
	}

	@Test
	public void equationTestMultiply() {
		Sheet s = new Sheet(3, 3);
		s.insertToSheet("A0", new Num(6));
		s.insertToSheet("A1", new Num(2));
		s.insertToSheet("A2", new Num(2));
		s.insertToSheet("B0", new Num(5));
		s.insertToSheet("B1", new Num(6));
		s.insertToSheet("B2", new Num(9));
		s.insertToSheet("C0", new Equation("10*B0"));
		s.insertToSheet("C1", new Equation("10*B1"));
		s.insertToSheet("C2", new Equation("10*B2"));
		assertEquals(s.toString(), ("6 5 50" + System.lineSeparator() + "2 6 60" + System.lineSeparator() + "2 9 90"));
	}
}