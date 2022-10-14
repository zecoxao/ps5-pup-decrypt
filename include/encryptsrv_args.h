#ifndef __ENCRYPTSERVICEARGS_H__
#define __ENCRYPTSERVICEARGS_H__

typedef struct _verify_blsheader_args
{
  void* buffer; //rbx (rsi)
  unsigned long length; //r14 (rdx)
  unsigned long unknown; //rax
}
verify_blsheader_args;

typedef struct _decrypt_header_args
{
  void* buffer;
  size_t length;
  int type;
}
decrypt_header_args;


typedef struct _verify_segment_args
{
  unsigned short index;
  void* buffer;
  size_t length;
}
verify_segment_args;

typedef struct _decrypt_segment_args
{
  unsigned short index;
  void* buffer;
  size_t length;
}
decrypt_segment_args;

typedef struct _decrypt_segment_block_args
{
  unsigned short entry_index;
  unsigned short block_index;
  void* block_buffer;
  size_t block_length;
  void* table_buffer;
  size_t table_length;
}
decrypt_segment_block_args;

#endif
