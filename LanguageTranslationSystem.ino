// Language Translation System by Arduino UNO

// Define maximum word length
#define MAX_WORD_LENGTH 20
#define MAX_INPUT_LENGTH 100

// Dictionary structure: [Original Word, Translated Word]
const char* dictionary[][2] = {
  {"hello", "hola"},         // English to Spanish
  {"world", "mundo"},
  {"good", "bueno"},
  {"morning", "mañana"},
  {"night", "noche"},
  {"friend", "amigo"},
  {"thank", "gracias"},
  {"you", "tú"},
  {"yes", "sí"},
  {"no", "no"},
  {"please", "por favor"},
  {"welcome", "bienvenido"},
  {"food", "comida"},
  {"water", "agua"},
  {"house", "casa"},
  {"computer", "computadora"},
  {"language", "idioma"},
  {"translate", "traducir"},
  {"system", "sistema"}
};

// Total number of dictionary entries
int dictionarySize = sizeof(dictionary) / sizeof(dictionary[0]);

// Buffer to hold input from the user
char inputText[MAX_INPUT_LENGTH];

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  Serial.println("Language Translation System");
  Serial.println("Please enter a word or sentence in English:");
  Serial.println(inputText);
}

void loop() {
  // Check if user input is available
  if (Serial.available() > 0) {
    // Read the input
    readInput();
    
    // Translate and display the output
    translateText(inputText);
  }
}

// Function to read the input from the user
void readInput() {
  int index = 0;
  while (Serial.available() > 0 && index < MAX_INPUT_LENGTH - 1) {
    char c = Serial.read();
    inputText[index] = c;
    index++;
    delay(5);  // Small delay for proper reading
  }
  inputText[index] = '\0';  // Null terminate the string
}

// Function to translate input text based on dictionary
void translateText(char* input) {
  char word[MAX_WORD_LENGTH];
  int wordIndex = 0;
  
  Serial.print("Translated Text: ");
  
  // Loop through the input string character by character
  for (int i = 0; input[i] != '\0'; i++) {
    // If we encounter a space or end of sentence, translate the word
    if (input[i] == ' ' || input[i] == '\n') {
      word[wordIndex] = '\0';  // Null terminate the word
      printTranslation(word);
      Serial.print(' ');  // Print a space after the word
      wordIndex = 0;  // Reset word index for the next word
    } else {
      // Build the word character by character
      word[wordIndex] = input[i];
      wordIndex++;
    }
  }
  
  // Translate and print the last word (if any)
  if (wordIndex > 0) {
    word[wordIndex] = '\0';
    printTranslation(word);
  }
  
  Serial.println();  // Move to the next line after translation
}

// Function to print the translated word
void printTranslation(char* word) {
  bool found = false;
  
  
  
  // Search for the word in the dictionary
  for (int i = 0; i < dictionarySize; i++) {
    if (strcmp(word, dictionary[i][0]) == 0) {
      // If found, print the translated word
      Serial.print(dictionary[i][1]);
      found = true;
      break;
    }
  }
  
  // If not found, print the original word
  if (!found) {
    Serial.print(word);
  }
}
