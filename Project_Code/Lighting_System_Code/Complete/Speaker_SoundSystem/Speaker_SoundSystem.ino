#define SPEAKER_PIN 9 // Example PWM pin

// Define note frequencies (Hz)
#define NOTE_B4 494
#define NOTE_D5 587
#define NOTE_E5 659
#define NOTE_G5 784

void setup() {
  pinMode(SPEAKER_PIN, OUTPUT);
}

void loop() {
  // Play the song
  playSong();
}

void playSong() {
  // Define the notes and their durations for "You're Losing Me" by Taylor Swift
  int melody[] = {NOTE_E5, NOTE_E5, NOTE_E5, 0, NOTE_D5, NOTE_E5, NOTE_G5, NOTE_G5, 0, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_D5};
  int noteDurations[] = {4, 4, 2, 2, 4, 4, 4, 4, 2, 4, 4, 4, 4};

  // Iterate through the notes and play each one
  for (int i = 0; i < 13; i++) {
    int noteDuration = 1000 / noteDurations[i];
    tone(SPEAKER_PIN, melody[i], noteDuration);

    // Pause between notes
    delay(noteDuration * 1.30);

    // Stop playing the note
    noTone(SPEAKER_PIN);
  }
}
