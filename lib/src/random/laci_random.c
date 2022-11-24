/**
 * Copyright or © or Copr. CEA Leti : contributor(s) : Antoine Loiseau (23/11/2022)
 * 
 * antoine.loiseau@cea.fr
 * 
 * This software is a computer program whose purpose is to provide
 * an optimized implementation of HQC-128 for embedded systems with
 * assembly optimisation for ARMv7.
 *
 * This software is governed by the CeCILL license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info". 
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability. 
 *
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security. 
 *
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL license and that you accept its terms.
 *
 * This work is supported by the French National Research Agency in the framework 
 * of the “Programme d’Investissement d’Avenir IRT Nanoelec” (ANR-10-AIRT-05).
 */

#include "laci.h"

#ifdef LACI_LINUX_RAND
#include <sys/random.h>
#endif /* LACI_LINUX_RAND */

#ifdef LACI_STM32_RAND
#ifdef STM32U585xx
#include "stm32u5xx_hal.h"
RNG_HandleTypeDef hrng;
#endif
#ifdef STM32F407xx
#include "stm32f4xx_hal.h"
RNG_HandleTypeDef hrng;
#endif
#endif

static uint8_t laci_get_rand_uint8(void)
{
#ifdef LACI_LINUX_RAND
    uint8_t rand[1] = {0};
    int result;

    result = getentropy(rand, 1);
    if (result < 0)
    {
        printf("Error in random generator\n");
        return (uint8_t ) 0;
    }

    return rand[0];
#elif defined(LACI_STM32_RAND)
#ifdef STM32U585xx
    laci_word_t tmp_rng;
#endif
    hrng.Instance = RNG;

#ifdef STM32F407xx
    return 0xFF & HAL_RNG_GetRandomNumber(&hrng);
#endif

#ifdef STM32U585xx
    HAL_RNG_GenerateRandomNumber(&hrng, &tmp_rng);
    return 0xFF & tmp_rng;
#endif

#else
    /* MUST be implemented */
    return (uint8_t ) 0;
#endif  
}


static uint16_t laci_get_rand_uint16(void)
{
#ifdef LACI_LINUX_RAND
    uint8_t rand[2] = {0, 0};
    int result;

    result = getentropy(rand, 2);
    if (result < 0)
    {
        printf("Error in random generator\n");
        return (uint16_t ) 0;
    }

    return (rand[1] << 8) | rand[0];
#elif defined(LACI_STM32_RAND)
#ifdef STM32U585xx
    laci_word_t tmp_rng;
#endif
    hrng.Instance = RNG;

#ifdef STM32F407xx
    return 0xFFFF & HAL_RNG_GetRandomNumber(&hrng);
#endif

#ifdef STM32U585xx
    HAL_RNG_GenerateRandomNumber(&hrng, &tmp_rng);
    return 0xFFFF & tmp_rng;
#endif
#else
    /* MUST be implemented */
    return (uint16_t ) 0;
#endif  
}


static uint32_t laci_get_rand_uint32(void)
{
#ifdef LACI_LINUX_RAND
    uint8_t rand[4] = {0, 0, 0, 0};
    int result;

    result = getentropy(rand, 4);
    if (result < 0)
    {
        printf("Error in random generator\n");
        return (uint32_t ) 0;
    }

    return (rand[3] << 24) | (rand[2] << 16) | (rand[1] << 8) | rand[0];
#elif defined(LACI_STM32_RAND)
#ifdef STM32U585xx
    laci_word_t tmp_rng;
#endif
    hrng.Instance = RNG;

#ifdef STM32F407xx
    return HAL_RNG_GetRandomNumber(&hrng);
#endif

#ifdef STM32U585xx
    HAL_RNG_GenerateRandomNumber(&hrng, &tmp_rng);
    return 0xFFFF & tmp_rng;
#endif
#else
    /* MUST be implemented */
    return (uint32_t ) 0;
#endif  
}


static uint64_t laci_get_rand_uint64(void)
{
    /* Must be implemented ! */
    return (uint64_t ) 0;
}


laci_byte_t laci_get_rand_byte(void)
{
    return laci_get_rand_uint8();
}


laci_hword_t laci_get_rand_hword(void)
{
#if LACI_WORD_BIT_LENGTH==32
    return laci_get_rand_uint16();
#else
    /* Must be implemented ! */
    return 0;
#endif
}


laci_word_t laci_get_rand_word(void)
{
#if LACI_WORD_BIT_LENGTH==32
    return laci_get_rand_uint32();
#else
    /* Must be implemented ! */
    return 0;
#endif
}


laci_dword_t laci_get_rand_dword(void)
{
#if LACI_WORD_BIT_LENGTH==32
    return laci_get_rand_uint64();
#else
    /* Must be implemented ! */
    return 0;
#endif
}

void laci_get_rand_bytes(laci_byte_t * const buffer, laci_word_t size)
{
	laci_word_t i;

	for (i = 0; i < size; i++)
	{
		buffer[i] = laci_get_rand_uint8();
	}
}


