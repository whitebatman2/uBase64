/*
Copyright (C) 2018 Milosz Kolenderski

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.
*/
#include "base64.h"

const char base64_tab [] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static char base64_decode_tab[256] = {0};

//Create Base64 decoding table
void base64_init(void)
{
	int i;
	for (i = 0; i < 64; ++i)
	{
		base64_decode_tab[base64_tab[i]] = i;
	}
}

//Encode data using Base64
void base64_encode(char * in, char * out, int len)
{
	int out_len = 4 * ((len + 2) / 3);
	int out_pos = 0;

	int i;
	for (i = 0; i < len; i += 3)
	{
		char octet_a = in[i];
		char octet_b = (i + 1 < len) ? in[i + 1] : 0;
		char octet_c = (i + 2 < len) ? in[i + 2] : 0;

		out[out_pos] = base64_tab[octet_a >> 2];
		out[out_pos + 1] = base64_tab[((octet_a << 4) | (octet_b >> 4)) & 0x3F];
		out[out_pos + 2] = base64_tab[((octet_b << 2)  | (octet_c >> 6)) & 0x3F];
		out[out_pos + 3] = base64_tab[octet_c & 0x3F];

		out_pos += 4;
	}

	if (len % 3 != 0)
	{
		for (i = 0; i < 3 - (len % 3); ++i)
		{
			out[out_len - i - 1] = '=';
		}
	}
}

//Decode Base64 to raw data
int base64_decode(char * in, char * out, int len)
{
	if (len % 4 != 0)
		return -1;

	//Position in output string
	int out_pos = 0;

	int i;
	for (i = 0; i < len; i += 4)
	{
		char sextet_a = in[i] == '=' ? 0 : base64_decode_tab[in[i]];
		char sextet_b = in[i + 1] == '=' ? 0 : base64_decode_tab[in[i + 1]];
		char sextet_c = in[i + 2] == '=' ? 0 : base64_decode_tab[in[i + 2]];
		char sextet_d = in[i + 3] == '=' ? 0 : base64_decode_tab[in[i + 3]];

		out[out_pos] = (sextet_a << 2) | (sextet_b >> 4);
		out[out_pos + 1] = (sextet_b << 4) | (sextet_c >> 2);
		out[out_pos + 2] = (sextet_c << 6) | sextet_d;

		out_pos += 3;
	}

	return 0;
}
