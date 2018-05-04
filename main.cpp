#include <iostream>
#include "/home/racso/Descargas/SDL2-2.0.8/include/SDL.h"

int main() {
    //bool ReadMP3ToBuffer(char* filename);
    bool success = false;
    const Uint32 Mp3ChunkLen = 4096;
    SDL_AudioSpec mp3Specs;

    SMPEG* mp3;
    SMPEG_Info infoMP3;
    Uint8 * ChunkBuffer;
    Uint32 MP3Length = 0;

// Allocate a chunk buffer
    ChunkBuffer = (Uint8*)malloc(Mp3ChunkLen);
    memset(ChunkBuffer, 0, Mp3ChunkLen);

    SDL_RWops *mp3File = SDL_RWFromFile(filename, "rb"); // filename is a char* passed to the function.
    if (mp3File != NULL)
    {
        mp3 = SMPEG_new_rwops(mp3File, &infoMP3, 0, 1);

        if(mp3 != NULL)
        {
            if(infoMP3.has_audio)
            {
                Uint32 readLen;

                // Get the MP3 audio specs for later conversion
                SMPEG_wantedSpec(mp3, &mp3Specs);

                SMPEG_enablevideo(mp3, 0);

                // Play the MP3 once to get the size of the needed buffer in relation with the audio specs
                SMPEG_play(mp3);
                while ((readLen = SMPEG_playAudio(mp3, ChunkBuffer, Mp3ChunkLen)) > 0)
                {
                    MP3Length += readLen;
                }
                SMPEG_stop(mp3);

                if(MP3Length > 0)
                {
                    // Reallocate the buffer with the new length (if needed)
                    if (MP3Length != Mp3ChunkLen)
                    {
                        ChunkBuffer = (Uint8*)realloc(ChunkBuffer, MP3Length);
                        memset(ChunkBuffer, 0, MP3Length);
                    }

                    // Replay the entire MP3 into the new ChunkBuffer.
                    SMPEG_rewind(mp3);
                    SMPEG_play(mp3);

                    bool readBackSuccess = (MP3Length == SMPEG_playAudio(mp3, ChunkBuffer, MP3Length));
                    SMPEG_stop(mp3);
                    if(readBackSuccess)
                    {
                        SDL_AudioCVT convertedSound;
                        // NOTE : static SDL_AudioSpec asDeviceSpecs; containing valid values after a call to SDL_OpenAudioDevice
                        if(SDL_BuildAudioCVT(&convertedSound, mp3Specs.format, mp3Specs.channels, mp3Specs.freq, asDeviceSpecs.format, asDeviceSpecs.channels, asDeviceSpecs.freq) >= 0)
                        {
                            Uint32 newBufferLen = MP3Length*convertedSound.len_mult;

                            // Make sure the audio length is a multiple of a sample size to avoid sound clicking
                            int sampleSize = ((asDeviceSpecs.format & 0xFF)/8)*asDeviceSpecs.channels;
                            newBufferLen &= ~(sampleSize-1);

                            // Allocate the new buffer and proceed with the actual conversion.
                            convertedSound.buf = (Uint8*)malloc(newBufferLen);
                            memcpy(convertedSound.buf, ChunkBuffer, MP3Length);

                            convertedSound.len = MP3Length;
                            if(SDL_ConvertAudio(&convertedSound) == 0)
                            {
                                // Save convertedSound.buf and convertedSound.len_cvt for future use in your mixer code.
                                // Dont forget to free convertedSound.buf once it's not used anymore.
                                success = true;
                            }
                        }
                    }
                }
            }
            SMPEG_delete(mp3);
            mp3 = NULL;
        }
        SDL_RWclose(mp3File);
        mp3File = NULL;
    }

    free(ChunkBuffer);

    return success;
}
