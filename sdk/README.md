# ps5-pup-decrypt for ps5-payload-sdk

Same decryption logic as the parent directory, built as a regular payload for
[ps5-payload-sdk](https://github.com/ps5-payload-dev/sdk). It can be sent to a
modern ELF loader (`ps5-payload-elfldr`, etaHEN, ...) on port 9021.

The original payload is a flat ELF that relies on the `payload_args->dlsym`
handle and on libkernel being module `0x2001`. That does not hold when started
by current loaders, so the payload exits before showing its first notification.

## What changed

* `include/resolve.h` maps the former `f_*` function pointers straight to
  libc/libkernel, so `decrypt.c`, `decryptio.c` and `encryptsrv.c` are unchanged
  (except for one `printf` argument that was missing in `decryptio.c`).
* `source/main.c` is a normal `main()`:
  * shows notifications with `sceNotificationSend`;
  * writes a log to `/mnt/usb0/pupdec.log` (and `/data/pupdec.log`) instead of a
    TCP debug server at a hard-coded address;
  * raises the process authid/caps with `kernel_set_ucred_authid` /
    `kernel_set_ucred_caps` until `/dev/pup_update0` can be opened. On the
    tested console `0x4801000000000013` worked, `0x4800000000010003` did not.

## Usage

Same as the original: put the update at `/mnt/usb0/safe.PS5UPDATE.PUP`, send the
ELF, wait for the "Complete!" notification and for `done` in `pupdec.log`.
Do not unplug the drive before that. Output: `PS5UPDATE1.PUP.dec` (and/or
`PS5UPDATE2.PUP.dec`) in the root of the drive.

Tested on firmware 13.60 with etaHEN, decrypting a 1.16 GB update in about 15
minutes. Built by calling clang/ld.lld with the same flags the SDK's
`prospero-clang` uses; `make` with the Makefile above has not been run.
