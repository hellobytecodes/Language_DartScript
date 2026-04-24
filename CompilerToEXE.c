/*
 * CompilerToEXE.c
 * Bundles DartScript.exe with a .drs script into a standalone executable.
 * 
 * Compile for Windows (on Termux with mingw-w64):
 * x86_64-w64-mingw32-gcc -o CompilerToEXE.exe CompilerToEXE.c
 * 
 * Usage:
 * CompilerToEXE.exe myscript.drs myprogram.exe
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input.drs> <output.exe>\n", argv[0]);
        return 1;
    }

    const char *interpreter_path = "DartScript.exe";  // باید در کنار این برنامه باشه
    const char *script_path   = argv[1];
    const char *output_path   = argv[2];

    // ۱. باز کردن فایل مفسر اصلی
    FILE *f_interp = fopen(interpreter_path, "rb");
    if (!f_interp) {
        fprintf(stderr, "Error: Cannot open %s\n", interpreter_path);
        return 1;
    }

    // ۲. باز کردن فایل اسکریپت
    FILE *f_script = fopen(script_path, "rb");
    if (!f_script) {
        fprintf(stderr, "Error: Cannot open %s\n", script_path);
        fclose(f_interp);
        return 1;
    }

    // ۳. ساخت فایل خروجی
    FILE *f_out = fopen(output_path, "wb");
    if (!f_out) {
        fprintf(stderr, "Error: Cannot create %s\n", output_path);
        fclose(f_interp);
        fclose(f_script);
        return 1;
    }

    // ۴. کپی کامل مفسر به خروجی
    int c;
    while ((c = fgetc(f_interp)) != EOF) {
        fputc(c, f_out);
    }

    // ۵. الصاق محتوای اسکریپت و محاسبهٔ اندازه
    long script_size = 0;
    while ((c = fgetc(f_script)) != EOF) {
        fputc(c, f_out);
        script_size++;
    }

    // ۶. نوشتن ۴ بایت اندازهٔ اسکریپت (unsigned int, little-endian)
    uint32_t size_le = (uint32_t)script_size;
    fwrite(&size_le, sizeof(size_le), 1, f_out);

    // ۷. بستن فایل‌ها
    fclose(f_interp);
    fclose(f_script);
    fclose(f_out);

    printf("Successfully created %s\n", output_path);
    return 0;
}