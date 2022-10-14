#include "resolve.h"
#include "assert.h"
#define CHECK_SIZE(x, y) _Static_assert(sizeof(x) == y, #x)

#include "encryptsrv_args.h"
#include "pup.h"
#include "bls.h"

//Check Bls related headers.
CHECK_SIZE(bls_header, 32);
CHECK_SIZE(bls_entry, 48);

//Check PUP related headers.
CHECK_SIZE(pup_file_header, 16);
CHECK_SIZE(pup_header, 32);
CHECK_SIZE(pup_segment, 32);
CHECK_SIZE(pup_block_info, 8);

//Check EncryptService related headers.
CHECK_SIZE(verify_blsheader_args, 24);
CHECK_SIZE(decrypt_header_args, 24);
CHECK_SIZE(verify_segment_args, 24);
CHECK_SIZE(decrypt_segment_args, 24);
CHECK_SIZE(decrypt_segment_block_args, 40);

