//
// Created by wangzhanzhi on 2020/10/10.
//

#include "image_file_reader.h"

const int MAJOR_VERSION = 1;
const int MINOR_VERSION = 0;
const int HEADER_SLOTS = 7;
int memory_map_image = sizeof(void*) == 8;

int location_size(ImageHeader header);
int string_size(ImageHeader header);
int index_size(ImageHeader header);
void inc_use(ImageFile *image);
void close_image(ImageFile *image);
u8 map_size(ImageFile *image);
void* map_image_memory(int fd, size_t offset, size_t bytes);

HashMap *image_pool = NULL;

ImageFile* read_image(char *image_path)
{

    ImageFile *image = malloc(sizeof(ImageFile));
    image->name = image_path;
    image->_fd = open(image_path, 0);
    if (image->_fd == -1) {
        free(image);
        return NULL;
    }

    struct stat statbuf;
    if (stat(image_path, &statbuf) < 0 ||
        (statbuf.st_mode & S_IFREG) != S_IFREG) {
        free(image);
        return NULL;
    }
    image->_file_size = statbuf.st_size;
    size_t header_size = sizeof(ImageHeader);
    if (image->_file_size < header_size || !(pread(image->_fd, &image->header, header_size, 0) == header_size)) {
        close_image(image);
        free(image);
        return NULL;
    }
    image->_index_size = index_size(image->header);
    if (image->_file_size < image->_index_size) {
        free(image);
        return NULL;
    }
    image->_index_data = map_image_memory(image->_fd, 0, map_size(image));
    if (!image->_index_data) {
        printf("image file not memory mapped");
        exit(-1);
    }
    u4 length = image->header.table_length;
    u4 redirect_table_offset = (u4)header_size;
    u4 offsets_table_offset = redirect_table_offset + length * (u4)sizeof(s4);
    u4 location_bytes_offset = offsets_table_offset + length * (u4)sizeof(u4);
    u4 string_bytes_offset = location_bytes_offset + location_size(image->header);

    image->_redirect_table = (s4*)(image->_index_data + redirect_table_offset);
    image->_offsets_table = (u4*)(image->_index_data + offsets_table_offset);
    image->_location_bytes = (u1*)image->_index_data + location_bytes_offset;
    image->_string_bytes = (u1*)image->_index_data + string_bytes_offset;
    put_map(&image_pool, image_path, image);
    return image;
}

ImageFile* find_image(char *name)
{
    if (NULL == image_pool) image_pool = create_map();
    ImageFile *image = get_map(&image_pool, name);
    if (NULL == image) {
        image = read_image(name);
    }
    if (NULL != image) {
        inc_use(image);
    }
    return image;
}


int location_size(ImageHeader header)
{
    return header.location_size;
}

int string_size(ImageHeader header)
{
    return header.string_size;
}

int index_size(ImageHeader header)
{
    return sizeof(ImageHeader) + header.table_length * sizeof(u4) * 2 + location_size(header) + string_size(header);
}

u8 map_size(ImageFile *image)
{
    return (u8)(memory_map_image ? image->_file_size : image->_index_size);
}

void inc_use(ImageFile *image)
{
    image->_use++;
}

void close_image(ImageFile *image)
{
    if (NULL == image) return;
    if (image->_index_data) {
        munmap((char *) image->_index_data, image->_index_size);
        image->_index_data = NULL;
    }
    if (image->_fd != -1) {
        close(image->_fd);
        image->_fd = -1;
    }
}

void* map_image_memory(int fd, size_t offset, size_t bytes)
{
    void* mapped_address = NULL;
    mapped_address = (void*) mmap(NULL,
                                  bytes, PROT_READ, MAP_SHARED,
                                  fd, offset);
    if (mapped_address == MAP_FAILED) {
        return NULL;
    }
    return mapped_address;
}