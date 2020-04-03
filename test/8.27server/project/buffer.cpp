/* buffer.c */
#include "buffer.h"

// 初始化缓冲区 buf，使用指定容量 capacity 申请内存空间
void buffer_init(struct Buffer *buf, size_t capacity){
    if(buf == NULL || capacity <= 0){
        errlog("Invalid argument.");
        // error
        errno = EINVAL; // // Invalid argument
        exit(EXIT_FAILURE);
    }
	// 实际分配内存
    buf -> data = (char*)malloc(capacity);
    if(buf -> data == NULL){
        errlog("Cannot allocate memory: unknown error.");
        // error
        errno = ENOMEM;
        exit(EXIT_FAILURE);
    }
    buf -> capacity = capacity;
    buf -> byte_readed_count = 0;
    buf -> byte_writed_count = 0; 
}
// 版本一，内部每次读/写一个字节，效率低
// 将指针 chars 指向的长度为 len 的数据写入缓冲区 buf，
// 返回值：实际写入的字节数，可能小于 len，当缓冲区可写空间不足时。
size_t buffer_write(struct Buffer *buf, char *chars, size_t len){
	if(buffer_available_write(buf) == 0){
	    return 0;
	}
    if(buf != NULL && chars != NULL && len > 0){
        int i = 0;
        for(;i < len && buffer_available_write(buf) > 0;i++, buf -> byte_writed_count ++){
        	// 每次写入一个字节
            (buf -> data)[buf -> byte_writed_count % buf -> capacity] = *(chars + i);
        }
        return i;
    }else{
        errlog("Invalid argument");
        // error
        errno = EINVAL;
        exit(EXIT_FAILURE);
    }
}
// 版本一，内部每次读/写一个字节，效率低
// 从缓冲区 buf 中读取长度为 len 的数据到指针 chars 指向的空间，
// 返回值：实际读取的字节数，可能小于 len，当缓冲区没有足够的数据时。
size_t buffer_read(struct Buffer *buf, char *chars, size_t len){
    if(buffer_available_read(buf) == 0){
	    return 0;
	}
    if(buf != NULL && chars != NULL && len > 0){
        int i = 0;
        for(;i < len && buffer_available_read(buf) > 0;i++, buf -> byte_readed_count ++){
        	// 每次读取一个字节
            *(chars + i) = (buf -> data)[buf -> byte_readed_count % buf -> capacity];
        }
        return i;
    }else{
        errlog("Invalid argument");
        // error
        errno = EINVAL;
        exit(EXIT_FAILURE);
    }
}
// 版本二，使用 memcpy 函数复制内存，效率高
size_t buffer_write_by_memcpy(struct Buffer *buf, char *chars, size_t len){
    if(buffer_available_write(buf) == 0){
	    return 0;
	}
    if(buf != NULL && chars != NULL && len > 0){
        //
        int avail_write_count = buffer_available_write(buf);
        int next_write_index = (buf -> byte_writed_count) % (buf -> capacity);
        int first_count = (buf -> capacity) - next_write_index;
        if(avail_write_count <= first_count){
        	// ‘可写区域’分布在写指针右侧，即：memcpy 函数最多可执行 1 次
            int write_count;
            if(avail_write_count <= len){
                write_count = avail_write_count;
            }else{
                write_count = len;
            }
            memcpy(&(buf -> data)[next_write_index], chars, write_count);
            buf -> byte_writed_count += write_count;
            return write_count;
        }else{
            // avail_write_count > first_count
            // ‘可写区域’分布在写指针两侧，即：memcpy 函数最多可执行 2 次
            if(len <= first_count){
                memcpy(&(buf -> data)[next_write_index], chars, len);
                buf -> byte_writed_count += len;
                return len;
            }else{
                // first write
                memcpy(&(buf->data)[next_write_index], chars, first_count);
                buf->byte_writed_count += first_count;
                int write_count;
                if (avail_write_count >= len){
                    write_count = len - first_count;
                }else{
                    // avail_write_count < len
                    write_count = avail_write_count - first_count;
                }
                // second write
                memcpy(&(buf->data)[0], &chars[first_count], write_count);
                buf->byte_writed_count += write_count;
                return first_count + write_count;
            }
        }
    }else{
        errlog("Invalid argument");
        // error
        errno = EINVAL;
        exit(EXIT_FAILURE);
    }
}
// 版本二，使用 memcpy 函数复制内存，效率高
size_t buffer_read_by_memcpy(struct Buffer *buf, char *chars, size_t len){
    if(buffer_available_read(buf) == 0){
	    return 0;
	}
    if(buf != NULL && chars != NULL && len > 0){
        //
        int avail_read_count = buffer_available_read(buf);
        int next_read_index = (buf -> byte_readed_count) % (buf -> capacity);
        int first_count = (buf -> capacity) - next_read_index;
        if(avail_read_count <= first_count){
        	// ‘可读区域’分布在读指针右侧，即：memcpy 函数最多可执行 1 次
            int read_count;
            if(avail_read_count <= len){
                read_count = avail_read_count;
            }else{
                read_count = len;
            }
            memcpy(chars, &(buf -> data)[next_read_index], read_count);
            buf -> byte_readed_count += read_count;
            return read_count;
        }else{
            // avail_read_count > first_count
            // ‘可读区域’分布在读指针两侧，即：memcpy 函数最多可执行 2 次
            if(len <= first_count){
                memcpy(chars, &(buf -> data)[next_read_index], len);
                buf -> byte_readed_count += len;
                return len;
            }else{
                // first write
                memcpy(chars, &(buf -> data)[next_read_index], first_count);
                buf->byte_readed_count += first_count;
                int read_count;
                if (avail_read_count >= len){
                    read_count = len - first_count;
                }else{
                    // avail_read_count < len
                    read_count = avail_read_count - first_count;
                }
                // second write
                memcpy(&chars[first_count], &(buf->data)[0], read_count);
                buf->byte_readed_count += read_count;
                return first_count + read_count;
            }
        }
    }else{
        errlog("Invalid argument");
        // error
        errno = EINVAL;
        exit(EXIT_FAILURE);
    }
}

