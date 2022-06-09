// Based on the May 4, 2022 version of https://github.com/Cyan4973/xxHash/blob/dev/xxhash.h
// Simplified to just what I need and done in my much superior, simpler and cleaner style

typedef struct
{
	uint64_t total_len;	// Total length hashed
	uint64_t v[4];		// Accumulator lanes
	uint8_t buf[32];	// Internal buffer for partial reads
	uint32_t bufsize;	// Amount of data in buf
} XXH64_state_t;

#define XXH_PRIME64_1	0x9E3779B185EBCA87ULL
#define XXH_PRIME64_2	0xC2B2AE3D27D4EB4FULL
#define XXH_PRIME64_3	0x165667B19E3779F9ULL
#define XXH_PRIME64_4	0x85EBCA77C2B2AE63ULL
#define XXH_PRIME64_5	0x27D4EB2F165667C5ULL

#define XXH_rotl64(x,r) (((x) << (r)) | ((x) >> (64 - (r))))

uint64_t XXH64_round(uint64_t acc, uint64_t input)
{
	acc += input * XXH_PRIME64_2;
	return XXH_rotl64(acc, 31) * XXH_PRIME64_1;
}

uint64_t XXH64_mergeRound(uint64_t acc, uint64_t val)
{
	val = XXH64_round(0, val);
	acc ^= val;
	return acc * XXH_PRIME64_1 + XXH_PRIME64_4;
}

uint64_t XXH64_avalanche(uint64_t hash)
{
	hash ^= hash >> 33;
	hash *= XXH_PRIME64_2;
	hash ^= hash >> 29;
	hash *= XXH_PRIME64_3;
	hash ^= hash >> 32;
	return hash;
}

uint64_t XXH64_finalise(uint64_t hash, const uint8_t *ptr, size_t len)
{
	len &= 31;

	while (len >= 8)
	{
		hash ^= XXH64_round(0, read_LE64(ptr, (size_t *) &ptr));
		hash = XXH_rotl64(hash, 27) * XXH_PRIME64_1 + XXH_PRIME64_4;
		len -= 8;
	}

	if (len >= 4)
	{
		hash ^= (uint64_t) read_LE32(ptr, (size_t *) &ptr) * XXH_PRIME64_1;
		hash = XXH_rotl64(hash, 23) * XXH_PRIME64_2 + XXH_PRIME64_3;
		len -= 4;
	}

	while (len > 0)
	{
		hash ^= (uint64_t) read_byte8(ptr, (size_t *) &ptr) * XXH_PRIME64_5;
		hash = XXH_rotl64(hash, 11) * XXH_PRIME64_1;
		len -= 1;
	}

	return XXH64_avalanche(hash);
}

void XXH64_reset(XXH64_state_t *s, uint64_t seed)
{
	memset(s, 0, sizeof(*s));

	s->v[0] = seed + XXH_PRIME64_1 + XXH_PRIME64_2;
	s->v[1] = seed + XXH_PRIME64_2;
	s->v[2] = seed + 0;
	s->v[3] = seed - XXH_PRIME64_1;
}

void XXH64_update(XXH64_state_t *s, const uint8_t *p, size_t len)
{
	size_t i=0;

	if (p == NULL)
		return;

	s->total_len += len;

	// If input isn't long enough to fill up the state buffer add to it and quit
	if (s->bufsize + len < 32)
	{
		memcpy(&s->buf[s->bufsize], p, len);
		s->bufsize += len;
		return;
	}

	// Add to the state buffer if it already contains anything and hash it
	if (s->bufsize)
	{
		memcpy(&s->buf[s->bufsize], &p[i], 32-s->bufsize);
		s->v[0] = XXH64_round(s->v[0], read_LE64(&s->buf[0], NULL));
		s->v[1] = XXH64_round(s->v[1], read_LE64(&s->buf[8], NULL));
		s->v[2] = XXH64_round(s->v[2], read_LE64(&s->buf[16], NULL));
		s->v[3] = XXH64_round(s->v[3], read_LE64(&s->buf[24], NULL));
		i += 32 - s->bufsize;
		s->bufsize = 0;
	}

	// Directly hash 32-byte blocks from the input
	while (i <= len - 32)
	{
		s->v[0] = XXH64_round(s->v[0], read_LE64(&p[i], &i));
		s->v[1] = XXH64_round(s->v[1], read_LE64(&p[i], &i));
		s->v[2] = XXH64_round(s->v[2], read_LE64(&p[i], &i));
		s->v[3] = XXH64_round(s->v[3], read_LE64(&p[i], &i));
	}

	// Add whatever remains of the input to the state buffer
	if (i < len)
	{
		s->bufsize = len - i;
		memcpy(s->buf, &p[i], s->bufsize);
	}

	return;
}

uint64_t XXH64_digest(const XXH64_state_t *s)
{
	uint64_t hash;

	if (s->total_len >= 32)
	{
		hash = XXH_rotl64(s->v[0], 1) + XXH_rotl64(s->v[1], 7) + XXH_rotl64(s->v[2], 12) + XXH_rotl64(s->v[3], 18);
		hash = XXH64_mergeRound(hash, s->v[0]);
		hash = XXH64_mergeRound(hash, s->v[1]);
		hash = XXH64_mergeRound(hash, s->v[2]);
		hash = XXH64_mergeRound(hash, s->v[3]);
	}
	else
		hash = s->v[2] + XXH_PRIME64_5;

	hash += s->total_len;

	return XXH64_finalise(hash, s->buf, s->total_len);
}

uint64_t XXH64(const void *input, size_t len, uint64_t seed)
{
	XXH64_state_t s;
	XXH64_reset(&s, seed);
	XXH64_update(&s, input, len);
	return XXH64_digest(&s);
}

/*
 * xxHash - Extremely Fast Hash algorithm
 * Copyright (C) 2012-2021 Yann Collet
 *
 * BSD 2-Clause License (https://www.opensource.org/licenses/bsd-license.php)
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *    * Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following disclaimer
 *      in the documentation and/or other materials provided with the
 *      distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * You can contact the author at:
 *   - xxHash homepage: https://www.xxhash.com
 *   - xxHash source repository: https://github.com/Cyan4973/xxHash
 */
