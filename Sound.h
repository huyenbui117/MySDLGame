#include<SDL_mixer.h>
class Sound
{
public:
	Sound() {};
	~Sound() {};
	Mix_Chunk *sound;
	Sound(const char* path) {
		sound = Mix_LoadWAV(path);
		if (sound == NULL)
		{
			printf("%s\n", Mix_GetError());
		}
	}
	void play() {
		Mix_HaltChannel(-1);
 		Mix_PlayChannel(-1, sound, 0);
	}
};