// 返回值：缓冲区中已缓存的（可读取）字节数
size_t buffer_available_read(struct Buffer *buf){
    if(buf != NULL){
        return (buf -> byte_writed_count) - (buf -> byte_readed_count);
    }else{
        return 0;
    }
}
// 返回值：缓冲区可写入的字节数
size_t buffer_available_write(struct Buffer *buf){
    if(buf != NULL){
        return (buf -> capacity) - ((buf -> byte_writed_count) - (buf -> byte_readed_count));
    }else{
        return 0;
    }
}
// 返回值：缓冲区容量 capacity
size_t buffer_capacity(struct Buffer *buf){
    if(buf != NULL){
        return buf -> capacity;
    }else{
        return 0;
    }
}
// 清空缓冲区，实际上仅仅重置读/写指针，缓冲区容量不变
void buffer_clear(struct Buffer *buf){
    if(buf != NULL){
        buf -> byte_readed_count = 0;
        buf -> byte_writed_count = 0;
    }
}
// 销毁/释放缓冲区，free 内存资源
void buffer_destroy(struct Buffer *buf){
    if(buf != NULL){
        buf -> capacity = 0;
        free(buf -> data);
    }
}
// 简单错误日志输出
void errlog(const char *msg){
    fprintf(stderr, "error: %s\n", msg);
}
// 简单日志输出
void infolog(const char *msg){
    fprintf(stdout, "info: %s\n", msg);
}

// 只读不取
size_t buffer_only_read_by_memcpy(struct Buffer *buf, char *chars, size_t len){
    if(buffer_available_read(buf) == 0){
        return 0;
    }
    if(buf != NULL && chars != NULL && len > 0){
        //
        int avail_read_count = buffer_available_read(buf);
        int next_read_index = (buf -> byte_readed_count) % (buf -> capacity);
        int first_count = (buf -> capacity) - next_read_index;
        if(avail_read_count <= first_count){
            // ‘可读区域’分布在读指针右侧，即：memcpy 函数最多可执行 1 次
            int read_count;
            if(avail_read_count <= len){
                read_count = avail_read_count;
            }else{
                read_count = len;
            }
            memcpy(chars, &(buf -> data)[next_read_index], read_count);
            //buf -> byte_readed_count += read_count;
            return read_count;
        }else{
            // avail_read_count > first_count
            // ‘可读区域’分布在读指针两侧，即：memcpy 函数最多可执行 2 次
            if(len <= first_count){
                memcpy(chars, &(buf -> data)[next_read_index], len);
                //buf -> byte_readed_count += len;
                return len;
            }else{
                // first write
                memcpy(chars, &(buf -> data)[next_read_index], first_count);
                //buf->byte_readed_count += first_count;
                int read_count;
                if (avail_read_count >= len){
                    read_count = len - first_count;
                }else{
                    // avail_read_count < len
                    read_count = avail_read_count - first_count;
                }
                // second write
                memcpy(&chars[first_count], &(buf->data)[0], read_count);
                //buf->byte_readed_count += read_count;
                return first_count + read_count;
            }
        }
    }else{
        errlog("Invalid argument");
        // error
        errno = EINVAL;
        exit(EXIT_FAILURE);
    }
}