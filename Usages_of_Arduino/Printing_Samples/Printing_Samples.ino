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
  int i = 42;
  double d = 42.3456;
  float f = 42.565f;

  Serial.print("integer: ");
  Serial.println(i);
  Serial.print("double: ");
  Serial.println(d);
  Serial.print("float: ");
  Serial.println(f);

  Serial.print("double (all): ");
  Serial.println(d, 4);
  Serial.print("float (all): ");
  Serial.println(f, 3);
  Serial.println();

  doAddtitionTest(i, d, f);
  doSubstractionTests(i, d, f);
  doMultiplicationTest(i, d, f);
  doDivisionTests(i, d, f);
}

void doAddtitionTest(int i, double d, float f) {
  int iRes = i + d + f;
  double dRes = i + d + f;
  float fRes = i + d + f;
  printNumberValues("Addition", iRes, dRes, fRes);
}

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

void doMultiplicationTest(int i, double d, float f) {
  int iRes = i * d * f;
  double dRes = i * d * f;
  float fRes = i * d * f;
  printNumberValues("Multiplication", iRes, dRes, fRes);
}

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

void printNumberValues(String operation, int iRes, double dRes, float fRes) {
  Serial.print(operation + " as integers: ");
  Serial.println(iRes);
  Serial.print(operation + " as double: ");
  Serial.println(dRes, 5);
  Serial.print(operation + " as float: ");
  Serial.println(fRes, 5);
  Serial.println();
}

void loop() {}
