//
// Created by wangzhanzhi on 2020/10/10.
//

#include "image_file_reader.h"

const int MAJOR_VERSION = 1;
const int MINOR_VERSION = 0;
const int HEADER_SLOTS = 7;

int header_size();
int redirect_size(ImageHeader header);
int offset_size(ImageHeader header);
int redirect_offset();
int offset_offset(ImageHeader header);
int location_size(ImageHeader header);
int location_offset(ImageHeader header);
int string_size(ImageHeader header);
int index_size(ImageHeader header);
void inc_use(ImageFile *image);

HashMap *image_pool = NULL;

ImageFile* read_image(char *image_path)
{

    FILE *fp = fopen(image_path, "rb");
    fseek(fp, 0, SEEK_END);
    long f_size = ftell(fp);
    u1* bytes = (u1*) malloc(f_size * sizeof(char));
    rewind(fp);
    fread(bytes, f_size, 1, fp);
    fclose(fp);

    ImageFile *image = malloc(sizeof(ImageFile));
    image->name = image_path;
    image->_file_size = f_size;
    image->_index_data = bytes;
    memcpy(&image->header, bytes, sizeof(ImageHeader));
//    image->header.magic = *(u4*)bytes;
//    bytes += sizeof(u4);
//    image->header.version = *(u4*)bytes;
//    bytes += sizeof(u4);
//    image->header.flags = *(u4*)bytes;
//    bytes += sizeof(u4);
//    image->header.res_count = *(u4*)bytes;
//    bytes += sizeof(u4);
//    image->header.table_length = *(u4*)bytes;
//    bytes += sizeof(u4);
//    image->header.location_size = *(u4*)bytes;
//    bytes += sizeof(u4);
//    image->header.string_size = *(u4*)bytes;
//    bytes += sizeof(u4);
//    image->header.major_version = (version >> 16);
//    image->header.minor_version = (version & 0xffff);
    image->_index_size = index_size(image->header);
    if (image->_file_size < image->_index_size) {
        return NULL;
    }
    u4 length = image->header.table_length;
    u4 redirect_table_offset = header_size();
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

int header_size()
{
    return HEADER_SLOTS * 4;
}

int redirect_size(ImageHeader header)
{
    return header.table_length * 4;
}

int offset_size(ImageHeader header)
{
    return header.table_length * 4;
}

int redirect_offset()
{
    return header_size();
}

int offset_offset(ImageHeader header)
{
    return redirect_offset() + redirect_size(header);
}

int location_size(ImageHeader header)
{
    return header.location_size;
}

int location_offset(ImageHeader header)
{
    return offset_offset(header) + offset_size(header);
}

int string_size(ImageHeader header)
{
    return header.string_size;
}

int index_size(ImageHeader header)
{
    return sizeof(ImageHeader) + header.table_length * sizeof(u4) * 2 + location_size(header) + string_size(header);
//    return header_size() + redirect_size(header) + offset_size(header) + location_size(header) + string_size(header);
}

void inc_use(ImageFile *image)
{
    image->_use++;
}