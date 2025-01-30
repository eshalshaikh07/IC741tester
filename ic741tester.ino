// Define pins
const int outputPin = A1; // IC741 output pin
const int testPin = A0;   // Test voltage applied internally

void setup() {
  Serial.begin(9600);
  Serial.println("IC741 Op-Amp Tester");
  Serial.println("Type '1' - Inverting Amplifier Test");
  Serial.println("Type '2' - Non-Inverting Amplifier Test");
  Serial.println("Type '3' - Voltage Follower Test");
}

void loop() {
  if (Serial.available() > 0) {
    char mode = Serial.read();

    if (mode == '1') {
      Serial.println("\nSelected Mode: Inverting Amplifier");
      displayInvertingConnections();
    } 
    else if (mode == '2') {
      Serial.println("\nSelected Mode: Non-Inverting Amplifier");
      displayNonInvertingConnections();
    } 
    else if (mode == '3') {
      Serial.println("\nSelected Mode: Voltage Follower");
      displayVoltageFollowerConnections();
    } 
    else {
      Serial.println("\nInvalid selection! Enter 1, 2, or 3.");
    }
  }
}

// Function to display Inverting Amplifier connections
void displayInvertingConnections() {
  Serial.println("Connect:");
  Serial.println("- A0 to IC741 Pin 2 (-)");
  Serial.println("- 10kΩ from A0 to IC741 Pin 2 (-)");
  Serial.println("- 1kΩ from IC741 Pin 6 (Output) to Pin 2 (-)");
  Serial.println("- IC741 Pin 3 (+) to GND");
  Serial.println("\nAfter connecting, type 'Y' to continue.");
  waitForConfirmation();
  testInvertingAmplifier();
}

// Function to display Non-Inverting Amplifier connections
void displayNonInvertingConnections() {
  Serial.println("Connect:");
  Serial.println("- A0 to IC741 Pin 3 (+)");
  Serial.println("- 1kΩ from A0 to IC741 Pin 3 (+)");
  Serial.println("- 10kΩ from IC741 Pin 6 (Output) to Pin 2 (-)");
  Serial.println("- 1kΩ from IC741 Pin 2 (-) to GND");
  Serial.println("\nAfter connecting, type 'Y' to continue.");
  waitForConfirmation();
  testNonInvertingAmplifier();
}

// Function to display Voltage Follower connections
void displayVoltageFollowerConnections() {
  Serial.println("Connect:");
  Serial.println("- A0 to IC741 Pin 3 (+)");
  Serial.println("- 10kΩ from A0 to IC741 Pin 3 (+)");
  Serial.println("- 1kΩ from IC741 Pin 6 (Output) to Pin 2 (-)");
  Serial.println("- 10kΩ from IC741 Pin 3 (+) to GND");
  Serial.println("\nAfter connecting, type 'Y' to continue.");
  waitForConfirmation();
  testVoltageFollower();
}

// Function to wait for user confirmation
void waitForConfirmation() {
  while (true) {
    if (Serial.available() > 0) {
      char confirm = Serial.read();
      if (confirm == 'Y' || confirm == 'y') {
        Serial.println("Testing now...");
        break;
      } else {
        Serial.println("Type 'Y' after completing the connections.");
      }
    }
  }
}

// Function to test Inverting Amplifier
void testInvertingAmplifier() {
  analogWrite(testPin, 128); // Generate 2.5V internally
  delay(100);
  
  float voltageOut = analogRead(outputPin) * (5.0 / 1023.0);
  Serial.print("Output Voltage: ");
  Serial.print(voltageOut);
  
  if (voltageOut < 2.0) {
    Serial.println(" --> GOOD IC (Inverting Mode)");
  } else {
    Serial.println(" --> BAD IC (Inverting Mode)");
  }
}

// Function to test Non-Inverting Amplifier
void testNonInvertingAmplifier() {
  analogWrite(testPin, 128); // Generate 2.5V internally
  delay(100);

  float voltageOut = analogRead(outputPin) * (5.0 / 1023.0);
  Serial.print("Output Voltage: ");
  Serial.print(voltageOut);

  if (voltageOut > 2.5) {
    Serial.println(" --> GOOD IC (Non-Inverting Mode)");
  } else {
    Serial.println(" --> BAD IC (Non-Inverting Mode)");
  }
}

// Function to test Voltage Follower
void testVoltageFollower() {
  analogWrite(testPin, 128); // Generate 2.5V internally
  delay(100);

  float voltageOut = analogRead(outputPin) * (5.0 / 1023.0);
  Serial.print("Output Voltage: ");
  Serial.print(voltageOut);

  if (abs(voltageOut - 2.5) < 0.2) {
    Serial.println(" --> GOOD IC (Voltage Follower)");
  } else {
    Serial.println(" --> BAD IC (Voltage Follower)");
  }
}
