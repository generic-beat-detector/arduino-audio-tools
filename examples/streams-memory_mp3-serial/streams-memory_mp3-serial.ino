/**
 * @file stream-memory_mp3-serial.ino
 * @author Phil Schatzmann
 * @brief decode MP3 stream
 * @version 0.1
 * @date 2021-01-24
 * 
 * @copyright Copyright (c) 2021
 
 */
#include "AudioTools.h"
#include "BabyElephantWalk60_mp3.h"

using namespace audio_tools;  

// MemoryStream -> AudioOutputStream -> MP3Decoder -> CsvStream
MemoryStream mp3(BabyElephantWalk60_mp3, BabyElephantWalk60_mp3_len);
CsvStream<int16_t> printer(Serial, 1);  // ASCII stream 
MP3DecoderMini decoder(printer);    // decode wav to pcm and send it to printer
AudioOutputStream out(decoder); // output to decoder
StreamCopy copier(out, mp3);    // copy in to out

void setup(){
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Debug);  
  // this is not really necessary
  decoder.begin();
}

void loop(){
  if (mp3) {
    copier.copy();
  } else {
    auto info = decoder.audioInfo();
    LOGI("The audio rate from the mp3 file is %d", info.sample_rate);
    LOGI("The channels from the mp3 file is %d", info.channels);
    stop();
  }
}