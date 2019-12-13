/*
 * Here we give some printing samples. There are many ways to print values out, here are just a few samples, most taken from:
 * https://www.arduino.cc/reference/en/language/functions/communication/serial/print/
 */

void setup() {
  Serial.begin(9600);                                               // Start a serial connection
  while(!Serial);                                                   // Wait for the serial connection to start

  printStrings();                                                   // String stuff
  Serial.println();                                                 // Print an empty line
  printNums();                                                      // Different numbers
  Serial.println();                                                 // Print an empty line
  numConversions();                                                 // Doing some conversions between numbers
}

/*
 * Some samples for working with Strings
 */
void printStrings() {
  Serial.println("This is a simple string");                        // Print a simple string
  String s = "String variable";
  Serial.print("Variable:\t");                                      // This prints out a string variable, but adds tab before variable value print
  Serial.println(s);
  Serial.print("There is another way to end line\n");               // This prints a line out, but uses \n as end line marker
  
  String t = "more string concatenation stuff";
  String r = s + " with " + t;
  Serial.println(r);
}

/*
 * Some samples of working with numbers
 */
void printNums() {
  int i = 42;
  double j = i + 0.735656;
  Serial.print("You can print out numbers too: ");                  // Printing out numbers
  Serial.println(42);
  Serial.println(i);
  Serial.println(j);
  Serial.print("i in binary (base 2): ");
  Serial.println(i, BIN);                                           // Variable value in binary
  Serial.print("i in octal (base 8): ");
  Serial.println(i, OCT);                                           // Variable value in octal
  Serial.print("i in decimal (base 10): ");
  Serial.println(i, DEC);                                           // Variable value in decimal. Since we use int i, which is already decimal itself, it just prints out the value as if the DEC format is not there since it's not needed
  Serial.print("i in hexadecimal (base 16): ");
  Serial.println(i, HEX);                                           // Variable value in hexadecimal

  Serial.println("You can actually print out decimals as well");
  Serial.println(j, 0);                                             // Prints out only full numbers
  Serial.println(j, 2);                                             // Prints out two decimal places
  Serial.println(j, 4);                                             // Prints out four decimal places
}

/*
 * Some more samples that show how Arduino works with numbers
 */
void numConversions() {
  int i = 42;                                                       // Local variables we use to show some conversion and printing stuff Arduino does
  double d = 42.3456;
  float f = 42.565f;

  Serial.print("integer: ");                                        // Printing the variables out
  Serial.println(i);
  Serial.print("double: ");
  Serial.println(d);
  Serial.print("float: ");
  Serial.println(f);

  Serial.print("double (all): ");                                   // Now it prints the decimals out as well
  Serial.println(d, 4);
  Serial.print("float (all): ");
  Serial.println(f, 3);
  Serial.println();

  doAddtitionTest(i, d, f);                                         // Adding integers, doubles and floats together
  doSubstractionTests(i, d, f);                                     // Substracting integers, doubles and floats
  doMultiplicationTest(i, d, f);                                    // Multiplying integers, doubles and floats
  doDivisionTests(i, d, f);                                         // Dividing integers, doubles and floats
}

/*
 * Does some addition stuff and prints it out.
 * Arduino actually has no issue with additions
 * 
 * @param i - integer value
 * @param d - double value
 * @param f - float value
 */
void doAddtitionTest(int i, double d, float f) {
  int iRes = i + d + f;
  double dRes = i + d + f;
  float fRes = i + d + f;
  printNumberValues("Addition", iRes, dRes, fRes);
}

/*
 * Does some substraction stuff and prints it out.
 * Arduino may or may not have issues here
 * 
 * First results are gotten by substracting all values
 * Second results are gotten by substracting all values from 500 (gives a bit different result)
 * 
 * @param i - integer value
 * @param d - double value
 * @param f - float value
 */
void doSubstractionTests(int i, double d, float f) {
  int iRes = i - d - f;
  double dRes = i - d - f;
  float fRes = i - d - f;
  printNumberValues("Substraction", iRes, dRes, fRes);

  iRes = 500 - i - d - f;
  dRes = 500 - i - d - f;
  fRes = 500 - i - d - f;
  printNumberValues("Substraction(2)", iRes, dRes, fRes);
}

/*
 * Does some multiplication stuff and prints it out
 * Arduino mostly has no issues with multiplication, unless trying to multipli large signed integers for example
 * 
 * @param i - integer value
 * @param d - double value
 * @param f - float value
 */
void doMultiplicationTest(int i, double d, float f) {
  int iRes = i * d * f;
  double dRes = i * d * f;
  float fRes = i * d * f;
  printNumberValues("Multiplication", iRes, dRes, fRes);
}

/*
 * Does some division testes
 * Arduino may or may not have issues here
 * 
 * First results are gotten by dividing all values
 * Second results are gotten by dividing all values from 500 (gives a bit different result)
 * 
 * @param i - integer value
 * @param d - double value
 * @param f - float value
 */
void doDivisionTests(int i, double d, float f) {
  int iRes = i / d / f;
  double dRes = i / d / f;
  float fRes = i / d / f;
  printNumberValues("Division", iRes, dRes, fRes);

  iRes = 500 / i / d / f;
  dRes = 500 / i / d / f;
  fRes = 500 / i / d / f;
  printNumberValues("Division (2)", iRes, dRes, fRes);
}

/*
 * Prints out given values.
 * 
 * @param operation - Shows which operation reslutls are printed out
 * @param iRes - Integer operation result
 * @param dRes - Double operation result
 * @param fRes - Float operation result
 */
void printNumberValues(String operation, int iRes, double dRes, float fRes) {
  Serial.print(operation + " as integers: ");
  Serial.println(iRes);
  Serial.print(operation + " as double: ");
  Serial.println(dRes, 5);
  Serial.print(operation + " as float: ");
  Serial.println(fRes, 5);
  Serial.println();
}

/*
 * This time, we don't do anything in loop method
 */
void loop() {}
