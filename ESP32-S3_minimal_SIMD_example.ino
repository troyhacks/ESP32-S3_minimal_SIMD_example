//
// ESP32-S3 minimal SIMD example
// Written by Larry Bank
// Copyright (c) 2024 BitBank Software, Inc.
//
// The purpose of this example is to show how to make use of ESP32-S3 SIMD instructions
// in your Arduino or ESP-IDF projects. The code is not comprehensive and just provides
// a starting point for someone wanting to learn how to use them. I wrote this because
// I couldn't find such an example and thought that people would appreciate saving some
// time with the research I did.
//
// TroyHacks: Added a bit more complexity as it was a little too minimial
//

extern "C" {
  int s3_add16x8(int16_t *pA, int16_t *pB, int16_t *pC, int16_t sar);
}

// 128-bit (16-byte) loads and stores need to be 16-byte aligned
int16_t __attribute__((aligned (16))) u16_A[] = {26, 225, 38, 21, 42, 217, 140, 102, 213, 15, 196, 94, 47, 176, 165, 233, 84, 211, 115, 241, 129, 207, 117, 52, 255, 48, 244, 149, 44, 10, 134, 96, 80, 23, 206, 119, 4, 164, 242, 154, 203, 158, 142, 79, 249, 118, 19, 82, 130, 128, 192, 5, 201, 222, 200, 83, 24, 191, 41, 66, 111, 193, 220, 147, 194, 236, 37, 181, 125, 182, 124, 252, 122, 180, 169, 74, 59, 174, 20, 146, 30, 95, 110, 13, 178, 32, 195, 152, 11, 27, 145, 224, 9, 229, 109, 148, 251, 72, 153, 136, 86, 199, 92, 55, 239, 25, 1, 114, 104, 230, 198, 131, 246, 168, 76, 159, 101, 113, 250, 187, 135, 71, 34, 179, 6, 57, 18, 184};
int16_t __attribute__((aligned (16))) u16_B[8] = {64,64,64,64,128,128,128,128};
int16_t __attribute__((aligned (16))) u16_C[128] = {0};
int16_t sar = 0;

void setup() {

  Serial.begin(115200);

}

void loop() {

  delay(1000);
  
  Serial.println("About to call Asm code");
  
  s3_add16x8(u16_A, u16_B, u16_C, sar);
  
  Serial.println("Returned from Asm code");
  
  for (int i=0; i<128; i++) {
    Serial.printf("value %3d * %3d >> %d = %5d\n", u16_A[i], u16_B[i%8], sar, u16_C[i]);
  }

  sar++;

  if (sar > 8) sar = 0;

}