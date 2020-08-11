#include "jmod.h"

u1 *load_from_jmod(char *jmod_name, char *name)
{
    unsigned long size = strlen(name) + 16;
    char *full_name = malloc(size);
    memset(full_name, 0, size);
    sprintf(full_name, "classes/%s.class", name);

    zip_error_t err;
    size = strlen(JAVA_HOME) + strlen(jmod_name) + 9;
    char *file_path = malloc(size);
    memset(file_path, 0, size);
    sprintf(file_path, "%s/jmods/%s", JAVA_HOME, jmod_name);
    FILE *fp = fopen(file_path, "rb");
    if (NULL == fp) exit(-1);
    fseek(fp, 0, SEEK_END);
    long f_size = ftell(fp);
    fclose(fp);
    int offset = 4;
    zip_error_t error;
    zip_source_t *source = zip_source_file_create(file_path, offset, f_size - offset, &error);
    zip_t *z = zip_open_from_source(source, 0, &err);

    //Search for the file of given name
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(z, full_name, 0, &st);

    //Alloc memory for its uncompressed contents
    u1 *contents = malloc(st.size);

    //Read the compressed file
    zip_file_t *f = zip_fopen(z, full_name, 0);
    zip_fread(f, contents, st.size);
    zip_fclose(f);

    //And close the archive
    zip_close(z);
    free(full_name);
    free(file_path);
    return contents;
}