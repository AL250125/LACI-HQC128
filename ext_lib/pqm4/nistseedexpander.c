//
//  rng.c
//
//  Created by Bassham, Lawrence E (Fed) on 8/29/17.
//  Copyright © 2017 Bassham, Lawrence E (Fed). All rights reserved.
//  Modified for PQClean by Sebastian Verschoor
//

#include "nistseedexpander.h"
#include "aes.h"
#include <string.h>

#if defined(STM32U585xx) && defined(STM32_HW_AES)
#include "stm32u5xx_hal.h"
extern CRYP_HandleTypeDef hcryp;
#endif

/*
 seedexpander_init()
 ctx            - stores the current state of an instance of the seed expander
 seed           - a 32 byte random value
 diversifier    - an 8 byte diversifier
 maxlen         - maximum number of bytes (less than 2**32) generated under this seed and diversifier
 */
int
seedexpander_init(AES_XOF_struct *ctx,
                  const uint8_t *seed,
                  const uint8_t *diversifier,
                  size_t maxlen)
{
    ctx->length_remaining = maxlen;

    memcpy(ctx->key, seed, 32);
    memcpy(ctx->ctr, diversifier, 8);

    ctx->ctr[11] = maxlen % 256;
    maxlen >>= 8;
    ctx->ctr[10] = maxlen % 256;
    maxlen >>= 8;
    ctx->ctr[9] = maxlen % 256;
    maxlen >>= 8;
    ctx->ctr[8] = maxlen % 256;
    memset(ctx->ctr+12, 0x00, 4);

    ctx->buffer_pos = 16;
    memset(ctx->buffer, 0x00, 16);

    return RNG_SUCCESS;
}

#if !defined(STM32U585xx) || !defined(STM32_HW_AES)
static void AES256_ECB(uint8_t *key, uint8_t *ctr, uint8_t *buffer) {
    aes256ctx ctx;
    aes256_ecb_keyexp(&ctx, key);
    aes256_ecb(buffer, ctr, 1, &ctx);
    aes256_ctx_release(&ctx);
}
#endif

/*
 seedexpander()
    ctx  - stores the current state of an instance of the seed expander
    x    - returns the XOF data
    xlen - number of bytes to return
 */
int
seedexpander(AES_XOF_struct *ctx, uint8_t *x, size_t xlen)
{
    size_t offset;
#if defined(STM32U585xx) && defined(STM32_HW_AES)
    uint32_t tmp_key[8];
#endif

    if ( x == NULL ) {
        return RNG_BAD_OUTBUF;
    }
    if ( xlen >= ctx->length_remaining ) {
        return RNG_BAD_REQ_LEN;
    }

    ctx->length_remaining -= xlen;

    offset = 0;
    while ( xlen > 0 ) {
        if ( xlen <= (16-ctx->buffer_pos) ) { // buffer has what we need
            memcpy(x+offset, ctx->buffer+ctx->buffer_pos, xlen);
            ctx->buffer_pos += xlen;

            return RNG_SUCCESS;
        }

        // take what's in the buffer
        memcpy(x+offset, ctx->buffer+ctx->buffer_pos, 16-ctx->buffer_pos);
        xlen -= 16-ctx->buffer_pos;
        offset += 16-ctx->buffer_pos;

#if defined(STM32U585xx) && defined(STM32_HW_AES)
        tmp_key[0] = (ctx->key[0] << 24) | (ctx->key[1] << 16) | (ctx->key[2] << 8) | ctx->key[3];
        tmp_key[1] = (ctx->key[4] << 24) | (ctx->key[5] << 16) | (ctx->key[6] << 8) | ctx->key[7];
        tmp_key[2] = (ctx->key[8] << 24) | (ctx->key[9] << 16) | (ctx->key[10] << 8) | ctx->key[11];
        tmp_key[3] = (ctx->key[12] << 24) | (ctx->key[13] << 16) | (ctx->key[14] << 8) | ctx->key[15];
        tmp_key[4] = (ctx->key[16] << 24) | (ctx->key[17] << 16) | (ctx->key[18] << 8) | ctx->key[19];
        tmp_key[5] = (ctx->key[20] << 24) | (ctx->key[21] << 16) | (ctx->key[22] << 8) | ctx->key[23];
        tmp_key[6] = (ctx->key[24] << 24) | (ctx->key[25] << 16) | (ctx->key[26] << 8) | ctx->key[27];
        tmp_key[7] = (ctx->key[28] << 24) | (ctx->key[29] << 16) | (ctx->key[30] << 8) | ctx->key[31];

        hcryp.Init.pKey = tmp_key;

        HAL_CRYP_Encrypt(&hcryp, (uint32_t *) ctx->ctr, 16, (uint32_t *) (ctx->buffer), 0xFFFFFF);
#else
        AES256_ECB(ctx->key, ctx->ctr, ctx->buffer);
#endif
        ctx->buffer_pos = 0;

        //increment the counter
        for (size_t i=15; i>=12; i--) {
            if ( ctx->ctr[i] == 0xff ) {
                ctx->ctr[i] = 0x00;
            } else {
                ctx->ctr[i]++;
                break;
            }
        }

    }

    return RNG_SUCCESS;
}
