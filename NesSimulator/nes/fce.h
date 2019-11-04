#ifndef FCE_H
#define FCE_H


bool load_file(const char* filepath);
int fce_load_rom(char *rom);
void fce_init();
void run_once();
void fce_run();
void fce_update_screen();

#endif
